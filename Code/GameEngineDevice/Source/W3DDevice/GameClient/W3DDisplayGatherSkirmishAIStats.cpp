// ?gatherSkirmishAIStats@W3DDisplay@@QAEXXZ
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG
// platformsdk
// W3DDisplay::gatherSkirmishAIStats, retail 0x0004AA4A..0x0004B180 (1846 B,
// RET 0). WorldBuilder 0x00966C80 names it (W3DDevice/GameClient/W3DDisplay.cpp,
// the "Failed to create DisplayString" assert at line 1339) and gives the
// statement order: build the debug display string once (native debug font or
// FixedSys 8), then for every active player (AI players only when they are
// the selected AI index) a block of "Human"/"AI (%s - %s)", the economy and
// unit stats, the skill points and the skirmish AI's targets, padded into
// 25-character columns. Retail keeps one display string at +0x1CC (the
// debug build's one-element array loop unrolled). Callee and field names are
// target evidence where rowed, address-derived otherwise.
#include <windows.h>
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../../GameEngine/Source/Common/PartitionRangeQueryCallView.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

struct Coord3D;
class GameFont;
class FontLibrary
{
public:
	GameFont *getFont(const AsciiString *name, float pointSize, bool bold);
};
extern FontLibrary *TheFontLibrary;

struct FontDesc
{
	AsciiString name;	// +0x00
	Int size;		// +0x04
	Bool bold;		// +0x08
};
class GlobalLanguage
{
public:
	char m_pad00[0xC8];
	FontDesc m_nativeDebugDisplay;	// +0xC8
};
extern GlobalLanguage *TheGlobalLanguageData;

class DisplayString
{
public:
	virtual ~DisplayString();
	virtual void setText(UnicodeString text);	// +0x04
	virtual UnicodeString getText();
	virtual Int getTextLength();
	virtual void notifyTextChanged();
	virtual void reset();
	virtual void setFont(GameFont *font);		// +0x18
};
class DisplayStringManager
{
public:
#define V(n) virtual void v##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
	V(10) V(11) V(12) V(13)
#undef V
	virtual DisplayString *newDisplayString();	// +0x38
};
extern DisplayStringManager *TheDisplayStringManager;

class ThingTemplate
{
public:
	unsigned char m_pad00[0x64];
	AsciiString m_displayName;			// +0x64
	unsigned char m_pad68[0x113 - 0x68];
	unsigned char m_kindOf113;			// +0x113, bit 2: hero
	unsigned char m_pad114[0x121 - 0x114];
	unsigned char m_kindOf121;			// +0x121, bit 4: searched for a structure
};
class Object
{
public:
	unsigned char m_pad00[4];
	const ThingTemplate *m_template;		// +0x04
	unsigned char m_pad08[0x38 - 8];
	unsigned char m_position[0x0C];			// +0x38
	unsigned char m_pad44[0x304 - 0x44];
	void *m_team;					// +0x304
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return (const Coord3D *)m_position; }
};

class Player
{
public:
	Bool rva002AA245() const;			// 0x002AA245
	unsigned char m_pad00[0x14];
	Real getSkillPointsTotal() const { return m_skillPointsTotal; }
	Real m_skillPointsTotal;			// +0x14
	unsigned char m_pad18[0x4C - 0x18];
	const AsciiString &getSide() const { return m_side; }
	const AsciiString &getPlayerName() const { return m_playerName; }
	AsciiString m_side;				// +0x4C
	unsigned char m_pad50[0x58 - 0x50];
	AsciiString m_playerName;			// +0x58
	Int m_playerType;				// +0x5C
	unsigned char m_pad60[0x94 - 0x60];
	Int m_money;					// +0x94
	unsigned char m_pad98[0x2EC - 0x98];
	void *m_defaultTeam;				// +0x2EC
};
class PlayerList
{
public:
	Player *getNthPlayer(int index);
	char m_pad00[0x10];
	Player *m_local; // +0x10
	int m_playerCount; // +0x14 +0x14
};
extern PlayerList *ThePlayerList;

// The per-player economy record and unit list the AI stats come from.
// 0x002BEDAB is the rowed hash_map<int,int>::bucket_count alias both holders call.
namespace _STL
{
template <class A, class B> struct pair
{
};
template <class T> struct hash
{
};
template <class T> struct equal_to
{
};
template <class T> class allocator
{
};
template <class K, class V, class H, class E, class A> class hash_map
{
public:
	unsigned int bucket_count() const;
};
}
typedef _STL::hash_map<int, int, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, int> > > IntMap;
class Rva0025BFF8 { public: Object *rva0025BFF8(Int index); };		// 0x0025BFF8
struct Rva002A8F24Economy
{
	unsigned char m_pad00[0x14];
	Int m_saved;					// +0x14
};
struct Rva002A8F24Stats
{
	Rva0025BFF8 *m_units;				// +0x00
	unsigned char m_pad04[0x0C - 4];
	Rva002A8F24Economy *m_economy;			// +0x0C
};
// A skirmish AI target: its type, its object and its done flags.
class Bfme939Helper { public: Int get() const; };
class Rva002C589B
{
public:
	Object *rva002C5DA6();				// 0x002C5DA6
	Int rva0030F2C7() const;			// 0x0030F2C7
	unsigned char m_pad00[4];
	Int m_type;					// +0x04
	unsigned char m_pad08[0x18 - 8];
	Bool m_destroyed;				// +0x18
	Bool m_cancelled;				// +0x19
	unsigned char m_pad1A[0x20 - 0x1A];
	Int m_count;					// +0x20
};
class Rva002C5FCBNullAdjustField { public: Int get() const; };	// 0x002C5FCB
struct Rva002C589BList
{
	Rva002C589B **m_begin;
	Rva002C589B **m_end;
};
struct Rva002A8AB1Record
{
	void *rva002C6ACB();				// 0x002C6ACB, the primary player target
	Player *getPrimaryPlayerTarget() { return (Player *)rva002C6ACB(); }
	unsigned char m_pad00[0x164];
	Rva002C5FCBNullAdjustField *m_targets;		// +0x164
};
class Rva002A8F24
{
public:
	void *rva002A8F24(Player *player);		// 0x002A8F24
	Rva002A8AB1Record *rva002A8AB1(void *player);	// 0x002A8AB1
	unsigned char m_pad00[0x860];
	Bool m_showAllAI;				// +0x860
};
extern Rva002A8F24 *TheSkirmishAIManager;
extern Int g_bfmeSkirmishAIDebugIndex;	// the selected AI index
extern const char *AITargetTypeNames[];

class BfmeFixedStorage0004543D
{
	unsigned char bytes[28];
};
struct Rva00045411BitSet
{
	Rva00045411BitSet(int, int) throw();
	unsigned int bits[7];
};
template <int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;
class Rva000421C8
{
public:
	Rva000421C8() : next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *next;
};
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &, const BfmeFixedStorage0004543D &);
	virtual bool allow(Object *);
	BfmeFixedStorage0004543D a, b;
};
extern PartitionManager *ThePartitionManager;

class W3DDisplay
{
public:
	void gatherSkirmishAIStats();
private:
	unsigned char m_pad00[0x1CC];
	DisplayString *m_skirmishAIString[1];		// +0x1CC
};

static __forceinline Int columnPad(const AsciiString &asciiString)
{
	return 25 - asciiString.getLength();
}

void W3DDisplay::gatherSkirmishAIStats()
{
	if (m_skirmishAIString[0] == NULL)
	{
		GameFont *font;
		GlobalLanguage *language = TheGlobalLanguageData;
		// The out-of-line StringBase test (0x00001E2F), not AsciiString's inline one.
		if (language && !((const StringBase<char> &)language->m_nativeDebugDisplay.name).isEmpty())
		{
			font = TheFontLibrary->getFont(&language->m_nativeDebugDisplay.name,
				(Real)language->m_nativeDebugDisplay.size,
				language->m_nativeDebugDisplay.bold);
		}
		else
		{
			AsciiString fixedSys("FixedSys");
			font = TheFontLibrary->getFont(&fixedSys, 8.0f, FALSE);
		}

		for (Int i = 0; i < 1; i++)
		{
			if (m_skirmishAIString[i] == NULL)
			{
				m_skirmishAIString[i] = TheDisplayStringManager->newDisplayString();
				m_skirmishAIString[i]->setFont(font);
			}
		}
	}

	UnicodeString unibuffer;
	unibuffer.format(L"\n");
	Int aiIndex = 0;
	Int numPlayers = ThePlayerList->m_playerCount;
	for (Int i = 0; i < numPlayers; i++)
	{
		Player *player = ThePlayerList->getNthPlayer(i);
		if (!player->rva002AA245())
			continue;
		if (player->m_playerType == 0 || aiIndex == g_bfmeSkirmishAIDebugIndex)
		{
			UnicodeString line;
			if (player->m_playerType == 1 || TheSkirmishAIManager->m_showAllAI)
			{
				AsciiString aiName;
				aiName.format("AI (%s - %s)\n", player->m_side.str(), player->m_playerName.str());
				line.translate(aiName);
			}
			else
			{
				line.format(L"Human\n");
			}
			unibuffer.concat(line);

			Rva002A8F24Stats *eStats = (Rva002A8F24Stats *)TheSkirmishAIManager->rva002A8F24(player);
			if (eStats)
			{
				Rva002A8F24Economy *economy = eStats->m_economy;
				line.format(L"<********* Economy Stats *********>\n");
				unibuffer.concat(line);
				line.format(L"...$: %d\n", player->m_money);
				unibuffer.concat(line);
				line.format(L"...Saved: %d\n", economy->m_saved);
				unibuffer.concat(line);
				line.format(L"...# of Farms: %d\n", ((IntMap *)economy)->bucket_count());
				unibuffer.concat(line);

				Rva0025BFF8 *units = eStats->m_units;
				line.format(L"<********* Unit Stats *********>\n");
				unibuffer.concat(line);
				Int hordeUnits = 0;
				Int heroUnits = 0;
				Int idleUnits = 0;
				UnsignedInt unitCount = ((IntMap *)units)->bucket_count();
				for (UnsignedInt unitIndex = 0; unitIndex < unitCount; unitIndex++)
				{
					Object *unit = units->rva0025BFF8(unitIndex);
					if (unit->m_team == player->m_defaultTeam)
						idleUnits++;
					if (unit->getTemplate()->m_kindOf113 & 4)
						heroUnits++;
					else
						hordeUnits++;
				}
				line.format(L"...Hordes units: %d\n", hordeUnits);
				unibuffer.concat(line);
				line.format(L"...Hero units: %d\n", heroUnits);
				unibuffer.concat(line);
				Real idleArmy;
				if (unitCount > 0)
					idleArmy = (Real)idleUnits / (Real)unitCount * 100.0f;
				else
					idleArmy = 0.0f;
				line.format(L"...Idle Army: %.2f\n", idleArmy);
				unibuffer.concat(line);
				line.format(L"<********* Skill Points *********>\n");
				unibuffer.concat(line);
				line.format(L"...Earned: %d\n", (Int)player->getSkillPointsTotal());
				unibuffer.concat(line);
			}

			Rva002A8AB1Record *ai = TheSkirmishAIManager->rva002A8AB1(player);
			if (ai)
			{
				line.format(L"<********* Targets *********>\n");
				unibuffer.concat(line);
				AsciiString targetText;
				if (ai->getPrimaryPlayerTarget())
					targetText.format("Primary Target: %s (%s)\n\n",
						ai->getPrimaryPlayerTarget()->getSide().str(),
						ai->getPrimaryPlayerTarget()->getPlayerName().str());
				else
					targetText.format("Primary Target: No Target\n\n");
				line.translate(targetText);
				unibuffer.concat(line);

				Rva002C589BList *targets = (Rva002C589BList *)ai->m_targets->get();
				if (targets)
				{
					AsciiString typeRow;
					Rva002C589B **end = targets->m_end;
					Rva002C589B **it;
					for (it = targets->m_begin; it != end; ++it)
					{
						AsciiString cell;
						Rva002C589B *target = *it;
						Int count = target->m_count;
						Int type = target->m_type;
						cell.format("%s(%d/%d)", AITargetTypeNames[type], ((const Bfme939Helper *)target)->get(), count);
						typeRow.concat(cell);
						for (Int pad = 0; pad < columnPad(cell); pad++)
							typeRow.concat(" ");
					}
					typeRow.concat("\n");
					line.translate(typeRow);
					unibuffer.concat(line);

					AsciiString objectRow;
					for (it = targets->m_begin; it != end; ++it)
					{
						AsciiString cell;
						Rva002C589B *target = *it;
						if (target->m_destroyed)
							cell.format("Destroyed");
						else if (target->m_cancelled)
							cell.format("Cancelled");
						else
						{
							Object *obj = target->rva002C5DA6();
							if (obj)
							{
								if (obj->getTemplate()->m_kindOf121 & 0x10)
								{
									BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange(obj->getPosition(), 300.0f, 0,
										&Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 50),
											*(BfmeFixedStorage0004543D *)&KINDOFMASK_NONE), 1);
									obj = iter.next();
								}
								if (obj)
									cell.format("%s", obj->getTemplate()->m_displayName.str());
							}
							else
								cell.format("Positional");
						}
						objectRow.concat(cell);
						for (Int pad = 0; pad < columnPad(cell); pad++)
							objectRow.concat(" ");
					}
					objectRow.concat("\n");
					line.translate(objectRow);
					unibuffer.concat(line);
				}
				else
				{
					line.format(L"Slaved AI (no targets)\n");
				}
			}
			line.format(L"*******************************\n");
			unibuffer.concat(line);
			line.format(L"\n\n\n");
			unibuffer.concat(line);
		}
		aiIndex++;
	}
	m_skirmishAIString[0]->setText(unibuffer);
}
