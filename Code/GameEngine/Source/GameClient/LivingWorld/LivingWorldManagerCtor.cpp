// cl: /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG /Ireference/shims/moduledata
//
// ??0LivingWorldManager@@QAE@XZ, retail 0x00213EEF..0x00214052 (355 bytes,
// EH, RET 0): the constructor of the 0x2D8-byte TheLivingWorldManager
// subsystem GameEngine::init (0x0022E2E4) allocates. Its methods are rowed
// as LivingWorldManager (vtable 0x00BE5234 slot 0 is the rowed ??_G of the
// 0x00214405 destructor).
//
// Three bases: SubsystemInterface at +0x00, Snapshot at +0x0C and a one-slot
// listener at +0x10 (vtable 0x00BE5114, inline constructor, out-of-line
// vptr-reset destructor 0x00210CC5) whose slot LivingWorldManager overrides
// with OnSwapArmyMembers. The members are opaque here: each is named after
// the destructor its unwind state calls. The hash table members have no
// constructor of their own: retail calls the rowed hash_map constructor
// 0x00213E11 directly, and the +0x2B4 tree the rowed map constructor
// 0x0033C432. 0x00212AEF is pinned. The vector members build through the
// folded _Vector_base constructor 0x00211E58, which cannot throw (retail
// keeps no unwind store between them). The body clears +0x230, then empties
// the +0x2B4 tree, the +0x218 table and the +0x2CC vector.
#include "Common/Snapshot.h"

#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"

struct ArmySwapView;
struct ArmyMemberRangeView;

class GameWindow;
struct Rva00390729Element;
namespace _STL
{
template <class T> class allocator
{
public:
	allocator() {}
};
template <class T, class A> class _Vector_base
{
public:
	_Vector_base(const A &a) throw();
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};
// Every vector member here builds through the GameWindow* instantiation
// folded at 0x00211E58.
template <class T, class A = allocator<T> > class vector
	: public _Vector_base<GameWindow *, allocator<GameWindow *> >
{
public:
	__forceinline vector() : _Vector_base<GameWindow *, allocator<GameWindow *> >(allocator<GameWindow *>()) {}
	~vector();
	T *erase(T *first, T *last);
};
}

// +0x14, 0x1F0 bytes: constructor 0x00212AEF, destructor 0x00212ED3.
class Rva00212ED3
{
public:
	Rva00212ED3();
	~Rva00212ED3();
private:
	unsigned char m_data[0x1F0];
};

// The hash tables at +0x204 and +0x26C/+0x280/+0x294 (destructor 0x002130CA)
// and +0x218 (destructor 0x00212379), all built by 0x00213E11.
struct Rva00213E11Element;

namespace _STL
{
template <class T> struct hash;
template <class T> struct equal_to;
template <class T> struct less;
template <class A, class B> struct pair;

// The rowed constructors 0x00213E11 and 0x0033C432; only their spellings are used here.
template <class K, class V, class H, class E, class A> class hash_map
{
public:
	hash_map();
private:
	unsigned char m_data[0x14];
};

template <class K, class V, class C, class A> class map
{
public:
	map();
private:
	unsigned char m_data[0xC];
};
}

typedef _STL::hash_map<int, Rva00213E11Element, _STL::hash<int>, _STL::equal_to<int>,
	_STL::allocator<_STL::pair<const int, Rva00213E11Element> > > Rva00213E11Map;
typedef _STL::map<unsigned char, int, _STL::less<unsigned char>,
	_STL::allocator<_STL::pair<const unsigned char, int> > > Rva0033C432Map;

class Rva002130CA
{
public:
	~Rva002130CA();
private:
	Rva00213E11Map m_data;
};

class Rva00212379
{
public:
	~Rva00212379();
private:
	Rva00213E11Map m_data;
};

class Rva004DFC20
{
public:
	void clear();
};

// +0x22C: a handle that clears its pointer.
class Rva0010F149Handle
{
public:
	Rva0010F149Handle() : m_ptr(0) {}
	~Rva0010F149Handle();
private:
	void *m_ptr;
};

// +0x2A8: a vector released by 0x0021397C.
class Rva0021397C : public _STL::vector<Rva00390729Element>
{
public:
	__forceinline Rva0021397C() {}
	~Rva0021397C();
};

// +0x2B4: a map built by 0x0033C432 and released by 0x00211FA3.
class Rva00211FA3
{
public:
	~Rva00211FA3();
private:
	Rva0033C432Map m_data;
};

class Rva0021119B
{
public:
	void rva00211DD2();
};

// The members are these opaque types here alone (see LivingWorldManager.h).
#define BFME_LIVINGWORLDMANAGER_CTOR_MEMBERS \
	Rva00212ED3 m_14;						/* +0x014 */ \
	Rva002130CA m_204;						/* +0x204 */ \
	Rva00212379 m_218;						/* +0x218 */ \
	Rva0010F149Handle m_22C;				/* +0x22C */ \
	void *m_230;							/* +0x230 */ \
	_STL::vector<Rva00390729Element> m_234;	/* +0x234 */ \
	_STL::vector<Rva00390729Element> m_240;	/* +0x240 */ \
	_STL::vector<Rva00390729Element> m_24C;	/* +0x24C */ \
	_STL::vector<Rva00390729Element> m_258;	/* +0x258 */ \
	int m_264;								/* +0x264 */ \
	void *m_268;							/* +0x268 */ \
	Rva002130CA m_26C;						/* +0x26C */ \
	Rva002130CA m_280;						/* +0x280 */ \
	Rva002130CA m_294;						/* +0x294 */ \
	Rva0021397C m_2A8;						/* +0x2A8 */ \
	Rva00211FA3 m_2B4;						/* +0x2B4 */ \
	bool m_2C0;								/* +0x2C0 */ \
	void *m_2C4;							/* +0x2C4 */ \
	bool m_2C8;								/* +0x2C8 */ \
	_STL::vector<Rva00390729Element> m_2CC;	/* +0x2CC */
#define BFME_LIVINGWORLDMANAGER_CTOR_PURE = 0
#include "../../../Include/GameLogic/LivingWorldManager.h"

__declspec(noinline) inline Rva00210CC5::~Rva00210CC5() {}

LivingWorldManager::LivingWorldManager()
	: m_264(0),
	  m_268(0),
	  m_2C0(false),
	  m_2C4(0),
	  m_2C8(false)
{
	m_230 = 0;
	((Rva0021119B *)&m_2B4)->rva00211DD2();
	((Rva004DFC20 *)&m_218)->clear();
	_STL::vector<unsigned char> *bytes = (_STL::vector<unsigned char> *)&m_2CC;
	bytes->erase((unsigned char *)bytes->_M_start, (unsigned char *)bytes->_M_finish);
}
