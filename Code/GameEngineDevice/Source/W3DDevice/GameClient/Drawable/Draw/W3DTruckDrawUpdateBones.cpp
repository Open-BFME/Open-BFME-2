// cl: /Ireference/shims/bfme2_ascii /GX /MD /DNDEBUG
//
// W3DTruckDraw::updateBones, retail 0x000CB8CB, 3766 bytes, ending where the
// matched setHidden at 0x000CC781 begins.
//
// Donor: Open-BFME-1 game/GameEngineDevice/Source/W3DDevice/GameClient/
// Drawable/Draw/W3DTruckDrawUpdateBones.cpp (matched there at 0x00780170).
// Carried from the donor: the method identity, the per-pair bone lookups,
// the debug report sequence and the reversed condition on the secondary and
// cab reports (they fire for a nonzero bone index).
// Target facts read from this body: the eighteen bone-name strings at module
// data +0x194..+0x1D8, the bone indices at +0x320..+0x368, m_prevNumBones at
// +0x370 and m_prevRenderObj at +0x484; getRenderObject at vtable +0xC4;
// RenderObjClass Get_Name +0x18, Get_Num_Bones +0xC0, Get_Bone_Index +0xC8;
// StringBase<char>::isEmpty called out of line; the report goes through
// theDebug's +0x60 / +0x6C(0,0,0) slots and the message's +0x38 / +0x4C(2)
// slots, with a 512-byte Debug::Format temporary. The message strings are
// retail's, including the duplicated "rear-left" texts.
//
// The module data is read straight from the member, not through the donor's
// inline getW3DTruckDrawModuleData(): with the accessor MSVC folds each
// name's offset into a lea for the isEmpty call, and the body grows by four
// bytes in each of blocks two to nine. Read directly, the offset is loaded
// into ebx ahead of isEmpty and reused for the str() reads, as in retail.

#include "ascii_string.h"

class RenderObjClass
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14();
	virtual const char *Get_Name() const;
	virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6C();
	virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7C();
	virtual void slot80(); virtual void slot84(); virtual void slot88(); virtual void slot8C();
	virtual void slot90(); virtual void slot94(); virtual void slot98(); virtual void slot9C();
	virtual void slotA0(); virtual void slotA4(); virtual void slotA8(); virtual void slotAC();
	virtual void slotB0(); virtual void slotB4(); virtual void slotB8(); virtual void slotBC();
	virtual int Get_Num_Bones();
	virtual void slotC4();
	virtual int Get_Bone_Index(const char *bonename) const;
};

class Debug
{
public:
	class Format
	{
	public:
		Format(const char *format, ...);
	private:
		char m_text[0x200];
	};
};

class TruckBoneReport
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual TruckBoneReport *setText(const char *text);
	virtual void slot3C(); virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual void show(int mode);
	TruckBoneReport &operator<<(const Debug::Format &value) { setText((const char *)&value); return *this; }
};

class TruckBoneDebug
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void beginReport();
	virtual void slot64(); virtual void slot68();
	virtual TruckBoneReport *getReport(int, int, int);
};

extern Debug *theDebug;
#define TheTruckBoneDebug (*(TruckBoneDebug **)&theDebug)
bool bfmeRva000387C0();
void _bfme_debugRecordCallsite(int kind);

static __forceinline void reportMissingBone(const char *format, const char *name, RenderObjClass *model)
{
	TruckBoneReport *out = TheTruckBoneDebug->getReport(0, 0, 0);
	(*out << Debug::Format(format, name, model->Get_Name())).show(2);
}
#define REPORT_MISSING(format, name, model) do { RenderObjClass *object = model; const char *boneName = name; reportMissingBone(format, boneName, object); } while (0)
#define TRUCK_ASSERT(condition, message) do { \
	if (!(condition) && bfmeRva000387C0()) { \
		_bfme_debugRecordCallsite(1); \
		TheTruckBoneDebug->beginReport(); \
		REPORT_MISSING message; \
	} \
} while (0)

static inline bool nameEmpty(const AsciiString &name)
{
	return ((const StringBase<char> *)&name)->isEmpty();
}

class W3DTruckDrawModuleData
{
public:
	char m_pad[0x194];
	AsciiString m_frontLeftTireBoneName;
	AsciiString m_frontRightTireBoneName;
	AsciiString m_rearLeftTireBoneName;
	AsciiString m_rearRightTireBoneName;
	AsciiString m_midFrontLeftTireBoneName;
	AsciiString m_midFrontRightTireBoneName;
	AsciiString m_midRearLeftTireBoneName;
	AsciiString m_midRearRightTireBoneName;
	AsciiString m_midMidLeftTireBoneName;
	AsciiString m_midMidRightTireBoneName;
	AsciiString m_secondaryFrontLeftTireBoneName;
	AsciiString m_secondaryFrontRightTireBoneName;
	AsciiString m_secondaryRearLeftTireBoneName;
	AsciiString m_secondaryRearRightTireBoneName;
	AsciiString m_secondaryMidMidLeftTireBoneName;
	AsciiString m_secondaryMidMidRightTireBoneName;
	AsciiString m_cabBoneName;
	AsciiString m_trailerBoneName;
};

class W3DTruckDraw
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6C();
	virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7C();
	virtual void slot80(); virtual void slot84(); virtual void slot88(); virtual void slot8C();
	virtual void slot90(); virtual void slot94(); virtual void slot98(); virtual void slot9C();
	virtual void slotA0(); virtual void slotA4(); virtual void slotA8(); virtual void slotAC();
	virtual void slotB0(); virtual void slotB4(); virtual void slotB8(); virtual void slotBC();
	virtual void slotC0();
	virtual RenderObjClass *getRenderObject() const;


protected:
	void updateBones();

private:
	const W3DTruckDrawModuleData *m_moduleData;
	char m_pad008[0x320 - 0x08];
	int m_frontLeftTireBone;
	int m_frontRightTireBone;
	int m_rearLeftTireBone;
	int m_rearRightTireBone;
	int m_midFrontLeftTireBone;
	int m_midFrontRightTireBone;
	int m_midRearLeftTireBone;
	int m_midRearRightTireBone;
	int m_midMidLeftTireBone;
	int m_midMidRightTireBone;
	int m_secondaryFrontLeftTireBone;
	int m_secondaryFrontRightTireBone;
	int m_secondaryRearLeftTireBone;
	int m_secondaryRearRightTireBone;
	int m_secondaryMidMidLeftTireBone;
	int m_secondaryMidMidRightTireBone;
	int m_cabBone;
	int m_pad364;
	int m_trailerBone;
	int m_pad36C;
	int m_prevNumBones;
	char m_pad374[0x484 - 0x374];
	RenderObjClass *m_prevRenderObj;
};

void W3DTruckDraw::updateBones()
{
	if (m_moduleData) {
		if (!nameEmpty(m_moduleData->m_frontLeftTireBoneName)) {
			m_frontLeftTireBone = getRenderObject()->Get_Bone_Index(m_moduleData->m_frontLeftTireBoneName.str());
			TRUCK_ASSERT(m_frontLeftTireBone, ("Missing front-left tire bone %s in model %s\n", m_moduleData->m_frontLeftTireBoneName.str(), getRenderObject()));
			m_frontRightTireBone = getRenderObject()->Get_Bone_Index(m_moduleData->m_frontRightTireBoneName.str());
			TRUCK_ASSERT(m_frontRightTireBone, ("Missing front-right tire bone %s in model %s\n", m_moduleData->m_frontRightTireBoneName.str(), getRenderObject()));
			if (!m_frontRightTireBone) m_frontLeftTireBone = 0;
		}
		if (!nameEmpty(m_moduleData->m_rearLeftTireBoneName)) {
			m_rearLeftTireBone = getRenderObject()->Get_Bone_Index(m_moduleData->m_rearLeftTireBoneName.str());
			TRUCK_ASSERT(m_rearLeftTireBone, ("Missing rear-left tire bone %s in model %s\n", m_moduleData->m_rearLeftTireBoneName.str(), getRenderObject()));
			m_rearRightTireBone = getRenderObject()->Get_Bone_Index(m_moduleData->m_rearRightTireBoneName.str());
			TRUCK_ASSERT(m_rearRightTireBone, ("Missing rear-left tire bone %s in model %s\n", m_moduleData->m_rearRightTireBoneName.str(), getRenderObject()));
			if (!m_rearRightTireBone) m_rearLeftTireBone = 0;
		}
		if (!nameEmpty(m_moduleData->m_midFrontLeftTireBoneName)) {
			m_midFrontLeftTireBone = getRenderObject()->Get_Bone_Index(m_moduleData->m_midFrontLeftTireBoneName.str());
			TRUCK_ASSERT(m_midFrontLeftTireBone, ("Missing mid-front-left tire bone %s in model %s\n", m_moduleData->m_midFrontLeftTireBoneName.str(), getRenderObject()));
			m_midFrontRightTireBone = getRenderObject()->Get_Bone_Index(m_moduleData->m_midFrontRightTireBoneName.str());
			TRUCK_ASSERT(m_midFrontRightTireBone, ("Missing mid-front-right tire bone %s in model %s\n", m_moduleData->m_midFrontRightTireBoneName.str(), getRenderObject()));
			if (!m_midFrontRightTireBone) m_midFrontLeftTireBone = 0;
		}
		if (!nameEmpty(m_moduleData->m_midRearLeftTireBoneName)) {
			m_midRearLeftTireBone = getRenderObject()->Get_Bone_Index(m_moduleData->m_midRearLeftTireBoneName.str());
			TRUCK_ASSERT(m_midRearLeftTireBone, ("Missing mid-rear-left tire bone %s in model %s\n", m_moduleData->m_midRearLeftTireBoneName.str(), getRenderObject()));
			m_midRearRightTireBone = getRenderObject()->Get_Bone_Index(m_moduleData->m_midRearRightTireBoneName.str());
			TRUCK_ASSERT(m_midRearRightTireBone, ("Missing mid-rear-right tire bone %s in model %s\n", m_moduleData->m_midRearRightTireBoneName.str(), getRenderObject()));
			if (!m_midRearRightTireBone) m_midRearLeftTireBone = 0;
		}
		if (!nameEmpty(m_moduleData->m_midMidLeftTireBoneName)) {
			m_midMidLeftTireBone = getRenderObject()->Get_Bone_Index(m_moduleData->m_midMidLeftTireBoneName.str());
			TRUCK_ASSERT(m_midMidLeftTireBone, ("Missing mid-mid-left tire bone %s in model %s\n", m_moduleData->m_midMidLeftTireBoneName.str(), getRenderObject()));
			m_midMidRightTireBone = getRenderObject()->Get_Bone_Index(m_moduleData->m_midMidRightTireBoneName.str());
			TRUCK_ASSERT(m_midMidRightTireBone, ("Missing mid-mid-right tire bone %s in model %s\n", m_moduleData->m_midMidRightTireBoneName.str(), getRenderObject()));
			if (!m_midMidRightTireBone) m_midMidLeftTireBone = 0;
		}
		if (!nameEmpty(m_moduleData->m_secondaryFrontLeftTireBoneName)) {
			m_secondaryFrontLeftTireBone = getRenderObject()->Get_Bone_Index(m_moduleData->m_secondaryFrontLeftTireBoneName.str());
			TRUCK_ASSERT(!m_secondaryFrontLeftTireBone, ("Missing secondary front-left tire bone %s in model %s\n", m_moduleData->m_secondaryFrontLeftTireBoneName.str(), getRenderObject()));
			m_secondaryFrontRightTireBone = getRenderObject()->Get_Bone_Index(m_moduleData->m_secondaryFrontRightTireBoneName.str());
			TRUCK_ASSERT(!m_secondaryFrontRightTireBone, ("Missing secondary front-right tire bone %s in model %s\n", m_moduleData->m_secondaryFrontRightTireBoneName.str(), getRenderObject()));
			if (!m_secondaryFrontRightTireBone) m_secondaryFrontLeftTireBone = 0;
			if (m_secondaryFrontLeftTireBone && !m_frontLeftTireBone) m_secondaryFrontLeftTireBone = 0;
			if (m_secondaryFrontRightTireBone && !m_frontRightTireBone) m_secondaryFrontRightTireBone = 0;
		}
		if (!nameEmpty(m_moduleData->m_secondaryRearLeftTireBoneName)) {
			m_secondaryRearLeftTireBone = getRenderObject()->Get_Bone_Index(m_moduleData->m_secondaryRearLeftTireBoneName.str());
			TRUCK_ASSERT(!m_secondaryRearLeftTireBone, ("Missing secondary rear-left tire bone %s in model %s\n", m_moduleData->m_secondaryRearLeftTireBoneName.str(), getRenderObject()));
			m_secondaryRearRightTireBone = getRenderObject()->Get_Bone_Index(m_moduleData->m_secondaryRearRightTireBoneName.str());
			TRUCK_ASSERT(!m_secondaryRearRightTireBone, ("Missing rear-left tire bone %s in model %s\n", m_moduleData->m_secondaryRearRightTireBoneName.str(), getRenderObject()));
			if (!m_secondaryRearRightTireBone) m_secondaryRearLeftTireBone = 0;
			if (m_secondaryRearLeftTireBone && !m_rearLeftTireBone) m_secondaryRearLeftTireBone = 0;
			if (m_secondaryRearRightTireBone && !m_rearRightTireBone) m_secondaryRearRightTireBone = 0;
		}
		if (!nameEmpty(m_moduleData->m_secondaryMidMidLeftTireBoneName)) {
			m_secondaryMidMidLeftTireBone = getRenderObject()->Get_Bone_Index(m_moduleData->m_secondaryMidMidLeftTireBoneName.str());
			TRUCK_ASSERT(!m_secondaryMidMidLeftTireBone, ("Missing secondary mid-mid-left tire bone %s in model %s\n", m_moduleData->m_secondaryMidMidLeftTireBoneName.str(), getRenderObject()));
			m_secondaryMidMidRightTireBone = getRenderObject()->Get_Bone_Index(m_moduleData->m_secondaryMidMidRightTireBoneName.str());
			TRUCK_ASSERT(!m_secondaryMidMidRightTireBone, ("Missing secondary mid-mid-right tire bone %s in model %s\n", m_moduleData->m_secondaryMidMidRightTireBoneName.str(), getRenderObject()));
			if (!m_secondaryMidMidRightTireBone) m_secondaryMidMidLeftTireBone = 0;
			if (m_secondaryMidMidLeftTireBone && !m_midMidLeftTireBone) m_secondaryMidMidLeftTireBone = 0;
			if (m_secondaryMidMidRightTireBone && !m_midMidRightTireBone) m_secondaryMidMidRightTireBone = 0;
		}
		if (!nameEmpty(m_moduleData->m_cabBoneName)) {
			m_cabBone = getRenderObject()->Get_Bone_Index(m_moduleData->m_cabBoneName.str());
			TRUCK_ASSERT(!m_cabBone, ("Missing cab bone %s in model %s\n", m_moduleData->m_cabBoneName.str(), getRenderObject()));
			m_trailerBone = getRenderObject()->Get_Bone_Index(m_moduleData->m_trailerBoneName.str());
		}
	}
	m_prevRenderObj = getRenderObject();
	m_prevNumBones = m_prevRenderObj->Get_Num_Bones();
}
