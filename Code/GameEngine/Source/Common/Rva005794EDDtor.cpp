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
#include "../../../Libraries/Source/Apt/AptCommandTarget.h"

#include "../../Include/Common/DelegateDesc.h"

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
#include "../../../Libraries/Source/Apt/AptCommandMapAdder.h"

static __forceinline void AddCommandMapDelegate(AptCommandMapAdder &adder, const AsciiString &name, DelegateDesc desc)
{
	adder.AddCommandMap(name, &desc);
}

// "prefix + name + text" concat nodes (layout as in System/RegistryAsciiPath.cpp).
#include "../../Include/Common/Rva000B3F84Pair.h"

#include "../../Include/Common/AsciiStringRef.h"

#include "../../Include/Common/AsciiStringPlusString.h"

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
extern "C" const void *const __identifier("??_7Rva00330C50Interface@@6B@")[];

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
	virtual void rva00579542() = 0;
};

// ??1Rva005794EDBase@@UAE@XZ present-unmatched (register key kept; the dtor is non-virtual)
inline Rva005794EDBase::~Rva005794EDBase()
{
	*(const void **)this = __identifier("??_7Rva00330C50Interface@@6B@");
}

// Click callback holder; invoking it is the rowed 0x0044BD79.
class BfmeA1042N
{
public:
	void bfmeGo1042D();

	TargetRef00217D4C *m_ptr;
};

struct TreeHintRef00217D4C : BfmeA1042N
{
	TreeHintRef00217D4C() { m_ptr = 0; }
	__declspec(noinline) TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other)
	{
		if (this != &other) {
			if (other.m_ptr)
				++other.m_ptr->references;
			if (m_ptr)
				ReleaseTreeHintRef00217D4C(m_ptr);
			m_ptr = other.m_ptr;
		}
		return *this;
	}
	__forceinline ~TreeHintRef00217D4C() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
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
	virtual void rva00579542();
private:
	int m_04;
	AsciiString m_08;
	AptCommandMapAdder m_0C;
	TreeHintRef00217D4C m_18;
	bool m_1C;
};
}

StrategicHUD::EndTurnButtonImpl::EndTurnButtonImpl(int level, const AsciiString &name)
	: m_04(level), m_08(name), m_1C(true)
{
	AsciiString prefix;
	prefix.format("_level%u.", m_04);
	AddCommandMapDelegate(m_0C, prefix + m_08 + "_OnClicked", DelegateDesc(this, &StrategicHUD::EndTurnButtonImpl::OnClicked));
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
class Rva00222A8BTarget;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
extern const char g_Rva0107301CEmptyString[];
int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function);
int __cdecl Rva0050E9FEAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char **a0ptr);

static __forceinline const char *Rva005794EDGetStr(const AsciiString &asciiString)
{
	char *t = *(char **)(void *)&asciiString;
	return t ? t + 8 : g_Rva0107301CEmptyString;
}

void StrategicHUD::EndTurnButtonImpl::DoSetEnabled(bool newState)
{
	if (newState == m_1C)
		return;
	const char *state = newState ? "_up" : "_disabled";
	const char *prefix = Rva005794EDGetStr(m_08);
	Rva0050E9FEAptCall(((Rva00222A8BTarget *)g_bfmeAptWindowManager), (void *)m_04, prefix, "SetState", &state);
	m_1C = newState;
}

// Vtable 0x0086ECBC slots 2 and 3: WorldBuilder
// StrategicHUD::EndTurnButtonImpl::DoPlayAlertFlash / DoHaltAlertFlash
// (retail strings "PlayAlertFlash" / "HaltAlertFlash").
void StrategicHUD::EndTurnButtonImpl::DoPlayAlertFlash()
{
	Rva00524EF4AptCall(((Rva00222A8BTarget *)g_bfmeAptWindowManager), (void *)m_04, Rva005794EDGetStr(m_08), "PlayAlertFlash");
}

void StrategicHUD::EndTurnButtonImpl::DoHaltAlertFlash()
{
	Rva00524EF4AptCall(((Rva00222A8BTarget *)g_bfmeAptWindowManager), (void *)m_04, Rva005794EDGetStr(m_08), "HaltAlertFlash");
}

// 0x00579542 (43 B), slot 6 of the table 0x00C6ECBC: drops the click target.
// The reference binding and the separate temporary keep cl's receiver setup
// (add ecx,0x18) ahead of the argument push, as retail emits it.
void StrategicHUD::EndTurnButtonImpl::rva00579542()
{
	TreeHintRef00217D4C tmp;
	TreeHintRef00217D4C &r = m_18;
	r = tmp;
}
