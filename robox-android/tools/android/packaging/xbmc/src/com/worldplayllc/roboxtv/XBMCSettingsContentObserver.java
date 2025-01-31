package com.worldplayllc.roboxtv;

import android.content.Context;
import android.database.ContentObserver;
import android.media.AudioManager;
import android.net.Uri;
import android.os.Handler;
import android.util.Log;

public class XBMCSettingsContentObserver extends ContentObserver
{
  native void _onVolumeChanged(int newVolume);

  private static final String TAG = "roboxtv";

  int previousVolume;
  Context context;

  public XBMCSettingsContentObserver(Context c, Handler handler)
  {
    super(handler);
    context = c;

    AudioManager audio = (AudioManager) context.getSystemService(Context.AUDIO_SERVICE);
    previousVolume = audio.getStreamVolume(AudioManager.STREAM_MUSIC);
  }

  // Implement the onChange(boolean) method to delegate the change notification to
  // the onChange(boolean, Uri) method to ensure correct operation on older versions
  // of the framework that did not have the onChange(boolean, Uri) method.
  @Override
  public void onChange(boolean selfChange)
  {
      onChange(selfChange, null);
  }

  // Implement the onChange(boolean, Uri) method to take advantage of the new Uri argument.
  public void onChange(boolean selfChange, Uri uri)
  {
    super.onChange(selfChange);

    Log.d(TAG, "Setting changed: " + uri.toString());

    if (
        uri.compareTo(Uri.parse("content://settings/system/volume_music_speaker")) == 0 ||
        uri.compareTo(Uri.parse("content://settings/system/volume_music_hdmi")) == 0
        )
    {
      AudioManager audio = (AudioManager) context
          .getSystemService(Context.AUDIO_SERVICE);
      int currentVolume = audio.getStreamVolume(AudioManager.STREAM_MUSIC);

      if (currentVolume != previousVolume)
      {
        try
        {
          _onVolumeChanged(currentVolume);
          previousVolume = currentVolume;
        }
        catch (UnsatisfiedLinkError e)
        {
          Log.e("XBMCSettingsContentObserver", "Native not registered");
        }
      }
    }
  }
}
