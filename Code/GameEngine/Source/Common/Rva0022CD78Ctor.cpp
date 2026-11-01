// cl: /Ireference/shims/bfme2_ascii /O1 /Ob2 /Oy- /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0022CD78@@QAE@XZ @0x0022CD78 (70B): EH ctor running
// baseConstruct() from an inlined novtable head, storing the own vtable,
// then constructing the +0xC 2x0x10 array through the rowed compiler
// vector-construct helper ??_L at 0x00629512 with the rowed element ctor
// ??0Rva0022CD65@@QAE@XZ at 0x0022CD65 and the rowed cleanup thunk
// ?cleanup@Rva0022CA3BCleanupForward@@QAEXXZ at 0x0022CA3B as callbacks;
// returns this.
// Evidence: baseConstruct call 0x22CD89; vtable VA 0x00BE7528 whose slot 0
// is the scalar deleting dtor at 0x0022CDBE; retail pushes
// (0x62ca3b, 0x62cd65, 2, 0x10, this+0xC); helper ret 0x14 (stdcall,
// 5 args); address-derived.
// 0x001B4E63 is the rowed SubsystemInterface ctor.
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class __declspec(novtable) Rva0022CD78Head
{
public:
	__forceinline Rva0022CD78Head() { reinterpret_cast<SubsystemInterface *>(this)->SubsystemInterface::SubsystemInterface(); }
	virtual ~Rva0022CD78Head() { reinterpret_cast<SubsystemInterface *>(this)->SubsystemInterface::SubsystemInterface(); }
private:
	char m_flag;
	int m_value;
};

// The +0xC array element. Its ctor is the rowed ??0Rva0022CD65@@QAE@XZ
// (0x0022CD65, Rva0022CD65Ctor.cpp); the compiler emits its address as the
// constructor iterator's ctor argument. The element's destructor is the
// rowed 5-byte tail-JMP wrapper ?cleanup@Rva0022CA3BCleanupForward@@QAEXXZ
// (0x0022CA3B, Rva0022C612Dtor.cpp), which retail passes as the dtor
// argument: the element dtor below is a view of that row (same unchanged-ECX
// tail call shape), so the iterator's dtor argument binds the ledger name.
struct Rva0022CA3BCleanupForward { void cleanup(); };

class Rva0022CD65
{
public:
	Rva0022CD65();
	~Rva0022CD65();
private:
	unsigned char m_bytes[0x10];
};

class Rva0022CD78 : public Rva0022CD78Head
{
public:
	virtual void rva_vtable_anchor() {}
	Rva0022CD78();
private:
	Rva0022CD65 m_arr[2]; // +0xC: 2 elements of 0x10 built by the helper
};

// ??1Rva0022CD65@@QAE@XZ absent-from-retail this element's dtor symbol has no
// retail row of its own: it exists only so the constructor iterator receives a
// function address for its dtor slot, and its 5-byte tail call binds the rowed
// cleanup thunk ?cleanup@Rva0022CA3BCleanupForward@@QAEXXZ (0x0022CA3B, in
// Rva0022C612Dtor.cpp).
Rva0022CD65::~Rva0022CD65()
{
	reinterpret_cast<Rva0022CA3BCleanupForward *>(this)->cleanup();
}

Rva0022CD78::Rva0022CD78()
{
}
