// ??0Rva001164D3@@QAE@ABVRva0036CA00Str@@@Z
// partial score=0.96 date=2026-10-03
// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// retail 0x001164D3, 34 bytes: vtable 0x00BCFB38, dword +4 zeroed, Str at +8
// copy-constructed. The +4 field belongs to a polymorphic base whose inlined
// ctor is scheduled after the member-address lea; the vfptr store follows it.
#include "../../Include/Common/Rva0036CA00Str.h"
#include "../../Include/Common/CountBase.h"
class Rva001164D3 : public CountBase {
public:
    Rva001164D3(const Rva0036CA00Str &s);
private:
    Rva0036CA00Str m_str;
};
Rva001164D3::Rva001164D3(const Rva0036CA00Str &s) : m_str(s) {}
