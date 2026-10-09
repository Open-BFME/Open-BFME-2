// cl: /Ob2 /Ireference/shims/bfmealloc /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
//
// BFME2's create-a-hero powers page, AptCreateAHero::Powers (WorldBuilder:
// Code/GameEngine/Source/GameClient/Gui/GUICallbacks/Apt/AptCreateAHeroPowers.cpp).
// Names are WorldBuilder's (wb-name-unverified); layouts are from the
// retail bodies.
#include "ascii_string.h"
#include "unicode_string.h"
#include <stdio.h>
// stlport
#include <stdlib.h>
// Retail uses the throwing allocation releaser during container teardown;
// unlike CRT free this preserves the destructor's native EH states.
void Rva00030830FreeAllocation(void *);
#define free Rva00030830FreeAllocation
#include <map>
#include <vector>
#undef free
#include <string.h>
struct BfmePod16 {char bytes[16];};
namespace _STL {template<> __declspec(noinline) BfmePod16 *vector<BfmePod16>::erase(BfmePod16 *,BfmePod16 *);}
class Rva005B3751 {public:void rva005B3947();};

class GameWindow;
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
class Rva00222A8BTarget
{
public:
	int invoke(void *owner, const char *name, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};
AsciiString Rva00222834Get(int value);
static inline const char *Rva005B2F42Str(const AsciiString &value)
{
	return ((const StringBase<char> *)&value)->str();
}
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
	int m_word18;           // +0x18; opaque native tail
};

// The prerequisite search over the page's grid (rowed 0x005B2E09, an
// address-named view of this page).
class Rva005B2DDF
{
public:
	void *rva005B2E09(Rva005B2E09Cell *cell);
	void *rva005B2DDF(unsigned int row, unsigned int column);
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
UnicodeString Rva005B2376Describe(void *power, const AsciiString &unused, const AsciiString &fallback);

// Native base vtable C72B74 and derived vtable C72F3C have eight slots.
// The base retains only its vptr and the holder pointer at +4; its original
// name is unknown. Target lifecycle bodies prove the empty base teardown.
class Rva005B414FBase
{
public:
    Rva005B414FBase(Rva005B3676Owner *owner) : m_owner(owner) {}
    virtual ~Rva005B414FBase() {}
    virtual void rva000B3FD0_1();
    virtual void rva005B455D(bool);
    virtual void rva005B486D();
    virtual void rva000B3FD0_4();
    virtual int rva005748AD_5(int, int, int);
    virtual int rva005748AD_6(int, int, int);
    virtual void rva005B2B6D(const char *);
protected:
    Rva005B3676Owner *m_owner;
};

namespace AptCreateAHero
{
class Powers : public Rva005B414FBase
{
public:
    Powers(Rva005B3676Owner *);
    virtual ~Powers();
    virtual void rva005B455D(bool);
    virtual void rva005B486D();
    virtual void rva005B2B6D(const char *);
    void rva000D1407(const char *, void *, GameWindow *);
    void rva005B314B(const char *);
    void UpdateAvailablePowerIcons();
    void rva005B2703(const char *);
    void rva005B271E(const char *);
    void rva005B278D(const char *);
    void MyPowerToolTip(const char *);
    void rva005B2951(int, char *, bool);
	void rva005B3D50();
	void MatrixToolTip(const char *path);
	void PalantirToolTip(const char *path);
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

	std::map<AsciiString, Rva005B2E09Cell> m_powersNameMap;
	std::vector<BfmePod16> m_groups; // target14..20
	Rva005B2E09Cell *m_groupCurrent; //20; selected cell pointer
	int m_groupMax; //24
	Rva005B2E09Cell *m_cells[10]; // +0x28; retail loop advances by four bytes
	int m_numPowers;             // +0x50
	unsigned int m_numPalantir;  // +0x54
	bool m_changed;             // +0x58
	bool m_flag59;
	char m_pad5a[2];
	std::vector<unsigned short> m_rows; // +0x5c; seven entries initially
	UnicodeString m_name;              // +0x68
	int m_word6c, m_word70;             // selected column/row
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

// Native 0x005B3245..0x005B32D5: parse the one-based matrix row/column,
// fetch the grid cell, and keep its description at +0x68 or the empty string.
// WB MatrixToolTip 0x015751D0 supplies the method identity (wb-name-unverified).
void AptCreateAHero::Powers::MatrixToolTip(const char *path)
{
	int row, column;
	if (sscanf(path, "%d,%d", &row, &column) != 2)
		return;
	--row;
	--column;
	Rva005B2E09Cell *cell = (Rva005B2E09Cell *)((Rva005B2DDF *)this)->rva005B2DDF(row, column);
	if (cell)
		m_name = Rva005B2376Describe(cell->m_button, AsciiString::TheEmptyString, AsciiString::TheEmptyString);
	else
		m_name = UnicodeString::TheEmptyString;
}

// Native 0x005B2BDD..0x005B2CE5: select the last matching grid cell,
// fall back to required buttons, and store the tooltip at +0x68.
// WB PalantirToolTip 0x01574F90 supplies the method lead (wb-name-unverified).
// The fallback loop tests the button before the bound; full-expression string
// temporaries give retail's lifetimes and stack slots.
void AptCreateAHero::Powers::PalantirToolTip(const char *path)
{
	int required = TheCreateAHeroManager->GetRequiredButtonCount();
	int index;
	if (sscanf(path, "%d", &index) != 1)
		return;
	--index;
	Rva005B2E09Cell *selected = 0;
	for (int i = 0; i < 10; ++i)
	{
		Rva005B2E09Cell *cell = m_cells[i];
		if (cell && cell->m_index0c + required == index)
			selected = cell;
	}
	const CommandButton *button = selected ? (const CommandButton *)selected->m_button : 0;
	if (!button)
	{
		for (int i = 0; !button && i < required; ++i)
			if (i == index)
				button = TheCreateAHeroManager->GetRequiredButton(i);
	}
	m_name = Rva005B2376Describe((void *)button, "TOOLTIP:CAH_IN_PALANTIR", "TOOLTIP:CAH_PALANTIR_EMPTY_SLOT");
}

static inline const char *Rva005B2F42Pass(const char *value) { return value; }

// Native 0x005B2F42..0x005B2FDC: six cdecl parameters; two integer
// references become temporary strings, while the third argument is a string
// held by reference. Callers pass UpdateSelectPowerIcon with row/column/state.
// The original template/helper name is unknown. The pass-through preserves
// evaluation of the third argument before str() on the temporary strings.
int Rva005B2F42Invoke(Rva00222A8BTarget *target, void *owner, const char *name, const int &a, const int &b, const char *const &c)
{
	return target->invoke(owner, name, 3, Rva005B2F42Str(Rva00222834Get(a)), (void *)Rva005B2F42Str(Rva00222834Get(b)), (void *)Rva005B2F42Pass(c), 0, 0);
}

// Native5B3D50..5B3D94,68B; called by BuildPowersData5B4653.
// WB15746F0 independently proves clearing cells/map/groups and resetting
// counts. Group stride16 and current/max20/24 are target facts.
void AptCreateAHero::Powers::rva005B3D50()
{
 memset(m_cells,0,sizeof(m_cells));
 ((Rva005B3751 *)&m_powersNameMap)->rva005B3947();
 std::vector<BfmePod16> *groups=&m_groups;
 groups->erase(groups->begin(),groups->end());
 m_groupCurrent=0;
 m_numPowers=0;
 m_groupMax=10;
 ((Rva005B35E8 *)this)->rva005B35E8();
 m_numPalantir=0;
}

class __single_inheritance AptDelegateTarget;
typedef void (AptDelegateTarget::*AptDelegateMethod)(void);

struct DelegateDesc
{
	template <class T, class M> DelegateDesc(T *object, M method)
		: m_object(reinterpret_cast<AptDelegateTarget *>(object))
		, m_method(reinterpret_cast<AptDelegateMethod>(method))
	{
	}

	AptDelegateTarget *m_object;
	AptDelegateMethod m_method;
};

template <class T, class M> __forceinline DelegateDesc MakeDelegate(T *object, M method)
{
	DelegateDesc desc(object, method);
	return desc;
}

class Rva00579E47
{
public:
	Rva00579E47(const DelegateDesc &desc);
	Rva00579E47(const Rva00579E47 &other);
	~Rva00579E47();

private:
	void *m_ptr;
};

template <class T> class AptRef : public Rva00579E47
{
public:
	AptRef(const DelegateDesc &desc) : Rva00579E47(desc) {}
};

class AptExternHandler;

class AptExternHandlerAdder
{
public:
	void AddExternHandler(const AsciiString &name, int arg, AptRef<AptExternHandler> handler);
};


class AptScreenInitGadgets;
class AptCommandMap;
class AptCommandMapAdder {public:void AddCommandMap(const AsciiString &,AptRef<AptCommandMap>);};
void _bfme_setAptScreenRef(const AsciiString&,AptRef<AptScreenInitGadgets>);
class Rva005B2725 {public:void Run(int);};
// Native 5B414F..5B4541 (1010B): member initialization followed by Apt
// registrations. WorldBuilder's Powers constructor supplies the class lead;
// retail literals, member addresses and callback targets establish the ABI.
AptCreateAHero::Powers::Powers(Rva005B3676Owner *holder)
    : Rva005B414FBase(holder), m_groupCurrent(0), m_groupMax(10),
      m_numPowers(0), m_numPalantir(0), m_changed(false), m_flag59(false),
      m_rows(7), m_word6c(0), m_word70(0)
{
 memset(m_cells,0,sizeof(m_cells));
 {AsciiString name("CahPowers::InitGadgets");_bfme_setAptScreenRef(name,AptRef<AptScreenInitGadgets>(MakeDelegate(this,&Powers::rva000D1407)));}

{AsciiString name("AptCreateAHero::OnPowerSelect");((AptCommandMapAdder*)((char*)holder+0x21c))->AddCommandMap(name,AptRef<AptCommandMap>(MakeDelegate(this,&Powers::rva005B314B)));}
{AsciiString name("AptCreateAHero::OnMyPowerSelect");((AptCommandMapAdder*)((char*)holder+0x21c))->AddCommandMap(name,AptRef<AptCommandMap>(MakeDelegate(this,&Powers::rva005B2703)));}
{AsciiString name("AptCreateAHero::PowersIconsUpdate");((AptCommandMapAdder*)((char*)holder+0x21c))->AddCommandMap(name,AptRef<AptCommandMap>(MakeDelegate(this,&Powers::rva005B271E)));}
{AsciiString name("AptCreateAHero::OnPowerSelectionComplete");((AptCommandMapAdder*)((char*)holder+0x21c))->AddCommandMap(name,AptRef<AptCommandMap>(MakeDelegate((Rva005B2725*)this,&Rva005B2725::Run)));}
{AsciiString name("AptCreateAHero::OnResetBttn");((AptCommandMapAdder*)((char*)holder+0x21c))->AddCommandMap(name,AptRef<AptCommandMap>(MakeDelegate(this,&Powers::rva005B278D)));}
{AsciiString name("AptCreateAHero::PalantirToolTip");((AptCommandMapAdder*)((char*)holder+0x21c))->AddCommandMap(name,AptRef<AptCommandMap>(MakeDelegate(this,&Powers::PalantirToolTip)));}
{AsciiString name("AptCreateAHero::MatrixToolTip");((AptCommandMapAdder*)((char*)holder+0x21c))->AddCommandMap(name,AptRef<AptCommandMap>(MakeDelegate(this,&Powers::MatrixToolTip)));}
{AsciiString name("AptCreateAHero::MyPowerToolTip");((AptCommandMapAdder*)((char*)holder+0x21c))->AddCommandMap(name,AptRef<AptCommandMap>(MakeDelegate(this,&Powers::MyPowerToolTip)));}

{AsciiString name("NumPowerRows");((AptExternHandlerAdder*)((char*)holder+0x228))->AddExternHandler(name,0,AptRef<AptExternHandler>(MakeDelegate(this,&Powers::rva005B2951)));}
{AsciiString name("DisablePowerInstructions");((AptExternHandlerAdder*)((char*)holder+0x228))->AddExternHandler(name,1,AptRef<AptExternHandler>(MakeDelegate(this,&Powers::rva005B2951)));}
{AsciiString name("CurrentPowerIndex");((AptExternHandlerAdder*)((char*)holder+0x228))->AddExternHandler(name,2,AptRef<AptExternHandler>(MakeDelegate(this,&Powers::rva005B2951)));}
{AsciiString name("NumCurrentPowers");((AptExternHandlerAdder*)((char*)holder+0x228))->AddExternHandler(name,3,AptRef<AptExternHandler>(MakeDelegate(this,&Powers::rva005B2951)));}
}

// Native callbacks registered by the constructor. Their original method
// names remain unknown; retain the address-derived spellings.
void AptCreateAHero::Powers::rva005B2703(const char *value)
{
    int n = atoi(value);
    if (n == m_numPowers)
        m_groupMax = n - 1;
}

void AptCreateAHero::Powers::rva005B271E(const char *)
{
    m_changed = true;
}

void AptCreateAHero::Powers::rva005B278D(const char *)
{
    m_groupMax = 0;
}

// Native callback 5B2951..5B2A37 (230B); WB1576FC0 query/set signature.
// The inventory's 11B entry ends inside its switch prologue; the complete
// body ends at RET12. The registered properties establish each selector.
static bool powersQuerySeen;
void AptCreateAHero::Powers::rva005B2951(int query, char *value, bool set)
{
    switch (query)
    {
    case 0:
        if (!set)
            sprintf(value, "%d", m_groups.size());
        break;
    case 1:
        if (!set)
        {
            strcpy(value, powersQuerySeen ? "1" : "0");
            powersQuerySeen = true;
        }
        break;
    case 2:
        if (set)
        {
            sscanf(value, "%d %d", &m_word70, &m_word6c);
            --m_word6c;
            --m_word70;
        }
        else
        {
            strcpy(value, "-1");
            if ((unsigned)m_word6c < 4 && (unsigned)m_word70 < m_groups.size())
            {
                Rva005B2E09Cell *cell = *(Rva005B2E09Cell **)
                    (m_groups[m_word70].bytes + 4 * m_word6c);
                if (cell)
                    sprintf(value, "%d", cell->m_powerIndex + 1);
            }
        }
        break;
    case 3:
        if (!set)
            sprintf(value, "%d", m_numPowers);
        break;
    }
}

void _bfme_closeAptScreen(const AsciiString &);
// Native 5B3D94..5B3E59 (197B): close the observed Apt registration,
// release its image name, then destroy string/vector/map members in order.
AptCreateAHero::Powers::~Powers()
{
    _bfme_closeAptScreen(AsciiString("CahPowers::Powers::InitGadgets"));
    ((Rva00223A94 *)g_bfmeAptWindowManager)->rva00223A94(&AsciiString("Cah::CurSpellImage"));
    m_groupCurrent = 0;
}

class Rva004072D2 {public: bool rva004072D2(int);};
// Native virtual slot2 C72F3C+8, 5B455D..5B4610; WB1574990.
// The current selection is a cell pointer; 24 is the requested retained count.
void AptCreateAHero::Powers::rva005B455D(bool active)
{
 if (!active) return;
 if (m_groupCurrent) {
   AddMyPower(m_groupCurrent,true);
   m_groupCurrent=0;
 } else if ((unsigned)m_groupMax < 10) {
   while ((unsigned)m_numPowers > (unsigned)m_groupMax) {
     --m_numPowers;
     Rva005B2E09Cell *cell=m_cells[m_numPowers];
     if (cell) {
       cell->m_index0c=-1;
       cell->m_powerIndex=-1;
       cell->m_owned=false;
       m_cells[m_numPowers]=0;
       ((Rva004072D2*)&m_owner->m_hero)->rva004072D2(m_numPowers);
       if (!FindPrereq(cell)) --m_numPalantir;
     }
   }
   m_owner->m_hero.slot14();
   ((Rva005B35E8*)this)->rva005B35E8();
   m_groupMax=10;
   m_changed=true;
 }
 if (m_changed) {
   UpdateAvailablePowerIcons();
   UpdatePalantirButtons();
 }
}

class BfmeAptWindowManager {public:void bfmeSetText(const AsciiString&,const UnicodeString&,bool);};
class GameTextInterface
{
public:
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0C();virtual void slot10();virtual void slot14();
 virtual void slot18();virtual void slot1C();virtual void slot20();virtual void slot24();virtual void slot28();virtual void slot2C();
 virtual void slot30();virtual void slot34();
 virtual UnicodeString fetch(const char *label,bool *exists=0);
 virtual UnicodeString fetch(const AsciiString &label,bool *exists=0);
};
extern GameTextInterface *TheGameText;
// Native writable seven-entry label table DD3A9C: zero followed by the six
// availability/error labels. Its original name is unknown.
const char *g_00DD3A9C[]={0,"TOOLTIP:CAH_IS_AVAILABLE","TOOLTIP:CAH_NEEDS_PREREQ","TOOLTIP:CAH_LEVEL_TOO_LOW","TOOLTIP:CAH_IS_SELECTED","TOOLTIP:CAH_PALANTIR_FULL","TOOLTIP:CAH_POWER_BOOK_FULL"};
void Rva0043DB23(Rva00222A8BTarget*,void*,const char*);
// Native250B constructor-registered OnPowerSelect callback; WB1574C40
// supplies the method lead. Keep the established address spelling.
void AptCreateAHero::Powers::rva005B314B(const char *path)
{
 int row,column;
 if (sscanf(path,"%d,%d",&row,&column)!=2) return;
 Rva005B2E09Cell *cell=(Rva005B2E09Cell*)((Rva005B2DDF*)this)->rva005B2DDF(row-1,column-1);
 if (!cell) return;
 switch (cell->m_word18) {
 case 1:m_groupCurrent=cell;break;
 case 2:case 3:case 5:case 6:
 {
   const char *label=g_00DD3A9C[cell->m_word18];
   {AsciiString key("APT:HeroPowersError");
   g_bfmeAptWindowManager->bfmeSetText(key,TheGameText->fetch(label),false);}
   Rva0043DB23((Rva00222A8BTarget*)g_bfmeAptWindowManager,m_owner->m_aptOwner,"ShowPowerErrorMessage");
 }break;
 }
}
