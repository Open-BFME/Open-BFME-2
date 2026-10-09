// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ?onDrawableBoundToObject@W3DScriptedModelDraw@@UAEXXZ retail 0x000C1252
// 504 bytes (pinned placeholder ?bfmeFinishYS@Gen_00755E70@@QAEXXZ).
// Identity: the six W3DScriptedModelDraw-family vftables hold it in the Module
// slot after getModuleNameKey (0x000C1201) and the empty onObjectCreated,
// before preloadAssets and the empty onDelete (the same slot order as the
// AIUpdateInterface and GarrisonContain vftables around their rowed
// onObjectCreated). WorldBuilder twin 0x00928590 carries the "*** ASSET
// ERROR: all draw modules must have a default model state" throw.
// Body: the Zero Hour constructor tail moved here - find the default model
// state for empty condition flags (throw INIException(3) when missing); copy
// the drawable value 0x000B2BA3 to +0xC0 when the module data asks (+0x135);
// unless the module data's +0x15F holds and +0xBC is set: apply the state
// through the slot +0x100 and 0x000BF9FC with its bone state (0x000B4BED);
// then the fade-in: with an emissive render object (+0x50 and +0x154 copied
// to +0x270) save the vertex material emissive to +0x280 and zero it (fade
// start frame +0x27C from TheGameClient) else Drawable::fadeIn; finally an
// object of KindOf bit 28 whose controlling player lacks +0x33B gets the
// "FELLOWSHIPBADGE" sub-object through ObjectDrawInterface slot +0x88.
// Field names are not asserted.

#include "ascii_string.h"

extern "C" void *__cdecl memset(void *, int, unsigned int);

class ModelConditionFlags
{
public:
	ModelConditionFlags() { memset(this, 0, sizeof(*this)); }
	unsigned int m_bits[19];
};

class INIException
{
public:
	char *mFailureMessage;
	int mErrorCode;
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &that);
	~INIException();
};

struct ModelConditionInfo;
class Rva000B4B23 { public: void *rva000B4B23(const ModelConditionFlags &); };
class Rva000B4BED { public: void *rva000B4BED(const void *); };
class Rva000B8F5AOuter { public: void rva000BF9FC(void *boneState, int a, int b); };

class W3DScriptedModelDrawModuleData
{
public:
	const ModelConditionInfo *findBestInfo(const ModelConditionFlags &c) const
	{
		return (const ModelConditionInfo *)((Rva000B4B23 *)this)->rva000B4B23(c);
	}
	const ModelConditionInfo *findBoneState(const ModelConditionFlags &c) const
	{
		return (const ModelConditionInfo *)((Rva000B4BED *)this)->rva000B4BED(&c);
	}

	unsigned char m_pad000[0x135];
	bool m_135;
	unsigned char m_pad136[0x150 - 0x136];
	unsigned int m_fadeInFrames;
	bool m_emissiveFade;
	unsigned char m_pad155[0x15f - 0x155];
	bool m_15f;
};

class Vector3 { public: float X, Y, Z; };

class VertexMaterialClass
{
public:
	virtual void Delete_This();
	void Get_Emissive(Vector3 *set) const;
	void Release_Ref()
	{
		if (--NumRefs == 0)
			Delete_This();
	}
	int NumRefs;
};

class MaterialInfoClass
{
public:
	virtual void Delete_This();
	VertexMaterialClass *Get_Vertex_Material(int index);
	void Release_Ref()
	{
		if (--NumRefs == 0)
			Delete_This();
	}
	int NumRefs;
};

#define SLOTS4(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3();
#define SLOTS16(p) SLOTS4(p##0) SLOTS4(p##1) SLOTS4(p##2) SLOTS4(p##3)

class RenderObjClass
{
public:
	SLOTS16(s0) SLOTS16(s1) SLOTS16(s2) SLOTS16(s3) SLOTS16(s4)
	SLOTS4(s50) virtual void s54();
	virtual MaterialInfoClass *Get_Material_Info();	// +0x154
};

void rva0010E4F6(void *robj, bool flag);
bool Rva0010E676_SetEmissive(RenderObjClass *robj, float r, float g, float b);

class GameClient
{
public:
	SLOTS16(s0) SLOTS4(s10) SLOTS4(s14) SLOTS4(s18) virtual void s1c0(); virtual void s1c1(); virtual void s1c2();
	virtual unsigned int getFrame();				// +0x7C
};
extern GameClient *TheGameClient;

class Player
{
public:
	unsigned char m_pad000[0x33b];
	bool m_33b;
};

class ThingTemplate
{
public:
	__forceinline bool isKindOf(int kind) const
	{
		return (m_kindOf[(unsigned int)kind >> 5] & (1 << (kind & 31))) != 0;
	}
	unsigned char m_pad000[0x108];
	unsigned int m_kindOf[14];
};

class Object
{
public:
	Player *getControllingPlayer() const;
	const ThingTemplate *getTemplate() const { return m_template; }
	void *m_vptr;
	const ThingTemplate *m_template;
};

struct Rva000B2BE5Src;
int Rva000B2BA3Get(const Rva000B2BE5Src *src, bool *out);

class Drawable
{
public:
	void fadeIn(unsigned int frames);
	unsigned char m_pad000[0xfc];
	Object *m_object;
};

class DrawModule
{
public:
	SLOTS16(s0) SLOTS16(s1) SLOTS16(s2) SLOTS16(s3)
	virtual void setModelState(const ModelConditionInfo *info, int unk, const ModelConditionInfo *boneState);	// +0x100
	const W3DScriptedModelDrawModuleData *getW3DModelDrawModuleData() const { return m_moduleData; }
	Drawable *getDrawable() const { return m_drawable; }
	const W3DScriptedModelDrawModuleData *m_moduleData;
	Drawable *m_drawable;
};

class ObjectDrawInterface
{
public:
	SLOTS16(s0) SLOTS16(s1) virtual void s20(); virtual void s21();
	virtual void showSubObject(const AsciiString &name, int unk, int show, float a, float b);	// +0x88
};

class W3DScriptedModelDrawInterface10
{
public:
	virtual void interface10();
};

class W3DScriptedModelDraw : public DrawModule, public ObjectDrawInterface, public W3DScriptedModelDrawInterface10
{
public:
	virtual void onDrawableBoundToObject();
	const ModelConditionInfo *findBestInfo(const ModelConditionFlags &c) const
	{
		return getW3DModelDrawModuleData()->findBestInfo(c);
	}
	void rva000BF9FC(const ModelConditionInfo *boneState, int a, int b)
	{
		((Rva000B8F5AOuter *)this)->rva000BF9FC((void *)boneState, a, b);
	}

	unsigned char m_pad014[0x50 - 0x14];
	RenderObjClass *m_renderObject;
	unsigned char m_pad054[0xbc - 0x54];
	int m_bc;
	int m_c0;
	unsigned char m_pad0c4[0x270 - 0xc4];
	bool m_emissiveFade;
	unsigned int m_fadeFrames;
	unsigned int m_fadeElapsed;
	unsigned int m_fadeStartFrame;
	Vector3 m_emissive;
	bool m_28c;
};

void W3DScriptedModelDraw::onDrawableBoundToObject()
{
	ModelConditionFlags emptyFlags;
	const ModelConditionInfo *info = findBestInfo(emptyFlags);
	if (!info)
		throw INIException(3, "*** ASSET ERROR: all draw modules must have a default model state");

	if (getW3DModelDrawModuleData()->m_135)
		m_c0 = Rva000B2BA3Get((const Rva000B2BE5Src *)getDrawable(), 0);

	if (getW3DModelDrawModuleData()->m_15f && m_bc != 0)
		return;

	const ModelConditionInfo *boneState = getW3DModelDrawModuleData()->findBoneState(emptyFlags);
	setModelState(info, 0, boneState);
	m_28c = false;
	rva000BF9FC(boneState, 0, 0);

	unsigned int fadeFrames = getW3DModelDrawModuleData()->m_fadeInFrames;
	if (getDrawable() && fadeFrames > 0)
	{
		m_emissiveFade = getW3DModelDrawModuleData()->m_emissiveFade;
		if (m_renderObject && m_emissiveFade)
		{
			MaterialInfoClass *matInfo = m_renderObject->Get_Material_Info();
			if (matInfo)
			{
				VertexMaterialClass *vmat = matInfo->Get_Vertex_Material(0);
				if (vmat)
				{
					vmat->Get_Emissive(&m_emissive);
					vmat->Release_Ref();
				}
				matInfo->Release_Ref();
			}
			rva0010E4F6(m_renderObject, false);
			Rva0010E676_SetEmissive(m_renderObject, 0.0f, 0.0f, 0.0f);
			m_fadeFrames = fadeFrames;
			m_fadeElapsed = 0;
			m_fadeStartFrame = TheGameClient->getFrame();
		}
		else
		{
			getDrawable()->fadeIn(fadeFrames);
		}
	}

	Object *obj = getDrawable()->m_object;
	if (obj && obj->getTemplate()->isKindOf(28))
	{
		Player *player = obj->getControllingPlayer();
		if (player && !player->m_33b)
			showSubObject(AsciiString("FELLOWSHIPBADGE"), 0, 1, 0.0f, 0.0f);
	}
}
