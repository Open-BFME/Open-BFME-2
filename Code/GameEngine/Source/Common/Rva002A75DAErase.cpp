// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Single-element vector erase at retail 0x002A75DA (55 bytes). Dedicated TU.
//
// Retail shifts the tail down via the rowed 4-arg _STL::__copy_ptrs for
// 12-byte BfmeE12 at 0x000B6569 when position+1 != finish, pops finish by one
// element, destroys the popped slot via the rowed dtor ??1Rva002A73B8 at
// 0x002A73B8, and returns position. Shape-identical to the rowed
// BfmeStringRecord erase at 0x00357CA2 (55B ret 4), whose TU supplies the
// self-contained _STL shim and the // cl: line copied above. Sole caller is
// 0x002A763B. The real element type is unproven beyond its 12-byte stride,
// so the ledger name below claims only the address plus the witnessed erase
// shape; BfmeE12 here is the tree's conventional 12-byte stand-in. The
// finish member is pointer-to-const so template deduction yields the rowed
// const-first-arg __copy_ptrs specialization with no explicit template
// arguments (explicit arguments force a value-initialized tag temporary and
// change codegen).
//
// The call's tag is the vendored-4.5.3 const __false_type& spelling (the
// caller pushes an address), while the rowed 29B forwarder at 0x000B6569 is
// named with the by-value tag. Both spellings compile to the same forwarder
// bytes under that row's flags (checked with a const& forwarder over
// const BfmeE12* -> BfmeE12*: byte-identical at 0x000B6569), so the const&
// name is pinned there as a folded alias, as the BfmePod12 and Gen_p12pod
// const& forwarders already are. Tricks the body needs: inline end() accessor
// (forces finish into eax), a named uninitialized tag local (a
// __false_type() temporary is value-initialized with stosb and breaks the
// registers), static_cast rather than explicit template arguments for the
// const-first-arg deduction.

#pragma comment(linker, "/alternatename:??$__copy_ptrs@PBUBfmeE12@@PAU1@@_STL@@YAPAUBfmeE12@@PBU1@0PAU1@ABU__false_type@0@@Z=??$__copy_ptrs@PBUBfmeE12@@PAU1@@_STL@@YAPAUBfmeE12@@PBU1@0PAU1@U__false_type@0@@Z")

struct BfmeE12
{
	float x, y, z;
};

class Rva002A73B8
{
public:
	~Rva002A73B8();
};

namespace _STL
{

struct __false_type
{
};

template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result,
	const __false_type &tag);

}

class Rva002A75DA
{
public:
	BfmeE12 *erase(BfmeE12 *position);
	const BfmeE12 *end() { return m_finish; }

private:
	BfmeE12 *m_start;
	const BfmeE12 *m_finish; // +0x04
	BfmeE12 *m_endOfStorage;
};

// ?erase@Rva002A75DA@@QAEPAUBfmeE12@@PAU2@@Z @0x002A75DA
BfmeE12 *Rva002A75DA::erase(BfmeE12 *position)
{
	_STL::__false_type tag;
	if (position + 1 != end())
		_STL::__copy_ptrs(static_cast<const BfmeE12 *>(position + 1), m_finish, position, tag);
	--m_finish;
	((Rva002A73B8 *)m_finish)->~Rva002A73B8();
	return position;
}
