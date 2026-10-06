// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva0035149F@Rva0035149F@@QAEAAV1@ABV1@@Z, RVA 0x0035149F, 209 bytes.
// Vector assign of 12-byte PODs. Evidence: size/capacity via (finish-start)/12,
// grow path via rowed Rva000E016A 0x000E016A allocate+uninit_copy, free via
// rowed _free 0x00030830, steady path via rowed __copy_ptrs<BfmeE12>
// 0x000B6569, tail via rowed __uninitialized_copy<Coord3D> 0x00346C2D.
// Callers 0x00351606 0x003530B0 0x00353198 0x0036EE46. BfmeE12 is the tree's
// 12-byte stand-in; Coord3D casts select the rowed uninit_copy name.
#pragma comment(linker, "/alternatename:??$__copy_ptrs@PBUBfmeE12@@PAU1@@_STL@@YAPAUBfmeE12@@PBU1@0PAU1@ABU__false_type@0@@Z=??$__copy_ptrs@PBUBfmeE12@@PAU1@@_STL@@YAPAUBfmeE12@@PBU1@0PAU1@U__false_type@0@@Z")
struct BfmeE12
{
	float x, y, z;
};
struct Coord3D
{
	float x, y, z;
	Coord3D(const Coord3D &that);
};
class Rva000E016A
{
public:
	BfmeE12 *rva000E016A(unsigned int n, Coord3D *first, Coord3D *last);
};
extern "C" void __cdecl free(void *);
namespace _STL
{
struct __false_type
{
};
template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result, const __false_type &tag);
template <class InputIter, class ForwardIter>
ForwardIter __uninitialized_copy(InputIter first, InputIter last, ForwardIter result, const __false_type &tag);
}
class Rva0035149F
{
public:
	BfmeE12 *m_start;
	BfmeE12 *m_finish;
	BfmeE12 *m_end;
	Rva0035149F &rva0035149F(const Rva0035149F &other);
};
Rva0035149F &Rva0035149F::rva0035149F(const Rva0035149F &other)
{
	_STL::__false_type tag;
	if (&other == this)
		return *this;
	unsigned int n = (unsigned int)(other.m_finish - other.m_start);
	unsigned int cap = (unsigned int)(m_end - m_start);
	if (n > cap)
	{
		BfmeE12 *fresh = ((Rva000E016A *)this)->rva000E016A(n, (Coord3D *)other.m_start, (Coord3D *)other.m_finish);
		if (m_start)
			free(m_start);
		m_start = fresh;
		m_end = fresh + n;
	}
	else
	{
		unsigned int sz = (unsigned int)(m_finish - m_start);
		if (sz >= n)
		{
			_STL::__copy_ptrs(static_cast<const BfmeE12 *>(other.m_start), static_cast<const BfmeE12 *>(other.m_finish), m_start, tag);
		}
		else
		{
			_STL::__copy_ptrs(static_cast<const BfmeE12 *>(other.m_start), static_cast<const BfmeE12 *>(other.m_start + sz), m_start, tag);
			_STL::__uninitialized_copy((Coord3D *)(other.m_start + (m_finish - m_start)), (Coord3D *)other.m_finish, (Coord3D *)m_finish, tag);
		}
	}
	m_finish = m_start + n;
	return *this;
}

// ?rva00351759@Rva00351759@@QAEAAVRva0035149F@@ABV2@@Z @0x00351759 8B member-assign forwarder to rowed 0x0035149F.
// Retail: add ecx 0x3c / jmp 0x35149F.
// Target facts: __thiscall (this + const Rva0035149F&) -> Rva0035149F&; this+0x3c is the Rva0035149F member; tail return gives add+jmp at /O1.
// Callers: 0x00262F36 0x00264949 0x002649FB 0x0026BB19 0x0026BBE6 0x0026BCA2 0x0036986E 0x0036BC30 all pass this+1 arg; callees: rowed 0x0035149F vector assign.
// Precedent: tail return m_member.method gives add ecx N + jmp at /O1; honest Rva address-derived class.

class Rva00351759
{
public:
	char m_pad[0x3c];
	Rva0035149F m_vec;
	Rva0035149F &rva00351759(const Rva0035149F &other);
};
Rva0035149F &Rva00351759::rva00351759(const Rva0035149F &other)
{
	return m_vec.rva0035149F(other);
}
