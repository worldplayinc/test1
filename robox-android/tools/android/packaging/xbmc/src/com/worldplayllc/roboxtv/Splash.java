package com.worldplayllc.roboxtv;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.lang.System;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Iterator;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Properties;
import java.util.Enumeration;
import java.util.ArrayList;

import android.net.Uri;
import android.os.AsyncTask;
import android.os.Build;
import android.os.Bundle;
import android.app.Activity;
import android.app.ActivityManager;
import android.app.ActivityManager.RunningTaskInfo;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.util.Log;
import android.text.Html;
import android.text.method.LinkMovementMethod;
import android.view.View;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.content.res.Resources;
import android.content.res.Resources.NotFoundException;

import android.os.Handler;
import android.os.Message;
import android.content.BroadcastReceiver;
import android.content.IntentFilter;
import android.os.Environment;

public class Splash extends Activity {

  private static final int Uninitialized = 0;
  private static final int InError = 1;
  private static final int Checking = 2;
  private static final int ChecksDone = 3;
  private static final int Clearing = 4;
  private static final int Caching = 5;
  private static final int CachingDone = 6;
  private static final int WaitingStorageChecked = 7;
  private static final int StorageChecked = 8;
  private static final int DownloadingObb = 90;
  private static final int DownloadObbDone = 91;
  private static final int StartingXBMC = 99;

  private static final String TAG = "RoBoXTV";

  private String mCpuinfo = "";
  private ArrayList<String> mMounts = new ArrayList<String>();
  private String mErrorMsg = "";

  private ProgressBar mProgress = null;
  private TextView mTextView = null;

  private int mState = Uninitialized;
  public AlertDialog myAlertDialog;

  private String sPackagePath = "";
  private String sXbmcHome = "";
  private String sXbmcdata = "";
  private File fPackagePath = null;
  private File fXbmcHome = null;

  private BroadcastReceiver mExternalStorageReceiver = null;
  private boolean mExternalStorageChecked = false;
  private boolean mCachingDone = false;
  private boolean mInstallLibs = false;

  private class StateMachine extends Handler {

    private Splash mSplash = null;

    StateMachine(Splash a) {
      this.mSplash = a;
    }


    @Override
    public void handleMessage(Message msg) {
      mSplash.mState = msg.what;
      switch(mSplash.mState) {
        case InError:
          showErrorDialog(mSplash, "Error", mErrorMsg);
          break;
        case Checking:
          break;
        case Clearing:
          mSplash.mTextView.setText("Clearing cache...");
          mSplash.mProgress.setVisibility(View.INVISIBLE);
          break;
        case DownloadingObb:
          break;
        case DownloadObbDone:
          new FillCache(mSplash).execute();
          break;
        case Caching:
          break;
        case CachingDone:
          mSplash.mCachingDone = true;
          sendEmptyMessage(StartingXBMC);
          break;
        case WaitingStorageChecked:
          mSplash.mTextView.setText("Waiting for external storage...");
          mSplash.mProgress.setVisibility(View.INVISIBLE);
          break;
        case StorageChecked:
          mSplash.mTextView.setText("External storage OK...");
          mExternalStorageChecked = true;
          mSplash.stopWatchingExternalStorage();
          if (mSplash.mCachingDone)
            sendEmptyMessage(StartingXBMC);
          else {
            SetupEnvironment();
            if (mState == InError) {
              sendEmptyMessage(InError);
            }
            if (fXbmcHome.exists() && fXbmcHome.lastModified() >= fPackagePath.lastModified() && !mInstallLibs) {
              mState = CachingDone;
              mCachingDone = true;

              sendEmptyMessage(StartingXBMC);
            } else {
              new FillCache(mSplash).execute();
            }
          }

          break;
        case StartingXBMC:
          mSplash.mTextView.setText("Starting RoBoXTV...");
          mSplash.mProgress.setVisibility(View.INVISIBLE);
          mSplash.startXBMC();
          break;
        default:
          break;
      }
    }
  }
  private StateMachine mStateMachine = new StateMachine(this);

  private class DownloadObb extends AsyncTask<String, Integer, Integer>
  {
    private Splash mSplash = null;
    private int mProgressStatus = 0;

    public DownloadObb(Splash splash) {
      this.mSplash = splash;
    }

    @Override
    protected Integer doInBackground(String... sUrl) {
      InputStream input = null;
      OutputStream output = null;
      HttpURLConnection connection = null;

      String src = sUrl[0];
      String dest = sUrl[1];
      File fObb = new File(dest);

      Log.d(TAG, "Downloading " + src + " to " + dest);

      if (!fObb.getParentFile().exists() && !fObb.getParentFile().mkdirs()) {
        Log.e(TAG, "Error creating directory " + fObb.getParentFile().getAbsolutePath());
        return -1;
      }

      int ret = 0;
      try {
        URL url = new URL(src);
        connection = (HttpURLConnection) url.openConnection();
        connection.connect();

        // expect HTTP 200 OK, so we don't mistakenly save error report
        // instead of the file
        if (connection.getResponseCode() != HttpURLConnection.HTTP_OK) {
            return -1;
        }

        // this will be useful to display download percentage
        // might be -1: server did not report the length
        int fileLength = connection.getContentLength();

        // download the file
        input = connection.getInputStream();
        output = new FileOutputStream(dest);

        byte data[] = new byte[4096];
        long total = 0;
        int count;
        mProgress.setProgress(0);
        mProgress.setMax(fileLength);
        while ((count = input.read(data)) != -1) {
          // allow canceling with back button
          if (isCancelled()) {
            ret = -1;
            break;
          }
          total += count;
          // publishing the progress....
          if (fileLength > 0) // only if total length is known
            publishProgress((int) total);
          output.write(data, 0, count);
        }
      } catch (Exception e) {
        return -1;
      } finally {
        try {
          if (output != null)
            output.close();
          if (input != null)
            input.close();
        } catch (IOException ignored) {
        }

        if (connection != null)
          connection.disconnect();
      }
      if (ret == 0)
        mState = DownloadObbDone;
      else
        fObb.delete();

      publishProgress(0);
      return ret;
    }

    @Override
    protected void onProgressUpdate(Integer... values) {
      switch (mState) {
      case DownloadingObb:
        mSplash.mTextView.setText("Downloading OBB...");
        mSplash.mProgress.setVisibility(View.VISIBLE);
        mSplash.mProgress.setProgress(values[0]);
        break;
      case DownloadObbDone:
        mSplash.mProgress.setVisibility(View.INVISIBLE);
        break;
      }
    }

    @Override
    protected void onPostExecute(Integer result) {
      super.onPostExecute(result);
      if (result < 0) {
        mState = InError;
        mErrorMsg = "Cannot download obb.";
      }

      mStateMachine.sendEmptyMessage(mState);
    }
  }

  private class FillCache extends AsyncTask<Void, Integer, Integer> {

    private Splash mSplash = null;
    private int mProgressStatus = 0;

    public FillCache(Splash splash) {
      this.mSplash = splash;
    }

    void DeleteRecursive(File fileOrDirectory) {
      if (fileOrDirectory.isDirectory())
        for (File child : fileOrDirectory.listFiles())
          DeleteRecursive(child);

      fileOrDirectory.delete();
    }

    @Override
    protected Integer doInBackground(Void... param) {
      if (fXbmcHome.exists()) {
        // Remove existing files
        mStateMachine.sendEmptyMessage(Clearing);
        Log.d(TAG, "Removing existing " + fXbmcHome.toString());
        DeleteRecursive(fXbmcHome);
      }
      fXbmcHome.mkdirs();

      // Log.d(TAG, "apk: " + sPackagePath);
      // Log.d(TAG, "output: " + sXbmcHome);

      ZipFile zip;
      byte[] buf = new byte[4096];
      int n;
      try {
        zip = new ZipFile(sPackagePath);
        Enumeration<? extends ZipEntry> entries = zip.entries();
        mProgress.setProgress(0);
        mProgress.setMax(zip.size());

        mState = Caching;
        publishProgress(mProgressStatus);
        while (entries.hasMoreElements()) {
          // Update the progress bar
          publishProgress(++mProgressStatus);

          ZipEntry e = (ZipEntry) entries.nextElement();
          String sName = e.getName();

          if (! (sName.startsWith("assets/") || (mInstallLibs && sName.startsWith("lib/"))) )
            continue;
          if (sName.startsWith("assets/python2.7"))
            continue;

          String sFullPath = null;
          if (sName.startsWith("lib/"))
          {
            if (e.isDirectory())
              continue;
            sFullPath = getApplicationInfo().nativeLibraryDir + "/" + new File(sName).getName();
          }
          else
          {
            sFullPath = sXbmcHome + "/" + sName;
            File fFullPath = new File(sFullPath);
            if (e.isDirectory()) {
              fFullPath.mkdirs();
              continue;
            }
            fFullPath.getParentFile().mkdirs();
         }

          try {
            InputStream in = zip.getInputStream(e);
            BufferedOutputStream out = new BufferedOutputStream(
                new FileOutputStream(sFullPath));
            while ((n = in.read(buf, 0, 4096)) > -1)
              out.write(buf, 0, n);

            in.close();
            out.close();
          } catch (IOException e1) {
            e1.printStackTrace();
          }
        }

        zip.close();

        fXbmcHome.setLastModified(fPackagePath.lastModified());

      } catch (FileNotFoundException e1) {
        e1.printStackTrace();
        mErrorMsg = "Cannot find package.";
        return -1;
      } catch (IOException e) {
        e.printStackTrace();
        mErrorMsg = "Cannot read package.";
        File obb = new File(sPackagePath);
        obb.delete();
        return -1;
      }

      mState = CachingDone;
      publishProgress(0);

      return 0;
    }

    @Override
    protected void onProgressUpdate(Integer... values) {
      switch (mState) {
      case Caching:
        mSplash.mTextView.setText("Preparing for first run. Please wait...");
        mSplash.mProgress.setVisibility(View.VISIBLE);
        mSplash.mProgress.setProgress(values[0]);
        break;
      case CachingDone:
        mSplash.mProgress.setVisibility(View.INVISIBLE);
        break;
      }
    }

    @Override
    protected void onPostExecute(Integer result) {
      super.onPostExecute(result);
      if (result < 0) {
        mState = InError;
      }

      mStateMachine.sendEmptyMessage(mState);
    }
  }

  public void showErrorDialog(final Activity act, final String title, final String message) {
    if (myAlertDialog != null && myAlertDialog.isShowing())
      return;

    AlertDialog.Builder builder = new AlertDialog.Builder(act);
    builder.setTitle(title);
    builder.setIcon(android.R.drawable.ic_dialog_alert);
    builder.setMessage(Html.fromHtml(message));
    builder.setPositiveButton("Exit",
        new DialogInterface.OnClickListener() {
          public void onClick(DialogInterface dialog, int arg1) {
            dialog.dismiss();
            act.finish();
          }
        });
    builder.setCancelable(false);
    myAlertDialog = builder.create();
    myAlertDialog.show();

    // Make links actually clickable
    ((TextView) myAlertDialog.findViewById(android.R.id.message))
        .setMovementMethod(LinkMovementMethod.getInstance());
  }
  
  private void SetupEnvironment() {
    File fProp = new File(Environment.getExternalStorageDirectory().getAbsolutePath() + "/xbmc_env.properties");
    if (fProp.exists()) {
      Log.i(TAG, "Loading xbmc_env.properties");
      try {
        Properties sysProp = new Properties(System.getProperties());
        FileInputStream xbmcenvprop = new FileInputStream(fProp);
        sysProp.load(xbmcenvprop);
        System.setProperties(sysProp);

        sXbmcHome = System.getProperty("xbmc.home", "");
        if (!sXbmcHome.isEmpty()) {
          File fXbmcHome = new File(sXbmcHome);
          int loop = 20;
          while (!fXbmcHome.exists() && loop > 0) {
             // Wait a while in case of non-primary sdcard
            try {
              Thread.sleep(1000);
            } catch (InterruptedException e) {
              continue;
            }
            loop--;
          }
          if (!fXbmcHome.exists()) {
            System.setProperty("xbmc.home", "");
            sXbmcHome = "";
          }
        }

        sXbmcdata = System.getProperty("xbmc.data", "");
        if (!sXbmcdata.isEmpty()) {
          File fXbmcData = new File(sXbmcdata);
          int loop = 20;
          while (!fXbmcData.exists() && loop > 0) {
             // Wait a while in case of non-primary sdcard
            try {
              Thread.sleep(1000);
            } catch (InterruptedException e) {
              continue;
            }
            loop--;
          }

           if (!fXbmcData.exists()) {
             sXbmcdata = "";
             System.setProperty("xbmc.data", "");
           }
        }

      } catch (NotFoundException e) {
        Log.e(TAG, "Cannot find xbmc_env properties file");
      } catch (IOException e) {
        Log.e(TAG, "Failed to open xbmc_env properties file");
      }
    }
    if (sXbmcHome.isEmpty()) {
      File fCacheDir = getCacheDir();
      sXbmcHome = fCacheDir.getAbsolutePath() + "/apk";
    }

    fXbmcHome = new File(sXbmcHome);

    sPackagePath = getPackageResourcePath();
    fPackagePath = new File(sPackagePath);
    String obbfn = "";
    if (fPackagePath.length() < 40 * 1024 * 1024)
    {
      sPackagePath = System.getProperty("RoBoXTV.obb", "");
      if (sPackagePath.equals(""))
      {
        try
        {
          obbfn = "main." + getPackageManager().getPackageInfo(getPackageName(), 0).versionCode + "." + getPackageName() + ".obb";
          sPackagePath = Environment.getExternalStorageDirectory()
              + "/Android/obb/" + getPackageName() + "/" + obbfn;
        } catch (Exception e) {}
      }

      fPackagePath = new File(sPackagePath);
      if (fPackagePath.length() < 10 * 1024 * 1024)
        fPackagePath.delete();  // borked download
      if (!fPackagePath.exists())
      {
        mState = DownloadingObb;
        new DownloadObb(this).execute("http://mirrors.kodi.tv/releases/android/obb/" + obbfn, sPackagePath);
      }
    }
  }

  private void MigrateUserData() {
      String sOldUserDir;
      File fOldUserDir;
      try {
        sOldUserDir = getExternalFilesDir(null).getParentFile().getParentFile() + "/com.worldplayllc.xbmc/files/.xbmc";
        fOldUserDir = new File(sOldUserDir);
        if (!fOldUserDir.exists())
          return;
      } catch (Exception e) {
        return;
      }

      File fNewUserDir = new File(getExternalFilesDir(null), ".roboxtv");
      String sKodiMigrated = fNewUserDir.getAbsolutePath() + "/.kodi_data_was_migrated";
      File fKodiMigrated = new File(sKodiMigrated);

      Log.d(TAG, "External_dir = " + fOldUserDir);
      if (fOldUserDir.exists() && !fNewUserDir.exists()) {
        Log.d(TAG, "XBMC user data detected at " + fOldUserDir.getAbsolutePath() + ", migrating to " + fNewUserDir.getAbsolutePath());
        if (!fNewUserDir.getParentFile().exists() && !fNewUserDir.getParentFile().mkdirs()) {
          Log.d(TAG, "Error creating " + fNewUserDir.getParentFile().getAbsolutePath());
          return;
        }
        if (fOldUserDir.renameTo(fNewUserDir)) {
          try {
            new FileOutputStream(fKodiMigrated).close();
          } catch (IOException e1) {
            e1.printStackTrace();
          }
          Log.d(TAG, "XBMC user data migrated to RoBoXTV successfully");
        } else {
          Log.d(TAG, "Error migrating XBMC user data");
        }
      }
  }


  private boolean ParseCpuFeature() {
    ProcessBuilder cmd;

    try {
      String[] args = { "/system/bin/cat", "/proc/cpuinfo" };
      cmd = new ProcessBuilder(args);

      Process process = cmd.start();
      InputStream in = process.getInputStream();
      byte[] re = new byte[1024];
      while (in.read(re) != -1) {
        mCpuinfo = mCpuinfo + new String(re);
      }
      in.close();
    } catch (IOException ex) {
      ex.printStackTrace();
      return false;
    }
    return true;
  }

  // We can't find a way to properly detect and monitor status of
  //  a physical sdcard currently.
  // "External storage" points to internal flash storage on modern
  //  devices and nothing else seems available.
  //
  // ParseMounts() was part of the attempts to solve the issue and is not in use currently,
  //   but kept for possible future use.
  private boolean ParseMounts() {
    ProcessBuilder cmd;
    final Pattern reMount = Pattern.compile("^(.+?)\\s+(.+?)\\s+(.+?)\\s");
    String strMounts = "";

    try {
      String[] args = { "/system/bin/cat", "/proc/mounts" };
      cmd = new ProcessBuilder(args);

      Process process = cmd.start();
      InputStream in = process.getInputStream();
      byte[] re = new byte[1024];
      while (in.read(re) != -1) {
        strMounts = strMounts + new String(re);
      }
      in.close();
    } catch (IOException ex) {
      ex.printStackTrace();
      return false;
    }

    String[] Mounts = strMounts.split("\n");
    for (int i=0; i<Mounts.length; ++i) {
      Log.d(TAG, "mount: " + Mounts[i]);
      Matcher m = reMount.matcher(Mounts[i]);
      if (m.find()) {
        if (m.group(1).startsWith("/dev/block/vold") && !m.group(2).startsWith("/mnt/secure/asec")) {
          Log.d(TAG, "addind mount: " + m.group(2));
          mMounts.add(m.group(2));
        }
      }
    }
    return true;
  }

  private boolean CheckCpuFeature(String feat) {
    final Pattern FeaturePattern = Pattern.compile("(?i):.*?\\s" + feat + "(?:\\s|$)");
    Matcher m = FeaturePattern.matcher(mCpuinfo);
    return m.find();
  }

  void updateExternalStorageState() {
    String state = Environment.getExternalStorageState();
    Log.d(TAG, "External storage = " + Environment.getExternalStorageDirectory().getAbsolutePath() + "; state = " + state);
    if (Environment.MEDIA_MOUNTED.equals(state)) {
      mStateMachine.sendEmptyMessage(StorageChecked);
    } else {
      mExternalStorageChecked = false;
    }
  }

  void startWatchingExternalStorage() {
    mExternalStorageReceiver = new BroadcastReceiver() {
      @Override
      public void onReceive(Context context, Intent intent) {
        Log.i(TAG, "Storage: " + intent.getData());
        updateExternalStorageState();
      }
    };
    IntentFilter filter = new IntentFilter();
    filter.addAction(Intent.ACTION_MEDIA_MOUNTED);
    filter.addAction(Intent.ACTION_MEDIA_REMOVED);
    filter.addAction(Intent.ACTION_MEDIA_SHARED);
    filter.addAction(Intent.ACTION_MEDIA_UNMOUNTABLE);
    filter.addAction(Intent.ACTION_MEDIA_UNMOUNTED);
    filter.addDataScheme("file");
    registerReceiver(mExternalStorageReceiver, filter);
  }

  void stopWatchingExternalStorage() {
    if (mExternalStorageReceiver != null)
      unregisterReceiver(mExternalStorageReceiver);
  }

  protected void startXBMC() {
    // Run RoBoXTV
    Intent intent = getIntent();
    intent.setClass(this, com.worldplayllc.roboxtv.Main.class);
    intent.addFlags(Intent.FLAG_ACTIVITY_PREVIOUS_IS_TOP);
    startActivity(intent);
    finish();
  }

  @Override
  public void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);

    // Check if RoBoXTV is not already running
    ActivityManager activityManager = (ActivityManager) getBaseContext()
        .getSystemService(Context.ACTIVITY_SERVICE);
    List<RunningTaskInfo> tasks = activityManager
        .getRunningTasks(Integer.MAX_VALUE);
    for (RunningTaskInfo task : tasks)
      if (task.topActivity.toString().equalsIgnoreCase(
          "ComponentInfo{com.worldplayllc.roboxtv/com.worldplayllc.roboxtv.Main}")) {
        // RoBoXTV already running; just activate it
        startXBMC();
        return;
      }

    mStateMachine.sendEmptyMessage(Checking);

    String curArch = "";
    String curArch2 = "";
    try
    {
      curArch = Build.CPU_ABI.substring(0,3);
    } catch (IndexOutOfBoundsException e)
    {
      mErrorMsg = "Error! Unexpected architecture: " + Build.CPU_ABI;
      Log.e(TAG, mErrorMsg);
      mState = InError;
    }
    try
    {
      curArch2 = Build.CPU_ABI2.substring(0,3);
    } catch (IndexOutOfBoundsException e) {}

    if (mState != InError)
    {
      // Check if we are on the proper arch

      // Read the properties
      try {
        Resources resources = this.getResources();
        InputStream xbmcprop = resources.openRawResource(R.raw.xbmc);
        Properties properties = new Properties();
        properties.load(xbmcprop);

        if (!curArch.equalsIgnoreCase(properties.getProperty("native_arch"))
              && !curArch2.equalsIgnoreCase(properties.getProperty("native_arch")))
        {
          mErrorMsg = "This RoBoXTV package is not compatible with your device (device=" + curArch + " vs. package=" + properties.getProperty("native_arch") +").\nPlease check the <a href=\"http://wiki.kodi.tv/index.php?title=XBMC_for_Android_specific_FAQ\">Kodi Android wiki</a> for more information.";
          Log.e(TAG, mErrorMsg);
          mState = InError;
        }
      } catch (NotFoundException e) {
        mErrorMsg = "Cannot find properties file";
        Log.e(TAG, mErrorMsg);
        mState = InError;
      } catch (IOException e) {
        mErrorMsg = "Failed to open properties file";
        Log.e(TAG, mErrorMsg);
        mState = InError;
      }
    }

    if (mState != InError) {
      if (curArch.equalsIgnoreCase("arm")) {
        // arm arch: check if the cpu supports neon
        boolean ret = ParseCpuFeature();
        //Log.d(TAG, "/proc/cpuinfo = " + mCpuinfo);
        if (!ret) {
          mErrorMsg = "Error! Cannot parse CPU features.";
          Log.e(TAG, mErrorMsg);
          mState = InError;
        } else {
          ret = CheckCpuFeature("neon") || CheckCpuFeature("aarch64");  //aarch64 is always neon
          if (!ret) {
            mErrorMsg = "This RoBoXTV package is not compatible with your device (NEON).\nPlease check the <a href=\"http://wiki.kodi.tv/index.php?title=XBMC_for_Android_specific_FAQ\">Kodi Android wiki</a> for more information.";
            Log.e(TAG, mErrorMsg);
            mState = InError;
          }
        }
      }
    }

    Log.d(TAG, "External storage = " + Environment.getExternalStorageDirectory().getAbsolutePath() + "; state = " + Environment.getExternalStorageState());
    if (Environment.MEDIA_MOUNTED.equals(Environment.getExternalStorageState()))
      mExternalStorageChecked = true;

    if (mState != InError && mExternalStorageChecked) {
      mState = ChecksDone;

      SetupEnvironment();
      MigrateUserData();

      if ((mState != DownloadingObb && mState != InError) && fXbmcHome.exists() && fXbmcHome.lastModified() >= fPackagePath.lastModified() && !mInstallLibs) {
        mState = CachingDone;
        mCachingDone = true;
      }
    }

    if ((mState != DownloadingObb && mState != InError) && mCachingDone && mExternalStorageChecked) {
      startXBMC();
      return;
    }

    setContentView(R.layout.activity_splash);
    mProgress = (ProgressBar) findViewById(R.id.progressBar1);
    mTextView = (TextView) findViewById(R.id.textView1);

    if (mState == DownloadingObb || mState == InError) {
      mStateMachine.sendEmptyMessage(mState);
      return;
    }

    if (!mExternalStorageChecked) {
      startWatchingExternalStorage();
      mStateMachine.sendEmptyMessage(WaitingStorageChecked);
    } else {
      if (!mCachingDone)
        new FillCache(this).execute();
      else
        mStateMachine.sendEmptyMessage(CachingDone);
    }
  }

}
