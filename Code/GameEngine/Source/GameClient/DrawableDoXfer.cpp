#include "BuffManager.h"
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /ICode/Libraries/Include/Lib
// stlport
// ?DoXfer@Drawable@@UAEXPAVXfer@@@Z retail 0x0027A219..0x0027B18C (3955 bytes) RET 4.
//
// Drawable::DoXfer, the Snapshot slot-3 overrider of Drawable (WorldBuilder
// twin 0x00CB26E0 in Drawable.cpp). Target evidence: `this` is the Snapshot
// subobject at Drawable+0x60 (members are addressed this+X for Drawable
// offset X+0x60 and full-Drawable callees take this-0x60); XferVersion 11;
// the rowed callees XferDrawableID 0x003060CA, Drawable::setID 0x00271058,
// BitFlags<591>::xfer 0x000BB710 (three condition-state members),
// getTransformMatrix 0x0027628E / Thing::setTransformMatrix 0x0030A2B7,
// the tint-envelope ctor 0x00271826 (0x50 bytes), DrawableLocoInfo
// 0x00270098, the icon-info getter 0x00270BA8 and its clear 0x00270041,
// Anim2DCollection's template lookup 0x002D752D and Anim2D 0x002D6D63,
// TheDrawableIconNames 0x009BB660 (14 entries, _strcmpi lookup),
// the custom-ambient helpers 0x00274DD4/0x0027974B/0x002781DA/0x00279354,
// DynamicAudioEventInfo::xferNoName 0x004331C6, BuffManager 0x00362DBD,
// the pathfind-map remove/add pair 0x002E718A/0x002E7178 and the
// XferException(5) throws. Version gates 2..11 are target facts.
// Donor structure: Open-BFME-1 DrawableXfer.cpp (version 4) and Zero Hour
// Drawable::xfer supply the field order and semantics; the BFME2 field set
// differs (v6 base-sound name, v7..v10 obsolete block, v9 +0x388, v10
// dropped uint). Member names past the cited offsets are placeholders.

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
	return a < b ? b : a;
}
}
#include <vector>
#include <string.h>
#include "ascii_string.h"
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#include "Common/Snapshot.h"

class Object;
class ModuleData;
// Use the rowed push_back owner at4DFCB0; it calls overflow2DFCF6.
// This avoids competing copies of its allocator/clear dependencies.
namespace _STL {
template<> void vector<const ModuleData *>::push_back(const ModuleData *const &);
}

class Anim2DCollection;
class Rva001DA2D5;
struct Rva002D752DNode;
enum ObjectID { INVALID_ID = 0 };

struct XferVersion
{
	unsigned char m_first;
	unsigned char m_version;
	unsigned char m_pad[2];
};

#include "../Common/System/XferVectorTypes.h"
#include "../../Include/Common/BfmeXfer.h"

#include "../../Include/Common/XferException.h"

void XferDrawableID(Xfer *xfer, int *id);
void XferObjectID(Xfer *xfer, ObjectID *id);
void XferStealthLookType(Xfer *xfer, int *value);
void XferWaypointID(Xfer *xfer, int *id);
Xfer *Rva003062FEXfer(Xfer *xfer, float *value);
void Rva0030612AXfer(Xfer *xfer, float *value);

#include "../../Include/Common/BitFlagsTemplate.h"
class ModelConditionFlags : public BitFlags<591> {};

#include "../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"
#include "../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"

// Retail references every icon-name entry at 0x009BB660.
extern const char *TheDrawableIconNames[14];
// Retail 0x0027015F: Zero Hour's static drawableIconIndexToName; xfer
// inlines it and cl still emits this register-convention copy (index in EAX).
static const char *drawableIconIndexToName(int iconIndex)
{
	return TheDrawableIconNames[iconIndex];
}
static __forceinline int drawableIconIndex(const char *name)
{
	for (int i = 0; i < 14; ++i)
		if (!_strcmpi(TheDrawableIconNames[i], name))
			return i;
	return -1;
}

class Anim2DTemplate
{
public:
	const AsciiString &getName() const { return m_name; }
	unsigned char m_pad00[8];
	AsciiString m_name;					// +0x08
};

class Anim2D
{
public:
	Anim2D(Anim2DTemplate *animTemplate, Anim2DCollection *collectionSystem);
	Anim2DTemplate *getAnimTemplate() const { return m_template; }
	void *m_vtbl;
	unsigned short m_currentFrame;
	unsigned int m_lastUpdateFrame;
	Anim2DTemplate *m_template;				// +0x0C
	unsigned char m_pad10[0x34 - 0x10];
};
extern Anim2DCollection *TheAnim2DCollection;

class Rva002D752D
{
public:
	Rva002D752DNode *rva002D752D(const StringBase<char> &name);
};

class Rva00270025
{
public:
	void rva00270041();
	void *m_vtbl;
	Anim2D *m_icons[14];					// +0x04
	unsigned int m_keepTillFrame[14];			// +0x3C
};
class Rva00270BA8
{
public:
	Rva00270025 *rva00270BA8();
	char m_pad00[0x354];
private:
	Rva00270025 *m_354; // +0x354
};

class Rva00271826
{
public:
	__declspec(nothrow) Rva00271826();
	unsigned char m_data[0x50];
};

class DrawableLocoInfo
{
public:
	DrawableLocoInfo();
	int m_00;
	float m_04, m_08, m_0c, m_10, m_14, m_18, m_1c, m_20, m_24, m_28, m_2c, m_30;
	float m_34, m_38;
	float m_3c, m_40, m_44, m_48, m_4c;
	int m_50, m_54;
};



#include "../../../Libraries/Source/WWVegas/WWLib/OpaqueRefCounted.h"
class Rva0036CA00Str
{
public:
	__declspec(nothrow) Rva0036CA00Str() : item(0) {}
	__declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str &);
	~Rva0036CA00Str() { if (item) item->Release_Ref(); }
	OpaqueRefCounted *item;
};
struct Rva0010F149Handle
{
	__declspec(nothrow) Rva0010F149Handle(const Rva0010F149Handle &r);
	~Rva0010F149Handle() { if (referent) referent->Release_Ref(); }
	OpaqueRefCounted *referent;
};
#include "../../Include/Common/OpaqueRefElement4.h"
class Rva000A8C9B
{
public:
	void rva000A8CE5(OpaqueRefCounted *item);
	void clear();
	OpaqueRefCounted *m_ptr; // +0x00
};
Rva0036CA00Str Rva00274DD4();

class Rva004333C0 { public: Rva004333C0(int); Rva004333C0(const Rva001DA2D5 &base, int); unsigned char m_data[0xD0]; };
class DynamicAudioEventInfo { public: void xferNoName(Xfer *xfer); };
#include "../../Include/Common/Rva000B56F0Object.h"

class AudioManager
{
public:
#define SLOT4(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3();
#define SLOT16(p) SLOT4(p##0) SLOT4(p##1) SLOT4(p##2) SLOT4(p##3)
	SLOT16(a) SLOT16(b) SLOT16(c) SLOT16(d)
	SLOT4(e0) SLOT4(e1)
	virtual void slot72(); virtual void slot73();
	virtual void addAudioEventInfo(OpaqueRefCounted *info);	// +0x128
	virtual Rva0036CA00Str findAudioEventInfo(const AsciiString &name);	// +0x12C
	SLOT4(f0) SLOT4(f1) SLOT4(f2)
	virtual void slot88(Xfer *xfer, void *value);		// +0x160
#undef SLOT16
#undef SLOT4
};
extern AudioManager *TheAudio;

#include "../../Include/GameLogic/Waypoint.h"
#include "../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;

#include "../../Include/GameLogic/AIPathfind.h"
class AI;
extern AI *TheAI;
struct AIPathfinderView
{
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder;				// +0x10
};

struct DrawableObjectTemplateView
{
	unsigned char m_pad000[0x11A];
	unsigned char m_kindOf11A;				// +0x11A
};
class Object
{
public:
	ObjectID getID() const { return m_id; }
	void *m_vtbl;
	DrawableObjectTemplateView *m_template;			// +0x04
	unsigned char m_pad08[0x74 - 0x08];
	ObjectID m_id;						// +0x74
};

#include "../../Include/GameClient/Rva002716Holder.h"
#include "../../Include/GameClient/Rva00279354Host.h"
class Rva0027974B
{
public:
	void rva0027974B();
	char m_pad00[0x10C];
	Rva0036CA00Str held; // +0x10C
};

#include "../Common/Thing/thing.h"

class Drawable : public Thing, public Snapshot
{
public:
	void setID(void *id);	// 0x00271058
	virtual ~Drawable();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void DoXfer(Xfer *xfer);

	const Matrix3D *getTransformMatrix() const;
	void rva00272870(int decal);
	void xferDrawableModules(Xfer *xfer);
	void rva002781DA(Rva0010F149Handle info);
	void rva002791E7(const ModelConditionFlags &flags, unsigned int a, unsigned int b);
	bool rva00272C1E();
	Rva00270025 *getIconInfo() { return ((Rva00270BA8 *)this)->rva00270BA8(); }

	Rva00271826 *m_colorTintEnvelope;			// +0x64
	Rva00271826 *m_selectionFlashEnvelope;			// +0x68
	unsigned char m_tintColor[0xC];				// +0x6C
	unsigned int m_78, m_7c, m_80;				// +0x78
	float m_84, m_88;					// +0x84
	unsigned char m_pad8c[4];
	float m_90[3];						// +0x90
	float m_9c[3];						// +0x9C
	unsigned int m_terrainDecalType;			// +0xA8
	float m_ac, m_b0, m_b4, m_b8, m_bc, m_c0, m_c4, m_c8, m_cc;	// +0xAC
	float m_d0;						// +0xD0
	unsigned int m_d4;					// +0xD4
	float m_d8, m_dc, m_e0;					// +0xD8
	bool m_e4;						// +0xE4
	int m_e8[2];						// +0xE8 ICoord2D
	int m_f0;						// +0xF0
	float m_f4, m_f8;					// +0xF4
	Object *m_object;					// +0xFC
	int m_id;						// +0x100
	unsigned char m_pad104[0x10C - 0x104];
	Rva0036CA00Str m_customSoundAmbientInfo;		// +0x10C
	Rva0036CA00Str m_baseSoundAmbientInfo;			// +0x110
	unsigned int m_status, m_118, m_11c;			// +0x114
	unsigned char m_pad120[0x128 - 0x120];
	unsigned char m_128[4];					// +0x128
	unsigned int m_12c, m_130;				// +0x12C
	unsigned char m_pad134[0x138 - 0x134];
	unsigned int m_138;					// +0x138
	DrawableLocoInfo *m_locoInfo;				// +0x13C
	float m_140;						// +0x140
	int m_ambientSound144;					// +0x144
	int m_ambientSound148;					// +0x148
	unsigned char m_pad14c[0x164 - 0x14C];
	int m_stealthLook;					// +0x164
	int m_168, m_16c;					// +0x168
	float m_170[12];					// +0x170
	float m_1a0[12];					// +0x1A0
	float m_1d0[12];					// +0x1D0
	float m_instanceScale;					// +0x200
	unsigned char m_pad204[0x248 - 0x204];
	ObjectID m_shroudStatusObjectID;			// +0x248
	unsigned char m_pad24c[0x258 - 0x24C];
	ModelConditionFlags m_conditionState;			// +0x258
	ModelConditionFlags m_pendingClear;			// +0x2A4
	ModelConditionFlags m_pendingSet;			// +0x2F0
	float m_33c;						// +0x33C
	unsigned char m_pad340[0x348 - 0x340];
	AsciiString m_348;					// +0x348
	AsciiString m_34c;					// +0x34C
	unsigned int m_350;					// +0x350
	void *m_iconInfo;					// +0x354
	float m_358;						// +0x358
	int m_35c;						// +0x35C
	unsigned char m_360[4];					// +0x360
	int m_364, m_368;					// +0x364
	_STL::vector<const ModuleData *> m_waypoints;		// +0x36C
	unsigned int m_frame;					// +0x378
	unsigned int m_37c, m_380, m_384, m_388;		// +0x37C
	unsigned char m_pad38c[0x3A4 - 0x38C];
	unsigned int m_3a4;					// +0x3A4
	bool m_3a8, m_3a9, m_3aa;				// +0x3A8
	unsigned char m_pad3ab[0x43D - 0x3AB];
	bool m_43d, m_43e, m_43f, m_440, m_441, m_442;		// +0x43D
	bool m_isModelDirty;					// +0x443
	bool m_444, m_445, m_446, m_447, m_448, m_449, m_44a, m_44b;	// +0x444
	unsigned char m_pad44c[0x450 - 0x44C];
	BuffManager *m_buffManager;				// +0x450
	int m_indicatorColor;					// +0x454
	unsigned char m_pad458[0x460 - 0x458];
	unsigned char m_460[0x10];				// +0x460
};

void Drawable::DoXfer(Xfer *xfer)
{
	XferVersion version;
	version.m_first = 1;
	version.m_version = 11;
	*xfer == reinterpret_cast<Xfer::Version &>(version);

	int id = m_id;
	XferDrawableID(xfer, &id);
	setID((void *)id);

	m_conditionState.xfer(xfer);
	m_pendingClear.xfer(xfer);
	m_pendingSet.xfer(xfer);

	Matrix3D mtx = *getTransformMatrix();
	Rva003062FEXfer(xfer, (float *)&mtx);
	setTransformMatrix(&mtx);

	bool hasColorTint = m_colorTintEnvelope != 0;
	*xfer == hasColorTint;
	if (hasColorTint)
	{
		if (!m_colorTintEnvelope)
			m_colorTintEnvelope = new Rva00271826;
		*xfer == reinterpret_cast<Snapshot &>(*(m_colorTintEnvelope));
	}

	bool hasSelectionFlash = m_selectionFlashEnvelope != 0;
	*xfer == hasSelectionFlash;
	if (hasSelectionFlash)
	{
		if (!m_selectionFlashEnvelope)
			m_selectionFlashEnvelope = new Rva00271826;
		*xfer == reinterpret_cast<Snapshot &>(*(m_selectionFlashEnvelope));
	}

	unsigned int decal = m_terrainDecalType;
	*xfer == decal;
	if (xfer->IsLoading())
		rva00272870(decal);

	*xfer == m_ac;
	*xfer == m_b0;
	*xfer == m_b4;
	*xfer == m_b8;
	*xfer == m_bc;
	*xfer == m_c0;
	*xfer == m_c4;
	*xfer == m_c8;
	*xfer == m_cc;
	*xfer == m_d4;
	*xfer == m_d0;
	*xfer == m_440;
	if (version.m_version >= 9)
		*xfer == m_388;
	else
		m_388 = 0;
	*xfer == m_d8;
	*xfer == m_dc;
	*xfer == m_e0;
	if (version.m_version < 10)
	{
		unsigned int obsolete = 0;
		*xfer == obsolete;
	}
	*xfer == m_384;

	ObjectID objectID = m_object ? m_object->getID() : INVALID_ID;
	XferObjectID(xfer, &objectID);
	if (xfer->IsLoading())
	{
		if (m_object)
		{
			if (objectID != m_object->getID())
				throw XferException(5, 0);
		}
		else if (objectID != INVALID_ID)
			throw XferException(5, 0);
	}

	*xfer == m_status;
	*xfer == m_118;
	*xfer == m_11c;
	xfer->XferRawBytes(m_128, 4);
	*xfer == m_12c;
	*xfer == m_130;
	*xfer == m_140;

	bool hasLocoInfo = m_locoInfo != 0;
	*xfer == hasLocoInfo;
	if (hasLocoInfo)
	{
		if (xfer->IsLoading() && !m_locoInfo)
			m_locoInfo = new DrawableLocoInfo;
		*xfer == m_locoInfo->m_04;
		*xfer == m_locoInfo->m_08;
		*xfer == m_locoInfo->m_0c;
		*xfer == m_locoInfo->m_10;
		*xfer == m_locoInfo->m_14;
		*xfer == m_locoInfo->m_18;
		*xfer == m_locoInfo->m_1c;
		*xfer == m_locoInfo->m_20;
		*xfer == m_locoInfo->m_24;
		*xfer == m_locoInfo->m_28;
		*xfer == m_locoInfo->m_2c;
		*xfer == m_locoInfo->m_30;
		*xfer == m_locoInfo->m_3c;
		*xfer == m_locoInfo->m_40;
		*xfer == m_locoInfo->m_44;
		*xfer == m_locoInfo->m_48;
		*xfer == m_locoInfo->m_4c;
		*xfer == m_locoInfo->m_50;
		*xfer == m_locoInfo->m_54;
	}

	if (version.m_version < 4)
		xferDrawableModules(xfer);

	XferStealthLookType(xfer, &m_stealthLook);
	*xfer == m_168;
	*xfer == m_16c;
	*xfer == m_43d;
	*xfer == m_43e;
	*xfer == m_358;
	*xfer == m_43f;

	Rva003062FEXfer(xfer, m_1a0);
	Rva003062FEXfer(xfer, m_170);
	Rva003062FEXfer(xfer, m_1d0);
	*xfer == m_frame;
	*xfer == m_instanceScale;
	XferObjectID(xfer, &m_shroudStatusObjectID);
	*xfer == m_350;

	unsigned char iconCount = 0;
	if (m_iconInfo)
	{
		for (unsigned char i = 0; i < 14; ++i)
			if (getIconInfo()->m_icons[i])
				++iconCount;
	}
	*xfer == iconCount;

	AsciiString iconIndexName;
	AsciiString iconTemplateName;
	unsigned int keepTillFrame;
	if (xfer->IsStoring())
	{
		for (unsigned char i = 0; i < 14; ++i)
		{
			if (!m_iconInfo || !getIconInfo()->m_icons[i])
				continue;
			iconIndexName = drawableIconIndexToName(i);
			*xfer == iconIndexName;
			keepTillFrame = getIconInfo()->m_keepTillFrame[i];
			*xfer == keepTillFrame;
			iconTemplateName = getIconInfo()->m_icons[i]->getAnimTemplate()->getName();
			*xfer == iconTemplateName;
			*xfer == reinterpret_cast<Snapshot &>(*(getIconInfo()->m_icons[i]));
		}
	}
	else
	{
		if (m_iconInfo)
			getIconInfo()->rva00270041();
		for (int i = 0; i < iconCount; ++i)
		{
			*xfer == iconIndexName;
			int index = drawableIconIndex(iconIndexName.str());
			*xfer == keepTillFrame;
			getIconInfo()->m_keepTillFrame[index] = keepTillFrame;
			*xfer == iconTemplateName;
			Anim2DTemplate *animTemplate = (Anim2DTemplate *)((Rva002D752D *)TheAnim2DCollection)->rva002D752D(*(const StringBase<char> *)&iconTemplateName);
			if (!animTemplate)
				throw XferException(5, 0);
			getIconInfo()->m_icons[index] = new Anim2D(animTemplate, TheAnim2DCollection);
			*xfer == reinterpret_cast<Snapshot &>(*(getIconInfo()->m_icons[index]));
		}
	}

	if (xfer->IsLoading())
	{
		m_stealthLook = 0;
		if (m_43d || m_43e)
			((Rva002716Holder *)this)->rva00271547();
	}
	if (!xfer->IsStoring())
		m_isModelDirty = true;

	*xfer == m_447;
	*xfer == m_448;
	*xfer == m_449;
	*xfer == m_44a;
	*xfer == m_44b;

	bool customized = m_customSoundAmbientInfo.item != 0;
	*xfer == customized;
	if (customized)
	{
		bool silent = m_customSoundAmbientInfo.item == Rva00274DD4().item;
		*xfer == silent;
		if (xfer->IsLoading())
		{
			if (silent)
				((Rva0027974B *)this)->rva0027974B();
			else
			{
				AsciiString baseInfoName;
				*xfer == baseInfoName;
				Rva0036CA00Str baseInfo = TheAudio->findAudioEventInfo(baseInfoName);
				Rva0036CA00Str info;
				bool success = true;
				if (!baseInfo.item)
				{
					((Rva000A8C9B *)&info)->rva000A8CE5((OpaqueRefCounted *)new Rva004333C0(0));
					success = false;
				}
				else
					((Rva000A8C9B *)&info)->rva000A8CE5((OpaqueRefCounted *)new Rva004333C0(*(const Rva001DA2D5 *)baseInfo.item, 0));
				rva002781DA(*(Rva0010F149Handle *)&info);
				((DynamicAudioEventInfo *)info.item)->xferNoName(xfer);
				if (success)
				{
					TheAudio->addAudioEventInfo(info.item);
					((Rva00279354Host *)this)->rva00279354(false);
					reinterpret_cast<OpaqueRefElement4 &>(m_customSoundAmbientInfo) = reinterpret_cast<const OpaqueRefElement4 &>(info);
				}
			}
		}
		else if (!silent)
		{
			AsciiString baseInfoName(*(const AsciiString *)((Rva000B56F0Object *)m_customSoundAmbientInfo.item)->selectStorage());
			*xfer == baseInfoName;
			((DynamicAudioEventInfo *)m_customSoundAmbientInfo.item)->xferNoName(xfer);
		}
	}

	if (TheAudio)
	{
		TheAudio->slot88(xfer, &m_ambientSound144);
		TheAudio->slot88(xfer, &m_ambientSound148);
	}

	if (version.m_version >= 6)
	{
		if (xfer->IsLoading())
		{
			AsciiString baseSoundName;
			*xfer == baseSoundName;
			if (TheAudio)
				reinterpret_cast<OpaqueRefElement4 &>(m_baseSoundAmbientInfo) = reinterpret_cast<const OpaqueRefElement4 &>(TheAudio->findAudioEventInfo(baseSoundName));
			else
				((Rva000A8C9B *)&m_baseSoundAmbientInfo)->clear();
		}
		else
		{
			AsciiString baseSoundName;
			if (m_baseSoundAmbientInfo.item)
				baseSoundName = *(const AsciiString *)((const char *)m_baseSoundAmbientInfo.item + 8);
			*xfer == baseSoundName;
		}
	}

	*xfer == m_364;
	*xfer == m_368;
	*xfer == m_37c;
	*xfer == m_380;

	if (xfer->IsLoading())
	{
		unsigned int count;
		*xfer == count;
		while (count--)
		{
			int waypointID;
			XferWaypointID(xfer, &waypointID);
			const ModuleData *waypoint = (const ModuleData *)TheTerrainLogic->getWaypointByID(waypointID);
			m_waypoints.push_back(waypoint);
		}
	}
	else
	{
		unsigned int count = m_waypoints.size();
		*xfer == count;
		for (_STL::vector<const ModuleData *>::iterator it = m_waypoints.begin(); it != m_waypoints.end(); ++it)
		{
			int waypointID = ((const Waypoint *)*it)->getID();
			XferWaypointID(xfer, &waypointID);
		}
	}

	*xfer == reinterpret_cast<RGBColor &>(*(m_tintColor));
	*xfer == m_78;
	*xfer == m_7c;
	*xfer == m_80;
	*xfer == m_84;
	*xfer == m_88;
	*xfer == m_3a4;
	*xfer == m_3a8;
	*xfer == m_3a9;
	*xfer == m_indicatorColor;
	*xfer == m_348;
	*xfer == m_34c;
	*xfer == m_3aa;
	*xfer == m_441;
	*xfer == m_444;
	Rva0030612AXfer(xfer, m_90);
	Rva0030612AXfer(xfer, m_9c);
	*xfer == m_e4;
	*xfer == reinterpret_cast<ICoord2D &>(*(m_e8));
	*xfer == m_f0;
	*xfer == m_f4;
	*xfer == m_f8;
	*xfer == m_138;
	*xfer == m_33c;
	*xfer == m_35c;
	*xfer == reinterpret_cast<IRegion2D &>(*(m_460));
	xfer->XferRawBytes(m_360, 4);

	if (xfer->IsLoading())
		rva002791E7(m_conditionState, 1, 1);

	if (version.m_version >= 4)
		xferDrawableModules(xfer);

	if (version.m_version >= 5)
		*xfer == m_445;
	else if (xfer->IsLoading())
		m_445 = false;

	if (version.m_version >= 8)
		*xfer == m_446;
	else if (xfer->IsLoading())
		m_446 = false;

	if (xfer->IsCRC())
		return;

	if (version.m_version >= 2)
	{
		bool hasBuffManager = m_buffManager != 0;
		*xfer == hasBuffManager;
		if (hasBuffManager)
		{
			if (xfer->IsLoading())
				m_buffManager = new BuffManager((int)this);
			m_buffManager->DoXfer(xfer);
		}
	}
	if (version.m_version >= 3)
		*xfer == m_442;

	if (xfer->IsLoading() && m_object && (m_object->m_template->m_kindOf11A & 0x40) && rva00272C1E())
	{
		((AIPathfinderView *)TheAI)->m_pathfinder->RemoveObjectFromPathfindMap(m_object);
		((AIPathfinderView *)TheAI)->m_pathfinder->AddObjectToPathfindMap(m_object);
	}

	if (version.m_version >= 7 && version.m_version < 11 && xfer->IsLoading())
	{
		float obsoleteReal;
		*xfer == obsoleteReal;
		*xfer == obsoleteReal;
		*xfer == obsoleteReal;
		*xfer == obsoleteReal;
		unsigned int obsoleteUInt;
		*xfer == obsoleteUInt;
	}
}
