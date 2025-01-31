package com.worldplayllc.roboxtv;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.egl.EGLSurface;

import android.R.bool;
import android.opengl.GLES20;
import android.util.AttributeSet;
import android.util.Log;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;

public class XBMCVideoView extends SurfaceView implements
    SurfaceHolder.Callback
{
  private static final String TAG = "XBMCVideoPlayView";
  public boolean mHasHolder = false;

  public XBMCVideoView(Context context)
  {
    super(context);
    getHolder().addCallback(this);
  }

  public XBMCVideoView(Context context, AttributeSet attrs)
  {
    this(context, attrs, 0);
    getHolder().addCallback(this);
  }

  public XBMCVideoView(Context context, AttributeSet attrs, int defStyle)
  {
    super(context, attrs, defStyle);
    getHolder().addCallback(this);
  }

  /**
   * Clears the playback surface to black.
   */
  public void clearSurface()
  {
    if (!mHasHolder)
      return;

    // Have to go EGL to allow reuse of surface

    final int EGL_OPENGL_ES2_BIT = 4;
    final int EGL_CONTEXT_CLIENT_VERSION = 0x3098;

    EGL10 egl = (EGL10) EGLContext.getEGL();
    EGLDisplay display = egl.eglGetDisplay(EGL10.EGL_DEFAULT_DISPLAY);
    egl.eglInitialize(display, null);

    int[] attribList =
    { EGL10.EGL_RED_SIZE, 8, EGL10.EGL_GREEN_SIZE, 8, EGL10.EGL_BLUE_SIZE, 8,
        EGL10.EGL_ALPHA_SIZE, 8, EGL10.EGL_RENDERABLE_TYPE,
        EGL_OPENGL_ES2_BIT, EGL10.EGL_NONE, 0, // placeholder for
                                                     // recordable [@-3]
        EGL10.EGL_NONE };
    EGLConfig[] configs = new EGLConfig[1];
    int[] numConfigs = new int[1];
    egl.eglChooseConfig(display, attribList, configs, configs.length,
        numConfigs);
    EGLConfig config = configs[0];
    EGLContext context = egl.eglCreateContext(display, config,
        EGL10.EGL_NO_CONTEXT, new int[]
        { EGL_CONTEXT_CLIENT_VERSION, 2, EGL10.EGL_NONE });
    EGLSurface eglSurface = egl.eglCreateWindowSurface(display, config,
        this, new int[]
        { EGL10.EGL_NONE });

    egl.eglMakeCurrent(display, eglSurface, eglSurface, context);
    GLES20.glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);
    egl.eglSwapBuffers(display, eglSurface);
    egl.eglDestroySurface(display, eglSurface);
    egl.eglMakeCurrent(display, EGL10.EGL_NO_SURFACE, EGL10.EGL_NO_SURFACE,
        EGL10.EGL_NO_CONTEXT);
    egl.eglDestroyContext(display, context);
    egl.eglTerminate(display);
  }

  public Surface getSurface()
  {
    if (!mHasHolder)
    {
      return null;
    } else
    {
      Log.d(TAG, "getSurface() = " + getHolder().getSurface());
      return getHolder().getSurface();
    }
  }

  @Override
  public void surfaceCreated(SurfaceHolder holder)
  {
    Log.d(TAG, "Created");
    mHasHolder = true;
  }

  @Override
  public void surfaceChanged(SurfaceHolder holder, int format, int width,
      int height)
  {
    Log.d(TAG, "Changed, format:" + format + ", width:" + width
        + ", height:" + height);
  }

  @Override
  public void surfaceDestroyed(SurfaceHolder holder)
  {
    Log.d(TAG, "Destroyed");
    mHasHolder = false;
  }
}
