// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Single-element vector erase @0x002606AF, 55B; 8-byte element.
// Masked twin of Rva0040DC1F erase.

// stlport
#include <utility>

struct Rva002606AFElem { char m_pad[8]; };
class Rva002606AFDtor { public: ~Rva002606AFDtor(); };

namespace _STL {
template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result, const __false_type &tag);
}

class Rva002606AF
{
public:
	Rva002606AFElem *erase(Rva002606AFElem*);
	const Rva002606AFElem *end() { return m_finish; }
private:
	Rva002606AFElem *m_start; // +0x00
	const Rva002606AFElem *m_finish; // +0x04
	Rva002606AFElem *m_endOfStorage; // +0x08
};

Rva002606AFElem *Rva002606AF::erase(Rva002606AFElem *position)
{
	_STL::__false_type tag;
	if (position + 1 != end())
		_STL::__copy_ptrs(static_cast<const Rva002606AFElem *>(position + 1), m_finish, position, tag);
	--m_finish;
	((Rva002606AFDtor *)m_finish)->~Rva002606AFDtor();
	return position;
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x005B804E reads ??1?$StringBase@G@@AAE@XZ
#pragma comment(linker, "/alternatename:??1Rva002606AFDtor@@QAE@XZ=??1?$StringBase@G@@AAE@XZ")
//   0x00260647 reads ?Rva00260647Copy@@YAPAUBfmeStringRecord002602A6@@PAU1@00@Z
#pragma comment(linker, "/alternatename:??$__copy_ptrs@PBURva002606AFElem@@PAU1@@_STL@@YAPAURva002606AFElem@@PBU1@0PAU1@ABU__false_type@0@@Z=?Rva00260647Copy@@YAPAUBfmeStringRecord002602A6@@PAU1@00@Z")
