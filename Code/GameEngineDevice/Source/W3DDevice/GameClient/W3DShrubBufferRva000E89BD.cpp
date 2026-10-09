// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// W3DShrubBuffer::rva000E89BD, retail 0x000E89BD (624 bytes, ret 4): the shrub
// buffer's per-frame update before drawing, the Zero Hour drawTrees body
// reduced to its update half. It runs the sway update unless time is frozen
// or the game is paused, handles the deferred texture update, advances 30
// round-robin records' visibility state, then pushes aside visible upright
// records and refills the vertex buffers (0x000E7DF3) or only re-writes them
// (0x000E8365) before the draw pass 0x000E663B. Donor semantics: Open-BFME-1
// W3DTreeBuffer.cpp drawTrees; the BFME2 shrub fields are read from retail.
// Layout: records of 0xA0 at +0x1958 (count +0x4FB58), index counts vector at
// +0x28, texture at +0x38, swayRate +0x5BC, flags +0x4FB5C/D/E/6D/6E, byte
// +0x51274, step +0x51278, round-robin index +0x5127C.
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../GameEngine/Source/Common/GameLogicObjectLookupView.h"

struct BreezeInfo;
class GlobalData;
class ScriptEngine;
class PartitionManager;
class PlayerList;
enum ObjectShroudStatus { SHROUD_STATUS_A = 0 };

class Rva00203ACEByteField { public: unsigned char get() const; };
class Rva00203B08 { public: bool rva0020424FF(); };
class Rva00739800 { public: ObjectShroudStatus rva00739800(int, const Coord3D *) const; };
class Rva000E76B8 { public: void rva000E76B8(); };
class Rva000EC9C6 { public: void rva000E663B(int); };

struct Rva000E89BDPlayer { unsigned char pad[0x54]; int index; };
struct Rva000E89BDPlayerList { unsigned char pad[0x10]; Rva000E89BDPlayer *local; };
struct Rva000E89BDGlobalData { unsigned char pad[0x1c]; bool flag1c; };
struct Rva000E89BDScriptEngine { unsigned char pad[0x1a4a8]; unsigned char breeze[1]; };

extern GlobalData *TheWritableGlobalData;
extern ScriptEngine *TheScriptEngine;
extern GameLogic *TheGameLogic;
extern PartitionManager *TheShroudManager;
extern PlayerList *ThePlayerList;

struct Rva000E89BDData
{
	unsigned char pad[0x14];
	unsigned int framesToMoveInward;
};

struct Rva000E89BDType
{
	unsigned char pad[0x20];
	const Rva000E89BDData *data;
	unsigned char pad24[0x5c - 0x24];
};

struct Rva000E89BDTree
{
	Coord3D location;
	unsigned char pad0c[0x40 - 0x0c];
	int treeType;
	bool visible;
	unsigned char pad45[0x5c - 0x45];
	float pushAside;
	float pushAsideDelta;
	unsigned char pad64[0x84 - 0x64];
	int toppleState;
	unsigned char pad88[0x9c - 0x88];
	int shroudState;
};

class W3DShrubBuffer
{
public:
	void rva000E89BD(int arg);
	void rva000E6406(const BreezeInfo &info);
	void rva000E7DF3(void);
	void rva000E8365(void);

protected:
	void updateTexture();

private:
	unsigned char pad00[0x28];
	int *m_curNumTreeIndices;
	unsigned char pad2c[0x34 - 0x2c];
	void *m_field34;
	void *m_texture38;
	unsigned char pad3c[0x5bc - 0x3c];
	float m_swayRate;
	unsigned char pad5c0[0x1958 - 0x5c0];
	Rva000E89BDTree m_trees[2000];
	int m_numTrees;
	bool m_anythingChanged;
	bool m_anyPushChanged;
	bool m_flag4fb5e;
	unsigned char pad4fb5f[0x4fb6d - 0x4fb5f];
	bool m_updateAllKeys;
	bool m_needToUpdateTexture;
	unsigned char pad4fb6f[0x4fb70 - 0x4fb6f];
	Rva000E89BDType m_treeTypes[64];
	unsigned char pad51270[4];
	bool m_prevChanged;
	unsigned char pad51275[3];
	int m_treeIndexStep;
	int m_nextKey;
};

// ?rva000E89BD@W3DShrubBuffer@@QAEXH@Z
void W3DShrubBuffer::rva000E89BD(int arg)
{
	if (!m_field34)
		return;
	if (!m_updateAllKeys)
		return;
	if (!((Rva000E89BDGlobalData *)TheWritableGlobalData)->flag1c)
		return;

	const BreezeInfo *info = (const BreezeInfo *)((Rva000E89BDScriptEngine *)TheScriptEngine)->breeze;
	bool pause;
	if (((Rva00203ACEByteField *)TheScriptEngine)->get() || ((Rva00203B08 *)TheScriptEngine)->rva0020424FF())
		pause = true;
	else
		pause = false;
	if (TheGameLogic && TheGameLogic->isGamePaused())
		pause = true;
	if (!pause)
		rva000E6406(*info);

	m_updateAllKeys = false;
	if (m_needToUpdateTexture) {
		m_needToUpdateTexture = false;
		updateTexture();
	}
	if (!m_texture38)
		return;

	for (int k = 30; k > 0; k--) {
		if (m_nextKey >= m_numTrees)
			m_nextKey = 0;
		m_trees[m_nextKey].shroudState = 0;
		m_nextKey++;
	}
	if (m_flag4fb5e)
		((Rva000E76B8 *)this)->rva000E76B8();

	int playerIndex = ThePlayerList ? ((Rva000E89BDPlayerList *)ThePlayerList)->local->index : 0;
	for (int curTree = 0; curTree < m_numTrees; curTree += m_treeIndexStep) {
		int type = m_trees[curTree].treeType;
		if (type < 0)
			continue;
		if (m_trees[curTree].toppleState != 0)
			continue;
		if (!m_trees[curTree].visible)
			continue;
		if (!ThePlayerList || !TheShroudManager)
			m_trees[curTree].shroudState = 1;
		if (m_trees[curTree].shroudState == 0)
			m_trees[curTree].shroudState = ((Rva00739800 *)TheShroudManager)->rva00739800(playerIndex, &m_trees[curTree].location);
		if (m_trees[curTree].shroudState >= 3 || m_trees[curTree].shroudState <= 0)
			continue;
		if (pause)
			continue;
		if (m_trees[curTree].pushAsideDelta != 0.0f) {
			m_trees[curTree].pushAside += m_trees[curTree].pushAsideDelta;
			if (m_trees[curTree].pushAside >= 1.0f) {
				m_trees[curTree].pushAsideDelta = -1.0 / ((float)m_treeTypes[type].data->framesToMoveInward * m_swayRate);
			} else if (m_trees[curTree].pushAside <= 0.0f) {
				m_trees[curTree].pushAsideDelta = 0.0f;
				m_trees[curTree].pushAside = 0.0f;
			}
		}
	}

	m_prevChanged = m_anythingChanged;
	if (m_anythingChanged) {
		rva000E7DF3();
		m_anythingChanged = false;
	} else if (m_anyPushChanged) {
		m_anyPushChanged = false;
		rva000E8365();
	}
	if (*m_curNumTreeIndices != 0)
		((Rva000EC9C6 *)this)->rva000E663B(arg);
}
