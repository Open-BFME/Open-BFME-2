// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/shims/stringinline /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas
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

#include "W3DTreeRecord.h"
#include "W3DTreeTypeRecord.h"

class Rva000E6AC0Base
{
public:
	Rva000E6AC0Base() {}
	virtual ~Rva000E6AC0Base() {}
};

class Rva0052413E
{
public:
	Rva0052413E() throw();
	~Rva0052413E();
private:
	unsigned char m_storage[12];
};

class TextureClass;

template <class T> class RefCountPtr;

template <> class RefCountPtr<TextureClass>
{
public:
	RefCountPtr const &operator=(RefCountPtr const &other);
	TextureClass *Ptr;
};

class Rva000E6AC0 : public Rva000E6AC0Base
{
public:
	Rva000E6AC0();
	void rva000E65B1();
	virtual ~Rva000E6AC0();
private:
	unsigned char m_storage[0x38 - 4]; // +0x04
protected:
	RefCountPtr<TextureClass> texture38, texture3c; // +0x38
	char list40[0x28], list68[0x28]; // +0x40
private:
	unsigned char m_pad90[0x5BC - 0x90];
protected:
	float m_sinkScale; // +0x5BC
};

struct TTree;

class Xfer;
struct Rva000EAFA4Coord3;
struct Rva000EAFA4Coord2;
struct Rva000ECF79Coord;
struct Rva000ECF79Data;

class W3DTreeBuffer : public Rva000E6AC0
{
	friend class Rva000EC9C6;
protected:
	void updateTexture();
	void updateTopplingTree(TTree *tree);
	virtual void xfer(Xfer *xfer);
public:
	W3DTreeBuffer();
public:
	void rva000EA24D();
private:
	Rva000EDA94Record m_records[1200];
private:
	int m_count;
private:
	unsigned char m_anythingChanged;
private:
	unsigned char m_44545; // +0x44545
private:
	unsigned char m_changed;
private:
	unsigned char m_44547;
private:
	Rva0052413E m_objects;
private:
	unsigned char m_initialized;
private:
	unsigned char m_44555;
private:
	unsigned char m_needUpdate;
private:
	unsigned char m_44557;
private:
	Rva000EC67F m_types[64]; // +0x44558
private:
	int m_typeCount;
private:
	int m_45c5c; // +0x45C5C
private:
	int m_45c60;
private:
	unsigned char m_45c64;
public:
	bool rva000EA48D(void *key, const Coord3D *direction, float height);
	bool rva000EA644(void *key);
	void rva000EA2C0(void *key);
	bool rva000EA6A7(void *key);
	void rva000EB2EF(int index);
	void rva000EB0E6(int index);
	bool rva000ECF2A(unsigned key, int mode);
	void startMorph(int index, int mode);
	int addTreeType(const AsciiString &modelName, const AsciiString &nameC, const void *data, int shadowKind,
		const AsciiString &textureName, const AsciiString &templateName);
	int rva000ECDF5(const AsciiString &templateName, int shadowKind, const AsciiString &textureName);
	char rva000EA327(void *key, Vector3 position, const Matrix3D *transform);
	bool rva000EAFA4(int index, Rva000EAFA4Coord3 *position, float *radius, Rva000EAFA4Coord2 *primary,
		Rva000EAFA4Coord2 *secondary);
	void addTree(unsigned int id, Rva000ECF79Coord location, float scale, const Matrix3D *transform,
		float randomScaleAmount, const Rva000ECF79Data *data, int shadowKind, const AsciiString &textureName,
		const AsciiString &templateName);
};

class FXList
{
public:
	static void doFXPos(const FXList *list, const Coord3D *position, const Matrix3D *transform, float speed, const Coord3D *direction);
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
	Int m_morphTreeType;
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
	Int m_toppleState;
	unsigned char m_pad84[0xc4 - 0x84];
	bool m_flagc4;
	unsigned char m_padc5[0xc8 - 0xc5];
	Int m_morphState;
	unsigned char m_padcc[0xd0 - 0xcc];
	Int m_fieldd0;
	Int m_morphFramesLeft;
	RenderObjClass *m_fieldd8;
	RenderObjClass *m_fielddc;
	unsigned char m_pade0[0xe8 - 0xe0];
};

// This method's native record and type views over the canonical tree records.
struct Rva000ECA4DBufferView
{
	unsigned char m_pad0000[0x5c0];
	Rva000ECA4DTree m_trees[1200];
	unsigned char m_pad44540[0x44558 - 0x44540];
	Rva000ECA4DType m_treeTypes[64];
};

// File-static matrix copy (LK3-style): the TU's copy-ctor COMDAT loses
// the link, and the rowed body below inlines the construction, so the def
// cannot just go away. The helper keeps a call in the source (regalloc
// preserved) while the copy-ctor goes unused.
static void CopyTreeMatrix3D(Matrix3D &dst, const Matrix3D &src)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
}

// ?startMorph@W3DTreeBuffer@@QAEXHH@Z
void W3DTreeBuffer::startMorph(Int index, Int request)
{
	if (index >= m_count)
		return;
	Int type = ((Rva000ECA4DBufferView *)this)->m_trees[index].m_treeType;
	if (type < 0)
		return;
	if (request == 1) {
		if (((Rva000ECA4DBufferView *)this)->m_treeTypes[type].m_data->m_flag54)
			return;
	}
	if (request == 2) {
		if (!((Rva000ECA4DBufferView *)this)->m_treeTypes[type].m_data->m_flag54)
			return;
	}
	if (!((Rva000ECA4DBufferView *)this)->m_trees[index].m_flagc4 && ((Rva000ECA4DBufferView *)this)->m_trees[index].m_toppleState != 0) {
		((Rva0027F2D6 *)TheTerrainLogic)->rva0027F2D6(((Rva000ECA4DBufferView *)this)->m_trees[index].m_drawableID);
		return;
	}
	if (((Rva000ECA4DBufferView *)this)->m_trees[index].m_flagc4 || ((Rva000ECA4DBufferView *)this)->m_trees[index].m_toppleState != 0)
		return;

	((Rva000ECA4DBufferView *)this)->m_trees[index].m_morphFramesLeft = ((Rva000ECA4DBufferView *)this)->m_treeTypes[type].m_data->m_duration;
	((Rva000ECA4DBufferView *)this)->m_trees[index].m_morphState = request;
	if (((Rva000ECA4DBufferView *)this)->m_trees[index].m_fieldd8 != 0) {
		((Rva000ECA4DBufferView *)this)->m_trees[index].m_fieldd8->Release_Ref();
		((Rva000ECA4DBufferView *)this)->m_trees[index].m_fieldd8 = 0;
	}
	((Rva000ECA4DBufferView *)this)->m_trees[index].m_fieldd8 = Create_Render_Obj(((Rva000ECA4DBufferView *)this)->m_treeTypes[type].m_modelName.str());
	rva0010E4F6(((Rva000ECA4DBufferView *)this)->m_trees[index].m_fieldd8, false);
	reinterpret_cast<SceneClass *>(W3DDisplay::m_3DScene)->Add_Render_Object(((Rva000ECA4DBufferView *)this)->m_trees[index].m_fieldd8);
	Matrix3D transform;
	CopyTreeMatrix3D(transform, ((Rva000ECA4DBufferView *)this)->m_trees[index].m_fieldd8->Get_Transform());
	transform[0][3] = ((Rva000ECA4DBufferView *)this)->m_trees[index].m_location.x;
	transform[1][3] = ((Rva000ECA4DBufferView *)this)->m_trees[index].m_location.y;
	transform[2][3] = ((Rva000ECA4DBufferView *)this)->m_trees[index].m_location.z;
	Matrix3 rotation(((Rva000ECA4DBufferView *)this)->m_trees[index].m_transform);
	transform.Set_Rotation(rotation);
	((Rva000ECA4DBufferView *)this)->m_trees[index].m_fieldd8->Set_Transform(transform);

	if (((Rva000ECA4DBufferView *)this)->m_trees[index].m_fielddc != 0) {
		((Rva000ECA4DBufferView *)this)->m_trees[index].m_fielddc->Release_Ref();
		((Rva000ECA4DBufferView *)this)->m_trees[index].m_fielddc = 0;
	}
	if (((Rva000ECA4DBufferView *)this)->m_treeTypes[type].m_morphTreeType != -2) {
		((Rva000ECA4DBufferView *)this)->m_trees[index].m_fielddc = Create_Render_Obj(((Rva000ECA4DBufferView *)this)->m_treeTypes[((Rva000ECA4DBufferView *)this)->m_trees[index].m_fieldd0].m_data->m_modelName.str());
		rva0010E4F6(((Rva000ECA4DBufferView *)this)->m_trees[index].m_fielddc, false);
		reinterpret_cast<SceneClass *>(W3DDisplay::m_3DScene)->Add_Render_Object(((Rva000ECA4DBufferView *)this)->m_trees[index].m_fielddc);
		transform = ((Rva000ECA4DBufferView *)this)->m_trees[index].m_fielddc->Get_Transform();
		transform[0][3] = ((Rva000ECA4DBufferView *)this)->m_trees[index].m_location.x;
		transform[1][3] = ((Rva000ECA4DBufferView *)this)->m_trees[index].m_location.y;
		transform[2][3] = ((Rva000ECA4DBufferView *)this)->m_trees[index].m_location.z;
		transform.Set_Rotation(rotation);
		((Rva000ECA4DBufferView *)this)->m_trees[index].m_fielddc->Set_Transform(transform);
	}
	if (((Rva000ECA4DBufferView *)this)->m_trees[index].m_fieldd8 != 0)
		Rva0010E87A_SetOpacity(((Rva000ECA4DBufferView *)this)->m_trees[index].m_fieldd8, 1.0f);
	if (((Rva000ECA4DBufferView *)this)->m_trees[index].m_fielddc != 0)
		Rva0010E87A_SetOpacity(((Rva000ECA4DBufferView *)this)->m_trees[index].m_fielddc, 0.0f);
	if (((Rva000ECA4DBufferView *)this)->m_treeTypes[type].m_data->m_effect != 0) {
		Coord3D position;
		position.x = ((Rva000ECA4DBufferView *)this)->m_trees[index].m_location.x;
		position.y = ((Rva000ECA4DBufferView *)this)->m_trees[index].m_location.y;
		position.z = ((Rva000ECA4DBufferView *)this)->m_trees[index].m_location.z;
		FXList::doFXPos(((Rva000ECA4DBufferView *)this)->m_treeTypes[type].m_data->m_effect, &position, 0, 0.0f, 0);
	}
	m_anythingChanged = true;
}
