// ?rva000BE775@Rva000C3886Obj@@QAEXPAVRva000C3886@@@Z
// partial score=0.95 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// ?rva000BE775@Rva000C3886Obj@@QAEXPAVRva000C3886@@@Z
// retail 0x000BE775..0x000BEDF0 (1659 bytes) thiscall RET 4 with EH frame.
//
// Builds the per-weapon-slot barrel table of a bone state from a condition
// state's weapon bone names: the BFME2 form of Zero Hour's
// ModelConditionInfo::validateWeaponBarrelInfo (W3DModelDraw.cpp), with the
// name vectors read from the argument and the bones from this object.
// WorldBuilder twin 0x009222A0 (unnamed; strings evidence) has the same
// calls and "*** ASSET ERROR: No fx bone named..." report.
// Target evidence: the only caller is the rowed 0x000C3886 (Rva000C3886
// passes itself to this member of its bone-state argument). Skips when bit 8
// at +0xF4 is set or the rowed 0x000B2CBD gate is clear; setFPMode 0x00040EA9;
// six slots: clears the 60-byte barrel vector at this+0xAC+12*slot (rowed
// erase 0x000BC1C2 / push_back 0x000BDAF3); copies the slot's names from the
// argument's AsciiString vectors at +0x84 (fx) +0x90 (recoil) +0x9C (muzzle
// flash) +0xA8 (projectile launch) when in range; for suffixes 1..99 formats
// "%s%02d" (imported sprintf) and looks bones up through the rowed pristine
// lookup 0x000BBDDF and NameKeyGenerator::nameToKey 0x00148E1A; marks the
// argument's per-slot flag at +0xF6; falls back to the unadorned names
// (nameToKey 0x0009FA65) when nothing was found; and reports through the
// release debug channel (0x000387C0 0x00038790 theDebug slots 0x60 0x6C and
// Debug::Format 0x000386E0) when the model name (rowed 0x000B4A9F and the
// out-of-line StringBase isEmpty 0x00001E2F) is set but the slot stays empty.
// Finally sets bit 8 at +0xF4. WeaponBarrelInfo ctor 0x000B493B is rowed.
#include "ascii_string.h"
#include <vector>
#include <stdio.h>

typedef int Int;
typedef float Real;

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;
#define NAMEKEY(s) TheNameKeyGenerator->nameToKey(s)

class Vector4
{
public:
	Real X, Y, Z, W;
	__forceinline Vector4 &operator=(const Vector4 &other)
	{
		X = other.X; Y = other.Y; Z = other.Z; W = other.W;
		return *this;
	}
	__forceinline void Set(Real x, Real y, Real z, Real w)
	{
		X = x; Y = y; Z = z; W = w;
	}
};

class Matrix3D
{
public:
	__forceinline Matrix3D &operator=(const Matrix3D &other)
	{
		Row[0] = other.Row[0];
		Row[1] = other.Row[1];
		Row[2] = other.Row[2];
		return *this;
	}
	__forceinline void Make_Identity()
	{
		Row[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
		Row[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
		Row[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
	}
	Vector4 Row[3];
};

struct ModelConditionInfo
{
	struct WeaponBarrelInfo
	{
		Int m_recoilBone;                 // +0x00
		Int m_fxBone;                     // +0x04
		Int m_muzzleFlashBone;            // +0x08
		Matrix3D m_projectileOffsetMtx;   // +0x0C
		WeaponBarrelInfo();
	};
};
typedef ModelConditionInfo::WeaponBarrelInfo WeaponBarrelInfo;

// The rowed vector spelling of the 60-byte barrel record.
struct BfmeFixedObject60 { char m_bytes[60]; };
namespace _STL
{
template <> BfmeFixedObject60 *vector<BfmeFixedObject60>::erase(BfmeFixedObject60 *first, BfmeFixedObject60 *last);
template <> void vector<BfmeFixedObject60>::push_back(const BfmeFixedObject60 &value);
}

int Rva000B2CBDGet();
void setFPMode();

class Rva000BBDDF
{
public:
	void *rva000BBDDF(int key, int *index) const;
};

class Rva000B4A9F
{
public:
	const char *rva000B4A9F();
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

class Rva000BE775Report
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual Rva000BE775Report *setText(const char *text);
	virtual void slot3C(); virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual void show(int mode);
	Rva000BE775Report &operator<<(const Debug::Format &value) { setText((const char *)&value); return *this; }
};

class Rva000BE775Debug
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
	virtual Rva000BE775Report *getReport(int, int, int);
};

extern Debug *theDebug;
#define TheBarrelDebug (*(Rva000BE775Debug **)&theDebug)
bool bfmeRva000387C0();
void _bfme_debugRecordCallsite(int kind);

static __forceinline void reportMissingFxBone(const char *format, const char *fxName, const char *plbName, const char *modelName)
{
	Rva000BE775Report *out = TheBarrelDebug->getReport(0, 0, 0);
	(*out << Debug::Format(format, fxName, plbName, modelName)).show(2);
}

enum { WEAPONSLOT_COUNT = 6, MAX_BARRELS = 99, BARRELS_VALID = 0x08 };

class Rva000C3886
{
public:
	const AsciiString *getModelName()
	{
		return (const AsciiString *)((Rva000B4A9F *)this)->rva000B4A9F();
	}

	char m_pad00[0x84];
	_STL::vector<AsciiString> m_weaponFireFXBoneName;            // +0x84
	_STL::vector<AsciiString> m_weaponRecoilBoneName;            // +0x90
	_STL::vector<AsciiString> m_weaponMuzzleFlashName;           // +0x9C
	_STL::vector<AsciiString> m_weaponProjectileLaunchBoneName;  // +0xA8
	char m_padB4[0xF6 - 0xB4];
	bool m_hasRecoilBonesOrMuzzleFlashes[WEAPONSLOT_COUNT];      // +0xF6
};

// The pristine-bone lookup is the rowed 0x000BBDDF on this same object.
struct Rva000C3886Obj : public Rva000BBDDF
{
	void rva000BE775(Rva000C3886 *src);

	char m_pad00[0xAC];
	_STL::vector<BfmeFixedObject60> m_weaponBarrelInfoVec[WEAPONSLOT_COUNT]; // +0xAC
	unsigned char m_validStuff;                                          // +0xF4
};

void Rva000C3886Obj::rva000BE775(Rva000C3886 *src)
{
	if (m_validStuff & BARRELS_VALID)
		return;
	if (!(unsigned char)Rva000B2CBDGet())
		return;

	setFPMode();

	for (Int wslot = 0; wslot < WEAPONSLOT_COUNT; ++wslot)
	{
		m_weaponBarrelInfoVec[wslot].clear();

		AsciiString plbName = AsciiString::TheEmptyString;
		if ((unsigned int)wslot < src->m_weaponProjectileLaunchBoneName.size())
			plbName = src->m_weaponProjectileLaunchBoneName[wslot];
		AsciiString fxBoneName = AsciiString::TheEmptyString;
		if ((unsigned int)wslot < src->m_weaponFireFXBoneName.size())
			fxBoneName = src->m_weaponFireFXBoneName[wslot];

		if (!fxBoneName.isEmpty() || !plbName.isEmpty())
		{
			Int prevFxBone = 0;
			char buffer[256];
			for (Int i = 1; i <= MAX_BARRELS; ++i)
			{
				WeaponBarrelInfo info;
				info.m_projectileOffsetMtx.Make_Identity();

				AsciiString recoilBoneName = AsciiString::TheEmptyString;
				if ((unsigned int)wslot < src->m_weaponRecoilBoneName.size())
					recoilBoneName = src->m_weaponRecoilBoneName[wslot];
				if (!recoilBoneName.isEmpty())
				{
					sprintf(buffer, "%s%02d", recoilBoneName.str(), i);
					rva000BBDDF(NAMEKEY(buffer), &info.m_recoilBone);
				}

				AsciiString mfName = AsciiString::TheEmptyString;
				if ((unsigned int)wslot < src->m_weaponMuzzleFlashName.size())
					mfName = src->m_weaponMuzzleFlashName[wslot];
				if (!mfName.isEmpty())
				{
					sprintf(buffer, "%s%02d", mfName.str(), i);
					rva000BBDDF(NAMEKEY(buffer), &info.m_muzzleFlashBone);
				}

				if (!fxBoneName.isEmpty())
				{
					sprintf(buffer, "%s%02d", fxBoneName.str(), i);
					rva000BBDDF(NAMEKEY(buffer), &info.m_fxBone);
					if (info.m_fxBone == 0 && info.m_muzzleFlashBone != 0)
						info.m_fxBone = prevFxBone;
				}

				Int plbBoneIndex = 0;
				if (!plbName.isEmpty())
				{
					sprintf(buffer, "%s%02d", plbName.str(), i);
					const Matrix3D *mtx = (const Matrix3D *)rva000BBDDF(NAMEKEY(buffer), &plbBoneIndex);
					if (mtx != 0)
						info.m_projectileOffsetMtx = *mtx;
				}

				if (info.m_fxBone != 0 || info.m_recoilBone != 0 || info.m_muzzleFlashBone != 0 || plbBoneIndex != 0)
				{
					m_weaponBarrelInfoVec[wslot].push_back(*(const BfmeFixedObject60 *)&info);
					if (info.m_recoilBone != 0 || info.m_muzzleFlashBone != 0)
						src->m_hasRecoilBonesOrMuzzleFlashes[wslot] = true;
				}
				else
				{
					break;
				}
				prevFxBone = info.m_fxBone;
			}

			if (m_weaponBarrelInfoVec[wslot].empty())
			{
				WeaponBarrelInfo info;
				const Matrix3D *mtx = plbName.isEmpty() ? 0 : (const Matrix3D *)rva000BBDDF(NAMEKEY(plbName), 0);
				if (mtx != 0)
					info.m_projectileOffsetMtx = *mtx;
				else
					info.m_projectileOffsetMtx.Make_Identity();

				if (!fxBoneName.isEmpty())
					rva000BBDDF(NAMEKEY(fxBoneName), &info.m_fxBone);

				if (info.m_fxBone != 0 || mtx != 0)
					m_weaponBarrelInfoVec[wslot].push_back(*(const BfmeFixedObject60 *)&info);
			}

			if (!((const StringBase<char> *)src->getModelName())->isEmpty() && m_weaponBarrelInfoVec[wslot].empty())
			{
				if (bfmeRva000387C0())
				{
					_bfme_debugRecordCallsite(1);
					TheBarrelDebug->beginReport();
					reportMissingFxBone("*** ASSET ERROR: No fx bone named '%s' (or prefixed by '%s') found in model %s!\n",
						fxBoneName.str(), plbName.str(), src->getModelName()->str());
				}
			}
		}
	}

	m_validStuff |= BARRELS_VALID;
}
