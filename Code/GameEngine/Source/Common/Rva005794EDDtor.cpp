// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ??1EndTurnButtonImpl@StrategicHUD@@QAE@XZ @0x005794ED 85B: dtor with AsciiString at +8 plus Rva0052413E at +0xC plus TargetRef at +0x18.
// Evidence: direct callers 0x0042D4EB 0x0042D7A3 0x0042D7C6 plus rowed Release 0x0007DEEF plus rowed 0x0052413E plus rowed releaseBuffer 0x00036410 plus vtables 0x00C6ECBC 0x00C6EE28; prev Rva004FAC6BCtor.
// Not virtual: slot 0 of the class's table 0x00C6ECBC is the byte getter 0x004C54EC (as WB's
// table's slot 0 is a 17-byte getter), the base table 0x00C6EE28 is seven __purecall slots,
// and every delete calls 0x005794ED directly before operator delete.
#include "ascii_string.h"

struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

// Delegate payload (object, member) handed to the command-map reference
// (as in Rva0042DB21Method.cpp).
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

class AptCommandMap
{
public:
	void *m_vtbl;
	int m_refCount;
};

// 0x00579E47 is rowed as the delegate-wrapper constructor ??0Rva00579E47@@QAE@ABUDelegateDesc@@@Z
// (built in place as the by-value AddCommandMap argument); AptRef<T> builds through it.
class Rva00579E47
{
public:
	Rva00579E47(const DelegateDesc &desc); // 0x00579E47
protected:
	Rva00579E47() {}
};

template <class T> class AptRef : public Rva00579E47
{
public:
	AptRef(const DelegateDesc *desc) : Rva00579E47(*desc) {}
	AptRef(const AptRef &that) : m_ptr(that.m_ptr)
	{
		if (m_ptr)
			m_ptr->m_refCount++;
	}
	~AptRef()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}

private:
	T *m_ptr;
};

// The 12-byte command-map name list: ctor 0x001F81BF (ICF fold, pinned),
// AddCommandMap 0x0052458E, dtor 0x0052413E (pinned).
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

// "prefix + name + text" concat nodes (layout as in System/RegistryAsciiPath.cpp).
class Rva000B3F84Pair
{
public:
	Rva000B3F84Pair() {}
	Rva000B3F84Pair *init(const char *src); // 0x000B3F84

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
	operator AsciiString(); // 0x0050F74B

	Rva000B3F84Pair m_right;
};

static __forceinline AsciiStringPlusString operator+(const AsciiString &left, const AsciiString &right)
{
	AsciiStringPlusString result;
	result.m_string = &left;
	result.m_second.m_string = &right;
	return result;
}

// ?operator+(AsciiStringPlusString, text) present-unmatched (inline, emitted out of line; ICF-folded at 0x00109CFD; pinned)
inline AsciiStringPlusStringText operator+(const AsciiStringPlusString &left, const char *right)
{
	Rva000B3F84Pair text;
	text.init(right);
	AsciiStringPlusStringText result;
	static_cast<AsciiStringPlusString &>(result) = left;
	result.m_right = text;
	return result;
}

extern const void *const g_00C6ECBC[];
extern const void *const g_00C6EE28[];

// The base table 0x00C6EE28 is seven __purecall slots and no deleting
// destructor. Slots 1-3 take the names of the EndTurnButtonImpl overrides
// WorldBuilder gives; slots 0 and 4-6 stay unnamed.
class __declspec(novtable) Rva005794EDBase
{
public:
	Rva005794EDBase() {}
	~Rva005794EDBase();
	virtual bool vslot0() const = 0;
	virtual void DoSetEnabled(bool newState) = 0;
	virtual void DoPlayAlertFlash() = 0;
	virtual void DoHaltAlertFlash() = 0;
	virtual void vslot4() = 0;
	virtual void vslot5() = 0;
	virtual void vslot6() = 0;
};

// ??1Rva005794EDBase@@UAE@XZ present-unmatched (register key kept; the dtor is non-virtual)
inline Rva005794EDBase::~Rva005794EDBase()
{
	*(const void **)this = g_00C6EE28;
}

// Click callback holder; invoking it is the rowed 0x0044BD79.
class BfmeA1042N
{
public:
	void bfmeGo1042D();

	TargetRef00217D4C *m_ptr;
};

struct Rva005794EDHolder18 : BfmeA1042N
{
	Rva005794EDHolder18() { m_ptr = 0; }
	__forceinline ~Rva005794EDHolder18() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};

// StrategicHUD::EndTurnButtonImpl per WorldBuilder, which names its slots
// DoSetEnabled, DoPlayAlertFlash and DoHaltAlertFlash; retail fires the same
// "SetState"/"_disabled", "PlayAlertFlash" and "HaltAlertFlash" literals.
namespace StrategicHUD
{
class EndTurnButtonImpl : public Rva005794EDBase
{
public:
	EndTurnButtonImpl(int level, const AsciiString &name);
	~EndTurnButtonImpl();
	virtual void DoSetEnabled(bool newState);
	virtual void DoPlayAlertFlash();
	virtual void DoHaltAlertFlash();
	void OnClicked(const char *path);
private:
	int m_04;
	AsciiString m_08;
	AptCommandMapAdder m_0C;
	Rva005794EDHolder18 m_18;
	bool m_1C;
};
}

StrategicHUD::EndTurnButtonImpl::EndTurnButtonImpl(int level, const AsciiString &name)
	: m_04(level), m_08(name), m_1C(true)
{
	AsciiString prefix;
	prefix.format("_level%u.", m_04);
	m_0C.AddCommandMapDelegate(prefix + m_08 + "_OnClicked", DelegateDesc(this, &StrategicHUD::EndTurnButtonImpl::OnClicked));
}

void StrategicHUD::EndTurnButtonImpl::OnClicked(const char *path)
{
	if (m_18.m_ptr != 0)
		m_18.bfmeGo1042D();
}

StrategicHUD::EndTurnButtonImpl::~EndTurnButtonImpl()
{
}

class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern const char g_Rva0107301CEmptyString[];
int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function);
int __cdecl Rva0050E9FEAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char **a0ptr);

static __forceinline const char *Rva005794EDGetStr(const AsciiString &s)
{
	char *t = *(char **)(void *)&s;
	return t ? t + 8 : g_Rva0107301CEmptyString;
}

void StrategicHUD::EndTurnButtonImpl::DoSetEnabled(bool newState)
{
	if (newState == m_1C)
		return;
	const char *state = newState ? "_up" : "_disabled";
	const char *prefix = Rva005794EDGetStr(m_08);
	Rva0050E9FEAptCall(TheRva00222A8BTarget, (void *)m_04, prefix, "SetState", &state);
	m_1C = newState;
}

// Vtable 0x0086ECBC slots 2 and 3: WorldBuilder
// StrategicHUD::EndTurnButtonImpl::DoPlayAlertFlash / DoHaltAlertFlash
// (retail strings "PlayAlertFlash" / "HaltAlertFlash").
void StrategicHUD::EndTurnButtonImpl::DoPlayAlertFlash()
{
	Rva00524EF4AptCall(TheRva00222A8BTarget, (void *)m_04, Rva005794EDGetStr(m_08), "PlayAlertFlash");
}

void StrategicHUD::EndTurnButtonImpl::DoHaltAlertFlash()
{
	Rva00524EF4AptCall(TheRva00222A8BTarget, (void *)m_04, Rva005794EDGetStr(m_08), "HaltAlertFlash");
}
