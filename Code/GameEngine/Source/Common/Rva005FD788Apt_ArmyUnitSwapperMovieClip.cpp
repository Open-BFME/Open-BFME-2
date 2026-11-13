// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// Split from Rva005FD788Apt.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// ?SetSlotString@Impl@ArmyUnitSwapperMovieClip@StrategicHUD@@QAEXHPBDABVUnicodeString@@@Z retail 0x005FD788 116B
// Evidence: format APT:_level%u.%s_%s%s via 0x00038150; bfmeSetText via pin 0x00225301; releaseBuffer 0x00036410; globals 0x009FE4CC 0x007BAC1C 0x0087A290; callers 0x005FD92E 0x005FD9A6 0x005FD9E9; sibling APT precedent Rva005FDF1C
#include "../../Include/Common/BfmeStringData.h"

#include "ascii_string.h"


#include "unicode_string.h"

#include "../../Include/Common/Rva005FD788Inner.h"

#include "../../../Libraries/Source/Apt/BfmeAptWindowManager.h"

extern BfmeAptWindowManager *g_bfmeAptWindowManager;
// The two slot-side names at RVA 0x0087A290 (.rdata): "Top", "Bottom".
const char *g_Va0087A290[] = { "Top", "Bottom" };

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref); // 0x0007DEEF

#include "../../../Libraries/Source/Apt/AptCommandTarget.h"

#include "../../Include/Common/DelegateDesc.h"

#include "../../Include/Common/AptCommandMap.h"

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

// The out-of-line copy is rowed in Rva005D25F2Dtor.cpp (ICF fold at 0x00109CFD).
inline AsciiStringPlusStringText operator+(const AsciiStringPlusString &left, const char *right)
{
	Rva000B3F84Pair text;
	text.init(right);
	AsciiStringPlusStringText result;
	static_cast<AsciiStringPlusString &>(result) = left;
	result.m_right = text;
	return result;
}

// The rowed TreeHintRef assignment (0x002174A4).
#include "../../../Libraries/Source/Apt/AptRefTarget.h"

// The 24-byte HUD slot has two reference handles and two Unicode strings.
// Its zeroing constructor folds with 0x00286297; its distinct destructor is
// 0x005FD5D4 (84 bytes including the native EH frame).
struct Rva005F4AD7
{
	__forceinline Rva005F4AD7() : m_ptr(0) {}
	~Rva005F4AD7();
	Rva005F4AD7 &operator=(const Rva005F4AD7 &other);
	void *m_ptr;
};

class Rva005FD5D4UnitSlot
{
public:
	Rva005FD5D4UnitSlot();
	~Rva005FD5D4UnitSlot();
	TreeHintRef00217D4C m_ref; // +0x00
	Rva005F4AD7 m_second; // +0x04
	UnicodeString m_text8, m_textC;
	int m_unknown10, m_unknown14;
};



// The Apt window manager's +0x318 mode (0: idle).
struct Rva00578A7EAptMode
{
	unsigned char m_pad000[0x318];
	int m_mode; // +0x318
};

#include "../../Include/GameClient/ArmyUnitSwapperMovieClip.h"
namespace StrategicHUD {
}

class StrategicHUD::ArmyUnitSwapperMovieClip::Impl
{
public:
	Impl(ArmyUnitSwapperMovieClip *owner, int level, const AsciiString &name, const TreeHintRef00217D4C &top, const TreeHintRef00217D4C &bottom);
	~Impl();
	void SetSlotString(int index, const char *suffix, const UnicodeString &text);
	void OnOpen(const char *path); // 0x005FD3EF
	void OnClosed(const char *path); // 0x005FD3FF
	void OnExitButtonClicked(const char *path); // 0x005FD416
	void OnMoveDownButtonClicked(const char *path); // 0x005FD434
	void OnMoveUpButtonClicked(const char *path); // 0x005FD452
	void OnSwapButtonClicked(const char *path); // 0x005FD470
	void OnTopPanelLoaded(const char *path); // 0x005FD88D
	void OnBottomPanelLoaded(const char *path); // 0x005FD89B
	void OnPanelLoaded(int which, const char *path); // 0x005FD7FC

	ArmyUnitSwapperMovieClip *m_owner; // +0x00
	int m_level4;
	AsciiString m_name; // +0x08
	AptCommandMapAdder m_commandMaps; // +0x0C
	int m_state; // +0x18 (0 closed, 1 open, 2/3 closing)
	Rva005FD5D4UnitSlot m_slots[2]; // +0x1C
	bool m_4c;
	bool m_4d;
	bool m_4e;
};

void StrategicHUD::ArmyUnitSwapperMovieClip::Impl::SetSlotString(int index, const char *suffix, const UnicodeString &text)
{
	const char *table = g_Va0087A290[index];
	AsciiString key;
	Rva005FD788Inner *inner = *(Rva005FD788Inner **)&m_name;
	const char *mid = inner ? inner->m_name : "";
	key.format("APT:_level%u.%s_%s%s", m_level4, mid, table, suffix);
	g_bfmeAptWindowManager->bfmeSetText(key, text, true);
}

StrategicHUD::ArmyUnitSwapperMovieClip::Impl::Impl(ArmyUnitSwapperMovieClip *owner, int level, const AsciiString &name, const TreeHintRef00217D4C &top, const TreeHintRef00217D4C &bottom)
	: m_owner(owner), m_level4(level), m_name(name), m_state(0), m_4c(false), m_4d(false), m_4e(false)
{
	m_slots[0].m_ref = top;
	m_slots[1].m_ref = bottom;

	AsciiString prefix;
	prefix.format("_level%u.", m_level4);
	AddCommandMapDelegate(m_commandMaps, prefix + m_name + "_OnOpen", DelegateDesc(this, &Impl::OnOpen));
	AddCommandMapDelegate(m_commandMaps, prefix + m_name + "_OnClosed", DelegateDesc(this, &Impl::OnClosed));
	AddCommandMapDelegate(m_commandMaps, prefix + m_name + "_OnExitButtonClicked", DelegateDesc(this, &Impl::OnExitButtonClicked));
	AddCommandMapDelegate(m_commandMaps, prefix + m_name + "_OnMoveDownButtonClicked", DelegateDesc(this, &Impl::OnMoveDownButtonClicked));
	AddCommandMapDelegate(m_commandMaps, prefix + m_name + "_OnMoveUpButtonClicked", DelegateDesc(this, &Impl::OnMoveUpButtonClicked));
	AddCommandMapDelegate(m_commandMaps, prefix + m_name + "_OnSwapButtonClicked", DelegateDesc(this, &Impl::OnSwapButtonClicked));
	AddCommandMapDelegate(m_commandMaps, prefix + m_name + "_OnTopPanelLoaded", DelegateDesc(this, &Impl::OnTopPanelLoaded));
	AddCommandMapDelegate(m_commandMaps, prefix + m_name + "_OnBottomPanelLoaded", DelegateDesc(this, &Impl::OnBottomPanelLoaded));

	for (int slot = 0; slot < 2; ++slot)
	{
		SetSlotString(slot, "RegionName", UnicodeString::TheEmptyString);
		SetSlotString(slot, "ArmyName", UnicodeString::TheEmptyString);
		SetSlotString(slot, "CP", UnicodeString::TheEmptyString);
	}
}









// R5 WB EVIDENCE (wb_show 0x5FD7FC --gd): true file
// C:\Projects\bfme2\Code\GameEngine\Source\GameClient\Gui\InGame\Strategic\StrategicHUDArmyUnitSwapperMovieClip.cpp.
// Guard names slotStuff.panelFactory.IsBound() / slotStuff.panel.IsBound()
// (assert !(!panelFactory.IsBound() || panel.IsBound()) @306..309, compiled
// out in retail NDEBUG). Body: leaf=SkipLevelN(path); AsciiString temp via
// StringBase::StringBase(leaf) at [ebp+8] (arg-slot reuse); LevelIndexFromTarget
// takes the path; rva005F4AED(sret-10, level) this=factory, leaf passed as the
// AsciiString argument; then operator=(this=&m_second,sret), ~Rva005F4AD7 on
// sret, releaseBuffer on temp, ReleaseTreeHintRef+null on m_ref. Retail guard
// is xor-edi + 2x cmp-mem,edi; assigning the receiver inside the level argument
// keeps the zero hoist and the factory load between the argument pushes.
namespace AptUtils { const char *SkipLevelN(const char *path); int LevelIndexFromTarget(const char *path); }
// The owner's ctor 0x005FDE24 (ret 0x10): vtable 0x0087A2E8 and its Impl
// (new 0x50) built with this and the four arguments.
StrategicHUD::ArmyUnitSwapperMovieClip::ArmyUnitSwapperMovieClip(int level, const AsciiString &name, const TreeHintRef00217D4C &top, const TreeHintRef00217D4C &bottom)
	: m_impl(new Impl(this, level, name, top, bottom))
{
}

// Slots 1..5 of the class table 0x00C7A2E8 (stored by the ctor 0x005FDE24) are
// the shared empty RET at 0x000B3FD0 (ICF fold).
void StrategicHUD::ArmyUnitSwapperMovieClip::notifyClosed()
{
}

void StrategicHUD::ArmyUnitSwapperMovieClip::notifyExit()
{
}

void StrategicHUD::ArmyUnitSwapperMovieClip::notifyMoveDown()
{
}

void StrategicHUD::ArmyUnitSwapperMovieClip::notifyMoveUp()
{
}

void StrategicHUD::ArmyUnitSwapperMovieClip::notifySwap()
{
}
