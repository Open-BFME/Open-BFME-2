// cl: /O1 /MD
// Assignment chain 001F9CCA .. 001FC231 (seven 41B bodies). Each operator=
// assigns the first base through the rowed Rva001F41CDAssign.cpp operator=
// at 0x001F41CD then the second base at +4 through the next link (the
// null-preserving source+4 conversion proves the second base). Second-base
// callees by REL32: 001F9CCA -> 001F8CC2 (unrowed vector-holder assign, pinned);
// 001FA676 -> 001F9CCA; 001FB8BB -> 001FA676; 001FBA5B -> 001FB8BB; 001FBBF6
// -> 001FBA5B; 001FBF9D -> 001FBBF6; 001FC231 -> 001FBF9D; 001FC404 -> 001FC231. These mirror the
// Rva001F8BE8DtorChain.cpp destructor chain; original class names are unknown
// so address-derived Rva names are used.
struct Rva001F41CDHelper;
class Rva001F41CD {
public:
    Rva001F41CDHelper *m_ptr;
    Rva001F41CD &operator=(const Rva001F41CD &other);
};
class Rva001F8CC2 {
public:
    Rva001F8CC2 &operator=(const Rva001F8CC2 &other);
};
class Rva001F9CCA : public Rva001F41CD, public Rva001F8CC2 {
public:
    Rva001F9CCA &operator=(const Rva001F9CCA &other);
};
Rva001F9CCA &Rva001F9CCA::operator=(const Rva001F9CCA &other)
{
    Rva001F41CD::operator=(other);
    Rva001F8CC2::operator=(other);
    return *this;
}
class Rva001FA676 : public Rva001F41CD, public Rva001F9CCA {
public:
    Rva001FA676 &operator=(const Rva001FA676 &other);
};
Rva001FA676 &Rva001FA676::operator=(const Rva001FA676 &other)
{
    Rva001F41CD::operator=(other);
    Rva001F9CCA::operator=(other);
    return *this;
}
class Rva001FB8BB : public Rva001F41CD, public Rva001FA676 {
public:
    Rva001FB8BB &operator=(const Rva001FB8BB &other);
};
Rva001FB8BB &Rva001FB8BB::operator=(const Rva001FB8BB &other)
{
    Rva001F41CD::operator=(other);
    Rva001FA676::operator=(other);
    return *this;
}
class Rva001FBA5B : public Rva001F41CD, public Rva001FB8BB {
public:
    Rva001FBA5B &operator=(const Rva001FBA5B &other);
};
Rva001FBA5B &Rva001FBA5B::operator=(const Rva001FBA5B &other)
{
    Rva001F41CD::operator=(other);
    Rva001FB8BB::operator=(other);
    return *this;
}
class Rva001FBBF6 : public Rva001F41CD, public Rva001FBA5B {
public:
    Rva001FBBF6 &operator=(const Rva001FBBF6 &other);
};
Rva001FBBF6 &Rva001FBBF6::operator=(const Rva001FBBF6 &other)
{
    Rva001F41CD::operator=(other);
    Rva001FBA5B::operator=(other);
    return *this;
}
class Rva001FBF9D : public Rva001F41CD, public Rva001FBBF6 {
public:
    Rva001FBF9D &operator=(const Rva001FBF9D &other);
};
Rva001FBF9D &Rva001FBF9D::operator=(const Rva001FBF9D &other)
{
    Rva001F41CD::operator=(other);
    Rva001FBBF6::operator=(other);
    return *this;
}
class Rva001FC231 : public Rva001F41CD, public Rva001FBF9D {
public:
    Rva001FC231 &operator=(const Rva001FC231 &other);
};
Rva001FC231 &Rva001FC231::operator=(const Rva001FC231 &other)
{
    Rva001F41CD::operator=(other);
    Rva001FBF9D::operator=(other);
    return *this;
}
// Top link: retail pins this address as FXParticleSystem::ParticleSystemTemplateTail.
namespace FXParticleSystem
{
class ParticleSystemTemplateTail : public Rva001F41CD, public Rva001FC231 {
public:
    ParticleSystemTemplateTail &operator=(const ParticleSystemTemplateTail &other);
};
ParticleSystemTemplateTail &ParticleSystemTemplateTail::operator=(const ParticleSystemTemplateTail &other)
{
    Rva001F41CD::operator=(other);
    Rva001FC231::operator=(other);
    return *this;
}
} // namespace FXParticleSystem
