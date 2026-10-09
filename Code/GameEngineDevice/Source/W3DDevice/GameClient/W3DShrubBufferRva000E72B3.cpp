// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// W3DShrubBuffer::pushAsideTree, retail 0x000E72B3 (283 bytes, ret 0x10): a unit walking past a shrub bends it away
// from the walker: records of the drawable that were not pushed by this pusher within three frames get a push
// direction perpendicular to the walker's heading and a push-aside rate from the type's frames to move outward.
// Open-BFME-1 twin: W3DShrubBuffer.cpp (pushAsideTree, BFME1 0x0071CBB0). BFME2 layout read from retail: 2000
// records of 0xA0 at +0x1958 (drawable +0x58, push-aside +0x5C, rate +0x60, sin +0x64, cos +0x68, source +0x6C,
// last frame +0x70), count +0x4FB58, push-changed byte +0x4FB5D, types of 0x5C at +0x4FB70 with the type data at
// +0x20, move-outward rate scale at +0x5BC; GlobalData flag +0x1C; TheGameLogic frame +0x40.
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../GameEngine/Source/Common/GameLogicObjectLookupView.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

class GlobalData;
struct Rva000E72B3GlobalData
{
	unsigned char m_pad00[0x1c];
	bool m_flag1c;
};
extern GlobalData *TheWritableGlobalData;
class GameLogic;
extern GameLogic *TheGameLogic;

struct Rva000E72B3Tree
{
	Real m_locationX;
	Real m_locationY;
	Real m_locationZ;
	unsigned char m_pad0c[0x34];
	Int m_treeType;
	unsigned char m_pad44[0x58 - 0x44];
	UnsignedInt m_drawableID;
	Real m_pushAside;
	Real m_pushAsideDelta;
	Real m_pushAsideSin;
	Real m_pushAsideCos;
	UnsignedInt m_pushAsideSource;
	UnsignedInt m_lastFrameUpdated;
	unsigned char m_pad74[0xa0 - 0x74];
};

struct Rva000E72B3TypeData
{
	unsigned char m_pad00[0x10];
	UnsignedInt m_framesToMoveOutward;
};

struct Rva000E72B3Type
{
	unsigned char m_pad00[0x20];
	Rva000E72B3TypeData *m_data;
	unsigned char m_pad24[0x5c - 0x24];
};

class W3DShrubBuffer
{
public:
	void rva000E72B3(UnsignedInt id, const Coord3D *pusherPos, const Coord3D *pusherDirection, UnsignedInt pusherID);

private:
	unsigned char m_pad0000[0x5bc];
	Real m_pushRateScale;
	unsigned char m_pad5c0[0x1958 - 0x5c0];
	Rva000E72B3Tree m_trees[2000];
	Int m_numTrees;
	unsigned char m_anythingChanged;
	unsigned char m_anyPushChanged;
	unsigned char m_pad4fb5e[0x4fb70 - 0x4fb5e];
	Rva000E72B3Type m_treeTypes[64];
};

void W3DShrubBuffer::rva000E72B3(UnsignedInt id, const Coord3D *pusherPos, const Coord3D *pusherDirection, UnsignedInt pusherID)
{
	if (!((const Rva000E72B3GlobalData *)TheWritableGlobalData)->m_flag1c)
		return;

	for (Int i = 0; i < m_numTrees; ++i) {
		Rva000E72B3Tree *tree = &m_trees[i];
		if (tree->m_drawableID == id) {
			UnsignedInt lastFrame = tree->m_lastFrameUpdated;
			tree->m_lastFrameUpdated = TheGameLogic->getFrame();
			if (tree->m_pushAsideSource == pusherID) {
				if (tree->m_lastFrameUpdated - lastFrame < 3)
					return;
			}

			if (tree->m_pushAside != 0.0f)
				return;

			tree->m_pushAsideSource = pusherID;
			Coord3D delta;
			delta.x = tree->m_locationX;
			delta.y = tree->m_locationY;
			delta.z = tree->m_locationZ;
			delta.x -= pusherPos->x;
			delta.y -= pusherPos->y;
			delta.z -= pusherPos->z;
			if (pusherDirection->x * delta.y - pusherDirection->y * delta.x > 0.0f) {
				tree->m_pushAsideCos = -pusherDirection->y;
				tree->m_pushAsideSin = pusherDirection->x;
			} else {
				tree->m_pushAsideCos = pusherDirection->y;
				tree->m_pushAsideSin = -pusherDirection->x;
			}

			m_anyPushChanged = true;
			tree->m_pushAsideDelta = 1.0f /
				((Real)m_treeTypes[tree->m_treeType].m_data->m_framesToMoveOutward * m_pushRateScale);
		}
	}
}
