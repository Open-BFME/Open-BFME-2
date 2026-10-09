// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// W3DTreeBuffer method at retail 0x000ECA4D (936 bytes, ret 8; called from the key lookup 0x000ECF2A):
// gives a tree its type's model and the model of the type at +0xD0 at the tree's position and rotation,
// starts the +0xD4 countdown and plays the type's effect. Donor: Open-BFME-1 W3DTreeBufferRva00736150.cpp
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

struct Rva000ECA4DTypeData
{
	unsigned char m_pad00[8];
	AsciiString m_modelName;
	unsigned char m_pad0c[0x4c - 0x0c];
	Int m_duration;
	const FXList *m_effect;
	bool m_flag54;
};

struct Rva000ECA4DType
{
	unsigned char m_pad00[0x20];
	const Rva000ECA4DTypeData *m_data;
	unsigned char m_pad24[0x4c - 0x24];
	AsciiString m_modelName;
	unsigned char m_pad50[0x58 - 0x50];
	Int m_field58;
};

struct Rva000ECA4DTree
{
	Coord3D m_location;
	Real m_scale;
	Matrix3D m_transform;
	Int m_treeType;
	unsigned char m_pad44[0x58 - 0x44];
	Int m_drawableID;
	unsigned char m_pad5c[0x80 - 0x5c];
	Int m_field80;
	unsigned char m_pad84[0xc4 - 0x84];
	bool m_flagc4;
	unsigned char m_padc5[0xc8 - 0xc5];
	Int m_fieldc8;
	unsigned char m_padcc[0xd0 - 0xcc];
	Int m_fieldd0;
	Int m_fieldd4;
	RenderObjClass *m_fieldd8;
	RenderObjClass *m_fielddc;
	unsigned char m_pade0[0xe8 - 0xe0];
};

class W3DTreeBuffer
{
public:
	void rva000ECA4D(Int index, Int request);

private:
	unsigned char m_pad0000[0x5c0];
	Rva000ECA4DTree m_trees[1200];
	Int m_numTrees;
	bool m_anythingChanged;
	unsigned char m_pad44545[0x44558 - 0x44545];
	Rva000ECA4DType m_treeTypes[64];
};

// ?rva000ECA4D@W3DTreeBuffer@@QAEXHH@Z
void W3DTreeBuffer::rva000ECA4D(Int index, Int request)
{
	if (index >= m_numTrees)
		return;
	Int type = m_trees[index].m_treeType;
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
	if (!m_trees[index].m_flagc4 && m_trees[index].m_field80 != 0) {
		((Rva0027F2D6 *)TheTerrainLogic)->rva0027F2D6(m_trees[index].m_drawableID);
		return;
	}
	if (m_trees[index].m_flagc4 || m_trees[index].m_field80 != 0)
		return;

	m_trees[index].m_fieldd4 = m_treeTypes[type].m_data->m_duration;
	m_trees[index].m_fieldc8 = request;
	if (m_trees[index].m_fieldd8 != 0) {
		m_trees[index].m_fieldd8->Release_Ref();
		m_trees[index].m_fieldd8 = 0;
	}
	m_trees[index].m_fieldd8 = Create_Render_Obj(m_treeTypes[type].m_modelName.str());
	rva0010E4F6(m_trees[index].m_fieldd8, false);
	reinterpret_cast<SceneClass *>(W3DDisplay::m_3DScene)->Add_Render_Object(m_trees[index].m_fieldd8);
	Matrix3D transform = m_trees[index].m_fieldd8->Get_Transform();
	transform[0][3] = m_trees[index].m_location.x;
	transform[1][3] = m_trees[index].m_location.y;
	transform[2][3] = m_trees[index].m_location.z;
	Matrix3 rotation(m_trees[index].m_transform);
	transform.Set_Rotation(rotation);
	m_trees[index].m_fieldd8->Set_Transform(transform);

	if (m_trees[index].m_fielddc != 0) {
		m_trees[index].m_fielddc->Release_Ref();
		m_trees[index].m_fielddc = 0;
	}
	if (m_treeTypes[type].m_field58 != -2) {
		m_trees[index].m_fielddc = Create_Render_Obj(m_treeTypes[m_trees[index].m_fieldd0].m_data->m_modelName.str());
		rva0010E4F6(m_trees[index].m_fielddc, false);
		reinterpret_cast<SceneClass *>(W3DDisplay::m_3DScene)->Add_Render_Object(m_trees[index].m_fielddc);
		transform = m_trees[index].m_fielddc->Get_Transform();
		transform[0][3] = m_trees[index].m_location.x;
		transform[1][3] = m_trees[index].m_location.y;
		transform[2][3] = m_trees[index].m_location.z;
		transform.Set_Rotation(rotation);
		m_trees[index].m_fielddc->Set_Transform(transform);
	}
	if (m_trees[index].m_fieldd8 != 0)
		Rva0010E87A_SetOpacity(m_trees[index].m_fieldd8, 1.0f);
	if (m_trees[index].m_fielddc != 0)
		Rva0010E87A_SetOpacity(m_trees[index].m_fielddc, 0.0f);
	if (m_treeTypes[type].m_data->m_effect != 0) {
		Coord3D position;
		position.x = m_trees[index].m_location.x;
		position.y = m_trees[index].m_location.y;
		position.z = m_trees[index].m_location.z;
		FXList::doFXPos(m_treeTypes[type].m_data->m_effect, &position, 0, 0.0f, 0);
	}
	m_anythingChanged = true;
}
