// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// 0x00055463 (5B), unreferenced: erase(key) of a holder of the audio-request
// pointer hash set at +0, a tail jump into the rowed hashtable erase
// (0x00054C93, MilesAudioManager.cpp). The declaration-only specialisation
// keeps that call out of line; functor and element spellings follow the
// rowed callee's mangled name. Owner address-derived.
#include <hash_set>

struct Rva00051107AudioRequest;
#include "../../../../GameEngine/Include/Common/Rva00051B89Hash.h"
struct Rva00050E1CEqualTo { bool operator()(Rva00051107AudioRequest *, Rva00051107AudioRequest *) const; };

typedef _STL::hashtable<Rva00051107AudioRequest *, Rva00051107AudioRequest *, Rva00051B89Hash,
	_STL::_Identity<Rva00051107AudioRequest *>, Rva00050E1CEqualTo,
	_STL::allocator<Rva00051107AudioRequest *> > Rva00055463Table;

namespace _STL {
template <> Rva00055463Table::size_type Rva00055463Table::erase(Rva00051107AudioRequest *const &key);
}

class Rva00055463
{
public:
	unsigned int rva00055463(Rva00051107AudioRequest *const &key);
private:
	Rva00055463Table m_00;
};

unsigned int Rva00055463::rva00055463(Rva00051107AudioRequest *const &key)
{
	return m_00.erase(key);
}
