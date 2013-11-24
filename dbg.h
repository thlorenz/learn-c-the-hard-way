#ifndef __dbh_h__
#define __dbh_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifdef NDEBUG
// compile with all debug messages removed
#define debug(M, ...)
#else
// debug("format", arg ..) => fprintf(stderr, "DEBUG %s:%d: format\n", file, line, arg ...)
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

// safe readable version of errno
#define clean_errno() (errno == 0 ? "None" : strerror(errno))

// log_* work just like debug, but cannot be compiled out
#define log_err(M, ...) fprintf(stderr, "[ERR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

// enhanced assert? check that A is true, otherwise log error M then jump to error: for cleanup
#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

// placed in part of fn that shouldn't run, i.e. if/switch branches, prints error followed by jumping to error: cleanup
#define sentinel(M, ...)  { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define check_mem(A) check((A), "Out of memory.")

// same as check, except that error only gets reported when ndebug flag is not set
#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; }

#endif
