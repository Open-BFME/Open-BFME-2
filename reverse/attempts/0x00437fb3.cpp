// _Rva00437FB3
// partial score=0.6 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// ??0Rva00437E72@@QAE@XZ @0x00437F0A 87B. Constructs the base message object
// with type 13 and the target string "MessageBox", then publishes this at the
// global slot used by the two prompt forwarders.
// ??1Rva00437E72@@UAE@XZ @0x00437E72 18B stores vtable g_00C3D294 clears g_Va00E032FC then tail-jmps to base dtor 0x0054D2CF.
// ??_GRva00437E72@@UAEPAXI@Z @0x00437EEE 28B deleting dtor calls ??1 then operator delete on flag.
// Evidence: packet disassembly pair; base dtor pin ??1Rva0054D2CF@@UAE@XZ; vtable g_00C3D294; global g_Va00E032FC.
#include "ascii_string.h"

class UnicodeString;

// This four-byte wrapper view is supported by the 0x0023E8D8 constructor,
// its vtable, and the callback argument traffic at 0x00437F61. The payload's
// application identity remains unresolved. Its +4 refcount uses the already
// matched release helper; TargetRef00217D4C is only that helper's ABI view.
struct TargetRef00217D4C;
extern void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);

class Rva0023E8D8
{
	void *m_ptr;
public:
	Rva0023E8D8(const Rva0023E8D8 &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++((int *)m_ptr)[1];
	}
	~Rva0023E8D8()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}
};

// The 0x0057BC63 holder stores a pointer to a 24-byte wrapper whose target
// vtable puts its refcount at +4. Keep the holder trivial; the prompt call's
// two temporary handles own the AddRef/Release pair visible at 0x00437FB3.
class Rva0057BC63FunctorHolder
{
public:
	void *m_ptr;
};

class Rva0057BC63FunctorRef
{
	public:
	void *m_ptr;
	explicit Rva0057BC63FunctorRef(void *ptr) : m_ptr(ptr)
	{
		if (m_ptr)
			++((int *)m_ptr)[1];
	}
	Rva0057BC63FunctorRef(const Rva0057BC63FunctorRef &other)
		: m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++((int *)m_ptr)[1];
	}
	~Rva0057BC63FunctorRef()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}
};

struct Rva0057BC63FunctorArg
{
	void *m_ptr;
	explicit Rva0057BC63FunctorArg(void *ptr) : m_ptr(ptr) {}
};

class Rva0054D2CF
{
public:
	Rva0054D2CF(int type, const AsciiString &label);
	virtual ~Rva0054D2CF();
	void Rva0054D308(int type, const UnicodeString &message,
		const UnicodeString &title, Rva0023E8D8 callback);
	void Rva0054D362(int type, const UnicodeString &message,
		const UnicodeString &title, Rva0057BC63FunctorArg secondCallback,
		Rva0057BC63FunctorArg firstCallback);
};

extern const void *const g_00C3D294[];
extern int g_Va00E032FC;

class Rva00437E72 : public Rva0054D2CF
{
public:
	Rva00437E72();
	virtual ~Rva00437E72();
};

Rva00437E72::Rva00437E72()
	: Rva0054D2CF(13, AsciiString("MessageBox"))
{
	g_Va00E032FC = (int)this;
}

Rva00437E72::~Rva00437E72()
{
	g_Va00E032FC = 0;
}

// The target copies the refcounted callback handle for the forwarding call.
// Its receiver is the object published through 0x00E032FC; the operation at
// 0x0054D308 remains address-derived.
extern "C" void __cdecl Rva00437F61(int type,
	const UnicodeString &message, const UnicodeString &title,
	Rva0023E8D8 callback)
{
	((Rva0054D2CF *)g_Va00E032FC)->Rva0054D308(
		type, message, title, callback);
}

// The helper's two holders are passed through as opaque pointer-backed values;
// each is retained for the target method call and released afterward.
extern "C" void __cdecl Rva00437FB3(int type,
	const UnicodeString &message, const UnicodeString &title,
	Rva0057BC63FunctorHolder secondCallback,
	Rva0057BC63FunctorHolder firstCallback)
{
	Rva0057BC63FunctorRef firstRef(firstCallback.m_ptr);
	Rva0057BC63FunctorRef secondRef(secondCallback.m_ptr);
	((Rva0054D2CF *)g_Va00E032FC)->Rva0054D362(type, message, title,
		Rva0057BC63FunctorArg(secondRef.m_ptr),
		Rva0057BC63FunctorArg(firstRef.m_ptr));
}
