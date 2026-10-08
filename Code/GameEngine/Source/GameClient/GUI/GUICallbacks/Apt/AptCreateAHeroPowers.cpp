// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
//
// BFME2's create-a-hero powers page, AptCreateAHero::Powers (WorldBuilder:
// Code/GameEngine/Source/GameClient/Gui/GUICallbacks/Apt/AptCreateAHeroPowers.cpp).
// Names are WorldBuilder's (wb-name-unverified); layouts are from the
// retail bodies.
#include "ascii_string.h"

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
	unsigned char m_pad10[0x14 - 0x10];
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

// Existing address-named cdecl helper: four machine-word arguments. Its
// unclaimed body's parameter names and source types remain unproven.
void rva005B2295(int button, int name, int index, int page);

namespace AptCreateAHero
{
class Powers
{
public:
	int CalculateFlashState(Rva005B2E09Cell *cell);
	void UpdatePalantirButtons();
	void ExternFunc(const CommandButton *button);

private:
	Rva005B2E09Cell *FindPrereq(Rva005B2E09Cell *cell)
	{
		return (Rva005B2E09Cell *)((Rva005B2DDF *)this)->rva005B2E09(cell);
	}

	unsigned char m_pad00[0x28];
	Rva005B2E09Cell *m_cells[10]; // +0x28; retail loop advances by four bytes
	int m_numPowers;             // +0x50
	unsigned int m_numPalantir;  // +0x54
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
		rva005B2295((int)button, (int)name, i, -1);
	}
	for (unsigned int i = 0; i < (unsigned int)m_numPowers; ++i)
	{
		Rva005B2E09Cell *cell = m_cells[i];
		if (cell)
			rva005B2295((int)cell->m_button, (int)name,
				cell->m_index0c + required, -1);
	}
	for (int i = m_numPalantir; i < 6 - required; ++i)
		rva005B2295(0, (int)name, i + required, -1);
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
