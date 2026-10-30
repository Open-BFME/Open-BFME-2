// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
#include "ascii_string.h"
#include "unicode_string.h"
//
// Vtable-slot forwarders with no ledger owner, batch W5SN4: each loads a
// member pointer and tail-jumps to a function that is either already rowed
// or pinned in reverse/symbols.csv under an address-derived name with the
// argument count its ret shows. Classes are address-derived and model only
// the member.

typedef int Int;

// 0x0057845C is rowed as the virtual AptRadialMenu::Impl::Show; called directly.
class AptRadialMenu { public: class Impl; };
class AptRadialMenu::Impl
{
public:
	virtual void Show(Int a0);
};
class Rva00578513
{
public:
	void rva00578513(Int a0);
private:
	char m_pad00[0x04];
	AptRadialMenu::Impl *m_04;
};
void Rva00578513::rva00578513(Int a0)
{
	m_04->AptRadialMenu::Impl::Show(a0);
}
class Image;
class Rva003F038E { public: const Image *rva003F03B9(); };
class Rva0020E89C { public: UnicodeString rva0020E89C(); };

class RegionUI {
public:
	virtual void v0();
	virtual void SetRegionImage(const Image *);
	virtual void v2();
	virtual void SetText(const UnicodeString &);
	virtual void SetPageCounts(Int enabled, Int total);
	virtual void SetUpgradeCounts(Int available, Int total);
	virtual void SetRegionValues(Int a, Int b);
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void SetVisibility(bool);
};

static __declspec(noinline) void rva005CB46A(RegionUI *ui, void *item)
{
	if (item) {
		const Image *img = ((Rva003F038E *)item)->rva003F03B9();
		ui->SetRegionImage(img);
		ui->SetText(((Rva0020E89C *)item)->rva0020E89C());
		ui->SetVisibility(1);
	} else {
		ui->SetVisibility(0);
	}
}

class Rva005CB723 {
public:
	void rva005CB723(void *item);
private:
	int m_00;
	void *m_04;
	RegionUI *m_ui08;
};

void Rva005CB723::rva005CB723(void *item)
{
	if (item != m_04) {
		if (m_ui08) {
			rva005CB46A(m_ui08, item);
		}
		m_04 = item;
	}
}

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class Rva002E2903Player;
class Rva003F287F;
class LivingWorldRegion
{
public:
	int rva003F0189(Rva002E2903Player *player) const;
private:
	int rva003EFD6F(Rva002E2903Player *player) const;
	friend class Rva005CB748;
};
class LivingWorldLogic
{
public:
	void GetNumUpgradeableTroopsInRegionForPlayer(Rva003F287F *region, Int playerId, Int *available, Int *total);
};
class Rva002B2B66 { public: Int rva002B2B66(); };
extern LivingWorldLogic *TheLivingWorldLogic;

struct Rva005CB748Slot { char m_pad00[0x20]; Int m_20; };
struct Rva005CB748Vec { Rva005CB748Slot **m_begin; Rva005CB748Slot **m_end; };
struct Rva005CB748Region { char m_pad00[0x170]; Rva005CB748Vec m_vec; };

class Rva005CB748Source
{
public:
	virtual void s0();
	virtual void *getHelpBox();
	virtual RegionUI *getUI();
};

class Rva005CB4E6Elem { public: void CreateHotSpotHelp(); };

class Rva005CB748
{
public:
	void rva005CB748();
private:
	Rva005CB748Source *m_source;
	Rva005CB748Region *m_region;
	RegionUI *m_ui;
	void *m_helpBox;
};
// 0x005CB748 (258 B): the region display state's lazy refresh (reached through the slot forwarder
// rva005CB852 below). Fetches the movie-clip RegionUI (source slot 2) and the help box (slot 1) once
// they exist, builds the hot-spot help when both are there, fills the RegionUI from the region (page
// count, upgradeable troops from TheLivingWorldLogic's player, two LivingWorldRegion values).
// Identity from target bytes and rowed callees (CreateHotSpotHelp 0x5CB52B, updater 0x5CB46A,
// GetNumUpgradeableTroopsInRegionForPlayer 0x2B6E8A); field and slot names are inferred. The
// WorldBuilder twin 0x015B0430 (ShowArmoryStats) is a different, smaller body and is not this one.
void Rva005CB748::rva005CB748()
{
	if (m_ui == 0) {
		m_ui = m_source->getUI();
		if (m_ui == 0) return;
		if (m_helpBox) ((Rva005CB4E6Elem *)this)->CreateHotSpotHelp();
		rva005CB46A(m_ui, m_region);
	}
	if (m_helpBox == 0) {
		m_helpBox = m_source->getHelpBox();
		if (m_helpBox && m_ui) ((Rva005CB4E6Elem *)this)->CreateHotSpotHelp();
	}
	Rva005CB748Region *region = m_region;
	if (region == 0) return;
	RegionUI *ui = m_ui;
	Rva005CB748Vec &vec = region->m_vec;
	Int enabled = 0;
	Int count = vec.m_end - vec.m_begin;
	_ReadWriteBarrier();
	if (count > 0) {
		Rva005CB748Slot **slot = vec.m_begin;
		for (Int remaining = count; remaining > 0; --remaining, ++slot) {
			if ((*slot)->m_20) ++enabled;
		}
	}
	ui->SetPageCounts(enabled, count);
	{
		Rva002B2B66 *logic = (Rva002B2B66 *)TheLivingWorldLogic;
		Int total, available;
		Rva003F287F *logicRegion = (Rva003F287F *)m_region;
		RegionUI *regionUI = m_ui;
		Int playerId = logic->rva002B2B66();
		TheLivingWorldLogic->GetNumUpgradeableTroopsInRegionForPlayer(logicRegion, playerId, &available, &total);
		regionUI->SetUpgradeCounts(total - available, total);
	}
	LivingWorldRegion *lwr = (LivingWorldRegion *)m_region;
	Rva002E2903Player *player = *(Rva002E2903Player **)((char *)TheLivingWorldLogic + 0x98);
	RegionUI *regionUi = m_ui;
	Int a = lwr->rva003EFD6F(player);
	Int b = lwr->rva003F0189(player);
	regionUi->SetRegionValues(b, a);
}
class Rva005CB852
{
public:
	void rva005CB852();
private:
	char m_pad00[0x04];
	Rva005CB748 *m_04;
};
void Rva005CB852::rva005CB852()
{
	m_04->rva005CB748();
}

// The target now has a verified bool parameter and a real C++ provider.
namespace StrategicHUD {
class RegionDetailsMovieClip { public: class Impl; };
class RegionDetailsMovieClip::Impl { public: void SetPageEnabled(Int page, bool enabled); };
}
class Rva005E3049
{
public:
    void rva005E3049(Int page, bool enabled);
private:
    char m_pad00[0x04];
    StrategicHUD::RegionDetailsMovieClip::Impl *m_04;
};
void Rva005E3049::rva005E3049(Int page, bool enabled)
{
    m_04->SetPageEnabled(page, enabled);
}

class Rva005ED385
{
public:
	void rva005ED385(Int a0, const Image *a1);	// row spelling
};
class Rva005ED5BB
{
public:
	void rva005ED5BB(Int a0, Int image);
private:
	char m_pad00[0x04];
	Rva005ED385 *m_04;
};
void Rva005ED5BB::rva005ED5BB(Int a0, Int image)
{
	m_04->rva005ED385(a0, (const Image *)image);
}

// 0x005ED6B9 is rowed on StrategicHUD::RegionAwardMovieClip::Impl.
namespace StrategicHUD {
class RegionAwardMovieClip { public: class Impl; };
class RegionAwardMovieClip::Impl { public: void rva005ED6B9(Int a0, Int a1); };
}
class Rva005ED849
{
public:
	void rva005ED849(Int a0, Int a1);
private:
	char m_pad00[0x04];
	StrategicHUD::RegionAwardMovieClip::Impl *m_04;
};
void Rva005ED849::rva005ED849(Int a0, Int a1)
{
	m_04->rva005ED6B9(a0, a1);
}

namespace StrategicHUD
{
class BattlePromptMovieClip
{
public:
	class Impl
	{
	public:
		void rva005F96D4();
	};
};
}
class Rva005F977D
{
public:
	void rva005F977D();
private:
	char m_pad00[0x04];
	StrategicHUD::BattlePromptMovieClip::Impl *m_04;
};
void Rva005F977D::rva005F977D()
{
	m_04->rva005F96D4();
}
