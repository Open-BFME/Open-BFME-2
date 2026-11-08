// cl: /DNDEBUG /MD
// ??$_Construct@VRva0046267A@@V1@@_STL@@YAXPAVRva0046267A@@ABV1@@Z @0x00462D83 18B.
// _STL::_Construct<Rva0046267A> null-guarded placement-new copy over the 0x50-byte
// Contain record (int at +0 plus WeaponTemplateSetHead at +0x4 via rowed 0x45455).
// Calls the just-landed copy ctor 0x0046267A; nothrow shape stays frameless with
// test/je plus ret (no EH). Dedicated TU so the copy-ctor definition cannot inline.
// Evidence: single caller 0x004634BA (0x60-byte RB node alloc plus +0x10 construct)
// unblocks 0x004634BA; prev 0x00462D62 in StringContainerRecordCopyBFME2.
#include <stddef.h>

class Rva0046267A
{
public:
	Rva0046267A(const Rva0046267A &that);
};

namespace _STL
{

template <class T1, class T2>
void _Construct(T1 *p, const T2 &value);

template <>
void _Construct<Rva0046267A, Rva0046267A>(Rva0046267A *p, const Rva0046267A &value)
{
	if (p)
		p->Rva0046267A::Rva0046267A(value);
}

}
