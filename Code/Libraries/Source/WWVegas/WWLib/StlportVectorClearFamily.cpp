// cl: /O1 /G7 /arch:SSE /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector<T>::clear() - erase(begin(), end()) - for element
// types whose 51-byte range erase is already rowed and whose 11-byte clear
// sits unclaimed in retail. Each erase is declared as a specialization so the
// clear calls retail's out-of-line copy instead of expanding it, as
// StlportFixedObject60Vector.cpp does for its clear (0x000BCFB8, the skeleton
// twin of every body here). Element types are the incomplete code-generation
// views their erase rows already spell; no layout is claimed.
//
//   clear       erase       element
//   0x00351BC5  0x002A133B  Gen_p12pod            (Rva007D85C0FilterShutdown.cpp)
//   0x00475BDD  0x004758F4  Rva004758F4Element    (StlportVectorEraseRangeFamily.cpp)
//   0x004F8DC9  0x004F89A8  Rva004F6352           (stlport_rva004f6352_sort.cpp)
//   0x00501A00  0x0050126C  Rva00501E3FElement    (LocomotorSetMapThunks.cpp)
//   0x003F1D18  0x00532803  ParticleSystemID      (BoneFXUpdate_eraseParticleSystemID.cpp)
#include <vector>

struct TreeHintRef00217D4C;
struct Gen_p12pod;
struct Rva004758F4Element;
struct Rva004F6352;
struct Rva00501E3FElement;
enum ParticleSystemID { INVALID_PARTICLE_SYSTEM_ID = 0 };

namespace _STL {
template <> TreeHintRef00217D4C *vector<TreeHintRef00217D4C>::erase(TreeHintRef00217D4C *, TreeHintRef00217D4C *);
template <> Gen_p12pod *vector<Gen_p12pod>::erase(Gen_p12pod *, Gen_p12pod *);
template <> Rva004758F4Element *vector<Rva004758F4Element>::erase(Rva004758F4Element *, Rva004758F4Element *);
template <> Rva004F6352 *vector<Rva004F6352>::erase(Rva004F6352 *, Rva004F6352 *);
template <> Rva00501E3FElement *vector<Rva00501E3FElement>::erase(Rva00501E3FElement *, Rva00501E3FElement *);
template <> ParticleSystemID *vector<ParticleSystemID>::erase(ParticleSystemID *, ParticleSystemID *);
}

template void _STL::vector<Gen_p12pod>::clear();
template void _STL::vector<Rva004758F4Element>::clear();
template void _STL::vector<Rva004F6352>::clear();
template void _STL::vector<Rva00501E3FElement>::clear();
template void _STL::vector<ParticleSystemID>::clear();

// 0x004C3F40 (8B): a member push_back over a vector embedded at +0x7C
// (add ecx, 0x7C; jmp vector<Rva004C3F09Element>::push_back 0x004C3F09, the
// element reference passed through); the member-forward shape of
// ~PlayerPosition 0x0022D920. The owner is not recovered (no direct
// caller), so the view is address-named.
struct Rva004C3F09Element;
namespace _STL {
template <> void vector<Rva004C3F09Element>::push_back(const Rva004C3F09Element &);
}
class Rva004C3F40
{
public:
	void rva004C3F40(const Rva004C3F09Element &element);
private:
	char m_pad00[0x7C];
	_STL::vector<Rva004C3F09Element> m_7C;
};
void Rva004C3F40::rva004C3F40(const Rva004C3F09Element &element)
{
	m_7C.push_back(element);
}

// The independent entry 0x004F8871 delegates its first two pointer fields to
// the same range-erase body as vector<TreeHintRef00217D4C>::clear at 0x002B8134.
// Keep an address-derived owner: the shared bytes do not prove the original
// class or template instantiation behind this second entry.
class Rva004F8871
{
public:
    void rva004F8871();
private:
    TreeHintRef00217D4C *m_begin;
    TreeHintRef00217D4C *m_end;
};

void Rva004F8871::rva004F8871()
{
    reinterpret_cast<_STL::vector<TreeHintRef00217D4C> *>(this)->erase(m_begin, m_end);
}
