// ?rva000EDB47@Rva000EDB47@@QAEXXZ
// partial score=0.97 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// NEAR (draft for Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeBufferRva000EDB47Update.cpp):
// 9 diff lines. Retail keeps a redundant `cmp [ebp-0x10],0 / je` null test of the
// found object at the out-of-line found block (0x000EDE1C); every source form tried
// either drops that test (this one) or inverts the query loop (duplicated next()).
//
// ?rva000EDB47@Rva000EDB47@@QAEXXZ
// retail 0x000EDB47..0x000EDE35 (750 bytes) thiscall RET 0 with __EH_prolog.
// Reached only through the null-checked tail jump of the byte-verified
// forwarder Rva00068D43::rva00068D43 (0x00068D43) on its +0x3850 member.
// The per-frame tree update that BFME 1 still runs inside
// W3DTreeBuffer::drawTrees (Open-BFME-1 W3DTreeBufferDrawTreesBfme.cpp
// donor loop): after the pending-region refresh (0x000EB21D) and the
// script/pause gates (0x00203ACE 0x000424FF GameLogic::isGamePaused) it
// updates the sway from TheScriptEngine's breeze (+0x1A4A8; pinned
// 0x000E6406) and walks the 0xE8 tree records at +0x5C0 (count +0x44540
// step +0x45C60): sinking trees lower by sinkDistance/sinkFrames and die at
// zero frames / falling or fogged trees go to updateTopplingTree (0x000EA746)
// / visible trees query ThePartitionManager around the tree (type data
// +0x60 radius and a static Rva002614ECFilter on TheWritableGlobalData
// +0xEB0) for a live controlled object that is not allied-in-cover and set
// the tree alpha (+0xE4) to the type's +0x5C or 255 / a changed alpha
// raises +0x45C64. Tree layout as in the rowed W3DTreeBuffer siblings.
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../GameEngine/Source/Common/PartitionRangeQueryCallView.h"

class Object;
class Player;
class Team;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *m_next;
};

// vftable 0x00BCECF0, allow 0x002614EC: +0x08 what to compare, +0x0C a
// player, +0x10 whether a hit allows.
class Rva002614ECFilter : public Rva000421C8
{
public:
	Rva002614ECFilter(const void *what, Player *player, bool match)
		: m_what(what), m_player(player), m_match(match) {}
	virtual bool allow(Object *obj);
	const void *m_what;
	Player *m_player;
	bool m_match;
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_0F = 0x0F,
	OBJECT_STATUS_11 = 0x11
};

enum Relationship
{
	ENEMIES,
	NEUTRAL,
	ALLIES
};

class Player
{
public:
	Relationship getRelationship(const Team *team) const;	// 0x002AD0C6
	Team *getDefaultTeam() const { return m_defaultTeam; }

private:
	unsigned char m_pad000[0x2EC];
	Team *m_defaultTeam;				// +0x2EC
};

class PlayerList
{
public:
	Player *getLocalPlayer() const { return m_local; }

private:
	unsigned char m_pad00[0x10];
	Player *m_local;				// +0x10
};

class Object
{
public:
	Player *getControllingPlayer() const;		// 0x0028AFA9
	bool rva0028F518();				// 0x0028F518
	bool testStatus(ObjectStatusTypes status) const;	// 0x0004E536
	bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }

private:
	unsigned char m_pad000[0x438];
	unsigned char m_privateStatus;			// +0x438
};

struct BreezeInfo;

class ScriptEngine
{
public:
	const BreezeInfo &getBreezeInfo() const
	{
		return *reinterpret_cast<const BreezeInfo *>(m_pad + 0x1A4A8);
	}

private:
	unsigned char m_pad[0x1A4A8];
};

class Rva00203ACEByteField
{
public:
	unsigned char get() const;			// 0x00203ACE
};

class Rva00203B08
{
public:
	bool rva0020424FF();				// 0x000424FF
};

class GameLogic
{
public:
	unsigned char isGamePaused();			// 0x0023CD97
};

class GameEngine
{
	bool rva00225D38();				// 0x00225D38
	friend class Rva000EDB47;
};

class GlobalData
{
public:
	unsigned char m_pad000[0x40];
	bool m_40;					// +0x40
	unsigned char m_pad041[0xEB0 - 0x41];
	unsigned char m_EB0;				// +0xEB0
};

class W3DShrubBuffer
{
public:
	void rva000E6406(const BreezeInfo &info);	// 0x000E6406
};

class Rva000EB08C
{
public:
	void rva000EB21D();				// 0x000EB21D
};

class Vector3
{
public:
	float &operator[](int i) { return (&X)[i]; }
	const float &operator[](int i) const { return (&X)[i]; }
	float X;
	float Y;
	float Z;
};

struct TreeMatrix
{
	void Set_Translation(const Vector3 &t)
	{
		Row[0][3] = t[0];
		Row[1][3] = t[1];
		Row[2][3] = t[2];
	}
	float Row[3][4];
};

static inline void setCoord3D(Coord3D &c, float px, float py, float pz)
{
	c.x = px;
	c.y = py;
	c.z = pz;
}

struct TTree
{
	Vector3 location;				// +0x00
	unsigned char m_pad0C[0x40 - 0x0C];
	int treeType;					// +0x40
	bool visible;					// +0x44
	unsigned char m_pad45[0x80 - 0x45];
	int m_toppleState;				// +0x80
	unsigned char m_pad84[0x90 - 0x84];
	TreeMatrix m_mtx;				// +0x90
	int m_sinkFramesLeft;				// +0xC0
	bool m_bSinking;				// +0xC4
	unsigned char m_padC5[0xC8 - 0xC5];
	int m_C8;					// +0xC8
	unsigned char m_padCC[0xE0 - 0xCC];
	int m_E0;					// +0xE0
	int m_E4;					// +0xE4
};

class W3DTreeBuffer
{
protected:
	void updateTopplingTree(TTree *tree);		// 0x000EA746
	friend class Rva000EDB47;
};

struct W3DTreeDrawModuleData
{
	unsigned char m_pad00[0x40];
	unsigned int m_sinkFrames;			// +0x40
	float m_sinkDistance;				// +0x44
	unsigned char m_pad48[0x5C - 0x48];
	int m_alpha;					// +0x5C
	float m_fadeRadius;				// +0x60
};

struct TTreeType
{
	unsigned char m_pad00[0x20];
	const W3DTreeDrawModuleData *m_data;		// +0x20
	unsigned char m_pad24[0x5C - 0x24];
};

extern ScriptEngine *TheScriptEngine;
extern GameLogic *TheGameLogic;
extern GameEngine *TheGameEngine;
extern GlobalData *TheWritableGlobalData;
extern PartitionManager *ThePartitionManager;
extern PlayerList *ThePlayerList;

class Rva000EDB47
{
public:
	void rva000EDB47();

private:
	unsigned char m_pad00000[0x5C0];
	TTree m_trees[1200];				// +0x5C0
	int m_numTrees;					// +0x44540
	bool m_anythingChanged;				// +0x44544
	bool m_anyPushChanged;				// +0x44545
	bool m_pendingRegions;				// +0x44546
	unsigned char m_pad44547[0x44558 - 0x44547];
	TTreeType m_treeTypes[64];			// +0x44558
	unsigned char m_pad45C58[0x45C60 - 0x45C58];
	int m_indexStep;				// +0x45C60
	bool m_alphaChanged;				// +0x45C64
};

void Rva000EDB47::rva000EDB47()
{
	if (m_pendingRegions)
		reinterpret_cast<Rva000EB08C *>(this)->rva000EB21D();
	if (reinterpret_cast<Rva00203ACEByteField *>(TheScriptEngine)->get())
		return;
	if (reinterpret_cast<Rva00203B08 *>(TheScriptEngine)->rva0020424FF())
		return;
	if (TheGameLogic && TheGameLogic->isGamePaused())
		return;

	reinterpret_cast<W3DShrubBuffer *>(this)->rva000E6406(TheScriptEngine->getBreezeInfo());

	static Rva002614ECFilter filter(&TheWritableGlobalData->m_EB0, 0, true);

	for (int curTree = 0; curTree < m_numTrees; curTree += m_indexStep)
	{
		TTree *tree = &m_trees[curTree];
		int type = tree->treeType;
		if (type < 0)
			continue;
		if (tree->m_C8)
			continue;
		if (tree->m_bSinking)
		{
			if (tree->m_sinkFramesLeft == 0)
			{
				tree->treeType = -2;
				m_anythingChanged = true;
			}
			tree->m_sinkFramesLeft--;
			const W3DTreeDrawModuleData *data = m_treeTypes[type].m_data;
			float sinkFrames = (float)data->m_sinkFrames;
			tree->location.Z -= data->m_sinkDistance / sinkFrames;
			tree->m_mtx.Set_Translation(tree->location);
			if (tree->visible)
				m_anyPushChanged = true;
		}
		if (tree->m_toppleState == 1 || tree->m_toppleState == 2)
			reinterpret_cast<W3DTreeBuffer *>(this)->updateTopplingTree(tree);
		if (!tree->visible)
			continue;
		if (TheWritableGlobalData->m_40 && ThePartitionManager && TheGameEngine->rva00225D38())
		{
			Coord3D pos;
			setCoord3D(pos, tree->location.X, tree->location.Y, tree->location.Z);
			BfmeWideResult result = ThePartitionManager->iterateObjectsInRange(&pos,
				m_treeTypes[type].m_data->m_fadeRadius, 1, &filter, 0);
			Object *found = 0;
			while (Object *obj = result.next())
			{
				if (!obj->getControllingPlayer() || obj->isEffectivelyDead())
					continue;
				if (obj->rva0028F518() || (obj->testStatus(OBJECT_STATUS_0F) && !obj->testStatus(OBJECT_STATUS_11)))
				{
					if (ThePlayerList->getLocalPlayer()->getRelationship(
						obj->getControllingPlayer()->getDefaultTeam()) != ALLIES)
						continue;
				}
				found = obj;
				break;
			}
			if (found)
			{
				if (tree->m_E4 != m_treeTypes[type].m_data->m_alpha)
					tree->m_E4 = m_treeTypes[type].m_data->m_alpha;
			}
			else
				tree->m_E4 = 255;
		}
		if (TheWritableGlobalData->m_40 && tree->m_E0 != tree->m_E4)
			m_alphaChanged = true;
	}
}
