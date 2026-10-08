// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
//
// BFME2's create-a-hero powers page, AptCreateAHero::Powers (WorldBuilder:
// Code/GameEngine/Source/GameClient/Gui/GUICallbacks/Apt/AptCreateAHeroPowers.cpp).
// Names are WorldBuilder's (wb-name-unverified); layouts are from the
// retail bodies.

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
	unsigned char m_pad0c[0x14 - 0x0C];
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
class CreateAHeroManager;
extern CreateAHeroManager *TheCreateAHeroManager;

class Rva00219309
{
public:
	int rva00219309();
};

namespace AptCreateAHero
{
class Powers
{
public:
	int CalculateFlashState(Rva005B2E09Cell *cell);

private:
	Rva005B2E09Cell *FindPrereq(Rva005B2E09Cell *cell)
	{
		return (Rva005B2E09Cell *)((Rva005B2DDF *)this)->rva005B2E09(cell);
	}

	unsigned char m_pad00[0x50];
	int m_numPowers;             // +0x50
	unsigned int m_numPalantir;  // +0x54
};
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
	if (m_numPalantir >= MAX_PALANTIR_POWERS - ((Rva00219309 *)TheCreateAHeroManager)->rva00219309())
	{
		prereq = FindPrereq(cell);
		if (!prereq || prereq->m_row < 0 || prereq->m_column < 0)
			return 5;
	}
	return 1;
}
