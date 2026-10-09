// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /ICode/GameEngine/Include /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?CreateBeaconObject@LivingWorldManager@@QAEXHPBVCoord2D@@H@Z
// retail 0x00213171..0x002133E0 (623 bytes EH) thiscall RET 0xC.
//
// Identity (WorldBuilder): the twin 0x00B602E0 is
// LivingWorldManager::CreateBeaconObject (LivingWorldManager.cpp; its
// debug-only crash text "Unhandled beacon type in
// LivingWorldManager::CreateBeaconObject" line 1333); the sole retail caller
// 0x003F43D3 calls it on TheLivingWorldManager (0x009FE1C8) with an id the
// 8-byte position at its +0x28 and type 0. This replaces the placeholder pin
// ?rva00213171@Rva00DFE1C8Host@@QAEXHPAXH@Z (Rva00DFE1C8Host is the same
// singleton).
// Body: the beacon name comes from the rowed BattleMarker formatter
// rva0060E7F0 (0x00211245); when the id is not yet in the int-key hash_map at
// +0x218 a 0xB0-byte beacon (rowed ctor 0x003FD14D given the name's address
// as in CreateSound) builds its render object through the rowed
// LivingWorldVisual::createRenderObject 0x003FCEA3 from one of three model
// names (+0xCC/+0xD4/+0xD0 by type 0/1/2; layer 1/2/1 else 6) with an empty
// sub-object list; rva0010E4F6 makes it unique; with a render object it is
// placed at the position's ground height (g_00DFEF18 rva002BF5B0 then
// +0xEC added) through Set_Transform (slot 21) and added to that scene
// (slot 17); the beacon gets +0x30 = 1 a unit scale at +0xA0 and
// rva003FB9EB(30 0). The beacon is stored in the map and handed to
// method_002BFFD4 with the layer; the beacon sound (+0x160) plays through
// TheAudio addAudioEvent (slot 25) when set.
// WorldBuilder evaluates the render object through an inline getter and the
// ground point / translation through Vector3 constructors: both shapes are
// needed for retail's evaluation order. Member and view names besides the
// method are address-derived or descriptive.
#include "ascii_string.h"
#include "Coord2D.h"
#include "Coord3D.h"
#include "Common/BfmeAudioEventPrefix136.h"
#include <vector>
#include <hash_map>

extern "C" AsciiString rva0060E7F0(int marker);
void rva0010E4F6(void *robj, bool flag);

class RenderObjClass;

class Matrix3D
{
public:
	Matrix3D(bool identity)
	{
		Row[0][0] = 1.0f; Row[0][1] = 0.0f; Row[0][2] = 0.0f; Row[0][3] = 0.0f;
		Row[1][0] = 0.0f; Row[1][1] = 1.0f; Row[1][2] = 0.0f; Row[1][3] = 0.0f;
		Row[2][0] = 0.0f; Row[2][1] = 0.0f; Row[2][2] = 1.0f; Row[2][3] = 0.0f;
	}
	void Set_Translation(float x, float y, float z)
	{
		Row[0][3] = x;
		Row[1][3] = y;
		Row[2][3] = z;
	}
	float Row[3][4];
};

class Vector3
{
public:
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	float X;
	float Y;
	float Z;
};

class Rva00213171RenderObj
{
public:
#define RENDER_SLOT(n) virtual void slot##n();
	RENDER_SLOT(00) RENDER_SLOT(01) RENDER_SLOT(02) RENDER_SLOT(03)
	RENDER_SLOT(04) RENDER_SLOT(05) RENDER_SLOT(06) RENDER_SLOT(07)
	RENDER_SLOT(08) RENDER_SLOT(09) RENDER_SLOT(10) RENDER_SLOT(11)
	RENDER_SLOT(12) RENDER_SLOT(13) RENDER_SLOT(14) RENDER_SLOT(15)
	RENDER_SLOT(16) RENDER_SLOT(17) RENDER_SLOT(18) RENDER_SLOT(19)
	RENDER_SLOT(20)
	virtual void Set_Transform(const Matrix3D &m); // slot 21 (+0x54)
};

class Rva002D3627Host
{
public:
	bool rva002BF5B0(const Coord2D *pos, Coord3D *out);
	void method_002BFFD4(void *object, int layer, void *extra);
};
extern Rva002D3627Host *g_00DFEF18;

class Rva00213171Scene
{
public:
	RENDER_SLOT(00) RENDER_SLOT(01) RENDER_SLOT(02) RENDER_SLOT(03)
	RENDER_SLOT(04) RENDER_SLOT(05) RENDER_SLOT(06) RENDER_SLOT(07)
	RENDER_SLOT(08) RENDER_SLOT(09) RENDER_SLOT(10) RENDER_SLOT(11)
	RENDER_SLOT(12) RENDER_SLOT(13) RENDER_SLOT(14) RENDER_SLOT(15)
	RENDER_SLOT(16)
	virtual void addRenderObject(RenderObjClass *robj); // slot 17 (+0x44)
};

class AudioManager;
extern AudioManager *TheAudio;

class Rva00213171AudioView
{
public:
	RENDER_SLOT(00) RENDER_SLOT(01) RENDER_SLOT(02) RENDER_SLOT(03)
	RENDER_SLOT(04) RENDER_SLOT(05) RENDER_SLOT(06) RENDER_SLOT(07)
	RENDER_SLOT(08) RENDER_SLOT(09) RENDER_SLOT(10) RENDER_SLOT(11)
	RENDER_SLOT(12) RENDER_SLOT(13) RENDER_SLOT(14) RENDER_SLOT(15)
	RENDER_SLOT(16) RENDER_SLOT(17) RENDER_SLOT(18) RENDER_SLOT(19)
	RENDER_SLOT(20) RENDER_SLOT(21) RENDER_SLOT(22) RENDER_SLOT(23)
	RENDER_SLOT(24)
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *event); // slot 25 (+0x64)
#undef RENDER_SLOT
};

class LivingWorldVisual
{
public:
	virtual void setHouseColor(const int &color);
	RenderObjClass *createRenderObject(const AsciiString &modelName,
		const _STL::vector<AsciiString> &subObjectNames, int shadowType, const int *houseColor);
	RenderObjClass *getRenderObject() { return m_primaryRObj; }
	char m_pad04[4];
	RenderObjClass *m_primaryRObj; // +0x08
};

class Rva003FB9C8
{
public:
	void rva003FB9EB(int a, int b);
};

class Rva003FD14D : public LivingWorldVisual
{
public:
	Rva003FD14D(int nameAddress);
	char m_pad0C[0x24];
	int m_30;
	char m_pad34[0x6c];
	Coord3D m_a0;
	char m_padAC[4];
};

struct LivingWorldManagerData
{
	char m_pad00[0xb8];
	AsciiString m_beaconModel0; // +0xB8 (manager +0xCC)
	AsciiString m_beaconModel2; // +0xBC (manager +0xD0)
	AsciiString m_beaconModel1; // +0xC0 (manager +0xD4)
	char m_padC4[0x14];
	float m_beaconHeight; // +0xD8 (manager +0xEC)
	char m_padDC[0x70];
	OpaqueRefElement4 m_beaconSound; // +0x14C (manager +0x160)
};

class LivingWorldManager
{
public:
	void CreateBeaconObject(int id, const Coord2D *pos, int type);
private:
	char m_pad00[0x14];
	LivingWorldManagerData m_data; // +0x14
	char m_pad164[0x218 - 0x164];
	_STL::hash_map<int, Rva003FD14D *> m_beacons; // +0x218
};

void LivingWorldManager::CreateBeaconObject(int id, const Coord2D *pos, int type)
{
	AsciiString name = rva0060E7F0(id);
	if (m_beacons.find(id) == m_beacons.end())
	{
		Rva003FD14D *beacon = new Rva003FD14D((int)&name);
		AsciiString model;
		int layer = 6;
		switch (type)
		{
		case 0:
			model = m_data.m_beaconModel0;
			layer = 1;
			break;
		case 1:
			model = m_data.m_beaconModel1;
			layer = 2;
			break;
		case 2:
			model = m_data.m_beaconModel2;
			layer = 1;
			break;
		}
		beacon->createRenderObject(model, _STL::vector<AsciiString>(), 0, 0);
		rva0010E4F6(beacon->getRenderObject(), false);
		if (beacon->m_primaryRObj != 0)
		{
			Matrix3D tm(true);
			Vector3 ground(pos->x, pos->y, 0.0f);
			g_00DFEF18->rva002BF5B0(pos, (Coord3D *)&ground);
			tm.Set_Translation(pos->x, pos->y, ground.Z + m_data.m_beaconHeight);
			((Rva00213171RenderObj *)beacon->m_primaryRObj)->Set_Transform(tm);
			((Rva00213171Scene *)g_00DFEF18)->addRenderObject(beacon->getRenderObject());
			beacon->m_30 = 1;
			Coord3D scale;
			scale.x = scale.y = scale.z = 1.0f;
			beacon->m_a0 = scale;
			((Rva003FB9C8 *)beacon)->rva003FB9EB(30, 0);
		}
		m_beacons[id] = beacon;
		g_00DFEF18->method_002BFFD4(beacon, layer, 0);
		if (m_data.m_beaconSound.referent != 0)
		{
			BfmeAudioEventPrefix136 sound(m_data.m_beaconSound, 1);
			((Rva00213171AudioView *)TheAudio)->addAudioEvent(&sound);
		}
	}
}
