// cl: /MD
//
// ??0Rva005CD0FEElem@@QAE@PAVRva005CD1A9@@@Z, retail 0x005CD0DC, 34 bytes.
// Inner element ctor: parent pointer at +0, int at +4 (AND-zero under /O1),
// _List_base<BfmePod8> at +8 via the rowed base 0x0035C9A6. Total 0xC bytes
// matching the operator new(0xC) in the outer ctor 0x005CD167 which passes
// its own this (Rva005CD1A9 vtable 0x00874F60) as the sole caller at
// 0x005CD192. Element dtor pinned at 0x005CD0FE, deleting dtor rowed at
// 0x005CD131, guarded clear rowed at 0x005CD14D. The one-byte allocator
// temporary reuses the dead arg slot ([ebp+0xB]) so no hovering local is
// needed; the user-defined empty allocator ctor avoids a stosb.
struct BfmePod8 { int a[2]; };

namespace _STL {
template<class _Tp>
class allocator
{
public:
	allocator() {}
};

template<class _Tp, class _Alloc>
class _List_base
{
public:
	_List_base(const _Alloc &a);
	~_List_base();

private:
	unsigned char m_data[4];
};
}

class Rva005CD1A9;

class Rva005CD0FEElem
{
public:
	Rva005CD0FEElem(Rva005CD1A9 *parent);

private:
	Rva005CD1A9 *m_parent; // +0
	int m_x; // +4
	_STL::_List_base<BfmePod8, _STL::allocator<BfmePod8> > m_list; // +8
};

Rva005CD0FEElem::Rva005CD0FEElem(Rva005CD1A9 *parent)
	: m_parent(parent), m_x(0), m_list(_STL::allocator<BfmePod8>())
{
}
