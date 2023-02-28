
#ifndef LIBDBCPPP_EXPORT_H
#define LIBDBCPPP_EXPORT_H

#ifdef LIBDBCPPP_STATIC_DEFINE
#  define LIBDBCPPP_EXPORT
#  define LIBDBCPPP_NO_EXPORT
#else
#  ifndef LIBDBCPPP_EXPORT
#    ifdef libdbcppp_EXPORTS
        /* We are building this library */
#      define LIBDBCPPP_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define LIBDBCPPP_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef LIBDBCPPP_NO_EXPORT
#    define LIBDBCPPP_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef LIBDBCPPP_DEPRECATED
#  define LIBDBCPPP_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef LIBDBCPPP_DEPRECATED_EXPORT
#  define LIBDBCPPP_DEPRECATED_EXPORT LIBDBCPPP_EXPORT LIBDBCPPP_DEPRECATED
#endif

#ifndef LIBDBCPPP_DEPRECATED_NO_EXPORT
#  define LIBDBCPPP_DEPRECATED_NO_EXPORT LIBDBCPPP_NO_EXPORT LIBDBCPPP_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef LIBDBCPPP_NO_DEPRECATED
#    define LIBDBCPPP_NO_DEPRECATED
#  endif
#endif

#endif /* LIBDBCPPP_EXPORT_H */
