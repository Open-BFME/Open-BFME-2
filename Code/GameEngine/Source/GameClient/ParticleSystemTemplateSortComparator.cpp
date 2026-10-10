// cl: /EHsc
//
// ??RRva00204BB8@@QBE_NHH@Z @0x00204BB8 94B: ParticleSystemTemplate name less-than for STL sort.
// Evidence: BFME1 donor Q4Sort0034BFC0Comparator.cpp (same right-hand-first getName plus compareNoCase shape);
// callees getName 0x00002600 and compareNoCase 0x00006A00 and releaseBuffer 0x00036410 all rowed;
// callers are STL sort helpers 0x002057D5 and 0x00205840 and 0x00206D33 and 0x00209A62 passing comparator as this.

template <typename T>
class StringBase
{
    friend class AsciiString;
    StringBase(const StringBase<T> &that);
    void releaseBuffer();
    __forceinline ~StringBase() { releaseBuffer(); }
    void *m_data;
public:
    __declspec(nothrow) int compareNoCase(const StringBase<T> &that) const;
};

class AsciiString : public StringBase<char>
{
public:
    __forceinline ~AsciiString() {}
};

namespace FXParticleSystem
{

class ParticleSystemTemplate
{
public:
    AsciiString getName() const;
};

}

struct Rva00204BB8
{
    bool operator()(int a, int b) const;
};

bool Rva00204BB8::operator()(int a, int b) const
{
    return ((const FXParticleSystem::ParticleSystemTemplate *)a)->getName().compareNoCase(
        ((const FXParticleSystem::ParticleSystemTemplate *)b)->getName()) < 0;
}

// Complete native accessor family 0x00204B6F..0x00204BB8: four RET4 bodies.
// Each own instruction stream proves the receiver+38 pointer and 14h record
// stride. Field0 is read as a dword; Field8 is addressed; pointer10 is
// loaded and advanced by four bytes. The Ref argument index is at +4.
// Donor field scalar types express observed widths; no semantic target
// class identity is claimed. Independent address-owned receiver views
// avoid inferring one owner merely from similar shapes or adjacency.
// This existing home is selected by the repository nearest-row policy.
// BF1 34f59164 Common/Bfme/Rva0033B310Containers.cpp is the semantic donor.
// Each target address owns its type until caller evidence unifies owners.
struct Rva00204B6FIndex { int unknown0; int index; };
struct Rva00204B6FRecord {
    int field0, field4, field8, fieldC;
    int *pointer10;
};
class Rva00204B6FOwner {
public: int *elementField8(Rva00204B6FIndex *reference);
private: char unknown[0x38]; Rva00204B6FRecord *items;
};
int *Rva00204B6FOwner::elementField8(Rva00204B6FIndex *reference)
{ return &items[reference->index].field8; }
class Rva00204B83Owner {
public: int elementField0(int index);
private: char unknown[0x38]; Rva00204B6FRecord *items;
};
int Rva00204B83Owner::elementField0(int index)
{ return items[index].field0; }
class Rva00204B93Owner {
public: int *elementPointer10Plus4(int index);
private: char unknown[0x38]; Rva00204B6FRecord *items;
};
int *Rva00204B93Owner::elementPointer10Plus4(int index)
{ return items[index].pointer10 + 1; }
class Rva00204BA7Owner {
public: int *elementField8(int index);
private: char unknown[0x38]; Rva00204B6FRecord *items;
};
int *Rva00204BA7Owner::elementField8(int index)
{ return &items[index].field8; }

// BFME1 575ba2b04743f190f069805fbdc59936123c45da, WWLib
// Deque20ByteElement.cpp supplied the STLport copy_backward forwarding lead.
// Native 0x00204B6A..0x00204B6F is exactly a tail jump to the independently
// matched 38B __copy_trivial_backward (0x00620840). The preceding matched
// deleting destructor ends at 0x00204B6A and the next accessor starts at
// 0x00204B6F. Payload type and original wrapper spelling are not recovered;
// use only the provider's established three-pointer ABI, without its donor
// deque element name or any target payload-layout claim.
namespace _STL {
    void * __cdecl __copy_trivial_backward(const void *, const void *, void *);
}
void * __cdecl rva00204B6ACopyBackward(const void *first, const void *last, void *result)
{
    return _STL::__copy_trivial_backward(first, last, result);
}
