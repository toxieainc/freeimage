/*
 * FreeImage: static replacement for the CMake generated opj_config_private.h
 * (src/lib/openjp2/opj_config_private.h.cmake.in), OpenJPEG 2.5.4.
 *
 * Valid for MSVC (x86 / x64 / ARM64), MinGW, and POSIX systems
 * (Linux, Android, macOS, iOS, BSD) built with GNU make or CMake.
 *
 * Threading: neither MUTEX_win32 nor MUTEX_pthread is defined, so thread.c
 * uses its single-threaded stub implementation (opj_has_thread_support()
 * returns false). FreeImage never calls opj_codec_set_threads(), and this
 * avoids any pthread link dependency.
 *
 * Large file support (_FILE_OFFSET_BITS / _LARGEFILE_SOURCE) is not enabled:
 * it only matters for opj_stream_create_default_file_stream(), which
 * FreeImage does not use (it provides its own stream callbacks).
 */

#ifndef OPJ_CONFIG_PRIVATE_H_INCLUDED
#define OPJ_CONFIG_PRIVATE_H_INCLUDED

#define OPJ_PACKAGE_VERSION "2.5.4"

#if defined(_WIN32)

/* MSVC and MinGW: <malloc.h> and _aligned_malloc are available */
#define OPJ_HAVE_MALLOC_H
#define OPJ_HAVE__ALIGNED_MALLOC

#else /* POSIX */

/* fseeko/ftello and posix_memalign are POSIX.1-2001 */
#define OPJ_HAVE_FSEEKO 1
#define OPJ_HAVE_POSIX_MEMALIGN

#endif /* _WIN32 */

#if !defined(_POSIX_C_SOURCE) && !defined(_WIN32)
#if defined(OPJ_HAVE_FSEEKO) || defined(OPJ_HAVE_POSIX_MEMALIGN)
/* Get declarations of fseeko, ftello, posix_memalign. */
#define _POSIX_C_SOURCE 200112L
#endif
#endif

/* Byte order.  */
/* Upstream uses a CMake TRY_RUN; here we rely on compiler predefined macros.
   All compilers that support Mac OS X define either __BIG_ENDIAN__ or
   __LITTLE_ENDIAN__ to match the endianness of the architecture being
   compiled for. GCC / Clang define __BYTE_ORDER__. */
#if defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__)
# if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#  define OPJ_BIG_ENDIAN
# endif
#elif defined(__BIG_ENDIAN__)
# define OPJ_BIG_ENDIAN
#elif (defined(BYTE_ORDER) && defined(BIG_ENDIAN) && BYTE_ORDER == BIG_ENDIAN) || \
      (defined(__BYTE_ORDER) && defined(__BIG_ENDIAN) && __BYTE_ORDER == __BIG_ENDIAN)
# define OPJ_BIG_ENDIAN
#endif

#endif /* OPJ_CONFIG_PRIVATE_H_INCLUDED */
