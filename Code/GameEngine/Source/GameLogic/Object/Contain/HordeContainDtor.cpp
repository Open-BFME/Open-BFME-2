// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1HordeContain@@UAE@XZ @ 0x0046F901 (325B).
// HordeContain dtor: restores 11 vptrs then tears down members in reverse
// construction order with EH states 0xA-0 before TransportContain base.
// Evidence: deleting-dtor caller 0x004704CB plus AOD/Horse dtors calling here;
// vptr stores match AOD 11-iface layout; member calls name Rva00462D35 tree
// 0x004636FE plus Rva0046A915/Rva0046AB7D plus int-ptr trees plus list_base
// plus frees plus TransportContain base 0x00467E61.
#include <stdlib.h>
#include <new>
#include <map>
#include <list>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> void _List_base<int, allocator<int> >::clear();
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> _List_base<int, allocator<int> >::~_List_base();
}
#include <vector>

// list<int> destruction otherwise instantiates per-TU deallocate
// COMDATs (one byte shape per TU flags); explicit dllimport+forceinline
// specializations take those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(_List_node<int>* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int> *, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int> *__p, size_t __n) {
  allocator<_List_node<int> >().deallocate(__p, __n);
}
}

class Thing;
class ModuleData;
class Object;
#include "ascii_string.h"

class B0 { public: virtual void b0(); private: unsigned char m_pad[8]; };
class B1 { public: virtual void b1(); };
class B2 { public: virtual void b2(); private: unsigned char m_pad[12]; };
class B3 { public: virtual void b3(); };
class B4 { public: virtual void b4(); };
class B5 { public: virtual void b5(); };
class B6 { public: virtual void b6(); };
class B7 { public: virtual void b7(); };
class B8 { public: virtual void b8(); private: unsigned char m_pad[0xC8 - 4]; };

class OpenContain : public B0, public B1, public B2, public B3, public B4, public B5, public B6, public B7, public B8
{
public:
	virtual ~OpenContain();
};

class ThingTemplate;
class PayloadContainView;
struct Coord3D;

class TransportExtra
{
public:
	virtual Object *createPayloadMember(const ThingTemplate *, PayloadContainView *, Object *, const char *, int) = 0;
};

class TransportContain : public OpenContain, public TransportExtra
{
public:
	virtual ~TransportContain();
	virtual Object *createPayloadMember(const ThingTemplate *, PayloadContainView *, Object *, const char *, int);
private:
	unsigned char m_pad100[0x10];
	_STL::vector<AsciiString> m_110;
};

struct Iface11C { virtual void rva00472329(const Coord3D *, int) = 0; };

struct DelBase { virtual void *F(int); };

struct FreeHolder
{
	void *m_ptr;
	~FreeHolder()
	{
		if (m_ptr)
			free(m_ptr);
	}
};

struct Rva00462D35Mapped { unsigned int m_bits; };
typedef _STL::pair<const int, Rva00462D35Mapped> HordeTreePair;
typedef _STL::_Rb_tree<int, HordeTreePair, _STL::_Select1st<HordeTreePair>, _STL::less<int>, _STL::allocator<HordeTreePair> > HordeTree;

typedef _STL::pair<const int, void *> IntPtrPair;
typedef _STL::_Rb_tree<int, IntPtrPair, _STL::_Select1st<IntPtrPair>, _STL::less<int>, _STL::allocator<IntPtrPair> > IntPtrTree;

class Rva0046A915 { public: ~Rva0046A915(); private: void *m_ptr; int m_flag; };
class Rva0046AB7D { public: ~Rva0046AB7D(); private: void *m_ptr; int m_flag; };
class Rva002EE9B7 { public: ~Rva002EE9B7(); private: void *m_ptr; int m_flag; };

// map<ObjectID, int>: the tree family dtor 0x00286852 -> clear 0x00286656 ->
// erase 0x00286183 (one instantiation: the self-recursive erase is not ICF-folded;
// AITargetHeuristicEnemyStructure::findBestTarget 0x005735C6 keys it by object ID).
enum ObjectID { INVALID_ID = 0 };
typedef _STL::map<ObjectID, int> ObjectIDIntMap;
typedef _STL::_Rb_tree<ObjectID, _STL::pair<const ObjectID, int>, _STL::_Select1st<_STL::pair<const ObjectID, int> >, _STL::less<ObjectID>, _STL::allocator<_STL::pair<const ObjectID, int> > > ObjectIDIntTree;
class HordeContain : public TransportContain, public Iface11C
{
public:
	virtual ~HordeContain();
	virtual void rva00472329(const Coord3D *, int);
private:
	unsigned char m_pad120[0x170 - 0x120];
	Rva002EE9B7 m_170;
	int m_pad174;
	ObjectIDIntTree m_17C;
	FreeHolder m_188;
	int m_pad18C[2];
	_STL::list<int> m_194;
	int m_pad198[2];
	Rva0046AB7D m_1A0;
	unsigned char m_pad1A8[0x24C - 0x1A8];
	ObjectIDIntTree m_24C;
	Rva0046A915 m_258;
	unsigned char m_pad260[0x270 - 0x260];
	FreeHolder m_270;
	unsigned char m_pad274[0x2C8 - 0x274];
	DelBase *m_2C8;
	FreeHolder m_2CC;
	unsigned char m_pad2D0[0x2DC - 0x2D0];
	HordeTree m_2DC;
	unsigned char m_tail[0x30C - 0x2E8];
};

HordeContain::~HordeContain()
{
	void *p = m_2C8 ? m_2C8->F(0) : 0;
	::operator delete(p);
}
