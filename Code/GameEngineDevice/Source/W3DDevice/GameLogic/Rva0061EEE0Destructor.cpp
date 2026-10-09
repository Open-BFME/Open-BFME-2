// cl: /O2 /G6 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_NO_CSTD_FUNCTION_IMPORTS /Ireference/shims/sweep
// stlport

// BFME2's base destructor call goes to the rowed 14-byte body at 0x001B4E74
// (??1GameEngineDeletingBase@@UAE@XZ, folded with ??1Snapshot/??1Subsystem-
// Interface pins), so the base is declared under that established name: zero
// new pins for the base call. The member's identity is unrecovered (opaque
// address-derived name on the BFME2 target).
//
// The class is not W3DRenderObjectSnapshot: that class's vftable is
// 0x00BC59F4 (slot 2 returns the string "W3DRenderObjectSnapshot"; see
// W3DGhostObjectScene.cpp). This one's 15-slot vftable 0x00C7C5C0 is
// installed by the ctor at 0x0061EEE0 (subsystem base ctor 0x001B4E63, then
// news a 0x200-byte member into +0x0C) and by this dtor. BFME1 carries the
// same body as the address-derived Rva009EB960 singleton destructor, whose
// member is the asset-registry object; named here after the BFME2 ctor.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class GameEngineDeletingBase
{
public:
	GameEngineDeletingBase();
	virtual void anchor();
	virtual ~GameEngineDeletingBase();
};

#define _STLP_USE_STATIC_LIB 1

#include <deque>
#include <hash_map>
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include <windows.h>

struct Rva001408C0Target;
typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key> Rva001408C0Set;

class BfmeThingBVA
{
public:
	BfmeThingBVA()
	{
		m_value = 0;
		m_active = true;
	}

	BfmeThingBVA &operator=(BfmeThingBVA &other)
	{
		if (this != &other)
		{
			bfmeStepBVA(&other);
			m_active = true;
			m_value = other.m_value;
		}
		return *this;
	}

	void bfmeStepBVA(BfmeThingBVA *other);

	Rva001408C0Set m_tree;
	unsigned int m_value;
	bool m_active;
};

// The shared release leaf 0x009EB7A0 decrements the low word at +4 and, once
// it reaches zero with bit 24 set, dispatches through the vtable at +0.
class Rva009EB7A0RefOwner
{
public:
	void Release_Ref();

	void *m_vtable;
	unsigned int m_refs : 16;
	unsigned int m_bits16 : 8;
	unsigned int m_deleteOnRelease : 1;
	unsigned int m_bits25 : 7;
};

struct Gen_t_009ee630_p12cd
{
	int a[3];
};

struct Gen_t_009ee750_p12cd
{
	Rva009EB7A0RefOwner *m_object;
	int m_unmodelled[2];
};

struct Gen_t_009edfe0_p12cd
{
	int a[3];
};

class Rva009EEA70CleanupDeleting
{
public:
	virtual ~Rva009EEA70CleanupDeleting();
};

class AssetManagerImpl;
class AssetRegistry;
class Q1Receiver0134FAAC;
extern Q1Receiver0134FAAC *TheQ1Receiver;

class Q1Receiver0134FAAC
{
public:
	void m009F0E50(int value);
	void m009F19E0(int value);
};

class Rva00624130
{
public:
	void rva00624130();
};

typedef _STL::hash_map<int, int> GenHashMap0C;
typedef _STL::hash_map<int, int> GenHashMap44;
typedef _STL::deque<int> GenDeque;

class Gen_dtor_00625040
{
public:
	~Gen_dtor_00625040();

private:
	uintptr_t m_thread;
	void *m_unknown04;
	bool m_active;
	unsigned char m_pad09[3];
	GenHashMap0C m_map0c;
	__int64 m_budget20;
	__int64 m_limit28;
	unsigned int m_reserved30;
	CRITICAL_SECTION m_lock34;
	GenHashMap44 m_map4c;
	GenHashMap44::iterator m_iterator60;
	CRITICAL_SECTION m_lock68;
	GenDeque m_deques80[7];
	BfmeThingBVA m_set198;
	BfmeThingBVA m_set1ac;
	BfmeThingBVA m_set1c0;
	BfmeThingBVA m_set1d4;
	unsigned int m_field1e8;
	unsigned int m_field1ec;
	unsigned char m_pad1f0[4];
	bool m_flag1f4;
	bool m_flag1f5;
	bool m_flag1f6;
	unsigned char m_pad1f7;
	Rva009EEA70CleanupDeleting *m_hashContext;
};

typedef char GenDtorSizeCheck[sizeof(Gen_dtor_00625040) == 0x200 ? 1 : -1];

// Constructor-only storage view for the already pinned 0x00624DB0 callee.
// The target ledger identifies that callee as AssetManagerImpl; allocation
// here proves 0x200 bytes and the +0x0C member is destroyed at 0x00625040.
// Retain the existing address-derived constructor pin, rather than adding an alias.
class Rva00624DB0
{
public:
	Rva00624DB0();
private:
	char m_storage[0x200];
};

class Rva0061EEE0 : public GameEngineDeletingBase
{
public:
	Rva0061EEE0();
	virtual ~Rva0061EEE0();

private:
	void *m_debugName;
	// BFME2 reads the member at +0x0C (BFME1: +0x08): one unidentified dword
	// sits between the debug name and the render object.
	void *m_bfme08;
	Gen_dtor_00625040 *m_renderObject;
};

Rva0061EEE0::~Rva0061EEE0()
{
	delete m_renderObject;
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?anchor@GameEngineDeletingBase@@UAEXXZ=??_GRva0061EEE0@@UAEPAXI@Z")

// Clean BFME1 donor 9cbfb551fe20dae985f91f2319d8997287b6a705:
// game/Libraries/Source/assetmanager/Gen_dtor_009eb9e0_Destructor.cpp.
// WB 0x0167D7F0 self-assertion names AssetManagerImpl::~AssetManagerImpl;
// native constructor 0x00624DB0 and the 0x200-byte allocation establish layout.
// Native fields at +20/+24 and +28/+2C are wider than the donor, shifting
// later members by eight. Container int spellings are verified storage views.
// Native RET at 0x006252C8 closes the 649-byte body (the old 646-byte
// inventory truncates its add-esp/RET). Global delete uses worker vslot flag 0
// followed by operator delete; /EHs preserves both hash-map cleanup states.
Gen_dtor_00625040::~Gen_dtor_00625040()
{
	Q1Receiver0134FAAC *receiver = (Q1Receiver0134FAAC *)this;

	{
		BfmeThingBVA empty;
		m_set1c0 = empty;
	}
	receiver->m009F0E50((int)&m_set1c0);
	receiver->m009F19E0((int)&m_set1c0);

	m_limit28 = 0;
	for (;;)
	{
		int i;
		for (i = 0; i < 7; ++i)
		{
			if (!m_deques80[i].empty())
				break;
		}
		if (i >= 7)
			break;
		receiver->m009F19E0((int)&m_set1c0);
		((Rva00624130 *)this)->rva00624130();
		Sleep(1);
	}

	TheQ1Receiver = 0;
	m_active = true;
	WaitForSingleObject((HANDLE)m_thread, INFINITE);

	for (GenHashMap44::iterator it = m_map4c.begin(); it != m_map4c.end(); ++it)
	{
		((Rva009EB7A0RefOwner *)it->second)->m_deleteOnRelease = 1;
		((Rva009EB7A0RefOwner *)it->second)->Release_Ref();
	}
	m_map4c.clear();

	::delete m_hashContext;
	DeleteCriticalSection(&m_lock34);
	DeleteCriticalSection(&m_lock68);
}

// Native 0x0061EEE0..0x0061EF5F: base construction has an unwind state,
// which requires saving this as well as the new-expression allocation.
Rva0061EEE0::Rva0061EEE0()
{
	m_renderObject = reinterpret_cast<Gen_dtor_00625040 *>(new Rva00624DB0);
}
