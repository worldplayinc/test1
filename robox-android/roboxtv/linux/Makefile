CXXFLAGS += -fPIC

SRCS  = ConvUtils.cpp
SRCS += DBusUtil.cpp
SRCS += DBusMessage.cpp
SRCS += DBusReserve.cpp
SRCS += FDEventMonitor.cpp
SRCS += LinuxResourceCounter.cpp
SRCS += LinuxTimezone.cpp
SRCS += PosixMountProvider.cpp
SRCS += XFileUtils.cpp
SRCS += XHandle.cpp
SRCS += XMemUtils.cpp
SRCS += XTimeUtils.cpp

SRCS += RBP.cpp

ifeq (,1)
SRCS += OMXClock.cpp
SRCS += OMXCore.cpp
endif

LIB = linux.a

include /home/zach/zach/opt/kodi-android/Makefile.include
-include $(patsubst %.cpp,%.P,$(patsubst %.c,%.P,$(SRCS)))
