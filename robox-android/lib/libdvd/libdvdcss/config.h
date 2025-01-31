/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Have IOKit DVD IOCTL headers */
/* #undef DARWIN_DVD_IOCTL */

/* Define if <linux/cdrom.h> defines DVD_STRUCT. */
#define DVD_STRUCT_IN_LINUX_CDROM_H 1

/* Define if <sys/cdio.h> defines dvd_struct. */
/* #undef DVD_STRUCT_IN_SYS_CDIO_H */

/* Define if <sys/dvdio.h> defines dvd_struct. */
/* #undef DVD_STRUCT_IN_SYS_DVDIO_H */

/* Define if you have a broken mkdir */
/* #undef HAVE_BROKEN_MKDIR */

/* Define if FreeBSD-like dvd_struct is defined. */
/* #undef HAVE_BSD_DVD_STRUCT */

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the <dvd.h> header file. */
/* #undef HAVE_DVD_H */

/* Define to 1 if you have the <errno.h> header file. */
#define HAVE_ERRNO_H 1

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <io.h> header file. */
/* #undef HAVE_IO_H */

/* Define to 1 if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define to 1 if you have the <linux/cdrom.h> header file. */
#define HAVE_LINUX_CDROM_H 1

/* Define if Linux-like dvd_struct is defined. */
#define HAVE_LINUX_DVD_STRUCT 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define if OpenBSD-like dvd_struct is defined. */
/* #undef HAVE_OPENBSD_DVD_STRUCT */

/* Define to 1 if you have the <pwd.h> header file. */
#define HAVE_PWD_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/cdio.h> header file. */
/* #undef HAVE_SYS_CDIO_H */

/* Define to 1 if you have the <sys/dvdio.h> header file. */
/* #undef HAVE_SYS_DVDIO_H */

/* Define to 1 if you have the <sys/ioctl.h> header file. */
#define HAVE_SYS_IOCTL_H 1

/* Define to 1 if you have the <sys/param.h> header file. */
#define HAVE_SYS_PARAM_H 1

/* Define to 1 if you have the <sys/scsi/impl/uscsi.h> header file. */
/* #undef HAVE_SYS_SCSI_IMPL_USCSI_H */

/* Define to 1 if you have the <sys/scsi/scsi_types.h,> header file. */
/* #undef HAVE_SYS_SCSI_SCSI_TYPES_H_ */

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/uio.h> header file. */
#define HAVE_SYS_UIO_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the <windows.h> header file. */
/* #undef HAVE_WINDOWS_H */

/* Define to 1 if you have the <winioctl.h> header file. */
/* #undef HAVE_WINIOCTL_H */

/* Define if <sys/scsi.h> defines sctl_io. */
/* #undef HPUX_SCTL_IO */

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Define O_BINARY if missing */
#define O_BINARY 0

/* Name of package */
#define PACKAGE "libdvdcss"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME "libdvdcss"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "libdvdcss 1.2.13"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "libdvdcss"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "1.2.13"

/* Have userspace SCSI headers. */
/* #undef SOLARIS_USCSI */

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define this if the compiler supports __attribute__((
   ifelse([visibility("default")], , [visibility_default],
   [visibility("default")]) )) */
#define SUPPORT_ATTRIBUTE_VISIBILITY_DEFAULT 1

/* Define this if the compiler supports the -fvisibility flag */
#define SUPPORT_FLAG_VISIBILITY 1

/* Version number of package */
#define VERSION "1.2.13"

/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _FILE_OFFSET_BITS */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

/* Define to '0x0401' for IE 4.01 (and shell) APIs. */
/* #undef _WIN32_IE */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */
