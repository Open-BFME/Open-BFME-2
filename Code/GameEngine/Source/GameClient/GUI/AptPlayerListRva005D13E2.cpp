// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /DNDEBUG
// ?SetupMovieClipPlayers@Impl@RegionAwardDialog@StrategicInGameUI@@QAEXXZ @ 0x005D13E2, 201 bytes.
// Target evidence: PE RVA 0x005D13E2 begins with push ecx and returns at
// 0x005D14AA; 0x005D14AB begins the next body. The method counts the pointer
// range at +0x10..+0x14, forwards that count to 0x005EE250, and for each
// entry updates its name, ARGB color, mapped image, region count and unit
// count through the player-row APT wrappers. It finishes by setting row 0.
// Callee addresses and offsets come from BFME2 target instructions. The
// player-row wrapper and record views are structural inferences from the
// +4 delegate thunks and their rowed callees; the original host class name
// and higher-level method name are unknown, so this remains address-derived.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include "ascii_string.h"
#include "unicode_string.h"

class Image;
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};
extern ImageCollection *TheMappedImageCollection;

class Rva0020E89C;
namespace StrategicInGameUI {
class RegionAwardDialog
{
public:
	class Impl;
};
}

class Rva002BA8F1Logic;
class Object;

class Rva0020E90FView;

class Rva0020EAF6View
{
public:
	Rva0020E89C *rva0020EAF6(int index);

private:
	char m_pad00[8];
	Rva0020E90FView *m_holder;
};

struct Rva005D137DKey
{
	char m_pad00[4];
	int m_index;
};

class Rva005EE014BaseView
{
public:
	Rva005EE014BaseView(int first, int second);

private:
	void *m_vtable;
	void *m_delegate;
};

class Rva005D13BDStorage : public Rva005EE014BaseView
{
public:
	Rva005D13BDStorage(StrategicInGameUI::RegionAwardDialog::Impl *owner, int first, int second);

private:
	StrategicInGameUI::RegionAwardDialog::Impl *m_owner;
};

class Rva00575674
{
public:
	void rva00575674(Object *value);

private:
	Object *m_value;
};

UnicodeString Rva005C95ECGet(Rva0020E89C *object);

struct RGBColor
{
	int getAsInt() const;
};

class Rva005EE250
{
public:
	void rva005EE250(int count);
};

class Rva005ED976
{
public:
	void rva005ED976(const UnicodeString &text);
	void rva005ED849(int index, int color);
	void rva005ED851(int index, int value);
	void rva005ED859(int index, int value);
	void rva005ED861(int row);
	void rva005ED986(int index, const UnicodeString &name);
	void SetRegionBonusText(int index, const UnicodeString &text);
	void rva005ED5BB(int index, const Image *image);
};

class Rva002E1001
{
public:
	int rva002E1001();
};

struct Rva002E0D02Arg;
int __cdecl CountOwnedUnits(Rva002E0D02Arg *arg);

class StrategicInGameUI::RegionAwardDialog::Impl
{
public:
	void SetupMovieClipPlayers();
	void OnMovieClipLoaded(int first, const AsciiString &second);
	Rva0020E89C *GetRegion();
	void rva005D1527();

private:
	char m_pad00[8];
	Rva005D137DKey *m_key;
	Rva005ED976 *m_rowView;
	char **m_entriesBegin;
	char **m_entriesEnd;
};

extern "C" const void *const vtbl_00C755C0[];
#pragma comment(linker, "/alternatename:_vtbl_00C755C0=??_7Rva005D13BD@@6B@")

struct Rva005D13E2LoopTemps
{
	void *imageInfo;
	Rva005ED976 *currentView;
};

void StrategicInGameUI::RegionAwardDialog::Impl::SetupMovieClipPlayers()
{
	int count = (int)(m_entriesEnd - m_entriesBegin);
	reinterpret_cast<Rva005EE250 *>(m_rowView)->rva005EE250(count);

	for (int index = 0; index < count; ++index) {
		char *entry = m_entriesBegin[index];
		Rva005D13E2LoopTemps temps;
		temps.imageInfo = *(void **)(entry + 0x40);
		m_rowView->rva005ED986(index, *(UnicodeString *)(entry + 0x1C));

		int color = ((RGBColor *)(entry + 0x184))->getAsInt() | 0xFF000000;
		m_rowView->rva005ED849(index, color);

		temps.currentView = m_rowView;
		const AsciiString &imageName = *(AsciiString *)((char *)temps.imageInfo + 0x20);
		const Image *image = TheMappedImageCollection->findImageByName(imageName);
		temps.currentView->rva005ED5BB(index, image);

		temps.currentView = m_rowView;
		int regions = ((Rva002E1001 *)entry)->rva002E1001();
		temps.currentView->rva005ED851(index, regions);

		temps.currentView = m_rowView;
		int units = CountOwnedUnits((Rva002E0D02Arg *)entry);
		temps.currentView->rva005ED859(index, units);
	}

	m_rowView->rva005ED861(0);
}

// ?GetRegion@Impl@RegionAwardDialog@StrategicInGameUI@@QAEPAVRva0020E89C@@XZ @ 0x005D137D, 26 bytes.
// Target evidence: Ghidra FUN_009d137d reads the +4 dword through this+8,
// loads the holder at TheLivingWorldLogic+0xB0 (singleton VA 0x00DFEF10),
// and passes that index to the rowed 0x0020EAF6 wrapper. The receiver and
// nested key views are address-derived; their original type names are unknown.
Rva0020E89C *StrategicInGameUI::RegionAwardDialog::Impl::GetRegion()
{
	Rva0020EAF6View *holder = *(Rva0020EAF6View **)((char *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic) + 0xB0);
	return holder->rva0020EAF6(m_key->m_index);
}

// ??0Rva005D13BDStorage@@QAE@PAVImpl@RegionAwardDialog@StrategicInGameUI@@HH@Z @ 0x005D1335, 35 bytes.
// Target evidence: FUN_009d1335 receives a 12-byte child at ECX, calls the
// 0x005EE014 constructor with two stack dwords, stores its parent at +8, and
// writes vtable 0x00C755C0. The +0..+7 base view follows 0x005EE014's writes;
// the C++ class and original member names remain inferred.
__declspec(noinline) Rva005D13BDStorage::Rva005D13BDStorage(
	StrategicInGameUI::RegionAwardDialog::Impl *owner, int first, int second)
	: Rva005EE014BaseView(first, second), m_owner(owner)
{
	*(void **)this = (void *)vtbl_00C755C0;
}

// ?OnMovieClipLoaded@Impl@RegionAwardDialog@StrategicInGameUI@@QAEXHABVAsciiString@@@Z @ 0x005D17B2, 148 bytes.
// Target evidence: the 148-byte FUN_009d17b2 entry has an EH prologue and
// ret 8; it lazily allocates a 12-byte child at this+0x0C, initializes it
// from this and an integer plus an AsciiString reference, and stores it through the rowed holder
// setter. It then obtains a text object, assigns its UnicodeString through
// the child's +4 delegate, calls the UI text helper at 0x005D1527, and
// refreshes through the rowed 0x005D13E2 body. The receiver relationship
// comes from those call sites and offsets; the original class and parameter
// meanings remain unknown.
void StrategicInGameUI::RegionAwardDialog::Impl::OnMovieClipLoaded(int first, const AsciiString &second)
{
	if (m_rowView == 0) {
		Rva005D13BDStorage *child = new Rva005D13BDStorage(this, first, (int)&second);
		((Rva00575674 *)&m_rowView)->rva00575674((Object *)child);
		m_rowView->rva005ED976(Rva005C95ECGet(GetRegion()));
		rva005D1527();
		SetupMovieClipPlayers();
	}
}

class GameTextInterface {
 public:
 virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();virtual void slot6();virtual void slot7();virtual void slot8();virtual void slot9();virtual void slot10();virtual void slot11();virtual void slot12();virtual void slot13();virtual void slot14();
 virtual UnicodeString fetch(const char*,bool*);
};
extern GameTextInterface *TheGameText;
struct RegionBonusFields
{
 char gap[0x90];
 int multiplier, commandPoints, spellPoints, bonus, otherBonus;
 __forceinline int GetCommandPoints() const { return commandPoints; }
 __forceinline int GetSpellPoints() const { return spellPoints; }
 __forceinline int GetBonus() const { return bonus; }
 __forceinline int GetOtherBonus() const { return otherBonus; }
};
// BF2 5D1527..5D17B2 and WB SetupMovieClipRegionBonuses establish purpose.
// Region field meanings are independently supported by the four native labels;
// offsets90..A0 are read from the target. Inline scalar accessors preserve argument
// loads before the following UnicodeString branch and match all651 bytes.
void StrategicInGameUI::RegionAwardDialog::Impl::rva005D1527() {
 const RegionBonusFields*region=(const RegionBonusFields*)GetRegion();
 UnicodeString text;
 bool found;
 UnicodeString format=TheGameText->fetch("STRATEGICHUD:RegionAwardCommandPoints",&found);
 if(found)text.format(format.str(),region->GetCommandPoints());
 m_rowView->SetRegionBonusText(0,text);
 text.clear();
 format=TheGameText->fetch("STRATEGICHUD:RegionAwardResourceMultiplier",&found);
 if(found){float multiplier=region->multiplier*0.01f;text.format(format.str(),multiplier);}
 m_rowView->SetRegionBonusText(1,text);
 text.clear();
 format=TheGameText->fetch("STRATEGICHUD:RegionAwardSpellPoints",&found);
 if(found)text.format(format.str(),region->GetSpellPoints());
 m_rowView->SetRegionBonusText(2,text);
 text.clear();
 format=TheGameText->fetch("STRATEGICHUD:RegionAwardBonus",&found);
 if(found){
  text.format(format.str(),region->GetBonus());
  m_rowView->SetRegionBonusText(3,text);
  text.format(format.str(),region->GetOtherBonus());
  m_rowView->SetRegionBonusText(4,text);
  text.format(format.str(),region->GetBonus());
 }else{
  m_rowView->SetRegionBonusText(3,text);
  m_rowView->SetRegionBonusText(4,text);
 }
 m_rowView->SetRegionBonusText(5,text);
}
