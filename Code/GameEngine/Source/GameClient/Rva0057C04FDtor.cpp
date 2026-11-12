// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
//
// ??1Rva0057C04F@@QAE@XZ @0x0057C04F 69B: dtor destroying AsciiString at +8 and Rva0052413E at +0xC.
// Stores vtable 0x0086F2D4 then s_first0C 0x0086FFFC (folded CategoryModuleClass FXParticleSystem).
// Evidence: reverse member destruction order (+0xC then +8) with EH states 1 then 0 proves dtor;
// callees Rva dtor and StringBase releaseBuffer are rowed; unblocks 3 callees; neighbours share FX shard.
//
// ?DoPlay@Rva0057C04F@@UAEXH@Z @0x0057C094 190B: vslot 1 of vtable 0x0086F2D4 TurnNumber setter.
// Formats APT:_level%u.%s_TurnNumber from +4 level and +8 prefix str then Unicode int format then bfmeSetText false
// then AptCall Go then flag at +0x18. Evidence: same literals and globals as free Rva0057A51CSet plus Go plus slot 1.
#include "ascii_string.h"
#include "unicode_string.h"

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref); // 0x0007DEEF

// Delegate payload (object, member) handed to the command-map reference
// (as in Common/Rva0042DB21Method.cpp).
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

static __forceinline AsciiStringPlusString operator+(const AsciiString &left, const AsciiString &right)
{
	AsciiStringPlusString result;
	result.m_string = &left;
	result.m_second.m_string = &right;
	return result;
}
extern "C" int s_first0C;

#include "../../../Libraries/Source/Apt/BfmeAptWindowManager.h"

#include "../../Include/Common/Rva00222A8BTarget.h"

class Rva00222A8BTarget;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *t, void *a1, const char *a2, const char *a3);
// Retail table 0x00C6FFFC: two __purecall entries; the derived table 0x00C6F2D4
// overrides both (slot 0 the shared +0x18 byte getter 0x004C9990, slot 1 DoPlay).
struct Base00
{
	virtual unsigned char rva004C9990() const = 0;
	virtual void DoPlay(int turn) = 0;
	~Base00() {}
};
class Rva0057C04F : public Base00
{
public:
	Rva0057C04F(int level, const AsciiString &name);
	~Rva0057C04F();
	virtual unsigned char rva004C9990() const;
	virtual void DoPlay(int turn);
	void OnDone(const char *path);
private:
	int m_level04;
	AsciiString m_08; // +0x08
	AptCommandMapAdder m_0C; // +0x0C
	unsigned char m_flag18; // +0x18
};

Rva0057C04F::Rva0057C04F(int level, const AsciiString &name)
	: m_level04(level), m_08(name), m_flag18(0)
{
	AsciiString prefix;
	prefix.format("_level%u.", m_level04);
	AddCommandMapDelegate(m_0C, prefix + m_08 + "_OnDone", DelegateDesc(this, &Rva0057C04F::OnDone));
}

void Rva0057C04F::OnDone(const char *path)
{
	if (m_flag18 != 0)
		m_flag18 = 0;
}

Rva0057C04F::~Rva0057C04F()
{
}

// ?rva004C9990@Rva0057C04F@@UBEEXZ: slot 0 of 0x00C6F2D4, retail's folded byte
// getter at 0x004C9990 (mov al,[ecx+18h]; ret) reading the flag OnDone clears.
unsigned char Rva0057C04F::rva004C9990() const
{
	return m_flag18;
}

void Rva0057C04F::DoPlay(int turn)
{
	AsciiString key;
	key.format("APT:_level%u.%s_TurnNumber", m_level04, m_08.str());
	UnicodeString value;
	value.format(L"%d", turn);
	g_bfmeAptWindowManager->bfmeSetText(key, value, false);
	Rva00524EF4AptCall(((Rva00222A8BTarget *)g_bfmeAptWindowManager), (void *)m_level04, m_08.str(), "Go");
	m_flag18 = 1;
}
