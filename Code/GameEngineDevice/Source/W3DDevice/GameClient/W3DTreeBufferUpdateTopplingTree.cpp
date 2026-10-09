// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas
//
// ?updateTopplingTree@W3DTreeBuffer@@IAEXPAUTTree@@@Z, retail 0x000EA746
// (1633 bytes), called from 0x000EDCB9; WorldBuilder twin 0x008A1CB0
// (W3DTreeBuffer::updateTopplingTree, callgraph).  Zero Hour's body through
// the BFME 1 port (Open-BFME-1 W3DTreeBufferRva00733580.cpp, retail BFME1
// 0x00733580, same tree record layout): skip settled trees, freeze trees in
// the fog, finish an interrupted topple, otherwise rotate by the angular
// velocity (WWMath In_Place_Pre_Rotate_X/Y), bounce, settle (scaled sink
// countdown for KillWhenToppled) and play the bounce FX at the tree top.
// BFME2 differences read from retail: the tree types sit at +0x44558
// (stride 0x5C), the local player index is PlayerList+0x10 -> +0x54, the
// shroud query is the rowed 0x00739800 on TheShroudManager, every rotation
// raises the +0x44545 dirty byte, settling raises +0x45C5C, and the sink
// scale is +0x5BC.
#include "matrix3d.h"
#include <math.h>
#include "../../../../Libraries/Include/Lib/Coord3D.h"

static __forceinline void setCoord3D(Coord3D &c, float px, float py, float pz)
{
	c.x = px;
	c.y = py;
	c.z = pz;
}

enum ObjectShroudStatus
{
	OBJECTSHROUD_INVALID,
	OBJECTSHROUD_CLEAR,
	OBJECTSHROUD_PARTIAL_CLEAR,
	OBJECTSHROUD_FOGGED
};

// The shroud query on TheShroudManager (0x00739800), rowed under its address.
class Rva00739800
{
public:
	ObjectShroudStatus rva00739800(int playerIndex, const Coord3D *pos) const;
};

class PartitionManager;
extern PartitionManager *TheShroudManager;

class Player
{
public:
	int getPlayerIndex() const { return m_playerIndex; }
private:
	char m_pad00[0x54];
	int m_playerIndex;	// +0x54
};

class PlayerList
{
public:
	Player *getLocalPlayer() const { return m_local; }
private:
	char m_pad00[0x10];
	Player *m_local;	// +0x10
};
extern PlayerList *ThePlayerList;

class FXList
{
public:
	static void doFXPos(const FXList *fx, const Coord3D *primary, const Matrix3D *primaryMtx,
		float primarySpeed, const Coord3D *secondary);	// 0x00094C29
};

struct W3DTreeDrawModuleData
{
	char m_pad00[0x24];
	FXList *m_bounceFX;	// +0x24
	char m_pad28[0x34 - 0x28];
	float m_bounceVelocityPercent;	// +0x34
	float m_minimumToppleSpeed;	// +0x38
	unsigned char m_killWhenToppled;	// +0x3C
	unsigned int m_sinkFrames;	// +0x40
};

struct TTreeType
{
	char m_pad00[0x20];
	const W3DTreeDrawModuleData *m_data;	// +0x20
	char m_pad24[0x5C - 0x24];
};

enum
{
	TOPPLE_UPRIGHT = 0,
	TOPPLE_FALLING = 1,
	TOPPLE_FOGGED = 2,
	TOPPLE_DOWN = 3
};

enum
{
	TOPPLE_OPTIONS_NO_BOUNCE = 1,
	TOPPLE_OPTIONS_NO_FX = 2
};

struct TTree
{
	Vector3 location;	// +0x00
	char m_pad0C[0x40 - 0x0C];
	int treeType;	// +0x40
	char m_pad44[0x6C - 0x44];
	float m_angularVelocity;	// +0x6C
	float m_angularAcceleration;	// +0x70
	Coord3D m_toppleDirection;	// +0x74
	int m_toppleState;	// +0x80
	float m_angularAccumulation;	// +0x84
	unsigned char m_88;	// +0x88
	unsigned int m_options;	// +0x8C
	Matrix3D m_mtx;	// +0x90
	int m_sinkFramesLeft;	// +0xC0
	unsigned char m_bSinking;	// +0xC4
};

static const float ANGULAR_LIMIT = 1.5217089653015137f;

class W3DTreeBuffer
{
protected:
	void updateTopplingTree(TTree *tree);

private:
	char m_pad00000[0x5BC];
	float m_sinkScale;	// +0x5BC
	char m_pad005C0[0x44545 - 0x5C0];
	unsigned char m_anythingChanged;	// +0x44545
	char m_pad44546[0x44558 - 0x44546];
	TTreeType m_treeTypes[64];	// +0x44558
	char m_pad45C58[0x45C5C - 0x45C58];
	unsigned char m_anyTreeSettled;	// +0x45C5C

};

void W3DTreeBuffer::updateTopplingTree(TTree *tree)
{
	if (tree->m_toppleState == TOPPLE_UPRIGHT || tree->m_toppleState == TOPPLE_DOWN)
		return;
	const W3DTreeDrawModuleData *data = m_treeTypes[tree->treeType].m_data;
	int playerIndex = ThePlayerList ? ThePlayerList->getLocalPlayer()->getPlayerIndex() : 0;
	Coord3D position;
	position.x = tree->location.X;
	position.y = tree->location.Y;
	position.z = tree->location.Z;
	ObjectShroudStatus status = ((Rva00739800 *)TheShroudManager)->rva00739800(playerIndex, &position);
	if (status == OBJECTSHROUD_FOGGED)
	{
		tree->m_toppleState = TOPPLE_FOGGED;
		return;
	}
	else if (tree->m_toppleState == TOPPLE_FOGGED)
	{
		tree->m_angularVelocity = 0;
		tree->m_toppleState = TOPPLE_DOWN;
		tree->m_mtx.In_Place_Pre_Rotate_X(-ANGULAR_LIMIT * tree->m_toppleDirection.y);
		tree->m_mtx.In_Place_Pre_Rotate_Y(ANGULAR_LIMIT * tree->m_toppleDirection.x);
		m_anythingChanged = 1;
		if (data->m_killWhenToppled)
		{
			tree->m_sinkFramesLeft = 0;
			tree->m_bSinking = 1;
		}
		return;
	}

	float curVelocityToAdd = tree->m_angularVelocity;
	if (tree->m_angularAccumulation + curVelocityToAdd > ANGULAR_LIMIT)
		curVelocityToAdd = ANGULAR_LIMIT - tree->m_angularAccumulation;
	tree->m_mtx.In_Place_Pre_Rotate_X(-curVelocityToAdd * tree->m_toppleDirection.y);
	tree->m_mtx.In_Place_Pre_Rotate_Y(curVelocityToAdd * tree->m_toppleDirection.x);
	m_anythingChanged = 1;
	tree->m_angularAccumulation += curVelocityToAdd;
	if (tree->m_angularAccumulation >= ANGULAR_LIMIT && tree->m_angularVelocity > 0)
	{
		tree->m_angularVelocity *= -data->m_bounceVelocityPercent;
		if ((tree->m_options & TOPPLE_OPTIONS_NO_BOUNCE) || fabs(tree->m_angularVelocity) < 0.01f)
		{
			tree->m_angularVelocity = 0;
			tree->m_toppleState = TOPPLE_DOWN;
			m_anyTreeSettled = 1;
			if (data->m_killWhenToppled)
			{
				tree->m_sinkFramesLeft = (int)((float)data->m_sinkFrames * m_sinkScale);
				tree->m_bSinking = 1;
			}
		}
		else if (fabs(tree->m_angularVelocity) >= 0.03f)
		{
			if (!(tree->m_options & TOPPLE_OPTIONS_NO_FX))
			{
				Vector3 local(0, 0, 27.0f), transformed;
				Matrix3D::Transform_Vector(tree->m_mtx, local, &transformed);
				Coord3D effect;
				setCoord3D(effect, transformed.X, transformed.Y, transformed.Z);
				FXList::doFXPos(data->m_bounceFX, &effect, 0, 0.0f, 0);
			}
		}
	}
	else
	{
		tree->m_angularVelocity += tree->m_angularAcceleration;
	}
}
