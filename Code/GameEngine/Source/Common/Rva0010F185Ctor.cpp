// cl: /Ireference/shims/bfme2_ascii /EHs /MD
// ??0Rva0010F185@@QAE@ABVRva0036CA00Str@@PBXABVAsciiString@@1@Z @0x0010F185 75B.
// Ctor with vtable g_00BCFAB8 via base Rva001164D3 plus StringBase at +0x10.
// Base Rva001164D3 from Rva001164D3Ctor plus StringBase shared header.
// Callees rowed 0x001164D3 0x000365F0. Caller 0x0010F9B4.
#include "ascii_string.h"
class Rva0036CA00Str {
    void *m_item;
public:
    __declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str &other);
    ~Rva0036CA00Str();
};
struct CountBase {
    volatile int m_count;
    __forceinline CountBase() : m_count(0) {}
    virtual void dummy();
};
class Rva001164D3 : public CountBase {
public:
    Rva001164D3(const Rva0036CA00Str &s);
private:
    Rva0036CA00Str m_str;
};
extern const void *const g_00BCFAB8[];
class Rva0010F185 : public Rva001164D3 {
public:
    Rva0010F185(const Rva0036CA00Str &a1, void const *a2, const AsciiString &a3, void const *a4);
private:
    void const *m_0C;
    AsciiString m_s10;
    void const *m_14;
};

Rva0010F185::Rva0010F185(const Rva0036CA00Str &a1, void const *a2, const AsciiString &a3, void const *a4)
    : Rva001164D3(a1), m_0C(a2), m_s10(a3), m_14(a4)
{
}
