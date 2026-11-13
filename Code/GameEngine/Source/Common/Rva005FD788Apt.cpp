// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ?SetSlotString@Impl@ArmyUnitSwapperMovieClip@StrategicHUD@@QAEXHPBDABVUnicodeString@@@Z retail 0x005FD788 116B
// Evidence: format APT:_level%u.%s_%s%s via 0x00038150; bfmeSetText via pin 0x00225301; releaseBuffer 0x00036410; globals 0x009FE4CC 0x007BAC1C 0x0087A290; callers 0x005FD92E 0x005FD9A6 0x005FD9E9; sibling APT precedent Rva005FDF1C
#include "../../Include/Common/BfmeStringData.h"

#include "ascii_string.h"


#include "unicode_string.h"

#include "../../Include/Common/Rva005FD788Inner.h"

struct Rva005FD788Outer
{
	Rva005FD788Inner *m_ptr;
};

#include "../../../Libraries/Source/Apt/BfmeAptWindowManager.h"

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

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

// The rowed TreeHintRef assignment (0x002174A4).
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
__forceinline TreeHintRef00217D4C::~TreeHintRef00217D4C() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }

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

Rva005FD5D4UnitSlot::Rva005FD5D4UnitSlot()
	: m_ref(), m_second(), m_text8(), m_textC(), m_unknown10(0), m_unknown14(0)
{
}

Rva005FD5D4UnitSlot::~Rva005FD5D4UnitSlot()
{
}

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



void StrategicHUD::ArmyUnitSwapperMovieClip::Impl::OnOpen(const char *path)
{
	if (m_state == 0)
		m_state = 1;
}

void StrategicHUD::ArmyUnitSwapperMovieClip::Impl::OnClosed(const char *path)
{
	if (m_state == 2)
	{
		m_state = 3;
		m_owner->notifyClosed();
	}
}

void StrategicHUD::ArmyUnitSwapperMovieClip::Impl::OnExitButtonClicked(const char *path)
{
	if (m_state == 1 && ((Rva00578A7EAptMode *)g_bfmeAptWindowManager)->m_mode == 0)
		m_owner->notifyExit();
}

void StrategicHUD::ArmyUnitSwapperMovieClip::Impl::OnMoveDownButtonClicked(const char *path)
{
	if (m_state == 1 && ((Rva00578A7EAptMode *)g_bfmeAptWindowManager)->m_mode == 0)
		m_owner->notifyMoveDown();
}

void StrategicHUD::ArmyUnitSwapperMovieClip::Impl::OnMoveUpButtonClicked(const char *path)
{
	if (m_state == 1 && ((Rva00578A7EAptMode *)g_bfmeAptWindowManager)->m_mode == 0)
		m_owner->notifyMoveUp();
}

void StrategicHUD::ArmyUnitSwapperMovieClip::Impl::OnSwapButtonClicked(const char *path)
{
	if (m_state == 1 && ((Rva00578A7EAptMode *)g_bfmeAptWindowManager)->m_mode == 0)
		m_owner->notifySwap();
}

void StrategicHUD::ArmyUnitSwapperMovieClip::Impl::OnTopPanelLoaded(const char *path)
{
	OnPanelLoaded(0, path);
}

void StrategicHUD::ArmyUnitSwapperMovieClip::Impl::OnBottomPanelLoaded(const char *path)
{
	OnPanelLoaded(1, path);
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
class Rva005F4AED
{
public:
	Rva005F4AD7 rva005F4AED(int level, const AsciiString &leaf);
};
#include "../../Include/Common/Rva002BED91.h"
void StrategicHUD::ArmyUnitSwapperMovieClip::Impl::OnPanelLoaded(int which, const char *path)
{
	Rva005FD5D4UnitSlot &slot = m_slots[which];
	Rva005F4AED *factory = 0;
	if (slot.m_ref.m_ptr != (TargetRef00217D4C *)factory && slot.m_second.m_ptr == factory) {
		slot.m_second = factory->rva005F4AED((factory = (Rva005F4AED *)slot.m_ref.m_ptr, AptUtils::LevelIndexFromTarget(path)), AptUtils::SkipLevelN(path));
		((Rva002BED91 *)&slot.m_ref)->clear();
	}
}


StrategicHUD::ArmyUnitSwapperMovieClip::Impl::~Impl() {}
