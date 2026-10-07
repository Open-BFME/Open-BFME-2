// cl: /O1 /arch:SSE /G7 /MD /EHs-c- /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
// ?rva000B7C24@W3DModelDraw@@QAEXXZ @0x000B7C24 615B.
// Donor: Open-BFME-1 game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawAttachableSubModels.cpp.
// Donor carries attachable-submodel semantics and owner; target independently
// establishes render pointer +50 condition set +17c 19-word masks and 0xb4 records.
// Target slots are one higher than donor for attachment/bone/collision; debug
// stream takes three zero arguments. Seed comes from Drawable +364.
#include <bitset>
#include <vector>

#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;

class WeaponTemplateSetHead
{
public:
    WeaponTemplateSetHead(const WeaponTemplateSetHead &);
    void rva000B3ED3(const WeaponTemplateSetHead &);
    void flip() { for (unsigned i = 0; i < 19; ++i) m_data[i] = ~m_data[i]; }
private:
    unsigned int m_data[19];
};
bool Rva00045473Equal(const void *, const void *);
typedef WeaponTemplateSetHead ModelConditionFlags;

struct Vector3
{
	float X;
	float Y;
	float Z;
};

class RenderObjClass
{
public:
	virtual void Delete_This();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05();
	virtual const char *Get_Name() const;
	virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20(); virtual void slot21();
	virtual void slot22(); virtual void slot23(); virtual void slot24(); virtual void slot25();
	virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33();
	virtual void slot34(); virtual void slot35(); virtual void slot36();
	virtual void targetExtra37();
	virtual int Add_Sub_Object_To_Bone(RenderObjClass *subobj, int bone_index, const Vector3 *offset);
	virtual void slot38(); virtual void slot39();
	virtual void _bfme_ro_v40();
	virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48();
	virtual int Get_Bone_Index(const char *bonename);
	virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
	virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72(); virtual void slot73(); virtual void slot74(); virtual void slot75();
	virtual void slot76(); virtual void slot77(); virtual void slot78(); virtual void slot79();
	virtual void slot80(); virtual void slot81(); virtual void slot82(); virtual void slot83();
	virtual void slot84(); virtual void slot85(); virtual void slot86(); virtual void slot87();
	virtual void slot88(); virtual void slot89(); virtual void slot90(); virtual void slot91();
	virtual void slot92(); virtual void slot93(); virtual void slot94(); virtual void slot95();
	virtual void slot96(); virtual void slot97(); virtual void slot98(); virtual void slot99();
	virtual void slot100(); virtual void slot101(); virtual void slot102(); virtual void slot103();
	virtual void slot104(); virtual void slot105(); virtual void slot106(); virtual void slot107();
	virtual void slot108(); virtual void slot109(); virtual void slot110(); virtual void slot111();
	virtual void slot112(); virtual void slot113(); virtual void slot114(); virtual void slot115();
	virtual void slot116(); virtual void slot117(); virtual void slot118(); virtual void slot119();
	virtual void Set_Collision_Type(int type, bool recurse);

	void Release_Ref()
	{
		NumRefs--;
		if (NumRefs == 0)
			Delete_This();
	}

	int NumRefs;
};

RenderObjClass *Create_Render_Obj(const char *name);

class BfmeAwakenLog
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual BfmeAwakenLog *slot38(const char *text);
	virtual void slot3C(); virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual BfmeAwakenLog *slot4C(int value);
};

class Debug
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60();
	virtual void slot64(); virtual void slot68();
	virtual BfmeAwakenLog *slot6C(int first, int second, int third);
};

extern Debug *theDebug;
bool bfmeRva000387C0();
void _bfme_debugRecordCallsite(int kind);

struct AttachableSubModelChoice00769720
{
	AsciiString m_modelName;
	UnsignedInt m_percent;
};

struct AttachableSubModel00769720
{
	AsciiString m_boneName;
	Vector3 m_offset;
	_STL::vector<AttachableSubModelChoice00769720> m_models;
	ModelConditionFlags m_conditionMask;
	mutable ModelConditionFlags m_conditionValue;
};

class Drawable
{
public:
	unsigned char m_pad000[0x364];
	UnsignedInt m_dword364;
};

class W3DModelDrawModuleData
{
public:
	unsigned char m_pad00[0x08];
	_STL::vector<AttachableSubModel00769720> m_attachableSubModels;
};

class W3DModelDraw
{
public:
	void rva000B7C24();

private:
	unsigned char m_pad00[0x04];
	const W3DModelDrawModuleData *m_moduleData;
	Drawable *m_drawable;
	unsigned char m_pad0C[0x50 - 0x0C];
	RenderObjClass *m_renderObject;
	unsigned char m_pad38[0x17c - 0x54];
	ModelConditionFlags m_conditionFlags17c;
};

void W3DModelDraw::rva000B7C24()
{
	if (m_moduleData->m_attachableSubModels.empty() || m_renderObject == 0)
		return;

	m_renderObject->_bfme_ro_v40();

	const Drawable *draw = m_drawable;
	const W3DModelDrawModuleData *d = m_moduleData;
	for (_STL::vector<AttachableSubModel00769720>::const_iterator it = d->m_attachableSubModels.begin();
		it != d->m_attachableSubModels.end(); ++it)
	{
		ModelConditionFlags tmp = m_conditionFlags17c;
		tmp.rva000B3ED3(it->m_conditionMask);
		if (!Rva00045473Equal(&tmp, &it->m_conditionValue))
			continue;

		Int bone = m_renderObject->Get_Bone_Index(it->m_boneName.str());
		if (bone == 0)
		{
			if (bfmeRva000387C0())
			{
				_bfme_debugRecordCallsite(1);
				theDebug->slot60();
				theDebug->slot6C(0, 0, 0)
					->slot38("Could not find bone '")
					->slot38(it->m_boneName.str())
					->slot38("' for attachable submodel in ")
					->slot38(m_renderObject->Get_Name())
					->slot4C(2);
			}
			it->m_conditionValue.flip();
			continue;
		}

		UnsignedInt seed = draw->m_dword364;
		seed = seed * 0x41c64e6d + 0x3039;
		seed = seed * 0x41c64e6d + 0x3039;
		seed = seed * 0x41c64e6d + 0x3039;
		UnsignedInt roll = (seed >> 10) % 100;

		_STL::vector<AttachableSubModelChoice00769720>::const_iterator choice = it->m_models.begin();
		for (; choice != it->m_models.end(); ++choice)
		{
			if (roll < choice->m_percent)
				break;
			roll -= choice->m_percent;
		}

		RenderObjClass *robj = Create_Render_Obj(choice->m_modelName.str());
		if (robj == 0)
		{
			if (bfmeRva000387C0())
			{
				_bfme_debugRecordCallsite(1);
				theDebug->slot60();
				theDebug->slot6C(0, 0, 0)
					->slot38("Could not find model '")
					->slot38(choice->m_modelName.str())
					->slot38("' for attachable submodel in ")
					->slot38(m_renderObject->Get_Name())
					->slot4C(2);
			}
			it->m_conditionValue.flip();
			continue;
		}

		robj->Set_Collision_Type(0, true);
		m_renderObject->Add_Sub_Object_To_Bone(robj, bone, &it->m_offset);
		robj->Release_Ref();
	}
}
