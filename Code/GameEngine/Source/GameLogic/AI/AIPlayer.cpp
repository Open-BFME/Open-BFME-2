// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX
//
// BFME2 BuildListInfo desired-gatherers getter, transferred from the exact
// BFME1 reconstruction (Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp).
// Retail BFME2 keeps the field at the same offset (+0x84); the layout
// authority is reference/shims/buildlistinfo/GameLogic/SidesList.h.
//
// AIPlayer::checkForSupplyCenter (211B @0x004F29E9), after the BFME1 donor
// GameEngine/Source/GameLogic/AI/AIPlayerSupply.cpp
// (?checkForSupplyCenter@AIPlayer@@IAEXPAVBuildListInfo@@PAVObject@@@Z,
// 259B @0x00162410 there). The shape is donor-verbatim except for four
// BFME2 divergences, all read straight off retail:
// - The side string sits at player+0x58 (donor +0x28); BFME2's Player grew.
// - The AI chain is TheAI->[+0x18]->[+0xF4] (donor +0x14/+0xEC).
// - The side address is recomputed at the top of every loop iteration
//   (retail reloads this->m_player through the volatile slot, adds 0x58,
//   and calls compare each time round), so the volatile read lives inside
//   the loop here instead of above it as in the donor.
// - The resInfo loop is a plain while (retail jumps to the test first);
//   the donor's if-guard plus do-while is the same walk written the other
//   way and does not reproduce retail's test-first layout.
// All four callees were already rowed: NameKeyGenerator::nameToKey
// (0x00148E1A), Object::findModule (0x0028B6D6, reached through a TU-local
// befriended Object the way CastleMemberBehaviorFind.cpp does it),
// StringBase<char>::compare (0x000069D6), and __EH_prolog (0x00629188).
//
// LAYOUT PUZZLE (bytes are exact; names may need a second pass):
// checkForSupplyCenter stores supply/count/minus-one at +0x46/+0x78/+0x7C,
// which is the donor's setSupplyBuilding/setDesiredGatherers/
// setCurrentGatherers mapping, but the pre-existing getDesiredGatherers row
// in this TU reads +0x84. Both are byte-proven, so the TU keeps both fields
// side by side until BuildListInfo archaeology settles which int is which.

typedef bool Bool;
typedef int Int;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum GameDifficulty
{
	DIFFICULTY_EASY,
	DIFFICULTY_NORMAL,
	DIFFICULTY_HARD
};

template <typename T> class StringBase
{
public:
	int compare(const StringBase<T> &other) const;
};

class AsciiString : public StringBase<char>
{
public:
	Bool operator==(const AsciiString &other) const { return compare(other) == 0; }
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Module
{
};

class Object
{
protected:
	Module *findModule(NameKeyType key) const;
	friend class AIPlayer;
};

class AISideInfo
{
public:
	void *m_vtable;				// +0x00
	AsciiString m_side;			// +0x04
	Int m_easy;				// +0x08
	Int m_normal;				// +0x0C
	Int m_hard;				// +0x10
	unsigned char m_pad[0x1BC - 0x14];
	AISideInfo *m_next;			// +0x1BC
};

struct TAiData
{
	unsigned char m_pad[0xF4];
	AISideInfo *m_sideInfo;			// +0xF4
};

class AI
{
public:
	TAiData *getAiData() const { return m_aiData; }

private:
	unsigned char m_pre[0x18];
	TAiData *m_aiData;			// +0x18
};

extern AI *TheAI;

class Player;

class BuildListInfo
{
public:
	int getDesiredGatherers();
	void setSupplyBuilding(Bool value) { m_isSupplyBuilding = value; }
	void setDesiredGatherers(Int value) { m_desiredGatherers = value; }
	void setCurrentGatherers(Int value) { m_currentGatherers = value; }

private:
	unsigned char m_preSupply[0x46];
	Bool m_isSupplyBuilding;		// +0x46
	unsigned char m_supplyPad[0x78 - 0x47];
	Int m_desiredGatherers;			// +0x78
	Int m_currentGatherers;			// +0x7C
	unsigned char m_gathererPad[0x84 - 0x80];
	int m_desiredGatherersReadback;		// +0x84 (pre-existing getter target)
};

// ?getDesiredGatherers@BuildListInfo@@QAEHXZ
int BuildListInfo::getDesiredGatherers()
{
	return m_desiredGatherersReadback;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class AIPlayer
{
protected:
	void checkForSupplyCenter(BuildListInfo *info, Object *bldg);

private:
	unsigned char m_pre[0x0C];
	Player *m_player;					// +0x0C
	unsigned char m_mid[0x2C - 0x10];
	GameDifficulty m_difficulty;				// +0x2C
};

// ?checkForSupplyCenter@AIPlayer@@IAEXPAVBuildListInfo@@PAVObject@@@Z
void AIPlayer::checkForSupplyCenter(BuildListInfo *info, Object *bldg)
{
	if (info)
	{
		if (bldg)
		{
			static const NameKeyType key_centerUpdate =
				TheNameKeyGenerator->nameToKey("SupplyCenterDockUpdate");
			Module *centerModule = bldg->findModule(key_centerUpdate);
			if (centerModule)
			{
				info->setSupplyBuilding(true);
				Int desiredGatherers = 0;
				const AISideInfo *resInfo = TheAI->getAiData()->m_sideInfo;
				while (resInfo)
				{
					// VC7 otherwise folds this into a shorter non-retail address calculation.
					void *playerStorage = *reinterpret_cast<void *volatile *>(
						reinterpret_cast<char *>(this) + 0x0c);
					const AsciiString *side = reinterpret_cast<const AsciiString *>(
						reinterpret_cast<char *>(playerStorage) + 0x58);
					if (resInfo->m_side == *side)
					{
						GameDifficulty difficulty = m_difficulty;
						if (difficulty == DIFFICULTY_EASY)
							desiredGatherers = resInfo->m_easy;
						if (difficulty == DIFFICULTY_NORMAL)
							desiredGatherers = resInfo->m_normal;
						if (difficulty == DIFFICULTY_HARD)
							desiredGatherers = resInfo->m_hard;
					}
					resInfo = resInfo->m_next;
				}

				info->setSupplyBuilding(true);
				info->setCurrentGatherers(-1);
				info->setDesiredGatherers(desiredGatherers + 1);
			}
		}
	}
}
