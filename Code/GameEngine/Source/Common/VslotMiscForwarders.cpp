// cl: /O1 /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner, grouped by shape. Every
// class, method and callee is address-derived unless the ledger already
// names the callee; the bytes prove only the shapes described per group.

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
BFME_PAIR_SETTER(Rva0029A85BPairSlot, 0x808)	// vtable 0x00BC7A88 slot 45
BFME_PAIR_SETTER(Rva000851A6PairSlot, 0x20)	// vtable 0x00BF6178 slot 18

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

BFME_CONST_ARG_CALL(Rva0005BD20Host, rva0005BD20, rva0005BBE2, 0)	// vtable 0x00BC55B0 slot 43
BFME_CONST_ARG_CALL(Rva0005BD28Host, rva0005BD28, rva0005BBE2, 1)	// vtable 0x00BC55B0 slot 44
BFME_CONST_ARG_CALL(Rva000F42F7Host, rva000F42F7, rva000F4017, 1)	// vtable 0x00BCEFC8 slot 1
BFME_CONST_ARG_CALL(Rva0034A871Host, rva0034A871, rva0034A570, 0)	// vtable 0x00C11068 slot 6
BFME_CONST_ARG_CALL(Rva00351949Host, rva00351949, rva003508C5, 0)	// vtable 0x00C11008 slot 6

// --- Hand `this` to a manager singleton's member.
class W3DVolumetricShadowManager
{
public:
	void rva000F0A75(void *owner);
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
	void rva0010B9E5(void *owner);
};
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
void Rva0010BB04Host::rva0010BB04() { Rva00DEC2D8Manager->rva0010B9E5(this); }

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
};

void Rva0035D781Self::rva0035D781() { slot2(0x16); }	// vtable 0x00C16530 slot 6
void Rva0035D781Self::rva0035E603() { slot2(0x11); }	// vtable 0x00C165F0 slot 6
void Rva0035D781Self::rva0035F49E() { slot2(0x0A); }	// vtable 0x00C1665C slot 6

// --- Float functions of the slot's one float argument (cdecl callees,
// ledger-named by address; 0x004D6B6E is also rowed as _atan).
float Rva004D6B9D(float v);
float Rva004D6B3A(float v);
float Rva004D6BB8(float v);
float Rva004D6B6E(float v);

class Rva0025ED90Math
{
public:
	float rva0025ED90(float v);		// vtable 0x00BC7568 slot 133
	float rva0025EDA1(float v);		// slot 134
	float rva0025EDB2(float v);		// slot 135
	float rva0025EDC3(float v);		// slot 136
};

float Rva0025ED90Math::rva0025ED90(float v) { return Rva004D6B9D(v); }
float Rva0025ED90Math::rva0025EDA1(float v) { return Rva004D6B3A(v); }
float Rva0025ED90Math::rva0025EDB2(float v) { return Rva004D6BB8(v); }
float Rva0025ED90Math::rva0025EDC3(float v) { return Rva004D6B6E(v); }

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

BFME_TWO_CALLS(Rva003FDD05Host, rva003FDD05, rva003FDAEB, rva000B3FD0)	// vtable 0x00C37DA0 slot 9
BFME_TWO_CALLS(Rva00062908Host, rva00062908, rva000A98BA, rva0022274A)	// vtable 0x00BC57E0 slot 14
BFME_TWO_CALLS(Rva00062918Host, rva00062918, rva000ABA2F, rva00224296)	// vtable 0x00BC57E0 slot 1
BFME_TWO_CALLS(Rva0008FF12Host, rva0008FF12, rva00118A90, rva002C108F)	// vtable 0x00BC7C90 slot 41
BFME_TWO_CALLS(Rva0009C134Host, rva0009C134, rva000B3FD0, rva0009BAA4)	// vtable 0x00BC89C8 slot 1
BFME_TWO_CALLS(Rva003FE402Host, rva003FE402, rva003FE342, rva005392EC)	// vtable 0x00C37E48 slot 7
