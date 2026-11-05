// cl: /DNDEBUG /MD /D_CRTIMP=
// EA Apt comparisons reconstructed from target operations using the existing
// EAStringCFind layout. Original identities/const signatures: Godfather QA PDB.
// Target stores a representation pointer at +0 and characters at rep+8.
// Original target source family: Apt/string/EAString.cpp (nearby Find assert).
// No confirmed callers for these retained bodies; reachability is unproven.
// Evidence: reverse/godfather_disk_evidence.json, eastring_comparisons.
#include <string.h>
#pragma intrinsic(strcmp)
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
#include "../EAStringC.h"
// ??MEAStringC@@QBE_NABV0@@Z
bool EAStringC::operator<(const EAStringC &other) const
{
    if(data==other.data) return false;
    if(strcmp((reinterpret_cast<const char *>(data) + 8),(reinterpret_cast<const char *>(other.data) + 8))<0) return true;
    return false;
}
// ??NEAStringC@@QBE_NABV0@@Z
bool EAStringC::operator<=(const EAStringC &other) const
{
    if(data==other.data) return true;
    if(strcmp((reinterpret_cast<const char *>(data) + 8),(reinterpret_cast<const char *>(other.data) + 8))<=0) return true;
    return false;
}
// ??MEAStringC@@QBE_NPBD@Z
bool EAStringC::operator<(const char *other) const { return strcmp((reinterpret_cast<const char *>(data) + 8),other)<0; }
// ??NEAStringC@@QBE_NPBD@Z
bool EAStringC::operator<=(const char *other) const { return strcmp((reinterpret_cast<const char *>(data) + 8),other)<=0; }
// ??OEAStringC@@QBE_NPBD@Z
bool EAStringC::operator>(const char *other) const { return strcmp((reinterpret_cast<const char *>(data) + 8),other)>0; }
// ??PEAStringC@@QBE_NPBD@Z
bool EAStringC::operator>=(const char *other) const { return strcmp((reinterpret_cast<const char *>(data) + 8),other)>=0; }
// ?Compare@EAStringC@@QBEHABV1@@Z
int EAStringC::Compare(const EAStringC &other) const
{
    if(data==other.data) return 0;
    return strcmp((reinterpret_cast<const char *>(data) + 8),(reinterpret_cast<const char *>(other.data) + 8));
}
// ??OEAStringC@@QBE_NABV0@@Z, retail 0x006D31F0 (18B). Gap body between the
// rowed operator<= 0x006D3190 and the next unit: forwards its argument to that
// operator<= and negates the bool (neg/sbb/inc). The spelling is the natural
// counterpart of the Godfather-PDB comparison family (inference, not PDB).
bool EAStringC::operator>(const EAStringC &other) const
{
    return !(*this <= other);
}
// ??PEAStringC@@QBE_NABV0@@Z, retail 0x006D3210 (18B). Same shape over the
// rowed operator< 0x006D3130; spelling inferred as above.
bool EAStringC::operator>=(const EAStringC &other) const
{
    return !(*this < other);
}
// ?Compare@EAStringC@@QBEHPBD@Z, retail 0x006D35A0 (107B). Gap body just
// before the rowed Compare(const EAStringC &) 0x006D3610: asserts the text is
// non-null (EAString.inl line 0x412, retail strings) and returns the inline
// strcmp of the buffer against it. The C-string overload of the PDB Compare
// name is inferred from the identical int result and sibling placement.
int EAStringC::Compare(const char *text) const
{
    if (!(text != 0)) {
        g_bfmeAptAssertAtE17734("pStrText != NULL", ".\\string\\EAString.inl", 0x412);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    return strcmp((reinterpret_cast<const char *>(data) + 8),text);
}
// ?rva006D3670@EAStringC@@QBEHPBD@Z, retail 0x006D3670 (66B). Case-insensitive
// counterpart: same non-null assert (line 0x447), then the rowed _strcmpi
// thunk 0x00629A2A over the buffer; address name, original spelling unknown.
int EAStringC::rva006D3670(const char *text) const
{
    if (!(text != 0)) {
        g_bfmeAptAssertAtE17734("pStrText != NULL", ".\\string\\EAString.inl", 0x447);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    return _strcmpi((reinterpret_cast<const char *>(data) + 8),text);
}
