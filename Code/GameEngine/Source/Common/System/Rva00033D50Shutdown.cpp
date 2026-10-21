// cl: /Od /MD
//
// ?rva00033D50@GeneralAllocator@Allocator@EA@@QAE_NXZ @0x00033D50 309B.
// Retail compiled this allocator teardown without optimisation (an ebp frame
// that spills `this` to [ebp-0x10] and reloads it for every access), so the
// unit is /Od. Target evidence: under the +0x4E4 lock (rowed AddRef 0x30DD0)
// a set +0 flag is cleared; when the 0x30CB0 field bit is set the pinned
// 0x00033930 runs; every entry still linked at +0x4A8 off the +0x49C sentinel
// is handed to the pinned freeBlock 0x00033150 through the rowed 0x30AE0
// back-offset and the folded +8 adjust 0x00169660 (rowed as an STLport
// _S_left spelling); every descriptor linked at +0x464 off the +0x448
// sentinel is unlinked (0x00031660, a thiscall that ignores this) and
// released through the rowed 0x000316B0(node, true); +0x440 is reset to the
// 0x0066D7D0 lea getter (this+0x30), +0x468 and +0x46C cleared. Finally the
// lock is detached, released (0x30DF0) and deleted (0x317E0). Returns true.
// The PPMalloc method name and field meanings are not recovered.

struct Rva00030DD0Lock;
int Rva00030DD0AddRef(Rva00030DD0Lock *lock);
int Rva00030DF0Release(Rva00030DD0Lock *lock);
int Rva00030AE0Sub(int *pointer);
void Rva000317E0Delete(void *section);

namespace _STL
{
template <class T1, class T2> struct pair;
template <class T> struct _Select1st;
template <class T> struct less;
template <class T> class allocator;
template <class V> struct _Rb_tree_node;
template <class K, class V, class KoV, class C, class A> class _Rb_tree
{
protected:
	static _Rb_tree_node<V> *&_S_left(_Rb_tree_node<V> *x);
};
}

typedef _STL::pair<const int, int> Rva00033D50Value;
typedef _STL::_Rb_tree<int, Rva00033D50Value, _STL::_Select1st<Rva00033D50Value>,
	_STL::less<int>, _STL::allocator<Rva00033D50Value> > Rva00033D50Tree;
class Rva00033D50TreeAccess : public Rva00033D50Tree
{
public:
	using Rva00033D50Tree::_S_left;
};
typedef _STL::_Rb_tree_node<Rva00033D50Value> Rva00033D50Node;

class Rva00030CB0MaskedDwordField
{
public:
	int get() const;
};

class Rva00034C90
{
public:
	void rva00033930();
};


class Rva0066D7D0LeaField
{
public:
	void *get() const;
};

namespace EA
{
namespace Allocator
{
class GeneralAllocator
{
public:
	// memory_pool.cpp owns the native 0x00033150 free engine under this ABI.
	void rva00033150(const void *block);

	bool rva00033D50();
	void rva00031660(void *node);
	bool rva000316B0(void *node, bool release);

private:
	bool m_active;	// +0x000
	unsigned char m_pad001[0x440 - 0x001];
	void *m_440;
	unsigned char m_pad444[0x448 - 0x444];
	unsigned char m_448[0x1C];	// descriptor sentinel
	void *m_464;	// its first link
	unsigned int m_468;
	bool m_46C;
	unsigned char m_pad46D[0x49C - 0x46D];
	unsigned char m_49C[0xC];	// entry sentinel
	void *m_4A8;	// its first link
	unsigned char m_pad4AC[0x4E4 - 0x4AC];
	Rva00030DD0Lock *m_lock;	// +0x4E4
};

bool GeneralAllocator::rva00033D50()
{
	if (m_lock)
		Rva00030DD0AddRef(m_lock);
	if (m_active)
	{
		m_active = false;
		if (((Rva00030CB0MaskedDwordField *)this)->get())
			((Rva00034C90 *)this)->rva00033930();
		while (m_4A8 != m_49C)
		{
			int chunk = Rva00030AE0Sub((int *)m_4A8);
			reinterpret_cast<EA::Allocator::GeneralAllocator *>(this)->rva00033150(&Rva00033D50TreeAccess::_S_left((Rva00033D50Node *)chunk));
		}
		while (m_464 != m_448)
		{
			void *node = m_464;
			rva00031660(node);
			rva000316B0(node, true);
		}
		m_440 = ((Rva0066D7D0LeaField *)this)->get();
		m_468 = 0;
		m_46C = false;
	}
	if (m_lock)
	{
		Rva00030DD0Lock *lock = m_lock;
		m_lock = 0;
		Rva00030DF0Release(lock);
		Rva000317E0Delete(lock);
	}
	return true;
}
}
}
