// ?rva005F9DCB@@YIXPAVRva005F9DCBObj@@HHHHHH@Z
// partial score=0.9 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// NEAR draft (not under Code/): every instruction matches retail except the
// stack-slot layout of the concat temporaries (retail frame 0x98 / this-save
// at ebp-0x18 / first concat temps at -0xA4 -0x94 -0x40; this draft frame
// 0x80 / this-save at -0x10 / one shared 16-byte slot). Needs pins:
// ?OnPageLoaded@Rva005F8FEE@@QAEXPBD@Z=0x005F9053
// ?InternalOnOpen@Rva005F8FEE@@QAEXPBD@Z=0x005F8E0D
// ?InternalOnClosed@Rva005F8FEE@@QAEXPBD@Z=0x005F8E22
//
// ??0Rva005F8FEE@@QAE@HABVAsciiString@@PBDHABURva005F91F3Src@@@Z
// retail 0x005F9DCB..0x005FA0C9 (766 bytes, ret 0x14).
// Constructor of the battle-prompt player page frame. WorldBuilder's twin
// (va 0x1609450) carries StrategicHUDBattlePromptMovieClip.cpp's own assert
// strings for StrategicHUD::`anonymous-namespace'::PlayerPageFrame::
// PlayerPageFrame (m_pageFactory.IsBound() line 111 / TheAptPlayer != NULL
// line 123); the anonymous-namespace class keeps the ledger's address name
// Rva005F8FEE (its virtual dtor row 0x005F8FEE and vtable 0x00879D20 which
// this body installs). Thiscall with five stack arguments: the callers
// 0x005FA0C9 / 0x005FA0F7 (Ally / Enemy frames built by Impl::AddAlly /
// AddEnemy) pass ecx = this and the owner Impl's level (+4) and name (+8)
// plus "Ally" / "Enemy" and their own index and Rva005F91F3Src record; edx
// is never read so the fastcall pin spelling does not describe it.
// Body: refcount base (vtable 0x007C6F20 / dtor 0x004E84A4) / level +8 /
// name +0xC / side text +0x10 / index +0x14 / page factory reference +0x18
// copied from the record / command-map adder +0x1C / state +0x28 / page
// reference +0x2C. It binds "_level%u." + name + "_On" + side + PageLoaded /
// PageFrameOpen / PageFrameClosed + index to OnPageLoaded (0x005F9053) /
// InternalOnOpen (0x005F8E0D) / InternalOnClosed (0x005F8E22) (WB names
// from the same file's asserts) and fires "Add" + side + "Page" like the
// matched FadeIn / FadeOut callbacks 0x005F94C2 / 0x005F9567.
#include "ascii_string.h"

struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};

// Reference holder: copy AddRefs; dtor 0x005F8F96 releases.
class Rva005F8F96
{
public:
	Rva005F8F96() : m_ptr(0) {}
	Rva005F8F96(const Rva005F8F96 &that) : m_ptr(that.m_ptr)
	{
		if (m_ptr)
			m_ptr->references++;
	}
	~Rva005F8F96();

	TargetRef00217D4C *m_ptr;
};

// The ally / enemy record (Rva005F91F3Copy.cpp): page factory reference first.
struct Rva005F91F3Src
{
	Rva005F8F96 m_pageFactory;
};

class AptCommandTarget
{
};

struct DelegateDesc
{
	template <class T> DelegateDesc(T *object, void (T::*method)(const char *path))
		: m_object(reinterpret_cast<AptCommandTarget *>(object)), m_method(reinterpret_cast<void (AptCommandTarget::*)(const char *path)>(method)) {}

	AptCommandTarget *m_object;
	void (AptCommandTarget::*m_method)(const char *path);
};

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

class AptCommandMap
{
public:
	void *m_vtbl;
	int m_refCount;
};

template <class T> class AptRef
{
public:
	AptRef(const DelegateDesc *desc) { rva00579E47(desc); }
	AptRef &rva00579E47(const DelegateDesc *desc); // 0x00579E47
	~AptRef()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}

private:
	T *m_ptr;
};

class AptCommandMapAdder
{
public:
	AptCommandMapAdder();
	~AptCommandMapAdder();
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);

	__forceinline void AddCommandMapDelegate(const AsciiString &name, DelegateDesc desc)
	{
		AddCommandMap(name, &desc);
	}

private:
	char m_pad[0xC];
};

// Expression-template concat nodes (System/RegistryAsciiPath.cpp family).
class Rva000B3F84Pair
{
public:
	Rva000B3F84Pair() {}
	const char *m_ptr;
	int m_len;
};

struct AsciiStringRef
{
	const AsciiString *m_string;
};

struct AsciiStringPlusString : AsciiStringRef
{
	AsciiStringRef m_second;
};

struct AsciiStringPlusStringText : AsciiStringPlusString
{
	Rva000B3F84Pair m_right;
};

struct Rva005D32EC : AsciiStringPlusStringText
{
	Rva000B3F84Pair m_right2;
};

struct Rva005D3311 : Rva005D32EC
{
	Rva000B3F84Pair m_right3;
};

struct Rva005F8FA2Src
{
	int m_data[8];
};

struct Rva005F8FA2Dst
{
	int m_data[9];
};

// The "... + AsciiString" node (36 bytes); converts through 0x005F9D69.
class Rva005F9852
{
public:
	operator AsciiString();
};

static __forceinline AsciiStringPlusString operator+(const AsciiString &left, const AsciiString &right)
{
	AsciiStringPlusString result;
	result.m_string = &left;
	result.m_second.m_string = &right;
	return result;
}

AsciiStringPlusStringText __cdecl operator+(const AsciiStringPlusString &left, const char *right);
Rva005D32EC __cdecl operator+(const AsciiStringPlusStringText &left, const char *right);
Rva005D3311 __cdecl operator+(const Rva005D32EC &left, const char *right);
Rva005F8FA2Dst *__cdecl Rva005F8FA2Copy(Rva005F8FA2Dst *dest, Rva005F8FA2Src *src, int value);

struct AsciiStringRefWithChar
{
	const AsciiString *m_string;
	char m_char;
};

struct AsciiStringCharPlusText : AsciiStringRefWithChar
{
	Rva000B3F84Pair m_right;
};

struct Rva005D2F96S16
{
	int m0, m1, m2, m3;
};

struct Rva005D2F96Base24
{
	int m0, m1, m2, m3, m4, m5;
};

struct Rva005D2F96S24 : Rva005D2F96Base24
{
};

Rva000B3F84Pair __cdecl Rva00108B93Make(const char *text);
AsciiStringCharPlusText __cdecl operator+(const AsciiStringRefWithChar &left, const char *right);
Rva005D2F96S24 __cdecl Rva005D2F96Build(const Rva005D2F96S16 &left, const char *right);
AsciiString __cdecl Rva002D56C3(const Rva005D2F96Base24 &node);
int __cdecl Rva0052519DFire(void *target, void *owner, const char *prefix, const char *event, int *result);
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

// Reference-counted base: vtable 0x007C6F20 and its destructor 0x004E84A4.
class Rva0007DF07
{
public:
	Rva0007DF07() : m_refs(0) {}
	virtual ~Rva0007DF07();

	int m_refs;
};

class Rva005F8FEE : public Rva0007DF07
{
public:
	Rva005F8FEE(int level, const AsciiString &name, const char *side, int index, const Rva005F91F3Src &data);
	virtual ~Rva005F8FEE();
	void OnPageLoaded(const char *path);     // 0x005F9053
	void InternalOnOpen(const char *path);   // 0x005F8E0D
	void InternalOnClosed(const char *path); // 0x005F8E22

private:
	int m_level;                   // +0x08
	AsciiString m_name;            // +0x0C
	const char *m_side;            // +0x10
	int m_index;                   // +0x14
	Rva005F8F96 m_pageFactory;     // +0x18
	AptCommandMapAdder m_commands; // +0x1C
	int m_state;                   // +0x28
	Rva005F8F96 m_page;            // +0x2C
};

Rva005F8FEE::Rva005F8FEE(int level, const AsciiString &name, const char *side, int index, const Rva005F91F3Src &data)
	: m_level(level), m_name(name), m_side(side), m_index(index), m_pageFactory(data.m_pageFactory), m_state(0)
{
	AsciiString prefix;
	prefix.format("_level%u.", m_level);
	AsciiString number;
	number.format("%d", m_index);
	Rva005F8FA2Dst node;
	m_commands.AddCommandMapDelegate(*(Rva005F9852 *)Rva005F8FA2Copy(&node, (Rva005F8FA2Src *)&(prefix + m_name + "_On" + m_side + "PageLoaded"), (int)&number), DelegateDesc(this, &Rva005F8FEE::OnPageLoaded));
	m_commands.AddCommandMapDelegate(*(Rva005F9852 *)Rva005F8FA2Copy(&node, (Rva005F8FA2Src *)&(prefix + m_name + "_On" + m_side + "PageFrameOpen"), (int)&number), DelegateDesc(this, &Rva005F8FEE::InternalOnOpen));
	m_commands.AddCommandMapDelegate(*(Rva005F9852 *)Rva005F8FA2Copy(&node, (Rva005F8FA2Src *)&(prefix + m_name + "_On" + m_side + "PageFrameClosed"), (int)&number), DelegateDesc(this, &Rva005F8FEE::InternalOnClosed));
	Rva0052519DFire((void *)g_bfmeAptWindowManager, (void *)m_level, m_name.str(),
		Rva002D56C3((Rva005D2F96Base24 &)Rva005D2F96Build(
			(const Rva005D2F96S16 &)operator+(
				(const AsciiStringRefWithChar &)Rva00108B93Make("Add"),
				m_side),
			"Page")).str(), &m_index);
}
