// cl: /O2 /G7 /Oy /Ob1 /MD /Oi-
// msvcr71.dll import thunks: typed C++ forwarding through the genuine PE
// import-pointer symbols, as AmsgExitImport.cpp does for _amsg_exit and
// Kernel32ImportThunks.cpp does for kernel32: each forwards through the
// export's cdecl __imp__name pointer. No alias, address pin, inline assembly,
// emitted bytes or replacement datum is used.
// Signatures: the VS2003 CRT headers, included with _CRTIMP empty (the
// headers' own guard) so these definitions are not dllimport; /Oi- keeps the
// intrinsic functions (memcpy, strlen, ...) ordinary definitions. The CRT
// headers leave parameters unnamed; the documented names are used. feof and
// _ismbblead are also function-like macros, so their definitions
// parenthesize the name.
// Each retail six-byte thunk's IAT slot names the export (row notes).
#define _CRTIMP
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <ctype.h>
#include <wchar.h>
#include <wctype.h>
#include <time.h>
#include <io.h>
#include <direct.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <process.h>
#include <setjmp.h>
#include <locale.h>
#include <mbstring.h>
#include <mbctype.h>
#include <malloc.h>
#include <search.h>
#include <errno.h>
#include <memory.h>
extern "C" {
// _malloc
typedef void * (__cdecl *PFN_malloc)(size_t);
extern PFN_malloc _imp__malloc;
void * __cdecl malloc(size_t size) {
 return _imp__malloc(size);
}

// __resetstkoflw
typedef int (__cdecl *PFN__resetstkoflw)(void);
extern PFN__resetstkoflw _imp___resetstkoflw;
int __cdecl _resetstkoflw(void) {
 return _imp___resetstkoflw();
}

// _strlen
typedef size_t (__cdecl *PFN_strlen)(const char *);
extern PFN_strlen _imp__strlen;
size_t __cdecl strlen(const char * str) {
 return _imp__strlen(str);
}

// _strpbrk
typedef char * (__cdecl *PFN_strpbrk)(const char *, const char *);
extern PFN_strpbrk _imp__strpbrk;
char * __cdecl strpbrk(const char * str, const char * strCharSet) {
 return _imp__strpbrk(str, strCharSet);
}

// _memset
typedef void * (__cdecl *PFN_memset)(void *, int, size_t);
extern PFN_memset _imp__memset;
void * __cdecl memset(void * dest, int c, size_t count) {
 return _imp__memset(dest, c, count);
}

// _atol
typedef long (__cdecl *PFN_atol)(const char *);
extern PFN_atol _imp__atol;
long __cdecl atol(const char * str) {
 return _imp__atol(str);
}

// _strcmp
typedef int (__cdecl *PFN_strcmp)(const char *, const char *);
extern PFN_strcmp _imp__strcmp;
int __cdecl strcmp(const char * string1, const char * string2) {
 return _imp__strcmp(string1, string2);
}

// _wcslen
typedef size_t (__cdecl *PFN_wcslen)(const wchar_t *);
extern PFN_wcslen _imp__wcslen;
size_t __cdecl wcslen(const wchar_t * str) {
 return _imp__wcslen(str);
}

// _wcscpy
typedef wchar_t * (__cdecl *PFN_wcscpy)(wchar_t *, const wchar_t *);
extern PFN_wcscpy _imp__wcscpy;
wchar_t * __cdecl wcscpy(wchar_t * strDestination, const wchar_t * strSource) {
 return _imp__wcscpy(strDestination, strSource);
}

// _memcmp
typedef int (__cdecl *PFN_memcmp)(const void *, const void *, size_t);
extern PFN_memcmp _imp__memcmp;
int __cdecl memcmp(const void * buf1, const void * buf2, size_t count) {
 return _imp__memcmp(buf1, buf2, count);
}

// __memicmp
typedef int (__cdecl *PFN__memicmp)(const void *, const void *, size_t);
extern PFN__memicmp _imp___memicmp;
int __cdecl _memicmp(const void * buf1, const void * buf2, size_t count) {
 return _imp___memicmp(buf1, buf2, count);
}

// _towlower
typedef wchar_t (__cdecl *PFN_towlower)(wchar_t);
extern PFN_towlower _imp__towlower;
wchar_t __cdecl towlower(wchar_t c) {
 return _imp__towlower(c);
}

// _strncat
typedef char * (__cdecl *PFN_strncat)(char *, const char *, size_t);
extern PFN_strncat _imp__strncat;
char * __cdecl strncat(char * strDest, const char * strSource, size_t count) {
 return _imp__strncat(strDest, strSource, count);
}

// _fputs
typedef int (__cdecl *PFN_fputs)(const char *, FILE *);
extern PFN_fputs _imp__fputs;
int __cdecl fputs(const char * str, FILE * stream) {
 return _imp__fputs(str, stream);
}

// _fflush
typedef int (__cdecl *PFN_fflush)(FILE *);
extern PFN_fflush _imp__fflush;
int __cdecl fflush(FILE * stream) {
 return _imp__fflush(stream);
}

// _setvbuf
typedef int (__cdecl *PFN_setvbuf)(FILE *, char *, int, size_t);
extern PFN_setvbuf _imp__setvbuf;
int __cdecl setvbuf(FILE * stream, char * buffer, int mode, size_t size) {
 return _imp__setvbuf(stream, buffer, mode, size);
}

// _ftell
typedef long (__cdecl *PFN_ftell)(FILE *);
extern PFN_ftell _imp__ftell;
long __cdecl ftell(FILE * stream) {
 return _imp__ftell(stream);
}

// _feof
typedef int (__cdecl *PFN_feof)(FILE *);
extern PFN_feof _imp__feof;
int (__cdecl feof)(FILE * stream) {
 return _imp__feof(stream);
}

// _fgetpos
typedef int (__cdecl *PFN_fgetpos)(FILE *, fpos_t *);
extern PFN_fgetpos _imp__fgetpos;
int __cdecl fgetpos(FILE * stream, fpos_t * pos) {
 return _imp__fgetpos(stream, pos);
}

// _fseek
typedef int (__cdecl *PFN_fseek)(FILE *, long, int);
extern PFN_fseek _imp__fseek;
int __cdecl fseek(FILE * stream, long offset, int origin) {
 return _imp__fseek(stream, offset, origin);
}

// _fsetpos
typedef int (__cdecl *PFN_fsetpos)(FILE *, const fpos_t *);
extern PFN_fsetpos _imp__fsetpos;
int __cdecl fsetpos(FILE * stream, const fpos_t * pos) {
 return _imp__fsetpos(stream, pos);
}

// _ungetc
typedef int (__cdecl *PFN_ungetc)(int, FILE *);
extern PFN_ungetc _imp__ungetc;
int __cdecl ungetc(int c, FILE * stream) {
 return _imp__ungetc(c, stream);
}

// __get_osfhandle
typedef intptr_t (__cdecl *PFN__get_osfhandle)(int);
extern PFN__get_osfhandle _imp___get_osfhandle;
intptr_t __cdecl _get_osfhandle(int fd) {
 return _imp___get_osfhandle(fd);
}

// _memchr
typedef void * (__cdecl *PFN_memchr)(const void *, int, size_t);
extern PFN_memchr _imp__memchr;
void * __cdecl memchr(const void * buf, int c, size_t count) {
 return _imp__memchr(buf, c, count);
}

// _atoi
typedef int (__cdecl *PFN_atoi)(const char *);
extern PFN_atoi _imp__atoi;
int __cdecl atoi(const char * str) {
 return _imp__atoi(str);
}

// _strncpy
typedef char * (__cdecl *PFN_strncpy)(char *, const char *, size_t);
extern PFN_strncpy _imp__strncpy;
char * __cdecl strncpy(char * strDest, const char * strSource, size_t count) {
 return _imp__strncpy(strDest, strSource, count);
}

// _strcspn
typedef size_t (__cdecl *PFN_strcspn)(const char *, const char *);
extern PFN_strcspn _imp__strcspn;
size_t __cdecl strcspn(const char * str, const char * strCharSet) {
 return _imp__strcspn(str, strCharSet);
}

// _strchr
typedef char * (__cdecl *PFN_strchr)(const char *, int);
extern PFN_strchr _imp__strchr;
char * __cdecl strchr(const char * str, int c) {
 return _imp__strchr(str, c);
}

// _strstr
typedef char * (__cdecl *PFN_strstr)(const char *, const char *);
extern PFN_strstr _imp__strstr;
char * __cdecl strstr(const char * str, const char * strSearch) {
 return _imp__strstr(str, strSearch);
}

// _abort
typedef void (__cdecl *PFN_abort)(void);
extern PFN_abort _imp__abort;
void __cdecl abort(void) {
 _imp__abort();
}

// _exit
typedef void (__cdecl *PFN_exit)(int);
extern PFN_exit _imp__exit;
void __cdecl exit(int status) {
 _imp__exit(status);
}

// _puts
typedef int (__cdecl *PFN_puts)(const char *);
extern PFN_puts _imp__puts;
int __cdecl puts(const char * str) {
 return _imp__puts(str);
}

// _isspace
typedef int (__cdecl *PFN_isspace)(int);
extern PFN_isspace _imp__isspace;
int __cdecl isspace(int c) {
 return _imp__isspace(c);
}

// _localtime
typedef struct tm * (__cdecl *PFN_localtime)(const time_t *);
extern PFN_localtime _imp__localtime;
struct tm * __cdecl localtime(const time_t * timer) {
 return _imp__localtime(timer);
}

// __stat
typedef int (__cdecl *PFN__stat)(const char *, struct _stat *);
extern PFN__stat _imp___stat;
int __cdecl _stat(const char * path, struct _stat * buffer) {
 return _imp___stat(path, buffer);
}

// _strtok
typedef char * (__cdecl *PFN_strtok)(char *, const char *);
extern PFN_strtok _imp__strtok;
char * __cdecl strtok(char * strToken, const char * strDelimit) {
 return _imp__strtok(strToken, strDelimit);
}

// __vsnprintf
typedef int (__cdecl *PFN__vsnprintf)(char *, size_t, const char *, va_list);
extern PFN__vsnprintf _imp___vsnprintf;
int __cdecl _vsnprintf(char * buffer, size_t count, const char * format, va_list argptr) {
 return _imp___vsnprintf(buffer, count, format, argptr);
}

// _fclose
typedef int (__cdecl *PFN_fclose)(FILE *);
extern PFN_fclose _imp__fclose;
int __cdecl fclose(FILE * stream) {
 return _imp__fclose(stream);
}

// _fread
typedef size_t (__cdecl *PFN_fread)(void *, size_t, size_t, FILE *);
extern PFN_fread _imp__fread;
size_t __cdecl fread(void * buffer, size_t size, size_t count, FILE * stream) {
 return _imp__fread(buffer, size, count, stream);
}

// _fopen
typedef FILE * (__cdecl *PFN_fopen)(const char *, const char *);
extern PFN_fopen _imp__fopen;
FILE * __cdecl fopen(const char * filename, const char * mode) {
 return _imp__fopen(filename, mode);
}

// __mbsdup
typedef unsigned char * (__cdecl *PFN__mbsdup)(const unsigned char *);
extern PFN__mbsdup _imp___mbsdup;
unsigned char * __cdecl _mbsdup(const unsigned char * strSource) {
 return _imp___mbsdup(strSource);
}

// _iswspace
typedef int (__cdecl *PFN_iswspace)(wint_t);
extern PFN_iswspace _imp__iswspace;
int __cdecl iswspace(wint_t c) {
 return _imp__iswspace(c);
}

// _tolower
typedef int (__cdecl *PFN_tolower)(int);
extern PFN_tolower _imp__tolower;
int __cdecl tolower(int c) {
 return _imp__tolower(c);
}

// _toupper
typedef int (__cdecl *PFN_toupper)(int);
extern PFN_toupper _imp__toupper;
int __cdecl toupper(int c) {
 return _imp__toupper(c);
}

// _towupper
typedef wchar_t (__cdecl *PFN_towupper)(wchar_t);
extern PFN_towupper _imp__towupper;
wchar_t __cdecl towupper(wchar_t c) {
 return _imp__towupper(c);
}

// _strrchr
typedef char * (__cdecl *PFN_strrchr)(const char *, int);
extern PFN_strrchr _imp__strrchr;
char * __cdecl strrchr(const char * str, int c) {
 return _imp__strrchr(str, c);
}

// __ultoa
typedef char * (__cdecl *PFN__ultoa)(unsigned long, char *, int);
extern PFN__ultoa _imp___ultoa;
char * __cdecl _ultoa(unsigned long value, char * str, int radix) {
 return _imp___ultoa(value, str, radix);
}

// __exit
typedef void (__cdecl *PFN__exit)(int);
extern PFN__exit _imp___exit;
void __cdecl _exit(int status) {
 _imp___exit(status);
}

// __itoa
typedef char * (__cdecl *PFN__itoa)(int, char *, int);
extern PFN__itoa _imp___itoa;
char * __cdecl _itoa(int value, char * str, int radix) {
 return _imp___itoa(value, str, radix);
}

// __control87
typedef unsigned int (__cdecl *PFN__control87)(unsigned int, unsigned int);
extern PFN__control87 _imp___control87;
unsigned int __cdecl _control87(unsigned int newValue, unsigned int mask) {
 return _imp___control87(newValue, mask);
}

// __statusfp
typedef unsigned int (__cdecl *PFN__statusfp)(void);
extern PFN__statusfp _imp___statusfp;
unsigned int __cdecl _statusfp(void) {
 return _imp___statusfp();
}

// __fpreset
typedef void (__cdecl *PFN__fpreset)(void);
extern PFN__fpreset _imp___fpreset;
void __cdecl _fpreset(void) {
 _imp___fpreset();
}

// __time64
typedef __time64_t (__cdecl *PFN__time64)(__time64_t *);
extern PFN__time64 _imp___time64;
__time64_t __cdecl _time64(__time64_t * timer) {
 return _imp___time64(timer);
}

// _strncmp
typedef int (__cdecl *PFN_strncmp)(const char *, const char *, size_t);
extern PFN_strncmp _imp__strncmp;
int __cdecl strncmp(const char * string1, const char * string2, size_t count) {
 return _imp__strncmp(string1, string2, count);
}

// _atof
typedef double (__cdecl *PFN_atof)(const char *);
extern PFN_atof _imp__atof;
double __cdecl atof(const char * str) {
 return _imp__atof(str);
}

// _fgets
typedef char * (__cdecl *PFN_fgets)(char *, int, FILE *);
extern PFN_fgets _imp__fgets;
char * __cdecl fgets(char * str, int n, FILE * stream) {
 return _imp__fgets(str, n, stream);
}

// _isdigit
typedef int (__cdecl *PFN_isdigit)(int);
extern PFN_isdigit _imp__isdigit;
int __cdecl isdigit(int c) {
 return _imp__isdigit(c);
}

// __strnicmp
typedef int (__cdecl *PFN__strnicmp)(const char *, const char *, size_t);
extern PFN__strnicmp _imp___strnicmp;
int __cdecl _strnicmp(const char * string1, const char * string2, size_t count) {
 return _imp___strnicmp(string1, string2, count);
}

// __mbslen
typedef size_t (__cdecl *PFN__mbslen)(const unsigned char *);
extern PFN__mbslen _imp___mbslen;
size_t __cdecl _mbslen(const unsigned char * str) {
 return _imp___mbslen(str);
}

// _srand
typedef void (__cdecl *PFN_srand)(unsigned int);
extern PFN_srand _imp__srand;
void __cdecl srand(unsigned int seed) {
 _imp__srand(seed);
}

// _fwrite
typedef size_t (__cdecl *PFN_fwrite)(const void *, size_t, size_t, FILE *);
extern PFN_fwrite _imp__fwrite;
size_t __cdecl fwrite(const void * buffer, size_t size, size_t count, FILE * stream) {
 return _imp__fwrite(buffer, size, count, stream);
}

// __strlwr
typedef char * (__cdecl *PFN__strlwr)(char *);
extern PFN__strlwr _imp___strlwr;
char * __cdecl _strlwr(char * str) {
 return _imp___strlwr(str);
}

// __wfopen
typedef FILE * (__cdecl *PFN__wfopen)(const wchar_t *, const wchar_t *);
extern PFN__wfopen _imp___wfopen;
FILE * __cdecl _wfopen(const wchar_t * filename, const wchar_t * mode) {
 return _imp___wfopen(filename, mode);
}

// __makepath
typedef void (__cdecl *PFN__makepath)(char *, const char *, const char *, const char *, const char *);
extern PFN__makepath _imp___makepath;
void __cdecl _makepath(char * path, const char * drive, const char * dir, const char * fname, const char * ext) {
 _imp___makepath(path, drive, dir, fname, ext);
}

// __access
typedef int (__cdecl *PFN__access)(const char *, int);
extern PFN__access _imp___access;
int __cdecl _access(const char * path, int mode) {
 return _imp___access(path, mode);
}

// _rand
typedef int (__cdecl *PFN_rand)(void);
extern PFN_rand _imp__rand;
int __cdecl rand(void) {
 return _imp__rand();
}

// _time
typedef time_t (__cdecl *PFN_time)(time_t *);
extern PFN_time _imp__time;
time_t __cdecl time(time_t * timer) {
 return _imp__time(timer);
}

// _getenv
typedef char * (__cdecl *PFN_getenv)(const char *);
extern PFN_getenv _imp__getenv;
char * __cdecl getenv(const char * varname) {
 return _imp__getenv(varname);
}

// _iswalpha
typedef int (__cdecl *PFN_iswalpha)(wint_t);
extern PFN_iswalpha _imp__iswalpha;
int __cdecl iswalpha(wint_t c) {
 return _imp__iswalpha(c);
}

// _wcscat
typedef wchar_t * (__cdecl *PFN_wcscat)(wchar_t *, const wchar_t *);
extern PFN_wcscat _imp__wcscat;
wchar_t * __cdecl wcscat(wchar_t * strDestination, const wchar_t * strSource) {
 return _imp__wcscat(strDestination, strSource);
}

// __unlink
typedef int (__cdecl *PFN__unlink)(const char *);
extern PFN__unlink _imp___unlink;
int __cdecl _unlink(const char * filename) {
 return _imp___unlink(filename);
}

// _wcstok
typedef wchar_t * (__cdecl *PFN_wcstok)(wchar_t *, const wchar_t *);
extern PFN_wcstok _imp__wcstok;
wchar_t * __cdecl wcstok(wchar_t * strToken, const wchar_t * strDelimit) {
 return _imp__wcstok(strToken, strDelimit);
}

// __wsplitpath
typedef void (__cdecl *PFN__wsplitpath)(const wchar_t *, wchar_t *, wchar_t *, wchar_t *, wchar_t *);
extern PFN__wsplitpath _imp___wsplitpath;
void __cdecl _wsplitpath(const wchar_t * path, wchar_t * drive, wchar_t * dir, wchar_t * fname, wchar_t * ext) {
 _imp___wsplitpath(path, drive, dir, fname, ext);
}

// _wcsncpy
typedef wchar_t * (__cdecl *PFN_wcsncpy)(wchar_t *, const wchar_t *, size_t);
extern PFN_wcsncpy _imp__wcsncpy;
wchar_t * __cdecl wcsncpy(wchar_t * strDest, const wchar_t * strSource, size_t count) {
 return _imp__wcsncpy(strDest, strSource, count);
}

// __wunlink
typedef int (__cdecl *PFN__wunlink)(const wchar_t *);
extern PFN__wunlink _imp___wunlink;
int __cdecl _wunlink(const wchar_t * filename) {
 return _imp___wunlink(filename);
}

// _vsprintf
typedef int (__cdecl *PFN_vsprintf)(char *, const char *, va_list);
extern PFN_vsprintf _imp__vsprintf;
int __cdecl vsprintf(char * buffer, const char * format, va_list argptr) {
 return _imp__vsprintf(buffer, format, argptr);
}

// _wcschr
typedef wchar_t * (__cdecl *PFN_wcschr)(const wchar_t *, wchar_t);
extern PFN_wcschr _imp__wcschr;
wchar_t * __cdecl wcschr(const wchar_t * str, wchar_t c) {
 return _imp__wcschr(str, c);
}

// _iswalnum
typedef int (__cdecl *PFN_iswalnum)(wint_t);
extern PFN_iswalnum _imp__iswalnum;
int __cdecl iswalnum(wint_t c) {
 return _imp__iswalnum(c);
}

// _iswdigit
typedef int (__cdecl *PFN_iswdigit)(wint_t);
extern PFN_iswdigit _imp__iswdigit;
int __cdecl iswdigit(wint_t c) {
 return _imp__iswdigit(c);
}

// _iswascii
typedef int (__cdecl *PFN_iswascii)(wint_t);
extern PFN_iswascii _imp__iswascii;
int __cdecl iswascii(wint_t c) {
 return _imp__iswascii(c);
}

// _fgetwc
typedef wint_t (__cdecl *PFN_fgetwc)(FILE *);
extern PFN_fgetwc _imp__fgetwc;
wint_t __cdecl fgetwc(FILE * stream) {
 return _imp__fgetwc(stream);
}

// _fputwc
typedef wint_t (__cdecl *PFN_fputwc)(wchar_t, FILE *);
extern PFN_fputwc _imp__fputwc;
wint_t __cdecl fputwc(wchar_t c, FILE * stream) {
 return _imp__fputwc(c, stream);
}

// _strtol
typedef long (__cdecl *PFN_strtol)(const char *, char **, int);
extern PFN_strtol _imp__strtol;
long __cdecl strtol(const char * nptr, char ** endptr, int base) {
 return _imp__strtol(nptr, endptr, base);
}

// _wcsrchr
typedef wchar_t * (__cdecl *PFN_wcsrchr)(const wchar_t *, wchar_t);
extern PFN_wcsrchr _imp__wcsrchr;
wchar_t * __cdecl wcsrchr(const wchar_t * str, wchar_t c) {
 return _imp__wcsrchr(str, c);
}

// _wcsstr
typedef wchar_t * (__cdecl *PFN_wcsstr)(const wchar_t *, const wchar_t *);
extern PFN_wcsstr _imp__wcsstr;
wchar_t * __cdecl wcsstr(const wchar_t * str, const wchar_t * strSearch) {
 return _imp__wcsstr(str, strSearch);
}

// _strftime
typedef size_t (__cdecl *PFN_strftime)(char *, size_t, const char *, const struct tm *);
extern PFN_strftime _imp__strftime;
size_t __cdecl strftime(char * strDest, size_t maxsize, const char * format, const struct tm * timeptr) {
 return _imp__strftime(strDest, maxsize, format, timeptr);
}

// __wstat
typedef int (__cdecl *PFN__wstat)(const wchar_t *, struct _stat *);
extern PFN__wstat _imp___wstat;
int __cdecl _wstat(const wchar_t * path, struct _stat * buffer) {
 return _imp___wstat(path, buffer);
}

// _wcscmp
typedef int (__cdecl *PFN_wcscmp)(const wchar_t *, const wchar_t *);
extern PFN_wcscmp _imp__wcscmp;
int __cdecl wcscmp(const wchar_t * string1, const wchar_t * string2) {
 return _imp__wcscmp(string1, string2);
}

// _asctime
typedef char * (__cdecl *PFN_asctime)(const struct tm *);
extern PFN_asctime _imp__asctime;
char * __cdecl asctime(const struct tm * timeptr) {
 return _imp__asctime(timeptr);
}

// __mbscmp
typedef int (__cdecl *PFN__mbscmp)(const unsigned char *, const unsigned char *);
extern PFN__mbscmp _imp___mbscmp;
int __cdecl _mbscmp(const unsigned char * string1, const unsigned char * string2) {
 return _imp___mbscmp(string1, string2);
}

// __wtoi
typedef int (__cdecl *PFN__wtoi)(const wchar_t *);
extern PFN__wtoi _imp___wtoi;
int __cdecl _wtoi(const wchar_t * str) {
 return _imp___wtoi(str);
}

// _isalnum
typedef int (__cdecl *PFN_isalnum)(int);
extern PFN_isalnum _imp__isalnum;
int __cdecl isalnum(int c) {
 return _imp__isalnum(c);
}

// _iswgraph
typedef int (__cdecl *PFN_iswgraph)(wint_t);
extern PFN_iswgraph _imp__iswgraph;
int __cdecl iswgraph(wint_t c) {
 return _imp__iswgraph(c);
}

// __close
typedef int (__cdecl *PFN__close)(int);
extern PFN__close _imp___close;
int __cdecl _close(int fd) {
 return _imp___close(fd);
}

// _remove
typedef int (__cdecl *PFN_remove)(const char *);
extern PFN_remove _imp__remove;
int __cdecl remove(const char * path) {
 return _imp__remove(path);
}

// __waccess
typedef int (__cdecl *PFN__waccess)(const wchar_t *, int);
extern PFN__waccess _imp___waccess;
int __cdecl _waccess(const wchar_t * path, int mode) {
 return _imp___waccess(path, mode);
}

// __read
typedef int (__cdecl *PFN__read)(int, void *, unsigned int);
extern PFN__read _imp___read;
int __cdecl _read(int fd, void * buffer, unsigned int count) {
 return _imp___read(fd, buffer, count);
}

// __lseek
typedef long (__cdecl *PFN__lseek)(int, long, int);
extern PFN__lseek _imp___lseek;
long __cdecl _lseek(int fd, long offset, int origin) {
 return _imp___lseek(fd, offset, origin);
}

// __write
typedef int (__cdecl *PFN__write)(int, const void *, unsigned int);
extern PFN__write _imp___write;
int __cdecl _write(int fd, const void * buffer, unsigned int count) {
 return _imp___write(fd, buffer, count);
}

// _qsort
typedef void (__cdecl *PFN_qsort)(void *, size_t, size_t, int (__cdecl *)(const void *, const void *));
extern PFN_qsort _imp__qsort;
void __cdecl qsort(void * base, size_t num, size_t width, int (__cdecl * compare)(const void *, const void *)) {
 _imp__qsort(base, num, width, compare);
}

// _clock
typedef clock_t (__cdecl *PFN_clock)(void);
extern PFN_clock _imp__clock;
clock_t __cdecl clock(void) {
 return _imp__clock();
}

// __beginthreadex
typedef uintptr_t (__cdecl *PFN__beginthreadex)(void *, unsigned, unsigned (__stdcall *)(void *), void *, unsigned, unsigned *);
extern PFN__beginthreadex _imp___beginthreadex;
uintptr_t __cdecl _beginthreadex(void * security, unsigned stack_size, unsigned (__stdcall * start_address)(void *), void * arglist, unsigned initflag, unsigned * thrdaddr) {
 return _imp___beginthreadex(security, stack_size, start_address, arglist, initflag, thrdaddr);
}

// _strspn
typedef size_t (__cdecl *PFN_strspn)(const char *, const char *);
extern PFN_strspn _imp__strspn;
size_t __cdecl strspn(const char * str, const char * strCharSet) {
 return _imp__strspn(str, strCharSet);
}

// __errno
typedef int * (__cdecl *PFN__errno)(void);
extern PFN__errno _imp___errno;
int * __cdecl _errno(void) {
 return _imp___errno();
}

// _bsearch
typedef void * (__cdecl *PFN_bsearch)(const void *, const void *, size_t, size_t, int (__cdecl *)(const void *, const void *));
extern PFN_bsearch _imp__bsearch;
void * __cdecl bsearch(const void * key, const void * base, size_t num, size_t width, int (__cdecl * compare)(const void *, const void *)) {
 return _imp__bsearch(key, base, num, width, compare);
}

// __beginthread
typedef uintptr_t (__cdecl *PFN__beginthread)(void (__cdecl *)(void *), unsigned, void *);
extern PFN__beginthread _imp___beginthread;
uintptr_t __cdecl _beginthread(void (__cdecl * start_address)(void *), unsigned stack_size, void * arglist) {
 return _imp___beginthread(start_address, stack_size, arglist);
}

// __c_exit
typedef void (__cdecl *PFN__c_exit)(void);
extern PFN__c_exit _imp___c_exit;
void __cdecl _c_exit(void) {
 _imp___c_exit();
}

// __ismbblead
typedef int (__cdecl *PFN__ismbblead)(unsigned int);
extern PFN__ismbblead _imp___ismbblead;
int (__cdecl _ismbblead)(unsigned int c) {
 return _imp___ismbblead(c);
}

// __cexit
typedef void (__cdecl *PFN__cexit)(void);
extern PFN__cexit _imp___cexit;
void __cdecl _cexit(void) {
 _imp___cexit();
}

// __fstat
typedef int (__cdecl *PFN__fstat)(int, struct _stat *);
extern PFN__fstat _imp___fstat;
int __cdecl _fstat(int fd, struct _stat * buffer) {
 return _imp___fstat(fd, buffer);
}

// __strcmpi
typedef int (__cdecl *PFN__strcmpi)(const char *, const char *);
extern PFN__strcmpi _imp___strcmpi;
int __cdecl _strcmpi(const char * string1, const char * string2) {
 return _imp___strcmpi(string1, string2);
}

// __wcsicmp
typedef int (__cdecl *PFN__wcsicmp)(const wchar_t *, const wchar_t *);
extern PFN__wcsicmp _imp___wcsicmp;
int __cdecl _wcsicmp(const wchar_t * string1, const wchar_t * string2) {
 return _imp___wcsicmp(string1, string2);
}

// _isprint
typedef int (__cdecl *PFN_isprint)(int);
extern PFN_isprint _imp__isprint;
int __cdecl isprint(int c) {
 return _imp__isprint(c);
}

// _gmtime
typedef struct tm * (__cdecl *PFN_gmtime)(const time_t *);
extern PFN_gmtime _imp__gmtime;
struct tm * __cdecl gmtime(const time_t * timer) {
 return _imp__gmtime(timer);
}

// _calloc
typedef void * (__cdecl *PFN_calloc)(size_t, size_t);
extern PFN_calloc _imp__calloc;
void * __cdecl calloc(size_t num, size_t size) {
 return _imp__calloc(num, size);
}

// __atoi64
typedef __int64 (__cdecl *PFN__atoi64)(const char *);
extern PFN__atoi64 _imp___atoi64;
__int64 __cdecl _atoi64(const char * str) {
 return _imp___atoi64(str);
}

// _rewind
typedef void (__cdecl *PFN_rewind)(FILE *);
extern PFN_rewind _imp__rewind;
void __cdecl rewind(FILE * stream) {
 _imp__rewind(stream);
}

// __mkdir
typedef int (__cdecl *PFN__mkdir)(const char *);
extern PFN__mkdir _imp___mkdir;
int __cdecl _mkdir(const char * dirname) {
 return _imp___mkdir(dirname);
}

// __chmod
typedef int (__cdecl *PFN__chmod)(const char *, int);
extern PFN__chmod _imp___chmod;
int __cdecl _chmod(const char * filename, int pmode) {
 return _imp___chmod(filename, pmode);
}

// _rename
typedef int (__cdecl *PFN_rename)(const char *, const char *);
extern PFN_rename _imp__rename;
int __cdecl rename(const char * oldname, const char * newname) {
 return _imp__rename(oldname, newname);
}

// __getcwd
typedef char * (__cdecl *PFN__getcwd)(char *, int);
extern PFN__getcwd _imp___getcwd;
char * __cdecl _getcwd(char * buffer, int maxlen) {
 return _imp___getcwd(buffer, maxlen);
}

// _isupper
typedef int (__cdecl *PFN_isupper)(int);
extern PFN_isupper _imp__isupper;
int __cdecl isupper(int c) {
 return _imp__isupper(c);
}

// _ispunct
typedef int (__cdecl *PFN_ispunct)(int);
extern PFN_ispunct _imp__ispunct;
int __cdecl ispunct(int c) {
 return _imp__ispunct(c);
}

// _iscntrl
typedef int (__cdecl *PFN_iscntrl)(int);
extern PFN_iscntrl _imp__iscntrl;
int __cdecl iscntrl(int c) {
 return _imp__iscntrl(c);
}

// _isalpha
typedef int (__cdecl *PFN_isalpha)(int);
extern PFN_isalpha _imp__isalpha;
int __cdecl isalpha(int c) {
 return _imp__isalpha(c);
}

// _islower
typedef int (__cdecl *PFN_islower)(int);
extern PFN_islower _imp__islower;
int __cdecl islower(int c) {
 return _imp__islower(c);
}

// _system
typedef int (__cdecl *PFN_system)(const char *);
extern PFN_system _imp__system;
int __cdecl system(const char * command) {
 return _imp__system(command);
}

// _tmpnam
typedef char * (__cdecl *PFN_tmpnam)(char *);
extern PFN_tmpnam _imp__tmpnam;
char * __cdecl tmpnam(char * str) {
 return _imp__tmpnam(str);
}

// _freopen
typedef FILE * (__cdecl *PFN_freopen)(const char *, const char *, FILE *);
extern PFN_freopen _imp__freopen;
FILE * __cdecl freopen(const char * path, const char * mode, FILE * stream) {
 return _imp__freopen(path, mode, stream);
}

// _longjmp
typedef void (__cdecl *PFN_longjmp)(jmp_buf, int);
extern PFN_longjmp _imp__longjmp;
void __cdecl longjmp(jmp_buf env, int value) {
 _imp__longjmp(env, value);
}

// _strtod
typedef double (__cdecl *PFN_strtod)(const char *, char **);
extern PFN_strtod _imp__strtod;
double __cdecl strtod(const char * nptr, char ** endptr) {
 return _imp__strtod(nptr, endptr);
}

// _strcoll
typedef int (__cdecl *PFN_strcoll)(const char *, const char *);
extern PFN_strcoll _imp__strcoll;
int __cdecl strcoll(const char * string1, const char * string2) {
 return _imp__strcoll(string1, string2);
}

// __strupr
typedef char * (__cdecl *PFN__strupr)(char *);
extern PFN__strupr _imp___strupr;
char * __cdecl _strupr(char * str) {
 return _imp___strupr(str);
}
}
