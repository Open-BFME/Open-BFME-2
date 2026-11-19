// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva003F7BB4@Rva003F7BB4@@QAEXABURva003F7B22Element@@@Z @0x003F7BB4 8B
// Tail-jmp forwarder adding 0x2c then calling rowed vector push_back 0x003F7B22.
// Evidence: add ecx 0x2c plus jmp to rowed push_back; neighbours share Eva bucket TU; unblocks 0x004E0860 0x003F2150.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
// Suppress this TU's non-retail copy of ??$__uninitialized_fill_n@PAURva003F7B22Element@@IU1@@_STL@@YAPAURva003F7B22Element@@PAU1@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva003F7B22Element;
namespace _STL { template <> Rva003F7B22Element * __uninitialized_fill_n<Rva003F7B22Element *,unsigned int,Rva003F7B22Element>(Rva003F7B22Element *,unsigned int,Rva003F7B22Element const &,__false_type const &); }
// Suppress this TU's non-retail copy of ??$__uninitialized_copy@PAURva003F7B22Element@@PAU1@@_STL@@YAPAURva003F7B22Element@@PAU1@0:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> Rva003F7B22Element * __uninitialized_copy<Rva003F7B22Element *,Rva003F7B22Element *>(Rva003F7B22Element *,Rva003F7B22Element *,Rva003F7B22Element *,__false_type const &); }
// Suppress this TU's non-retail copy of ?push_back@?$vector@URva003F7B22Element@@V?$allocator@URva003F7B22Element@@@_STL@@@_STL@@Q:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void vector<Rva003F7B22Element,allocator<Rva003F7B22Element> >::push_back(Rva003F7B22Element const &); }
// Suppress this TU's non-retail copy of ?_M_insert_overflow@?$vector@URva003F7B22Element@@V?$allocator@URva003F7B22Element@@@_STL@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void vector<Rva003F7B22Element,allocator<Rva003F7B22Element> >::_M_insert_overflow(Rva003F7B22Element *,Rva003F7B22Element const &,__false_type const &,unsigned int,bool); }

struct Rva003F7B22Element { int a[1]; };

class Rva003F7BB4
{
public:
	void rva003F7BB4(const Rva003F7B22Element &e);
private:
	char m_pad[0x2c];
	_STL::vector<Rva003F7B22Element> m_vec;
};

void Rva003F7BB4::rva003F7BB4(const Rva003F7B22Element &e)
{
	m_vec.push_back(e);
}
