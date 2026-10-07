// cl: /MD
// STLport 4.5.3 Win32 locale code-page helpers.
// The default-locale and ctype-name entry points retain the donor workers
// (__GetLocaleName, __ConvertToCP, __GetDefaultCP). The donor's Rva* probe
// wrappers and T3 guess bodies stay out: their names are this sweep's pick
// among ICF twins, so they get no row and no definition here.
// The two workers stay static exactly like the donor. Retail passes their
// first argument in a register (fromCP in eax, lcid in esi), which MSVC only
// does for static functions with known call sites, so each worker keeps the
// donor's pair of A/B forwarder callers. The forwarders are static too and
// would be dropped as unreferenced, taking the workers with them; the
// address tables below keep them emitted without adding any code.
// __intGetACP/__intGetOCP are static here (extern in the donor) so the only
// out-of-line defs with external linkage are rowed; inlining into the
// callers is unchanged, which is what the byte match checks.

typedef unsigned long LCID;
typedef unsigned int bfme_size_t;

#define LOCALE_IDEFAULTCODEPAGE 0x0000000b
#define LOCALE_IDEFAULTANSICODEPAGE 0x00001004

__declspec(dllimport) int __stdcall GetLocaleInfoA(
    LCID locale, unsigned long type, char *data, int count);
__declspec(dllimport) int __cdecl atoi(const char *text);
__declspec(dllimport) void *__cdecl malloc(unsigned int size);
__declspec(dllimport) void __cdecl free(void *memory);
__declspec(dllimport) char *__cdecl strcpy(char *destination, const char *source);
__declspec(dllimport) char *__cdecl strcat(char *destination, const char *source);
__declspec(dllimport) unsigned int __cdecl strlen(const char *text);
__declspec(dllimport) void *__cdecl memcpy(void *destination, const void *source,
    unsigned int count);
__declspec(dllimport) int __stdcall lstrcmpiA(const char *left, const char *right);
__declspec(dllimport) int __stdcall EnumSystemLocalesA(
    int (__stdcall *callback)(char *), unsigned long flags);
__declspec(dllimport) int __stdcall MultiByteToWideChar(
    unsigned int codePage, unsigned long flags, const char *source, int sourceCount,
    unsigned short *destination, int destinationCount);
__declspec(dllimport) int __stdcall WideCharToMultiByte(
    unsigned int codePage, unsigned long flags, const unsigned short *source,
    int sourceCount, char *destination, int destinationCount,
    const char *defaultChar, int *usedDefaultChar);

typedef struct _Locale_ctype_t
{
    LCID lcid;
    int cp;
} _Locale_ctype_t;

static void my_ltoa(long value, char *buf)
{
    char reverse[64];
    char *ptr = reverse;
    if (value == 0)
        *ptr++ = '0';
    else
    {
        for (; value != 0; value /= 10)
            *ptr++ = (int)(value % 10) + '0';
    }
    while (ptr > reverse)
        *buf++ = *--ptr;
    *buf = '\0';
}

static int __intGetACP(LCID lcid);
static int __intGetOCP(LCID lcid);

static int __intGetACP(LCID lcid)
{
    char cp[6];
    GetLocaleInfoA(lcid, LOCALE_IDEFAULTANSICODEPAGE, cp, 6);
    return atoi(cp);
}

static int __intGetOCP(LCID lcid)
{
    char cp[6];
    GetLocaleInfoA(lcid, LOCALE_IDEFAULTCODEPAGE, cp, 6);
    return atoi(cp);
}

// ___GetDefaultCP
static int __GetDefaultCP(LCID lcid)
{
    int cp = __intGetACP(lcid);
    if (cp == 0)
        return __intGetOCP(lcid);
    return cp;
}

// Donor-verbatim A/B caller shapes for __GetDefaultCP. Static, so they need
// the address table at the bottom to stay emitted.
static int __UseDefaultCPA(LCID lcid)
{
    return __GetDefaultCP(lcid);
}

static int __UseDefaultCPB(LCID lcid)
{
    return __GetDefaultCP(lcid) + 1;
}

// The donor keeps this worker static and calls it from two Rva* probe
// wrappers that game.dat does not keep. It stays static (see above).
static char *__ConvertToCP(int fromCP, int toCP, const char *from,
    bfme_size_t size, bfme_size_t *resultSize)
{
    int wideSize;
    int bufferSize;
    unsigned short *wideBuffer;
    char *buffer;

    wideSize = MultiByteToWideChar(fromCP, 1, from, size, 0, 0);
    wideBuffer = (unsigned short *)malloc(sizeof(unsigned short) * wideSize);
    MultiByteToWideChar(fromCP, 1, from, size, wideBuffer, wideSize);

    bufferSize = WideCharToMultiByte(toCP, 0x220, wideBuffer, wideSize,
        0, 0, 0, 0);
    buffer = (char *)malloc(bufferSize);
    WideCharToMultiByte(toCP, 0x220, wideBuffer, wideSize,
        buffer, bufferSize, 0, 0);

    free(wideBuffer);
    *resultSize = bufferSize;
    return buffer;
}

// Donor-verbatim A/B caller shapes for __ConvertToCP (see above).
static char *__UseConvertToCPA(int fromCP, int toCP, const char *from,
    bfme_size_t size, bfme_size_t *resultSize)
{
    return __ConvertToCP(fromCP, toCP, from, size, resultSize);
}

static char *__UseConvertToCPB(int fromCP, int toCP, const char *from,
    bfme_size_t size, bfme_size_t *resultSize)
{
    char *result = __ConvertToCP(fromCP, toCP, from, size, resultSize);
    return result ? result : fromCP ? (char *)from : result;
}

static char *__GetLocaleName(LCID lcid, const char *cp, char *buf)
{
    char lang[65];
    char country[65];
    GetLocaleInfoA(lcid, 0x1001, lang, 64);
    GetLocaleInfoA(lcid, 0x1002, country, 64);
    strcpy(buf, lang);
    strcat(buf, "_");
    strcat(buf, country);
    strcat(buf, ".");
    return strcat(buf, cp);
}

// __Locale_common_default
char *_Locale_common_default(char *buf)
{
    char cp[6];
    int codePage = __intGetACP(0x400);
    if (!codePage)
        codePage = __intGetOCP(0x400);
    my_ltoa(codePage, cp);
    return __GetLocaleName(0x400, cp, buf);
}

// __Locale_ctype_name
char *_Locale_ctype_name(const void *loc, char *buf)
{
    char cpBuf[6];
    _Locale_ctype_t *ctype = (_Locale_ctype_t *)loc;
    my_ltoa(ctype->cp, cpBuf);
    return __GetLocaleName(ctype->lcid, cpBuf, buf);
}

// Keeps the static A/B forwarders (and through them the static workers)
// emitted. Data only: no code, no effect on any body above.
typedef int (*DefaultCPForwarder)(LCID lcid);
typedef char *(*ConvertToCPForwarder)(int fromCP, int toCP, const char *from,
    bfme_size_t size, bfme_size_t *resultSize);

static const DefaultCPForwarder g_defaultCPForwarders[] =
{
    __UseDefaultCPA,
    __UseDefaultCPB
};

static const ConvertToCPForwarder g_convertToCPForwarders[] =
{
    __UseConvertToCPA,
    __UseConvertToCPB
};

// Rva0084ECA0/Rva0084ECE0 (retail 0x00021E30/0x00021E70, 61B each): locale
// language/country name getters. The sweep promotes them from T3 guesses to
// unique free-ground placements at distinct addresses with distinct buffers.
// Retail uses separate zero-filled .data buffers. Named arrays retain
// those operands while allowing the buffers to move in the linked image.
// __ConvertFromACP stays static exactly like the donor: retail
// passes its first argument in edi (caller cleans 8 for the other two),
// which MSVC only does for static callees, and the tail call needs the
// Rva0084DE40Tail pin (same TU shape as the BFME1 donor).
typedef struct LocaleCodePageObject_0084EED0
{
    LCID locale;
    char codePage[1];
} LocaleCodePageObject_0084EED0;

static void __ConvertFromACP(char *buf, int bufSize, const char *cp)
{
    unsigned short *wideBuffer;
    int wideSize = MultiByteToWideChar(0, 0, buf, -1, 0, 0);
    wideBuffer = (unsigned short *)malloc(sizeof(unsigned short) * (wideSize + 1));
    MultiByteToWideChar(0, 0, buf, -1, wideBuffer, wideSize);
    WideCharToMultiByte(atoi(cp), 0, wideBuffer, -1, buf, bufSize, 0, 0);
    free(wideBuffer);
}

extern char *__cdecl Rva0084DE40Tail(char *buffer);

// Retail operands identify distinct zero-filled buffers at VA 0x00DDF368
// and 0x00DDEF58. Their original declared capacities are unknown; the linked
// storage covers each unchanged GetLocaleInfoA request of 0x104 bytes.
char locale_buffer_0084ECA0[0x104];
char locale_buffer_0084ECE0[0x104];
char locale_buffer_0084EED0[9];
char locale_buffer_0084EF00[9];

char *Rva0084ECA0(LocaleCodePageObject_0084EED0 *object)
{
    LCID locale = object->locale;
    GetLocaleInfoA(locale, 0x1f, locale_buffer_0084ECA0, 0x104);
    {
        char *buffer = locale_buffer_0084ECA0;
        __ConvertFromACP(buffer, 0x50, object->codePage);
        return Rva0084DE40Tail(buffer);
    }
}

char *Rva0084ECE0(LocaleCodePageObject_0084EED0 *object)
{
    LCID locale = object->locale;
    GetLocaleInfoA(locale, 0x20, locale_buffer_0084ECE0, 0x104);
    {
        char *buffer = locale_buffer_0084ECE0;
        __ConvertFromACP(buffer, 0x50, object->codePage);
        return Rva0084DE40Tail(buffer);
    }
}

// Rva0084EED0 (retail 0x00022060, 48B): locale measurement-system getter.
// Same file-unit as Rva0084ECA0/ECE0 above: donor-verbatim wrapper around the
// rowed ___ConvertFromACP (0x00021740) with its named output buffer,
// GetLocaleInfoA type 0x28 and 9-byte size. Returns the converted buffer
// directly (no Rva0084DE40Tail tail call), hence 48B not 61B.
char *Rva0084EED0(LocaleCodePageObject_0084EED0 *object)
{
    LCID locale = object->locale;
    GetLocaleInfoA(locale, 0x28, locale_buffer_0084EED0, 9);
    {
        char *buffer = locale_buffer_0084EED0;
        __ConvertFromACP(buffer, 9, object->codePage);
        return buffer;
    }
}

// Rva0084EF00 (retail 0x00022090, 48B): locale digit-substitution getter.
// Same file-unit as Rva0084EED0 above: donor-verbatim wrapper around the
// rowed ___ConvertFromACP (0x00021740) with its named output buffer,
// GetLocaleInfoA type 0x29 and 9-byte size. Returns the converted buffer
// directly (no Rva0084DE40Tail tail call), hence 48B not 61B.
char *Rva0084EF00(LocaleCodePageObject_0084EED0 *object)
{
    LCID locale = object->locale;
    GetLocaleInfoA(locale, 0x29, locale_buffer_0084EF00, 9);
    {
        char *buffer = locale_buffer_0084EF00;
        __ConvertFromACP(buffer, 9, object->codePage);
        return buffer;
    }
}

// Rva000219C0LocaleName (retail 0x000219C0, 23B): the donor's five
// Rva0084E7B0/7D0/7F0/810/830LocaleName twins, which lotrbfme.exe ICF-folded
// onto one body. Retail keeps a single identity here, so the name stays
// address-derived rather than borrowing one twin's. The argument slots are
// read off the callee (0x000215B0): it keeps its destination in eax and its
// appended code-page string on the stack, so retail's caller puts the object's
// codePage field on the stack and the caller's buffer in eax.
char *Rva000219C0LocaleName(LocaleCodePageObject_0084EED0 *object, char *buf)
{
    return __GetLocaleName(object->locale, object->codePage, buf);
}

// Rva0084EF30 (retail 0x000220C0, 227B): time-format builder, last of the
// locale-buffer getters in this file-unit. GetLocaleInfoA fills a 4-byte
// separator (type 0x1e), the rowed ___ConvertFromACP (0x00021740) re-codes it,
// then the donor composes "%H<sep>%M<sep>%S %p" with strcpy/strcat into the
// static format buffer. Retail reads the three literals from the .rdata pool
// at 0x00BBD3F4/0x00BBD3FC/0x00BBD400 and writes the format at 0x00DDEFA8; the
// zero-filled output buffer is defined below and follows the linked image.
extern char locale_format_0084EF30[];

char *Rva0084EF30(LocaleCodePageObject_0084EED0 *object)
{
    LCID locale = object->locale;
    char separator[4];
    GetLocaleInfoA(locale, 0x1e, separator, 4);
    __ConvertFromACP(separator, 4, object->codePage);
    {
        char *format = locale_format_0084EF30;
        strcpy(format, "%H");
        strcat(format, separator);
        strcat(format, "%M");
        strcat(format, separator);
        strcat(format, "%S %p");
        return format;
    }
}

// Rva00850560 (retail 0x000236F0, 159B): locale long-date/time formatter.
// The BFME1 donor supplies the operation order; retail proves its locale type,
// conversion calls, buffer addresses and appended separator. The output is
// the existing FndLang storage at its retail address.
extern char __FndLang[];
extern char *Rva0084ED20Tail(LocaleCodePageObject_0084EED0 *object);
char *Rva00850560(LocaleCodePageObject_0084EED0 *object)
{
    LCID locale = object->locale;
    GetLocaleInfoA(locale, 0x20, locale_buffer_0084ECE0, 0x104);
    {
        char *buffer = locale_buffer_0084ECE0;
        __ConvertFromACP(buffer, 0x50, object->codePage);
        strcpy(__FndLang, Rva0084DE40Tail(buffer));
        strcat(__FndLang, " ");
        strcat(__FndLang, Rva0084ED20Tail(object));
        return __FndLang;
    }
}

// Rva008504C0 (retail 0x00023650, 159B): locale long-date/time formatter,
// twin of Rva00850560 above. Same BFME1 donor operation order
// (game/stlport/LocaleCodePageQueries.c Rva008504C0); retail proves locale
// type 0x1f, input buffer locale_buffer_0084ECA0 and output FndLCID storage.
// Caller 0x000195A6 in stlport_X4TimeFacets _Init_timeinfo. LINK leaf.
extern char __FndLCID[];
char *Rva008504C0(LocaleCodePageObject_0084EED0 *object)
{
    LCID locale = object->locale;
    GetLocaleInfoA(locale, 0x1f, locale_buffer_0084ECA0, 0x104);
    {
        char *buffer = locale_buffer_0084ECA0;
        __ConvertFromACP(buffer, 0x50, object->codePage);
        strcpy(__FndLCID, Rva0084DE40Tail(buffer));
        strcat(__FndLCID, " ");
        strcat(__FndLCID, Rva0084ED20Tail(object));
        return __FndLCID;
    }
}

/* BFME1 donor: game/stlport/LocaleCodePageQueries.c at 10af19f44a.
 * BFME2 evidence: unique 420-byte placement at RVA 0x00021EB0; the return
 * ends the 308-byte instruction stream and switch tables fill the rest.
 * GetLocaleInfoA type 0x1003 uses retail's 0x104 count and 80-byte local;
 * the following worker converts the locale pattern to strftime directives.
 * The locale object layout and helper name are donor facts. Retail proves
 * the same field accesses, imports, branches and separate output buffer. */
extern char locale_format_0084ED20[];
char *Rva0084ED20Tail(LocaleCodePageObject_0084EED0 *object)
{
    char format[80];
    char *source;
    char *out;
    GetLocaleInfoA(object->locale, 0x1003, format, 0x104);
    __ConvertFromACP(format, 80, object->codePage);
    source = format;
    out = locale_format_0084ED20;
    while (*source) {
        switch (*source) {
        case 'h':
            *out++ = '%';
            if (source[1] == 'h') { *out++ = 'I'; ++source; }
            else { *out++ = '#'; *out++ = 'I'; }
            break;
        case 'H':
            *out++ = '%';
            if (source[1] == 'H') { *out++ = 'H'; ++source; }
            else { *out++ = '#'; *out++ = 'H'; }
            break;
        case 'm':
            *out++ = '%';
            if (source[1] == 'm') { *out++ = 'M'; ++source; }
            else { *out++ = '#'; *out++ = 'M'; }
            break;
        case 's':
            *out++ = '%';
            if (source[1] == 's') { *out++ = 'S'; ++source; }
            else { *out++ = '#'; *out++ = 'S'; }
            break;
        case 't':
            if (source[1] == 't') ++source;
            *out++ = '%'; *out++ = 'p';
            break;
        case '%':
            *out++ = '%'; *out++ = '%';
            break;
        case '\'':
            ++source;
            while (*source != '\'') {
                if (!*source) goto done;
                *out++ = *source++;
            }
            break;
        default:
            *out++ = *source;
        }
        if (!*source) break;
        ++source;
    }
done:
    *out = 0;
    return locale_format_0084ED20;
}

// Retail VA 0x00DDEFA8: zero-filled; covers the donor's 80-byte format bound.
char locale_format_0084EF30[0x50];
// Retail VA 0x00DDF3C8; its original declared capacity is unknown.
// Linked storage covers at most two output characters per input byte.
char locale_format_0084ED20[2 * 80 + 1];
