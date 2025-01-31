package com.worldplayllc.roboxtv;

import android.app.NativeActivity;
import android.content.ComponentName;
import android.content.Intent;
import android.media.AudioManager;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.Surface;
import android.widget.RelativeLayout;
import android.graphics.Color;
import android.graphics.PixelFormat;
import android.os.Handler;
import com.worldplayllc.roboxtv.XBMCVideoView;

public class Main extends NativeActivity
{
  private static final String TAG = "roboxtv";

  private XBMCSettingsContentObserver mSettingsContentObserver;
  private XBMCVideoView mVideoView = null;
  private RelativeLayout mVideoLayout = null;
  private View thisView = null;
  private Handler handler = new Handler();

  native void _onNewIntent(Intent intent);

  public Main()
  {
    super();
  }

  public Surface getVideoViewSurface()
  {
    return mVideoView.getSurface();
  }

  public void setVideoViewSurfaceRect(final int left, final int top, final int right, final int bottom)
  {
    runOnUiThread(new Runnable()
    {
      @Override
      public void run()
      {
        android.widget.RelativeLayout.LayoutParams mp = new android.widget.RelativeLayout.LayoutParams(mVideoView.getLayoutParams());
        mp.setMargins(left, top, mVideoLayout.getWidth() - right, mVideoLayout.getHeight() - bottom);
        mVideoView.setLayoutParams(mp);
        mVideoView.requestLayout();
      }
    });
  }

  public void clearVideoView()
  {
    runOnUiThread(new Runnable()
    {
      @Override
      public void run()
      {
        mVideoView.clearSurface();
      }
    });
  }
  
  public void registerMediaButtonEventReceiver()
  {
    AudioManager manager = (AudioManager) getSystemService(AUDIO_SERVICE);
    manager.registerMediaButtonEventReceiver(new ComponentName(getPackageName(), XBMCBroadcastReceiver.class.getName()));
  }

  public void unregisterMediaButtonEventReceiver()
  {
    AudioManager manager = (AudioManager) getSystemService(AUDIO_SERVICE);
    manager.unregisterMediaButtonEventReceiver(new ComponentName(getPackageName(), XBMCBroadcastReceiver.class.getName()));
  }

  @Override
  public void onCreate(Bundle savedInstanceState)
  {
    // The dynamic linker on droid is a mess.
    // Depending on version, it might not be able to properly resolve
    try
    {
      // Surround with try-catch to allow static version (3.0)
      System.loadLibrary("smbclient");
    }
    catch (UnsatisfiedLinkError e) {}
    System.loadLibrary("roboxtv");

    super.onCreate(savedInstanceState);
    getWindow().setFormat(PixelFormat.TRANSPARENT);

    setContentView(R.layout.activity_main);
    mVideoView = (XBMCVideoView)findViewById(R.id.VideoView1);
    mVideoView.getHolder().setFormat(PixelFormat.TRANSPARENT);
    mVideoLayout = (RelativeLayout) findViewById(R.id.VideoLayout);

    setVolumeControlStream(AudioManager.STREAM_MUSIC);

    mSettingsContentObserver = new XBMCSettingsContentObserver(this, new Handler());
    getApplicationContext().getContentResolver().registerContentObserver(android.provider.Settings.System.CONTENT_URI, true, mSettingsContentObserver );

    thisView = getWindow().getDecorView();
    thisView.setOnSystemUiVisibilityChangeListener(new View.OnSystemUiVisibilityChangeListener()
          {
            @Override
            public void onSystemUiVisibilityChange(int visibility)
            {
              if ((visibility & View.SYSTEM_UI_FLAG_HIDE_NAVIGATION) == 0)
              {
                handler.post(new Runnable()
                {
                  public void run()
                  {
                    if (android.os.Build.VERSION.SDK_INT >= 19) {
                      // Immersive mode

                      // Constants from API > 17
                      final int API_SYSTEM_UI_FLAG_IMMERSIVE_STICKY = 0x00001000;

                      thisView.setSystemUiVisibility(
                                View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                              | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                              | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                              | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                              | View.SYSTEM_UI_FLAG_FULLSCREEN
                              | API_SYSTEM_UI_FLAG_IMMERSIVE_STICKY);
                    }
                  }
                });
              }
            }
          });
  }

  @Override
  protected void onNewIntent(Intent intent)
  {
    super.onNewIntent(intent);
    try {
      _onNewIntent(intent);
    } catch (UnsatisfiedLinkError e) {
      Log.e("Main", "Native not registered");
    }
  }

  @Override
  public void onStart()
  {
    super.onStart();
    getWindow().setFormat(PixelFormat.TRANSPARENT);
  }

  @Override
  public void onResume()
  {
    super.onResume();

    if (android.os.Build.VERSION.SDK_INT >= 19) {
      // Immersive mode

      // Constants from API > 17
      final int API_SYSTEM_UI_FLAG_IMMERSIVE_STICKY = 0x00001000;

      thisView.setSystemUiVisibility(
                View.SYSTEM_UI_FLAG_LAYOUT_STABLE
              | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
              | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
              | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
              | View.SYSTEM_UI_FLAG_FULLSCREEN
              | API_SYSTEM_UI_FLAG_IMMERSIVE_STICKY);
    }
  }

  @Override
  public void onDestroy()
  {
    getApplicationContext().getContentResolver().unregisterContentObserver(mSettingsContentObserver);
    super.onDestroy();
  }

  private native void _callNative(long funcAddr, long variantAddr);

  private void runNativeOnUiThread(final long funcAddr, final long variantAddr)
  {
    runOnUiThread(new Runnable()
    {
      @Override
      public void run()
      {
        _callNative(funcAddr, variantAddr);
      }
    });
  }
}
