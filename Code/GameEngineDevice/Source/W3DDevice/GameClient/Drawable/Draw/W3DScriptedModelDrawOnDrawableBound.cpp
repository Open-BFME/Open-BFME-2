// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ?onDrawableBoundToObject@W3DScriptedModelDraw@@UAEXXZ retail 0x000C1252
//
// ?buildPlayingAnimationStringInfo@W3DScriptedModelDraw@@UAEXHPAVAsciiString@@0@Z
// retail 0x000C14F5 (252 bytes, ret 12; WB 0x00930400 names it, strings
// "%s %d/%d frames(%.1fs), AnimMode:%s, BlendTime:%d" and the release
// notice): slot 12 of the +0x0C interface tables (0x00BCBB78 and siblings).
// After the rowed animation refresh 0x000C0386 it describes playing slot
// index (0..2, 0x1C-byte records at +0x110) using the canonical
// native BfmeAnimationModeNames table at VA DB4E44.
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
#include <string.h>

class ModelConditionFlags
{
public:
	ModelConditionFlags() { memset(this, 0, sizeof(*this)); }
	unsigned int m_bits[19];
};

#include "../../../../../../GameEngine/Include/Common/INI/FieldParse.h"

struct ModelConditionInfo;
class Rva000B4B23 { public: void *rva000B4B23(const ModelConditionFlags &); };
class Rva000B4BED { public: void *rva000B4BED(const void *); };
class Rva000B8F5AOuter { public: bool rva000BF9FC(void *boneState, bool force, int options); };

class W3DScriptedModelDrawModuleData
{
public:
	const ModelConditionInfo *findBestInfo(const ModelConditionFlags &modelConditionFlags) const
	{
		return (const ModelConditionInfo *)((Rva000B4B23 *)this)->rva000B4B23(modelConditionFlags);
	}
	const ModelConditionInfo *findBoneState(const ModelConditionFlags &modelConditionFlags) const
	{
		return (const ModelConditionInfo *)((Rva000B4BED *)this)->rva000B4BED(&modelConditionFlags);
	}

	unsigned char m_pad000[0x135];
	bool m_135;
	unsigned char m_pad136[0x150 - 0x136];
	unsigned int m_fadeInFrames;
	bool m_emissiveFade;
	unsigned char m_pad155[0x15f - 0x155];
	bool m_15f;
};

#include "../../../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

#include "../../../../../../Libraries/Source/WWVegas/WW3D2/VertexMaterialClass.h"

#include "../../../../../../Libraries/Source/WWVegas/WW3D2/MaterialInfoClass.h"

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

#include "../../../../../../GameEngine/Include/GameClient/GameClientClass.h"
extern GameClient *TheGameClient;

class Player
{
public:
	unsigned char m_pad000[0x33b];
	bool m_33b;
};

#include "../../../../../../GameEngine/Include/Common/ThingTemplate.h"

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

#include "../../../../../../GameEngine/Include/GameClient/Drawable.h"

#include "../../../../../../GameEngine/Include/GameLogic/Module/DrawModule.h"

#include "../../../../../../GameEngine/Include/Common/Rva000BFDFE.h"
extern const char *animationModeNames[];

// The playing animation's slot views: name (2), frame count (5), total
// seconds (7).
class Rva000C14F5Anim
{
public:
	virtual void a0(); virtual void a1();
	virtual const char *getName();	// slot 2
	virtual void a3(); virtual void a4();
	virtual int getNumFrames();	// slot 5
	virtual void a6();
	virtual float getTotalTime();	// slot 7
};

struct Rva000C14F5Playing
{
	Rva000C14F5Anim *m_anim;	// +0x00
	float m_frame;	// +0x04
	float m_08;
	float m_blendTime;	// +0x0C
	int m_mode;	// +0x10
	unsigned char m_pad14[0x1C - 0x14];
};

class ObjectDrawInterface
{
public:
	SLOTS4(s00) SLOTS4(s01) SLOTS4(s02)
	virtual void buildPlayingAnimationStringInfo(int index, AsciiString *animInfo, AsciiString *stateInfo);	// slot 12
	virtual void s031(); virtual void s032(); virtual void s033();
	SLOTS16(s1) virtual void s20(); virtual void s21();
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
	virtual void scriptedSlot62();
	virtual void scriptedSlot63();
	virtual void setModelState(const ModelConditionInfo *info, int unk, const ModelConditionInfo *boneState); // slot 64
	const W3DScriptedModelDrawModuleData *getW3DModelDrawModuleData() const { return (const W3DScriptedModelDrawModuleData *)getModuleData(); }
	virtual void onDrawableBoundToObject();
	virtual void buildPlayingAnimationStringInfo(int index, AsciiString *animInfo, AsciiString *stateInfo);
	const ModelConditionInfo *findBestInfo(const ModelConditionFlags &modelConditionFlags) const
	{
		return getW3DModelDrawModuleData()->findBestInfo(modelConditionFlags);
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
	unsigned char m_pad0c4[0x110 - 0xc4];
	Rva000C14F5Playing m_playing[3];	// +0x110
	unsigned char m_pad164[0x270 - 0x164];
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
	if (obj && (obj->getTemplate()->m_kindof[0] & (1u << 28)) != 0)
	{
		Player *player = obj->getControllingPlayer();
		if (player && !player->m_33b)
			showSubObject(AsciiString("FELLOWSHIPBADGE"), 0, 1, 0.0f, 0.0f);
	}
}

void W3DScriptedModelDraw::buildPlayingAnimationStringInfo(int index, AsciiString *animInfo, AsciiString *stateInfo)
{
	((Rva000BFDFE *)this)->rva000C0386();
	if (index < 0 || (unsigned int)index >= 3)
		return;
	if (m_playing[index].m_anim == 0)
		return;
	if (animInfo)
	{
		float totalTime = m_playing[index].m_anim->getTotalTime();
		int numFrames = m_playing[index].m_anim->getNumFrames();
		int frame = (int)m_playing[index].m_frame;
		int blendTime = (int)m_playing[index].m_blendTime;
		AsciiString mode(animationModeNames[m_playing[index].m_mode]);
		animInfo->format("%s %d/%d frames(%.1fs), AnimMode:%s, BlendTime:%d", m_playing[index].m_anim->getName(),
			frame + 1, numFrames, (double)totalTime, mode.str(), blendTime);
	}
	if (stateInfo)
		stateInfo->format("(ModelState and AnimState info not available in release)");
}
