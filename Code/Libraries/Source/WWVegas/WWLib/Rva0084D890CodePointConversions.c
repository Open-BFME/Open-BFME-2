// cl: /MD /D_STLP_USE_STATIC_LIB
// platformsdk
// stlport46

#include <windows.h>

typedef struct Rva0084D890CodePage
{
    unsigned long locale;
    unsigned int codePage;
} Rva0084D890CodePage;

WCHAR _Locale_btowc(Rva0084D890CodePage *locale, int character)
{
    WCHAR converted;
    if (character == -1)
        return (WCHAR)-1;
    MultiByteToWideChar(locale->codePage, 1, (const char *)&character, 1, &converted, 1);
    return converted;
}

int _Locale_wctob(Rva0084D890CodePage *locale, WCHAR character)
{
    char converted;
    int result = WideCharToMultiByte(locale->codePage, 0x240,
        &character, 1, &converted, 1, 0, 0);
    if (!result)
        return 0xffff;
    return (signed char)converted;
}

// Retail 0x00020AC0 is named by address: the BFME1 Rva0084D7F0 donor is
// ICF-folded across two BFME1 addresses, so its symbol is not target identity.
// Target bytes read the first dword of the input as LCMapStringW's LCID,
// apply flags 0x200 to the one-WCHAR source, and return the output word.
WCHAR _Locale_wchar_toupper(Rva0084D890CodePage *owner, int character)
{
    WCHAR converted;
    LCMapStringW(owner->locale, 0x200,
        (const WCHAR *)&character, 1, &converted, 1);
    return converted;
}

/* BFME2 0x00020E30; Open-BFME-1 5cae4bdff Rva0084DB70 (BFME1 0x0084DB70), written
   against this file's code-page record: the LCID is its first dword. */
int _Locale_strwxfrm(Rva0084D890CodePage *owner, WCHAR *to, int count,
    const WCHAR *from, int fromCount)
{
    return LCMapStringW(owner->locale, 0x400, from, fromCount, to, count);
}
