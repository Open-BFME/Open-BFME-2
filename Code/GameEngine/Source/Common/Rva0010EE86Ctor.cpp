// cl: /MD
// ??0Rva0010EE86@@QAE@ABVRva0036CA00Str@@@Z @0x0010EE86 24B. Derived ctor passes const Rva0036CA00Str& to rowed base 0x001164D3 then stores vtable 0x00BCFA5C.
// Evidence: retail push esi push [esp+8] mov esi ecx call base mov [esi] vtable ret 4; siblings 0x0010EE4F 0x0010EE9E same shape same base; caller 0x0010FB29 in 0x0010FAEA.
#include "../../Include/Common/Rva0036CA00Str.h"
#include "../../Include/Common/CountBase.h"
class Rva001164D3 : public CountBase {
public:
    Rva001164D3(const Rva0036CA00Str &s);
    ~Rva001164D3();
private:
    Rva0036CA00Str m_str;
};
class Rva0010EE86 : public Rva001164D3 {
public:
    Rva0010EE86(const Rva0036CA00Str &s);
};
Rva0010EE86::Rva0010EE86(const Rva0036CA00Str &s) : Rva001164D3(s) {}
