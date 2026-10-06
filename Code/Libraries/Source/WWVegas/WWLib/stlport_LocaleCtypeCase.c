// cl: /MD
// STLport 4.5.3 _Locale_toupper/_Locale_tolower (retail 0x000219E0/0x00021B10)
// and _dup_0084EBC0 (retail 0x00021D50).
// Distinct TU under WWLib: Code/stlport/ is not an allowed root for a new
// source, so these donor bodies live here like stlport_LocaleStrcmp.c.
// Trimmed to the T1 bodies game.dat keeps; the donor's _Locale_strcmp
// already lives in stlport_LocaleStrcmp.c and the KeepDefault helpers are
// unserved (no row, no definition). Static workers stay static exactly
// like the donor.
typedef unsigned long LCID;
typedef unsigned int UINT;

__declspec(dllimport) int __stdcall GetLocaleInfoA(
    LCID locale, unsigned long type, char *data, int count);
__declspec(dllimport) int __cdecl atoi(const char *text);
__declspec(dllimport) int __stdcall LCMapStringA(
    LCID locale, unsigned long flags, const char *src, int srcCount,
    char *dest, int destCount);
__declspec(dllimport) int __stdcall MultiByteToWideChar(
    unsigned int codePage, unsigned long flags, const char *source, int sourceCount,
    unsigned short *destination, int destinationCount);
__declspec(dllimport) int __stdcall WideCharToMultiByte(
    unsigned int codePage, unsigned long flags, const unsigned short *source,
    int sourceCount, char *destination, int destinationCount,
    const char *defaultChar, int *usedDefaultChar);
__declspec(dllimport) void *__cdecl malloc(unsigned int size);
__declspec(dllimport) void __cdecl free(void *memory);

typedef unsigned int bfme_size_t;

typedef struct _Locale_ctype_t {
    LCID lcid;
    UINT cp;
} _Locale_ctype_t;

typedef struct _Locale_collate_t {
    LCID lcid;
    char cp[6];
} _Locale_collate_t;

static int __intGetACP(LCID lcid)
{
    char cp[6];
    GetLocaleInfoA(lcid, 0x1004, cp, 6);
    return atoi(cp);
}

static int __intGetOCP(LCID lcid)
{
    char cp[6];
    GetLocaleInfoA(lcid, 0xb, cp, 6);
    return atoi(cp);
}

static int __GetDefaultCP(LCID lcid)
{
    int cp = __intGetACP(lcid);
    if (cp == 0)
        return __intGetOCP(lcid);
    return cp;
}

static char *__ConvertToCP(int from_cp, int to_cp, const char *from,
    bfme_size_t size, bfme_size_t *ret_buf_size)
{
    int wideSize;
    int bufferSize;
    unsigned short *wideBuffer;
    char *buffer;

    wideSize = MultiByteToWideChar(from_cp, 1, from, (int)size, 0, 0);
    wideBuffer = (unsigned short *)malloc(sizeof(unsigned short) * wideSize);
    MultiByteToWideChar(from_cp, 1, from, (int)size, wideBuffer, wideSize);
    bufferSize = WideCharToMultiByte(to_cp, 0x220, wideBuffer, wideSize, 0, 0, 0, 0);
    buffer = (char *)malloc(bufferSize);
    WideCharToMultiByte(to_cp, 0x220, wideBuffer, wideSize, buffer, bufferSize, 0, 0);
    free(wideBuffer);
    *ret_buf_size = bufferSize;
    return buffer;
}

int _Locale_toupper(_Locale_ctype_t *ltype, int c)
{
    char buf[2], out_buf[2];
    buf[0] = (char)c;
    buf[1] = 0;
    if ((UINT)__GetDefaultCP(ltype->lcid) == ltype->cp) {
        LCMapStringA(ltype->lcid, 0x01000200, buf, 2, out_buf, 2);
        return (signed char)out_buf[0];
    } else {
        unsigned short wbuf[2];
        MultiByteToWideChar(ltype->cp, 1, buf, 2, wbuf, 2);
        WideCharToMultiByte(__GetDefaultCP(ltype->lcid), 0x220, wbuf, 2, buf, 2, 0, 0);
        LCMapStringA(ltype->lcid, 0x01000200, buf, 2, out_buf, 2);
        MultiByteToWideChar(__GetDefaultCP(ltype->lcid), 1, out_buf, 2, wbuf, 2);
        WideCharToMultiByte(ltype->cp, 0x220, wbuf, 2, out_buf, 2, 0, 0);
        return (signed char)out_buf[0];
    }
}

int _Locale_tolower(_Locale_ctype_t *ltype, int c)
{
    char buf[2], out_buf[2];
    buf[0] = (char)c;
    buf[1] = 0;
    if ((UINT)__GetDefaultCP(ltype->lcid) == ltype->cp) {
        LCMapStringA(ltype->lcid, 0x01000100, buf, 2, out_buf, 2);
        return (signed char)out_buf[0];
    } else {
        unsigned short wbuf[2];
        MultiByteToWideChar(ltype->cp, 1, buf, 2, wbuf, 2);
        WideCharToMultiByte(__GetDefaultCP(ltype->lcid), 0x220, wbuf, 2, buf, 2, 0, 0);
        LCMapStringA(ltype->lcid, 0x01000100, buf, 2, out_buf, 2);
        MultiByteToWideChar(__GetDefaultCP(ltype->lcid), 1, out_buf, 2, wbuf, 2);
        WideCharToMultiByte(ltype->cp, 0x220, wbuf, 2, out_buf, 2, 0, 0);
        return (signed char)out_buf[0];
    }
}

// _dup_0084EBC0  (donor b1 0x0084EBC0, 224B -> game.dat 0x00021D50, 224B)
//
// The donor's own comment for this body records an IDENTITY THAT IS NOT
// RECOVERED: no caller, string or vtable names the holder, so the name keeps the
// donor's address token. What the donor does record is the shape read off
// retail: the arg-1 object arrives with the LCID at +0 and the code-page text at
// +4, the inline GetLocaleInfoA(LOCALE_IDEFAULTANSICODEPAGE)/atoi pair with the
// LOCALE_IDEFAULTCODEPAGE fallback computes the default, and equality with
// atoi([obj+4]) takes the single LCMapStringA(..., 0x400, ...) direct map; else
// __GetDefaultCP + __ConvertToCP convert the source into a malloced buffer,
// LCMapStringA maps that buffer, and the buffer is freed. The destination pair
// precedes the source pair in the argument list: retail reads dest at
// [esp+0x2c] before src at [esp+0x34].
int _dup_0084EBC0(_Locale_collate_t *lcol, char *s2, bfme_size_t n2,
    const char *s1, bfme_size_t n1)
{
    int result;
    if (__GetDefaultCP(lcol->lcid) == atoi(lcol->cp)) {
        result = LCMapStringA(lcol->lcid, 0x400, s1, (int)n1, s2, (int)n2);
    } else {
        char *buf1;
        bfme_size_t size1;
        buf1 = __ConvertToCP(atoi(lcol->cp), __GetDefaultCP(lcol->lcid), s1, n1, &size1);
        result = LCMapStringA(lcol->lcid, 0x400, buf1, (int)size1, s2, (int)n2);
        free(buf1);
    }
    return result;
}
