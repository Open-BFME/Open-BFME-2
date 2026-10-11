// ?rva000E8C2D@W3DShrubBuffer@@QAEXHH@Z
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// W3DShrubBuffer start-morph at retail 0x000E8C2D (880 bytes, ret 8), shrub twin of the tree 0x000ECA4D:
// gives a shrub its type's model and the model of the type at +0xD0 at the tree's position and rotation,
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
	Rva000E8C2DTree m_trees[2000];
	Int m_numTrees;
	bool m_anythingChanged;
	unsigned char m_pad4fb5d[0x4fb70 - 0x4fb5d];
	Rva000E8C2DType m_treeTypes[64];
};

// File-static matrix copy (LK3-style): the TU's copy-ctor COMDAT loses
// the link, and the rowed body below inlines the construction, so the def
// cannot just go away. The helper keeps a call in the source (regalloc
// preserved) while the copy-ctor goes unused.
static void CopyShrubMatrix3D(Matrix3D &dst, const Matrix3D &src)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
}

// ?rva000E8C2D@W3DShrubBuffer@@QAEXHH@Z
void W3DShrubBuffer::rva000E8C2D(Int index, Int request)
{
	Int type = m_trees[index].m_treeType;
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

	m_trees[index].m_sinkFrames = m_treeTypes[type].m_data->m_duration;
	m_trees[index].m_request = request;
	if (m_trees[index].m_topple != 0) {
		m_trees[index].m_topple->Release_Ref();
		m_trees[index].m_topple = 0;
	}
	m_trees[index].m_topple = Create_Render_Obj(m_treeTypes[type].m_modelName.str());
	rva0010E4F6(m_trees[index].m_topple, false);
	reinterpret_cast<SceneClass *>(W3DDisplay::m_3DScene)->Add_Render_Object(m_trees[index].m_topple);
	Matrix3D transform;
	CopyShrubMatrix3D(transform, m_trees[index].m_topple->Get_Transform());
	transform[0][3] = m_trees[index].m_location.x;
	transform[1][3] = m_trees[index].m_location.y;
	transform[2][3] = m_trees[index].m_location.z;
	Matrix3 rotation(m_trees[index].m_transform);
	transform.Set_Rotation(rotation);
	m_trees[index].m_topple->Set_Transform(transform);

	if (m_trees[index].m_pushAside != 0) {
		m_trees[index].m_pushAside->Release_Ref();
		m_trees[index].m_pushAside = 0;
	}
	if (m_treeTypes[type].m_field58 != -2) {
		m_trees[index].m_pushAside = Create_Render_Obj(m_treeTypes[m_trees[index].m_toppledType].m_data->m_modelName.str());
		rva0010E4F6(m_trees[index].m_pushAside, false);
		reinterpret_cast<SceneClass *>(W3DDisplay::m_3DScene)->Add_Render_Object(m_trees[index].m_pushAside);
		transform = m_trees[index].m_pushAside->Get_Transform();
		transform[0][3] = m_trees[index].m_location.x;
		transform[1][3] = m_trees[index].m_location.y;
		transform[2][3] = m_trees[index].m_location.z;
		transform.Set_Rotation(rotation);
		m_trees[index].m_pushAside->Set_Transform(transform);
	}
	if (m_trees[index].m_topple != 0)
		Rva0010E87A_SetOpacity(m_trees[index].m_topple, 1.0f);
	if (m_trees[index].m_pushAside != 0)
		Rva0010E87A_SetOpacity(m_trees[index].m_pushAside, 0.0f);
	if (m_treeTypes[type].m_data->m_effect != 0) {
		Coord3D position;
		position.x = m_trees[index].m_location.x;
		position.y = m_trees[index].m_location.y;
		position.z = m_trees[index].m_location.z;
		FXList::doFXPos(m_treeTypes[type].m_data->m_effect, &position, 0, 0.0f, 0);
	}
	m_anythingChanged = true;
}
