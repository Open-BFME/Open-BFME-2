// cl: /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner, grouped by shape. Every
// class, method and callee is address-derived unless the ledger already
// names the callee; the bytes prove only the shapes described per group.

#include <new>
typedef int Int;
typedef bool Bool;

// --- Two-field setters: store both stack arguments at two adjacent fields.
#define BFME_PAIR_SETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void set(Int a, Int b); \
		char m_lead[DISP]; \
		Int m_a; \
		Int m_b; \
	}; \
	void NAME::set(Int a, Int b) \
	{ \
		m_a = a; \
		m_b = b; \
	}

BFME_PAIR_SETTER(Rva0008BBA1PairSlot, 0x8C)	// vtable 0x00BC7568 slot 120
// InGameUI::setScrollAmount: defined in InGameUIInputModes.cpp (its row's unit).

// --- A one-shot flag: answers whether the global byte at VA 0x00DFF005
// (ledger g_flag2) was set, clearing it (vtable 0x00BC4858 slot 5).
extern Bool g_flag2;

class Rva002CEF14FlagTest
{
public:
	Bool rva002CEF14();
};

Bool Rva002CEF14FlagTest::rva002CEF14()
{
	if (g_flag2)
	{
		g_flag2 = false;
		return true;
	}
	return false;
}

// --- Calls of one member of `this` with a constant argument.
#define BFME_CONST_ARG_CALL(HOST, SLOT, CALLEE, VALUE) \
	class HOST \
	{ \
	public: \
		void SLOT(); \
		void CALLEE(Int value); \
	}; \
	void HOST::SLOT() \
	{ \
		CALLEE(VALUE); \
	}

// The callees below are rowed; they are called by their row names.
class MilesAudioManager { public: void rva0005BBE2(Int value); virtual void rva0005BD20(); virtual void rva0005BD28(); };	// 0x0005BBE2
class W3DVolumetricShadow { public: void Update(Bool force); };	// 0x000F4017
enum StateReturnType { STATE_CONTINUE = 0 };
class AIAttackAimAtTargetState { public: StateReturnType updateInternal(Bool flag); };	// 0x003508C5

class Rva000F42F7Host { public: void rva000F42F7(); };	// vtable 0x00BCEFC8 slot 1
// AIAttackPositionAimAtTargetState::update is owned with updateInternal in AIStates.cpp.
class Rva00351949Host { public: void rva00351949(); };	// vtable 0x00C11008 slot 6

void MilesAudioManager::rva0005BD20() { ((MilesAudioManager *)this)->rva0005BBE2(0); }
void MilesAudioManager::rva0005BD28() { ((MilesAudioManager *)this)->rva0005BBE2(1); }
void Rva000F42F7Host::rva000F42F7() { ((W3DVolumetricShadow *)this)->Update(true); }
void Rva00351949Host::rva00351949() { ((AIAttackAimAtTargetState *)this)->updateInternal(false); }

// --- Hand `this` to a manager singleton's member.
// Callee evidence (retail bytes): 0x000F0A75 walks the manager head at
// +0x0 with node next at +0x68, unlinks the matching owner, then deletes
// owner->slot0(0) via rowed operator delete; 0x0010713A null-checks its
// owner and performs the same virtual-then-delete tail with `this` unused.
// ZH/BFME1 removeShadow (plain `delete shadow`, projected type checks)
// does not match either tail, so the virtual-then-delete shape below is
// modeled on the byte-proven neighbor 0x00107152 (`delete p->rvaFoo(0)`)
// with honest address-derived node names; manager/owner identities beyond
// the caller ABI (thiscall void*(owner), ret 4) remain unclaimed.
class Rva000F0A75Node
{
public:
	virtual void *rvaFoo(int x);
private:
	char m_pad[0x64];
public:
	Rva000F0A75Node *m_next;
};
class Rva0010713ANode
{
public:
	virtual void *rvaFoo(int x);
};
class W3DVolumetricShadowManager
{
public:
	void rva000F0A75(void *owner);
private:
	Rva000F0A75Node *m_head;
};
class W3DProjectedShadowManager
{
public:
	void rva0010713A(void *owner);
};
class Rva00108660ResourceManager
{
public:
	void rva001091A8(void *owner);
};
struct Node;
class Rva0010B9E5 { public: void rva0010B9E5(Node *node); };	// rowed 0x0010B9E5
extern W3DVolumetricShadowManager *TheW3DVolumetricShadowManager;
extern W3DProjectedShadowManager *TheW3DProjectedShadowManager;
extern Rva00108660ResourceManager *Rva00DEC2D8Manager;

class Rva000F168BHost { public: void rva000F168B(); };		// vtable 0x00BCEFC8 slot 2
class Rva001074C8Host { public: void rva001074C8(); };		// vtable 0x00BCF964 slot 2
class Rva00109DA6Host { public: void rva00109DA6(); };		// vtable 0x00BCF9E0 slot 2
class Rva0010BB04Host { public: void rva0010BB04(); };		// vtable 0x00BCF9F4 slot 2

void Rva000F168BHost::rva000F168B() { TheW3DVolumetricShadowManager->rva000F0A75(this); }
void Rva001074C8Host::rva001074C8() { TheW3DProjectedShadowManager->rva0010713A(this); }
void Rva00109DA6Host::rva00109DA6() { Rva00DEC2D8Manager->rva001091A8(this); }
void Rva0010BB04Host::rva0010BB04() { ((Rva0010B9E5 *)Rva00DEC2D8Manager)->rva0010B9E5((Node *)this); }

void W3DProjectedShadowManager::rva0010713A(void *owner)
{
	if (owner)
		delete ((Rva0010713ANode *)owner)->rvaFoo(0);
}

void W3DVolumetricShadowManager::rva000F0A75(void *owner_)
{
	Rva000F0A75Node *owner = (Rva000F0A75Node *)owner_;
	Rva000F0A75Node *prev = 0;
	for (Rva000F0A75Node *cur = m_head; cur != 0; prev = cur, cur = cur->m_next) {
		if (cur == owner) {
			if (prev != 0)
				prev->m_next = owner->m_next;
			else
				m_head = owner->m_next;
			delete owner->rvaFoo(0);
			break;
		}
	}
}

// --- Call this object's own vtable slot 2 with a constant.
class Rva0035D781Self
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2(Int value);
	void rva0035D781();
	void rva0035E603();
	void rva0035F49E();
};	// vtable 0x00C1665C slot 6

// --- Float functions of the slot's one float argument (cdecl callees,
// ledger-named by address; 0x004D6B6E is also rowed as _atan).
float Rva004D6B9D(float v);
float Rva004D6B3A(float v);
float focalLengthToFovDegrees(float v);
float focalLengthToFov(float v);

class Rva0025ED90Math
{
public:
	float rva0025ED90(float v);		// vtable 0x00BC7568 slot 133
	float rva0025EDA1(float v);		// slot 134
	float rva0025EDB2(float focalLength);		// slot 135
	float rva0025EDC3(float focalLength);		// slot 136
};

float Rva0025ED90Math::rva0025ED90(float v) { return Rva004D6B9D(v); }
float Rva0025ED90Math::rva0025EDA1(float v) { return Rva004D6B3A(v); }
float Rva0025ED90Math::rva0025EDB2(float focalLength) { return focalLengthToFovDegrees(focalLength); }
float Rva0025ED90Math::rva0025EDC3(float focalLength) { return focalLengthToFov(focalLength); }

// --- Two members of `this` in a row, the second as a tail jump.
#define BFME_TWO_CALLS(HOST, SLOT, FIRST, SECOND) \
	class HOST \
	{ \
	public: \
		void SLOT(); \
		void FIRST(); \
		void SECOND(); \
	}; \
	void HOST::SLOT() \
	{ \
		FIRST(); \
		SECOND(); \
	}

// 0x000B3FD0 is the shared one-byte empty `ret` body; its neutral row name.
class Rva000B3FD0 { public: void rva000B3FD0(); };
class Rva003FDD05Host
{
public:
	void rva003FDD05();	// vtable 0x00C37DA0 slot 9
	void rva003FDAEB();
};
void Rva003FDD05Host::rva003FDD05()
{
	rva003FDAEB();
	((Rva000B3FD0 *)this)->rva000B3FD0();
}
// A rowed cdecl first callee that takes nothing (it reads only globals):
// `this` stays in esi across it exactly as for a member call.
#define BFME_FREE_THEN_MEMBER(HOST, SLOT, FIRST, SECOND) 	class HOST 	{ 	public: 		void SLOT(); 		void SECOND(); 	}; 	void HOST::SLOT() 	{ 		FIRST(); 		SECOND(); 	}

void Rva000A98BACleanup();	// rowed 0x000A98BA
void rva000ABA2F();		// rowed 0x000ABA2F
void Rva00118A90();		// rowed 0x00118A90
BFME_FREE_THEN_MEMBER(Rva00062908Host, rva00062908, Rva000A98BACleanup, rva0022274A)	// vtable 0x00BC57E0 slot 14
BFME_FREE_THEN_MEMBER(Rva00062918Host, rva00062918, rva000ABA2F, rva00224296)	// vtable 0x00BC57E0 slot 1
BFME_FREE_THEN_MEMBER(Rva0008FF12Host, rva0008FF12, Rva00118A90, rva002C108F)	// vtable 0x00BC7C90 slot 41
// vtable 0x00BC89C8 slot 1: the tail jump goes to the rowed
// Rva0009D55BProduct::rva0009BAA4 (0x0009BAA4), called by its row name.
class Rva0009D55BProduct
{
public:
	void rva0009BAA4();
};
class Rva0009C134Host
{
public:
	void rva0009C134();
};
void Rva0009C134Host::rva0009C134()
{
	((Rva000B3FD0 *)this)->rva000B3FD0();
	((Rva0009D55BProduct *)this)->rva0009BAA4();
}
class LivingWorldArmyIcon { public: void rva003FE342(); };	// rowed 0x003FE342
class Rva0053947D { public: virtual void rva005392EC(); };	// rowed 0x005392EC (vtable slot)
class Rva003FE402Host { public: void rva003FE402(); };	// vtable 0x00C37E48 slot 7
void Rva003FE402Host::rva003FE402()
{
	((LivingWorldArmyIcon *)this)->rva003FE342();
	((Rva0053947D *)this)->Rva0053947D::rva005392EC();
}

// ?rva003FDD15@Rva003FDD15Host@@QAEXXZ @0x003FDD15 16B: chain after 0x003FDC46;
// calls rowed 0x003FDC46 then tail-jmps to rowed 0x003FBA58. Callees carry
// their own row names so they are declared only here. Evidence: lane=chain,
// prev 0x003FDD05 in this file, same 16B two-call tail-jmp shape.
class Rva003FDC46
{
public:
	void rva003FDC46();
};

class Rva003FBA58
{
public:
	void rva003FBA58();
};

class Rva003FDD15Host
{
public:
	void rva003FDD15();
};

void Rva003FDD15Host::rva003FDD15()
{
	((Rva003FDC46 *)this)->rva003FDC46();
	((Rva003FBA58 *)this)->rva003FBA58();
}
