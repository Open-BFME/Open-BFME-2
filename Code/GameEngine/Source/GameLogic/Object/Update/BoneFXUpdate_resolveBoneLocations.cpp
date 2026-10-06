// cl: /DNDEBUG /MD /EHs-c-
//
// ?resolveBoneLocations@BoneFXUpdate@@MAEXXZ, retail 0x00487634, 355 bytes.
//
// BoneFXUpdate virtual slot 13 (vtable 0x0084B170) resolveBoneLocations.
// Donor is BFME1 BoneFXUpdate::resolveBoneLocations
// (reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate.cpp:542)
// via Zero Hour BoneFXUpdate.cpp:502. BFME2 layout matches the landed
// initTimes TU in this directory (moduleData at +4, object at +8,
// info arrays at +0x0C/+0x490/+0x914 element 0x24, positions at
// +0x1AC/+0x32C/+0x4AC, curBodyState at +0x62C, bonesResolved at +0x630).
// Retail inlines AsciiString::str as data+8 vs "" default (0x007BAC1C)
// and calls the rowed StringBase compare at 0x000069D6 via the AsciiString
// pin, Thing::getDrawable via pin 0x005508E2, and the rowed Drawable
// getPristineBonePositions at 0x0027274D. DEBUG_ASSERTCRASH compiles out
// under /DNDEBUG so the drawable null check emits no code.

struct BfmeAsciiStringData
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_len;
	unsigned short m_pad;
};

class AsciiString
{
public:
	static const AsciiString TheEmptyString;
	int compare(const AsciiString &stringSrc) const;
	const char *str() const
	{
		return m_data ? reinterpret_cast<const char *>(m_data + 1) : "";
	}

private:
	BfmeAsciiStringData *m_data;
};

// AsciiString::TheEmptyString: defined in Common/Rva00380200Getter.cpp.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Matrix3D;

class Drawable
{
public:
	int getPristineBonePositions(const char *boneNamePrefix, int startIndex,
		Coord3D *positions, Matrix3D *transforms, int maxBones, int extra) const;
};

class Thing
{
public:
	Drawable *getDrawable() const;
};

class Object : public Thing
{
};

struct BoneFXListInfo
{
	AsciiString boneName;
	char m_pad[0x20];
};

struct BoneOCLInfo
{
	AsciiString boneName;
	char m_pad[0x20];
};

struct BoneParticleSystemInfo
{
	AsciiString boneName;
	char m_pad[0x20];
};

class BoneFXUpdateModuleData
{
public:
	char m_hdr[0x0C];
	BoneFXListInfo m_fxList[4][8];
	int m_damageOCLTypes;
	BoneOCLInfo m_OCL[4][8];
	int m_damageParticleTypes;
	BoneParticleSystemInfo m_particleSystem[4][8];
};

class BoneFXUpdate
{
protected:
	virtual void resolveBoneLocations();

public:
	const BoneFXUpdateModuleData *getBoneFXUpdateModuleData() const
	{
		return m_moduleData;
	}
	Object *getObject() const
	{
		return m_object;
	}

private:
	const BoneFXUpdateModuleData *m_moduleData;
	Object *m_object;
	char m_pad0C[0x2C - 0x0C];
	int m_nextFXFrame[4][8];
	int m_nextOCLFrame[4][8];
	int m_nextParticleSystemFrame[4][8];
	Coord3D m_FXBonePositions[4][8];
	Coord3D m_OCLBonePositions[4][8];
	Coord3D m_PSBonePositions[4][8];
	int m_curBodyState;
	bool m_bonesResolved[4];
};

void BoneFXUpdate::resolveBoneLocations()
{
	int i;
	Object *building = getObject();
	const BoneFXUpdateModuleData *d = getBoneFXUpdateModuleData();
	if (building == 0) {
		return;
	}

	Drawable *drawable = building->getDrawable();

	if (d == 0) {
		return;
	}

	for (i = 0; i < 8; ++i) {
		if (d->m_fxList[m_curBodyState][i].boneName.compare(AsciiString::TheEmptyString) != 0) {
			const BoneFXListInfo *info = &(d->m_fxList[m_curBodyState][i]);
			drawable->getPristineBonePositions(info->boneName.str(), 0, &m_FXBonePositions[m_curBodyState][i], 0, 1, 0);
		}

		if (d->m_OCL[m_curBodyState][i].boneName.compare(AsciiString::TheEmptyString) != 0) {
			const BoneOCLInfo *info = &(d->m_OCL[m_curBodyState][i]);
			drawable->getPristineBonePositions(info->boneName.str(), 0, &m_OCLBonePositions[m_curBodyState][i], 0, 1, 0);
		}

		if (d->m_particleSystem[m_curBodyState][i].boneName.compare(AsciiString::TheEmptyString) != 0) {
			const BoneParticleSystemInfo *info = &(d->m_particleSystem[m_curBodyState][i]);
			drawable->getPristineBonePositions(info->boneName.str(), 0, &m_PSBonePositions[m_curBodyState][i], 0, 1, 0);
		}
	}
	m_bonesResolved[m_curBodyState] = true;
}
