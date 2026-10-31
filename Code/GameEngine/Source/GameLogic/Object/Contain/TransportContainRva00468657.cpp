// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// The map subscript 0x004650A0 is defined in this unit (noinline, the bytes of its own rowed
// row) because retail's compiler knew it does not keep the address of the key temporary:
// without the body visible the frame grows by four bytes (0x1c instead of 0x18).
// Target: 0x00468657..0x00468748 (242 bytes). The receiver is the
// secondary contain interface: its owner Object is at -0x18, its int-key
// string map at +0x1C, and slot 0xB0 returns four status words by value.
// The transport-family placement is a boundary/neighbour lead; neither the
// exact method name nor the status flag's semantic name is established.
// The mapped four-byte value uses the existing verified AsciiString view.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#undef _STLP_DEFAULT_CONSTRUCTED
#define _STLP_DEFAULT_CONSTRUCTED(T) T()
#include <map>
#include "ascii_string.h"

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

class Drawable
{
public:
	void rva0027656F(int ownerID, AsciiString bone);void setDrawableHidden(bool);
};

#include "../../../Common/Thing/thing.h"

class Object {public:int getID()const{return id;}char pad[0x74];int id;};

class Rva0055A88BDwordField
{
public:
	int get() const;
};

class Rva002716Holder
{
public:
	void Rva0027167FBroadcast(int id);
	void Rva002716D3Broadcast(int id);
	
};

// The hinted insertion 0x00464984 (rowed in Rva00464984.cpp). Its value temporary is built by
// the rowed pair<int, AsciiString> constructor 0x00523DB7 and torn down by 0x0029D7C2
// (add ecx,4 / jmp releaseBuffer, unwind funclet 0x0078ABF3).
class Rva00464984Iterator
{
public:
	Rva00464984Iterator(const Rva00464984Iterator &other) : m_node(other.m_node) {}
	void *m_node;
};
class Rva00464984Pair;
class Rva00464984
{
public:
	Rva00464984Iterator rva00464984(Rva00464984Iterator hint, const Rva00464984Pair &value);
};

typedef _STL::pair<const int, AsciiString> Rva004650A0Pair;
typedef _STL::map<int, AsciiString, _STL::less<int>, _STL::allocator<Rva004650A0Pair> > Rva004650A0Map;
class Rva004650A0 : public Rva004650A0Map
{
public:
	typedef Rva004650A0Map::iterator Iterator;
	typedef Rva004650A0Map::value_type Value;
	__declspec(noinline) AsciiString &rva004650A0(const int &key)
	{
		Iterator it = lower_bound(key);
		if (it == end() || key_comp()(key, (*it).first))
		{
			AsciiString empty;
			it = Iterator((_STL::_Rb_tree_node<Value> *)((Rva00464984 *)this)->rva00464984(
				*(Rva00464984Iterator *)&it, (const Rva00464984Pair &)_STL::pair<int, AsciiString>(key, empty)).m_node);
		}
		return (*it).second;
	}
};

struct ContainStatus468657 {unsigned char test(unsigned i)const{return static_cast<unsigned char>(words[i>>5]>>(i&31))&1;}unsigned int words[4];};
class Rva00468657
{
public:
#define CONTAIN_SLOT(n) virtual void slot##n() = 0;
	CONTAIN_SLOT(00) CONTAIN_SLOT(01) CONTAIN_SLOT(02) CONTAIN_SLOT(03)
	CONTAIN_SLOT(04) CONTAIN_SLOT(05) CONTAIN_SLOT(06) CONTAIN_SLOT(07)
	CONTAIN_SLOT(08) CONTAIN_SLOT(09) CONTAIN_SLOT(10) CONTAIN_SLOT(11)
	CONTAIN_SLOT(12) CONTAIN_SLOT(13) CONTAIN_SLOT(14) CONTAIN_SLOT(15)
	CONTAIN_SLOT(16) CONTAIN_SLOT(17) CONTAIN_SLOT(18) CONTAIN_SLOT(19)
	CONTAIN_SLOT(20) CONTAIN_SLOT(21) CONTAIN_SLOT(22) CONTAIN_SLOT(23)
	CONTAIN_SLOT(24) CONTAIN_SLOT(25) CONTAIN_SLOT(26) CONTAIN_SLOT(27)
	CONTAIN_SLOT(28) CONTAIN_SLOT(29) CONTAIN_SLOT(30) CONTAIN_SLOT(31)
	CONTAIN_SLOT(32) CONTAIN_SLOT(33) CONTAIN_SLOT(34) CONTAIN_SLOT(35)
	CONTAIN_SLOT(36) CONTAIN_SLOT(37) CONTAIN_SLOT(38) CONTAIN_SLOT(39)
	CONTAIN_SLOT(40) CONTAIN_SLOT(41) CONTAIN_SLOT(42) CONTAIN_SLOT(43)
#undef CONTAIN_SLOT
	virtual ContainStatus468657 status(int mode) = 0;
	void rva00468657(Object *object, bool value);
private:
	char pad04[0x18];
	_STL::map<int, AsciiString> bones;
};

void Rva00468657::rva00468657(Object *object, bool value)
{
	if (!object)
		return;
	Drawable *passenger = reinterpret_cast<Thing *>(object)->getDrawable();
	if (!passenger)
		return;
	Thing *owner = *reinterpret_cast<Thing **>(reinterpret_cast<char *>(this) - 0x18);
	Drawable *drawable = owner->getDrawable();
	if (!drawable)
		return;
	if (!status(0).test(61))
	{
		int id = reinterpret_cast<Rva0055A88BDwordField *>(passenger)->get();
		if (value)
			reinterpret_cast<Rva002716Holder *>(drawable)->Rva002716D3Broadcast(id);
		else
			reinterpret_cast<Rva002716Holder *>(drawable)->Rva0027167FBroadcast(id);
		if (bones.find(object->getID()) != bones.end())
			passenger->rva0027656F(
				reinterpret_cast<Rva0055A88BDwordField *>(drawable)->get(),
				reinterpret_cast<Rva004650A0 *>(&bones)->rva004650A0(
					object->getID()));
		else
			passenger->rva0027656F(
				reinterpret_cast<Rva0055A88BDwordField *>(drawable)->get(),
				AsciiString("FIREPOINT01"));
	}
	passenger->setDrawableHidden(value);
}
