// cl: /EHsc /MD
//
// ??0Rva005CD1A9@@QAE@XZ, retail 0x005CD167, 66 bytes.
// Outer default ctor (vtable 0x00874F60): allocates the 0xC-byte inner
// element with operator new 0x0002FDA0 and constructs it with the rowed
// inner ctor 0x005CD0DC passing its own this, storing to +4 (null on
// alloc failure). Single-state EH via __EH_prolog guards the new'd memory.
// Sole inner caller at 0x005CD192; outer callers at 0x0057624E 0x00576E13
// 0x005776C9. Dtor rowed at 0x005CD1A9, deleting dtor at 0x005CD1B7, clear
// at 0x005CD14D. Inner layout (parent +0 int +4 list +8) gives sizeof 0xC.
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

class Rva005CD1A9
{
public:
	Rva005CD1A9();
	virtual ~Rva005CD1A9();

private:
	Rva005CD0FEElem *m_elem; // +4
	int m_pad; // +8
};

Rva005CD1A9::Rva005CD1A9()
{
	m_elem = new Rva005CD0FEElem(this);
}
