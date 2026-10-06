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
