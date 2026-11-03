// Target facts: copy constructor RVA 0x000A8C7C (31 bytes) copies the pointer at +0 and increments the pointee's count at +4 through IAT 0x00BBA214. Destructor RVA 0x0010F149 (12 bytes) loads that pointer, tests null and tail-calls Release_Ref at RVA 0x00050ED3. Neither body stores a vptr; this handle has no virtual functions. The copies at RVAs 0x00403087 and 0x00403093 have no intervening EH-state update, supporting the nonthrowing copy declaration.
// Target facts: RVA 0x004D9A4B constructs this handle at +0 and RVA 0x004D9A54 constructs the next member at +4; the copy loop at RVA 0x002393BC advances by four bytes. Its size is 4 with one pointer at +0 and no evidenced base. The table 0x00BCFB38 stored at RVA 0x001164E4 belongs to the enclosing Rva001164D3, whose handle is constructed at +8 (RVA 0x001164DA).
// Target facts: the empty result at RVA 0x0073F1A6 stores a null pointer at +0. The clear call at RVA 0x0050C45D targets RVA 0x00036410, the existing clear pin. Copy construction and destruction are declared out of line to retain the retail calls. m_item is a neutral opaque-pointer placeholder; the original class and member names are unknown.
#pragma once
#ifndef BFME2_RVA0036CA00STR_H
#define BFME2_RVA0036CA00STR_H

class OpaqueRefCounted;

class Rva0036CA00Str
{
public:
    Rva0036CA00Str() : m_item(0) {}
    __declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str &other);
    ~Rva0036CA00Str();
    void clear();

    OpaqueRefCounted *m_item;
};

#endif
