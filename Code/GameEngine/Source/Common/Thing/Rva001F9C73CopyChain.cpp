// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Copy-constructor chain 001F9C73 .. 001FC3BF (eight 69B bodies), the copy
// counterpart of Rva001F9CCAAssignChain.cpp. Each link copy-constructs the
// first base holder through 0x001F41AF (rowed as the clone-assign
// ??4Rva001F41AF; it is called on raw storage and returns this, so the copy
// ctor spelling is pinned to the same address) then enters EH state 0 and
// copy-constructs the second base at +4 from the null-preserving source+4.
// Second-base callees by REL32: 001F9C73 -> rowed Rva001F8C5B vector ctor;
// 001FA631 -> 001F9C73; 001FB864 -> 001FA631; 001FBA00 -> 001FB864; 001FBB9F
// -> 001FBA00; 001FBEF2 -> 001FBB9F; 001FC19B -> 001FBEF2; 001FC3BF ->
// 001FC19B (called by the ParticleSystemTemplate copy ctor 0x001FCE6B for its
// +0xA4 tail). Original names unknown so address-derived Rva names are used.
#include <vector>

class Rva001F4206
{
public:
    void rva001F4206();
};
class Rva001F41AF
{
public:
    void *m_ptr;
    Rva001F41AF(const Rva001F41AF &other);
    ~Rva001F41AF();
};
// ??1Rva001F41AF@@QAE@XZ present-unmatched
inline Rva001F41AF::~Rva001F41AF()
{
    ((Rva001F4206 *)this)->rva001F4206();
}
class Rva001F8C5B
{
public:
    Rva001F8C5B(const _STL::vector<void*> &src);
private:
    void *m_vec[3];
};
class Rva001F9C73 : public Rva001F41AF, public Rva001F8C5B
{
public:
    Rva001F9C73(const Rva001F9C73 &other);
};
Rva001F9C73::Rva001F9C73(const Rva001F9C73 &other) :
    Rva001F41AF(other),
    Rva001F8C5B(*(const _STL::vector<void*> *)(const Rva001F8C5B *)&other)
{
}
class Rva001FA631 : public Rva001F41AF, public Rva001F9C73
{
public:
    Rva001FA631(const Rva001FA631 &other);
};
Rva001FA631::Rva001FA631(const Rva001FA631 &other) :
    Rva001F41AF(other),
    Rva001F9C73(other)
{
}
class Rva001FB864 : public Rva001F41AF, public Rva001FA631
{
public:
    Rva001FB864(const Rva001FB864 &other);
};
Rva001FB864::Rva001FB864(const Rva001FB864 &other) :
    Rva001F41AF(other),
    Rva001FA631(other)
{
}
class Rva001FBA00 : public Rva001F41AF, public Rva001FB864
{
public:
    Rva001FBA00(const Rva001FBA00 &other);
};
Rva001FBA00::Rva001FBA00(const Rva001FBA00 &other) :
    Rva001F41AF(other),
    Rva001FB864(other)
{
}
class Rva001FBB9F : public Rva001F41AF, public Rva001FBA00
{
public:
    Rva001FBB9F(const Rva001FBB9F &other);
};
Rva001FBB9F::Rva001FBB9F(const Rva001FBB9F &other) :
    Rva001F41AF(other),
    Rva001FBA00(other)
{
}
class Rva001FBEF2 : public Rva001F41AF, public Rva001FBB9F
{
public:
    Rva001FBEF2(const Rva001FBEF2 &other);
};
Rva001FBEF2::Rva001FBEF2(const Rva001FBEF2 &other) :
    Rva001F41AF(other),
    Rva001FBB9F(other)
{
}
class Rva001FC19B : public Rva001F41AF, public Rva001FBEF2
{
public:
    Rva001FC19B(const Rva001FC19B &other);
};
Rva001FC19B::Rva001FC19B(const Rva001FC19B &other) :
    Rva001F41AF(other),
    Rva001FBEF2(other)
{
}
// Top link: retail pins this address as FXParticleSystem::ParticleSystemTemplateTail.
namespace FXParticleSystem
{
class ParticleSystemTemplateTail : public Rva001F41AF, public Rva001FC19B
{
public:
    ParticleSystemTemplateTail(const ParticleSystemTemplateTail &other);
};
ParticleSystemTemplateTail::ParticleSystemTemplateTail(const ParticleSystemTemplateTail &other) :
    Rva001F41AF(other),
    Rva001FC19B(other)
{
}
} // namespace FXParticleSystem

// 0x001F41AF is rowed as ??4Rva001F41AF (clone-assign); the copy-ctor spelling
// above calls the same address on raw storage, so alias it to the row.
#pragma comment(linker, "/alternatename:??0Rva001F41AF@@QAE@ABV0@@Z=??4Rva001F41AF@@QAEAAV0@ABV0@@Z")
