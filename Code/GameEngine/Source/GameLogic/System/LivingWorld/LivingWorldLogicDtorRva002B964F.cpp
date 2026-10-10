// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
//
// ??1Rva002B964F@@UAE@XZ
// retail 0x002B964F..0x002B98AD (606 bytes), thiscall, EH frame.
//
// LivingWorldLogic's destructor, kept under the class's existing placeholder
// name (the adjustor thunk 0x002B9647 is rowed as ??_ERva002B964F@@WM@AE).
// WorldBuilder twin 0xD7CBB0 (unnamed; it calls
// LivingWorldLogic::processArmyDestroyList) gives the body: leave the two
// global observer lists (rowed 0x002B7250 on 0x00E04424 and 0x00E02E88)
// with the +0x10 and +0x14 observer bases, run the rowed cleanup members
// (0x002B7C74 0x002B753B 0x002B7BBB 0x002B7B25 0x002B6900 0x002B7B71),
// ::delete the region manager at +0xB0 (virtual destructor with flag 0, then
// the global operator delete) and clear it, then rowed 0x002B7D91.  The rest
// is compiler-generated member and base destruction, whose EH states fix
// the declaration order: SubsystemInterface (+0x00, rowed dtor 0x001B4E74),
// Snapshot (+0x0C), seven 0x10-byte observer lists (+0x1C..+0x7C; vector
// buffer freed through _free; MSVC places these non-polymorphic bases after
// the polymorphic ones), the observer interfaces at +0x10 +0x14 +0x18
// (vtables 0x00C77F44 0x00BFDF68 0x00BFDF8C, whose slots are all empty
// stubs: the interfaces have no virtual destructor), then the members: vectors at
// +0x8C +0xBC +0xCC +0xD8, list<UnicodeString> at +0xF0 (rowed _List_base
// dtor 0x00433BD7), vectors at +0x10C +0x118 +0x124, the map and multimap at
// +0x130 +0x13C (rowed dtors 0x002B5FF1 0x002B602E), the vector at +0x148,
// the message vector at +0x154 (rowed dtor 0x002B7000), the message
// reference at +0x160 (rowed release 0x0007DEEF) and the auto battle
// resolver holder at +0x178 (rowed clear 0x002B9099).

#include "unicode_string.h"
#include "Common/Snapshot.h"

extern "C" void __cdecl free(void *p);

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

	unsigned char m_pad04[0x0c - 0x04];
};

class CreateAHeroData;

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *listener);

	unsigned char m_pad[0x10];
};
extern Rva002B7250 g_00E04424;
extern Rva002B7250 g_00E02E88;

class Rva002B7C74 { public: void rva002B7C74(); };
class Rva002B4CED { public: void rva002B753B(); };
class LivingWorldLogic { public: void processArmyDestroyList(); };
class Rva002B7B25 { public: void rva002B7B25(); };
class Rva002B6900 { public: void rva002B6900(); };
class Rva002B7B71 { public: void rva002B7B71(); };
class Glo012F1028Type { public: void rva002B7D91(); };

class Rva002B964FRegions
{
public:
	virtual ~Rva002B964FRegions();
};

// A vector of plain words: the buffer goes back through _free.
struct Rva002B964FWordVector
{
	void *m_start;
	void *m_finish;
	void *m_endOfStorage;

	~Rva002B964FWordVector()
	{
		if (m_start)
			free(m_start);
	}
};

#define RVA002B964F_LIST( Name ) \
struct Name \
{ \
	Rva002B964FWordVector m_listeners; \
	unsigned int m_selected; \
};

RVA002B964F_LIST( Rva002B964FList1C )
RVA002B964F_LIST( Rva002B964FList2C )
RVA002B964F_LIST( Rva002B964FList3C )
RVA002B964F_LIST( Rva002B964FList4C )
RVA002B964F_LIST( Rva002B964FList5C )
RVA002B964F_LIST( Rva002B964FList6C )
RVA002B964F_LIST( Rva002B964FList7C )

class LivingWorldBuildingObserver
{
public:
	virtual void slot00() = 0;
	~LivingWorldBuildingObserver() {}
};

class Rva0056B126B2
{
public:
	virtual void slot00() = 0;
	~Rva0056B126B2() {}
};

class Rva002B964FPlayerObserver
{
public:
	virtual void slot00() = 0;
	~Rva002B964FPlayerObserver() {}
};

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class _List_base
{
public:
	~_List_base();

	void *m_node;
};
template <class T, class A = allocator<T> > class list : public _List_base<T, A>
{
};
template <class T, class A> class vector;
}

struct Rva002B7000Element
{
	void *m_object;
};

namespace _STL
{
template <> class vector<Rva002B7000Element, allocator<Rva002B7000Element> >
{
public:
	~vector();

	Rva002B7000Element *m_start;
	Rva002B7000Element *m_finish;
	Rva002B7000Element *m_endOfStorage;
};
}

class Rva002B54F9
{
public:
	~Rva002B54F9();

	unsigned char m_pad[0x0c];
};

class Rva002B5522
{
public:
	~Rva002B5522();

	unsigned char m_pad[0x0c];
};

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

struct Rva002B964FMessageRef
{
	TargetRef00217D4C *m_object;

	~Rva002B964FMessageRef()
	{
		if (m_object)
			ReleaseTreeHintRef00217D4C(m_object);
	}
};

class Rva002B9099
{
public:
	void clear();

	~Rva002B9099()
	{
		clear();
	}

	void *m_object;
};

class Rva002B964F : public SubsystemInterface, public Snapshot,
	public Rva002B964FList1C, public Rva002B964FList2C, public Rva002B964FList3C,
	public Rva002B964FList4C, public Rva002B964FList5C, public Rva002B964FList6C,
	public Rva002B964FList7C, public LivingWorldBuildingObserver,
	public Rva0056B126B2, public Rva002B964FPlayerObserver
{
public:
	virtual ~Rva002B964F();

	Rva002B964FWordVector m_vector8C;			// +0x8C
	unsigned char m_pad98[0xb0 - 0x98];
	Rva002B964FRegions *m_regions;				// +0xB0
	unsigned char m_padB4[0xbc - 0xb4];
	Rva002B964FWordVector m_vectorBC;			// +0xBC
	unsigned char m_padC8[0xcc - 0xc8];
	Rva002B964FWordVector m_vectorCC;			// +0xCC
	Rva002B964FWordVector m_vectorD8;			// +0xD8
	unsigned char m_padE4[0xf0 - 0xe4];
	_STL::list<UnicodeString> m_stringsF0;			// +0xF0
	unsigned char m_padF4[0x10c - 0xf4];
	Rva002B964FWordVector m_vector10C;			// +0x10C
	Rva002B964FWordVector m_vector118;			// +0x118
	Rva002B964FWordVector m_vector124;			// +0x124
	Rva002B54F9 m_map130;					// +0x130
	Rva002B5522 m_multimap13C;				// +0x13C
	Rva002B964FWordVector m_vector148;			// +0x148
	_STL::vector<Rva002B7000Element, _STL::allocator<Rva002B7000Element> > m_messages;	// +0x154
	Rva002B964FMessageRef m_message160;			// +0x160
	unsigned char m_pad164[0x178 - 0x164];
	Rva002B9099 m_autoBattleResolver;			// +0x178
};

Rva002B964F::~Rva002B964F()
{
	g_00E04424.rva002B7250((CreateAHeroData *)(LivingWorldBuildingObserver *)this);
	g_00E02E88.rva002B7250((CreateAHeroData *)(Rva0056B126B2 *)this);
	((Rva002B7C74 *)this)->rva002B7C74();
	((Rva002B4CED *)this)->rva002B753B();
	((LivingWorldLogic *)this)->processArmyDestroyList();
	((Rva002B7B25 *)this)->rva002B7B25();
	((Rva002B6900 *)this)->rva002B6900();
	((Rva002B7B71 *)this)->rva002B7B71();
	::delete m_regions;
	m_regions = 0;
	((Glo012F1028Type *)this)->rva002B7D91();
}
