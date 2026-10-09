// ?rva000E8C2D@W3DShrubBuffer@@QAEXHH@Z
// partial score=0.9 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// W3DShrubBuffer method at retail 0x000ECA4D (936 bytes, ret 8; called from the key lookup 0x000ECF2A):
// gives a tree its type's model and the model of the type at +0xD0 at the tree's position and rotation,
// starts the +0xD4 countdown and plays the type's effect. Donor: Open-BFME-1 W3DShrubBufferRva00736150.cpp
// (BFME1 0x00736150). BFME2 layout read from retail.
#include "matrix3.h"
#include "rendobj.h"
#include "scene.h"
#include "ascii_string.h"

typedef int Int;
typedef float Real;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class FXList
{
public:
	static void doFXPos(const FXList *list, const Coord3D *position, const Matrix3D *matrix, Real speed,
		const Coord3D *direction);
};

class Rva0027F2D6
{
public:
	void rva0027F2D6(Int id);
};

// retail singleton: TerrainLogic *TheTerrainLogic (mangled ?TheTerrainLogic@@3PAVTerrainLogic@@A),
// defined in GameLogic/Map/TerrainLogic.cpp. Uses go through this TU's Rva0027F2D6 view.
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
// Retail global 0x012F8058 is W3DDisplay::m_3DScene
// (?m_3DScene@W3DDisplay@@2PAVRTS3DScene@@A, defined in W3DDisplay's own TU).
// RTS3DScene is forward declared: the two scene calls go through scene.h's
// SceneClass view, which is what the retail call sites do.
class RTS3DScene;
class W3DDisplay { public: static RTS3DScene *m_3DScene; };

RenderObjClass *Create_Render_Obj(const char *name);
void rva0010E4F6(void *object, bool geometry);
bool Rva0010E87A_SetOpacity(RenderObjClass *object, float value);

struct Rva000E8C2DTypeData
{
	unsigned char m_pad00[8];
	AsciiString m_modelName;
	unsigned char m_pad0c[0x4c - 0x0c];
	Int m_duration;
	const FXList *m_effect;
	bool m_flag54;
};

struct Rva000E8C2DType
{
	unsigned char m_pad00[0x20];
	const Rva000E8C2DTypeData *m_data;
	unsigned char m_pad24[0x4c - 0x24];
	AsciiString m_modelName;
	unsigned char m_pad50[0x58 - 0x50];
	Int m_field58;
};

struct Rva000E8C2DTree
{
	unsigned char m_prefix[0x1958];
	Coord3D m_location;
	Real m_scale;
	Matrix3D m_transform;
	Int m_treeType;
	unsigned char m_pad44[0x84 - 0x44];
	Int m_request;
	Int m_uprightType;
	Int m_toppledType;
	Int m_sinkFrames;
	RenderObjClass *m_topple;
	RenderObjClass *m_pushAside;
	unsigned char m_pad9c[0xa0 - 0x9c];
};

class W3DShrubBuffer
{
public:
	void rva000E8C2D(Int index, Int request);

private:
	unsigned char m_pad0000[0x1958];
	unsigned char m_trees[2000 * 0xa0];
	Int m_numTrees;
	bool m_anythingChanged;
	unsigned char m_pad4fb59[0x4fb70 - 0x4fb59];
	Rva000E8C2DType m_treeTypes[64];
};

// ?rva000E8C2D@W3DShrubBuffer@@QAEXHH@Z
void W3DShrubBuffer::rva000E8C2D(Int index, Int request)
{
	Rva000E8C2DTree *tree = (Rva000E8C2DTree *)(index * 0xa0 + (char *)this);
	Int type = tree->m_treeType;
	if (index >= m_numTrees)
		return;
	if (type < 0)
		return;
	if (request == 1) {
		if (m_treeTypes[type].m_data->m_flag54)
			return;
	}
	if (request == 2) {
		if (!m_treeTypes[type].m_data->m_flag54)
			return;
	}

	tree->m_sinkFrames = m_treeTypes[type].m_data->m_duration;
	tree->m_request = request;
	if (tree->m_topple != 0) {
		tree->m_topple->Release_Ref();
		tree->m_topple = 0;
	}
	tree->m_topple = Create_Render_Obj(m_treeTypes[type].m_modelName.str());
	rva0010E4F6(tree->m_topple, false);
	reinterpret_cast<SceneClass *>(W3DDisplay::m_3DScene)->Add_Render_Object(tree->m_topple);
	Matrix3D transform = tree->m_topple->Get_Transform();
	transform[0][3] = tree->m_location.x;
	transform[1][3] = tree->m_location.y;
	transform[2][3] = tree->m_location.z;
	Matrix3 rotation(tree->m_transform);
	transform.Set_Rotation(rotation);
	tree->m_topple->Set_Transform(transform);

	if (tree->m_pushAside != 0) {
		tree->m_pushAside->Release_Ref();
		tree->m_pushAside = 0;
	}
	if (m_treeTypes[type].m_field58 != -2) {
		tree->m_pushAside = Create_Render_Obj(m_treeTypes[tree->m_toppledType].m_data->m_modelName.str());
		rva0010E4F6(tree->m_pushAside, false);
		reinterpret_cast<SceneClass *>(W3DDisplay::m_3DScene)->Add_Render_Object(tree->m_pushAside);
		transform = tree->m_pushAside->Get_Transform();
		transform[0][3] = tree->m_location.x;
		transform[1][3] = tree->m_location.y;
		transform[2][3] = tree->m_location.z;
		transform.Set_Rotation(rotation);
		tree->m_pushAside->Set_Transform(transform);
	}
	if (tree->m_topple != 0)
		Rva0010E87A_SetOpacity(tree->m_topple, 1.0f);
	if (tree->m_pushAside != 0)
		Rva0010E87A_SetOpacity(tree->m_pushAside, 0.0f);
	if (m_treeTypes[type].m_data->m_effect != 0) {
		Coord3D position;
		position.x = tree->m_location.x;
		position.y = tree->m_location.y;
		position.z = tree->m_location.z;
		FXList::doFXPos(m_treeTypes[type].m_data->m_effect, &position, 0, 0.0f, 0);
	}
	m_anythingChanged = true;
}
