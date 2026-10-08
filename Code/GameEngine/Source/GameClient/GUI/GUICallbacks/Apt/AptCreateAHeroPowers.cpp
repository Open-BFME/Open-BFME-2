// cl: /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
//
// BFME2's create-a-hero powers page, AptCreateAHero::Powers (WorldBuilder:
// Code/GameEngine/Source/GameClient/Gui/GUICallbacks/Apt/AptCreateAHeroPowers.cpp).
// Names are WorldBuilder's (wb-name-unverified); layouts are from the
// retail bodies.
#include "ascii_string.h"
// stlport
#include <map>

class Image;
class CommandButton
{
public:
	const Image *rva0035B19E() const;
};
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};
extern ImageCollection *TheMappedImageCollection;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
class Rva002239B2
{
public:
	void rva002239E2(const AsciiString &name, const Image *image);
};
class Rva00223A94
{
public:
	int rva00223A94(const AsciiString *name);
};

// The hero at owner+0x27c is accessed through its rowed button setter and
// an unidentified target vslot at +0x14. This declaration adds no vtable body.
class CreateAHeroHero
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	bool SetButtonForLevel(const AsciiString &button, unsigned int level, unsigned int value);
};
struct Rva005B3676Owner
{
	char m_pad00[0x274];
	void *m_aptOwner;
	char m_pad278[4];
	CreateAHeroHero m_hero;
};
class Rva005B35E8
{
public:
	void rva005B35E8();
};
class Rva00222A8BTarget;
int Rva002D4531Invoke(Rva00222A8BTarget *target, void *owner, const char *name, const int &arg);

// The power grid's cell: its command button at +0x00, the grid row and
// column at +0x04 / +0x08 (negative when unset) and the owned flag at +0x14.
struct Rva005B2E09Cell;

// The command button's +0x?? count getter (rowed 0x002190A1).
class Rva002190A1DwordField
{
public:
	int get() const;
};

struct Rva005B2E09Cell
{
	Rva002190A1DwordField *m_button; // +0x00
	int m_row;                       // +0x04
	int m_column;                    // +0x08
	int m_index0c;                    // +0x0c; UpdatePalantirButtons adds required count
	int m_powerIndex;                 // +0x10; AddMyPower stores the page count
	bool m_owned;                    // +0x14
};

// The prerequisite search over the page's grid (rowed 0x005B2E09, an
// address-named view of this page).
class Rva005B2DDF
{
public:
	void *rva005B2E09(Rva005B2E09Cell *cell);
};

// TheCreateAHeroManager 0x009FE344 and its rowed 0x00219309 count.
class CreateAHeroManager
{
public:
	int GetRequiredButtonCount();
	const class CommandButton *GetRequiredButton(unsigned int index);
};
extern CreateAHeroManager *TheCreateAHeroManager;

// Rowed in AptHeroPowerText.cpp: points the Apt image key "%s_%d" (or
// "%s_%d_%d") at the button's image and returns whether it changed.
bool __cdecl rva005B2295(const CommandButton *button, const char *prefix, int index, int page);

// Target 0x005B2B3B returns a copy of the string at +0x240, substituting
// AsciiString::TheEmptyString when it is absent. The caller 0x005B3FAB
// supplies the grid cell's button pointer. The owner's original name is unknown.
class Rva005B2B3BOwner {
public:
	AsciiString rva005B2B3B() const;
private:
	unsigned char m_pad00[0x240];
	AsciiString m_prerequisite;
};
namespace AptCreateAHero
{
class Powers
{
public:
	Rva005B2E09Cell *GetPrereqData(Rva005B2E09Cell *cell);
	int CalculateFlashState(Rva005B2E09Cell *cell);
	void UpdatePalantirButtons();
	void ExternFunc(const CommandButton *button);
	void AddMyPower(Rva005B2E09Cell *cell, bool flash);

private:
	Rva005B2E09Cell *FindPrereq(Rva005B2E09Cell *cell)
	{
		return (Rva005B2E09Cell *)((Rva005B2DDF *)this)->rva005B2E09(cell);
	}

	unsigned char m_pad00[4];
	Rva005B3676Owner *m_owner;  // +0x04; target owner contains hero at +0x27c
	std::map<AsciiString, Rva005B2E09Cell> m_powersNameMap;
	unsigned char m_pad14[0x28 - 0x14];
	Rva005B2E09Cell *m_cells[10]; // +0x28; retail loop advances by four bytes
	int m_numPowers;             // +0x50
	unsigned int m_numPalantir;  // +0x54
	bool m_changed;             // +0x58
};
}

// ?UpdatePalantirButtons@Powers@AptCreateAHero@@QAEXXZ @0x005B2794 154B.
// WorldBuilder method lead (wb-name-unverified); target evidence: the required
// button count/getter pair, "PalantirBttn", cell pointers +0x28, count +0x50,
// next free slot +0x54, and cell index +0x0c. The caller 0x005B486D tail-calls
// this member with its original receiver.
void AptCreateAHero::Powers::UpdatePalantirButtons()
{
	int required = TheCreateAHeroManager->GetRequiredButtonCount();
	const char *name = "PalantirBttn";
	for (int i = 0; i < required; ++i)
	{
		const CommandButton *button = TheCreateAHeroManager->GetRequiredButton(i);
		rva005B2295(button, name, i, -1);
	}
	for (unsigned int i = 0; i < (unsigned int)m_numPowers; ++i)
	{
		Rva005B2E09Cell *cell = m_cells[i];
		if (cell)
			rva005B2295((const CommandButton *)cell->m_button, name,
				cell->m_index0c + required, -1);
	}
	for (int i = m_numPalantir; i < 6 - required; ++i)
		rva005B2295(0, name, i + required, -1);
}

// ?ExternFunc@Powers@AptCreateAHero@@QAEXPBVCommandButton@@@Z @0x005B2E65 187B.
// WorldBuilder supplies the ExternFunc lead (wb-name-unverified). Retail does
// not use the receiver; ret4 consumes one button pointer. The image getter,
// fallback image lookup and Apt set/erase bodies establish the argument roles.
void AptCreateAHero::Powers::ExternFunc(const CommandButton *button)
{
	if (button)
	{
		const Image *image = button->rva0035B19E();
		if (!image)
			image = TheMappedImageCollection->findImageByName("CircleRed_42x42");
		((Rva002239B2 *)g_bfmeAptWindowManager)->rva002239E2("Cah::CurSpellImage", image);
	}
	else
	{
		AsciiString name("Cah::CurSpellImage");
		((Rva00223A94 *)g_bfmeAptWindowManager)->rva00223A94(&name);
	}
}

static const unsigned int MAX_POWERS = 10;
static const unsigned int MAX_PALANTIR_POWERS = 6;

// ?AddMyPower@Powers@AptCreateAHero@@QAEXPAURva005B2E09Cell@@_N@Z
// @0x005B3676 219B: WorldBuilder name lead (wb-name-unverified). The target
// stores cell indices +0x0c/+0x10, calls the rowed hero setter at owner+0x27c,
// optionally dispatches "FlashPalantir", updates the count and owned flags.
void AptCreateAHero::Powers::AddMyPower(Rva005B2E09Cell *cell, bool flash)
{
	if (cell->m_owned || (unsigned int)m_numPowers >= MAX_POWERS)
		return;
	Rva005B2E09Cell *prereq = FindPrereq(cell);
	int required = TheCreateAHeroManager->GetRequiredButtonCount();
	if (prereq)
		cell->m_index0c = prereq->m_index0c;
	else
	{
		if (m_numPalantir >= MAX_PALANTIR_POWERS - required)
			return;
		cell->m_index0c = m_numPalantir;
		++m_numPalantir;
	}
	m_cells[m_numPowers] = cell;
	cell->m_powerIndex = m_numPowers;
	m_owner->m_hero.SetButtonForLevel(*(const AsciiString *)((const char *)cell->m_button + 0x10),
		m_numPowers, cell->m_index0c + required);
	if (flash)
	{
		m_owner->m_hero.slot14();
		int slot = cell->m_index0c + required + 1;
		Rva002D4531Invoke((Rva00222A8BTarget *)g_bfmeAptWindowManager,
			m_owner->m_aptOwner, "FlashPalantir", slot);
	}
	++m_numPowers;
	((Rva005B35E8 *)this)->rva005B35E8();
	cell->m_owned = true;
	m_changed = true;
}

// Retail 0x005B32D5, 137 bytes: AptCreateAHero::Powers::CalculateFlashState
// (WorldBuilder, AptCreateAHeroPowers.cpp line 803; wb-name-unverified).
int AptCreateAHero::Powers::CalculateFlashState(Rva005B2E09Cell *cell)
{
	if (cell->m_owned)
		return 4;
	Rva002190A1DwordField *button = cell->m_button;
	if (!button)
		return 0;
	int needed = button->get() - 1;
	int count = m_numPowers;
	if (count < needed)
		return 3;
	Rva005B2E09Cell *prereq = FindPrereq(cell);
	if (prereq && !prereq->m_owned)
		return 2;
	if ((unsigned int)count >= MAX_POWERS)
		return 6;
	if (m_numPalantir >= MAX_PALANTIR_POWERS - TheCreateAHeroManager->GetRequiredButtonCount())
	{
		prereq = FindPrereq(cell);
		if (!prereq || prereq->m_row < 0 || prereq->m_column < 0)
			return 5;
	}
	return 1;
}

// WorldBuilder names GetPrereqData at 0x01576D30, paired with retail
// 0x005B3FAB..0x005B400A. The target supplies cell->button, returns the
// prerequisite string through 0x005B2B3B, and searches the AsciiString-keyed
// map at +8. Its result is the address of the inline cell at node+0x14.
// The grid-cell type is the established view used by the sibling methods;
// the mapped type is structural inference, checked by the whole emitted find
// body and every pre-existing row in this unit.
Rva005B2E09Cell *AptCreateAHero::Powers::GetPrereqData(Rva005B2E09Cell *cell)
{
	AsciiString prereq = ((const Rva005B2B3BOwner *)cell->m_button)->rva005B2B3B();
	if (prereq.isEmpty())
	    return 0;
	std::map<AsciiString, Rva005B2E09Cell>::iterator it = m_powersNameMap.find(prereq);
	if (it == m_powersNameMap.end())
	    return 0;
	return &it->second;
}

AsciiString Rva005B2B3BOwner::rva005B2B3B() const
{
	if (m_prerequisite.isNone())
	    return AsciiString::TheEmptyString;
	return m_prerequisite;
}
