// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// FXList's nugget parse callbacks, one per keyword row of the FXList FieldParse
// table at 0x007DC720 (retail keyword, parse). BFME2 rewrote them against the
// BFME1 donor (FXListNuggetParse_Thunk.cpp): every row news its nugget, runs
// the out-of-line no-arg ctor, lets one cdecl per-class builder fill a
// MultiIniFieldParse, hands both to INI::initFromINIMulti and appends the
// nugget to the FXList's list at +4 -- 124 bytes each, identical bar the new
// size, the ctor and the builder.
//
// Names: the keyword is the retail evidence. The <keyword>FXNugget class names
// are BFME1's (itself Zero Hour's convention); buildFieldParse is the name
// BFME gives the same role on ModuleData classes, not a retail fact.

#include <list>

class INI;
#include "../../Include/Common/INI/FieldParse.h"

#include "../../Include/Common/INI/INI.h"

typedef int Int;

class FXNugget;

class FXList
{
public:
	void addFXNugget(FXNugget *fxn) { m_nuggets.push_back(fxn); }
	static void parseCullingInfo(INI *ini, void *instance, void *, const void *);
private:
	int m_unused00;
	_STL::list<FXNugget *> m_nuggets;	// +0x04
};

// Target evidence: the retail callback's own strings name
// FXList::parseCullingInfo and its three keywords. It reads/writes the
// culling settings at instance offsets +0x14, +0x1C and +0x20; the minimum
// and maximum error strings identify the latter two fields independently.
// Donor evidence: GeneralsMD's FXList subsystem is the family source, but its
// FXList has no culling parser or those fields, so this body follows retail's
// parser calls and control flow rather than claiming a donor implementation.
struct FXListCullingSettingsView
{
	char m_pad00[0x14];
	int m_trackingSeconds;
	int m_pad18;
	unsigned int m_cullTrackingMax;
	unsigned int m_cullTrackingMin;
};

// Retail uses the _strcmpi IAT slot at 0x00BBA518 for these keyword checks.
extern "C" int (__cdecl * const _imp___strcmpi)(const char *left, const char *right);
extern int BfmeLogicFramesPerSecond;

// ?parseCullingInfo@FXList@@SAXPAVINI@@PAX1PBX@Z
void FXList::parseCullingInfo(INI *ini, void *instance, void *, const void *)
{
	FXListCullingSettingsView *settings = (FXListCullingSettingsView *)instance;
	const char *token = ini->getNextTokenOrNull(*(const char **)((char *)ini + 0x420));
	while (token != 0) {
		if (_imp___strcmpi(token, "TrackingSeconds") == 0) {
			settings->m_trackingSeconds =
				(int)(ini->scanReal(ini->getNextToken(0)) * BfmeLogicFramesPerSecond);
		} else if (_imp___strcmpi(token, "StartCullingAbove") == 0) {
			settings->m_cullTrackingMin = ini->scanUnsignedInt(ini->getNextToken(0));
		} else if (_imp___strcmpi(token, "CullAllAbove") == 0) {
			settings->m_cullTrackingMax = ini->scanUnsignedInt(ini->getNextToken(0));
		} else {
			throw INIException(3,
				"bad colon spacing, or unexpected token in FXList::parseCullingInfo");
		}
		token = ini->getNextTokenOrNull(*(const char **)((char *)ini + 0x420));
	}

	if (settings->m_cullTrackingMax == 0)
		throw INIException(3, "m_cullTrackingMax == 0 in FXList::parseCullingInfo");
	if (settings->m_cullTrackingMin == 0)
		throw INIException(3, "m_cullTrackingMin == 0 in FXList::parseCullingInfo");
	if (settings->m_cullTrackingMax <= settings->m_cullTrackingMin)
		settings->m_cullTrackingMax = settings->m_cullTrackingMin + 1;
}

struct FieldParse;

class MultiIniFieldParse;

// FXNugget's own FieldParse (0x00BDCA18): every builder adds it after the
// derived table.
extern const FieldParse FXNuggetFieldParse[];

class FXNugget
{
};

// "Sound": parse 0x001E1329, news 0x14C, ctor 0x001E00A3, builder 0x001DFAE0
class SoundFXNugget : public FXNugget
{
public:
	SoundFXNugget();
	static void buildFieldParse(MultiIniFieldParse &fieldParse);
	static void parse(INI *ini, void *instance, void *, const void *);
private:
	char m_pad[0x14C];
};

extern const FieldParse SoundFXNuggetFieldParse[];	// 0x00BDCB18

// ?buildFieldParse@SoundFXNugget@@SAXAAVMultiIniFieldParse@@@Z
void SoundFXNugget::buildFieldParse(MultiIniFieldParse &fieldParse)
{
	fieldParse.add(SoundFXNuggetFieldParse);
	fieldParse.add(FXNuggetFieldParse);
}

// ?parse@SoundFXNugget@@SAXPAVINI@@PAX1PBX@Z
inline void SoundFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	SoundFXNugget *nugget = new SoundFXNugget;
	MultiIniFieldParse fieldParse;
	buildFieldParse(fieldParse);
	ini->initFromINIMulti(nugget, fieldParse);
	((FXList *)instance)->addFXNugget(nugget);
}

// "EvaEvent": parse 0x001E12AD, news 0x154, ctor 0x001DFFFA, builder 0x001DFABF
class EvaEventFXNugget : public FXNugget
{
public:
	EvaEventFXNugget();
	static void buildFieldParse(MultiIniFieldParse &fieldParse);
	static void parse(INI *ini, void *instance, void *, const void *);
private:
	char m_pad[0x154];
};

extern const FieldParse EvaEventFXNuggetFieldParse[];	// 0x00BDCAD8

// ?buildFieldParse@EvaEventFXNugget@@SAXAAVMultiIniFieldParse@@@Z
void EvaEventFXNugget::buildFieldParse(MultiIniFieldParse &fieldParse)
{
	fieldParse.add(EvaEventFXNuggetFieldParse);
	fieldParse.add(FXNuggetFieldParse);
}

// ?parse@EvaEventFXNugget@@SAXPAVINI@@PAX1PBX@Z
void EvaEventFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	EvaEventFXNugget *nugget = new EvaEventFXNugget;
	MultiIniFieldParse fieldParse;
	buildFieldParse(fieldParse);
	ini->initFromINIMulti(nugget, fieldParse);
	((FXList *)instance)->addFXNugget(nugget);
}

// "RayEffect": parse 0x001E13A5, news 0x164, ctor 0x001E01B2, builder 0x001DFB01
class RayEffectFXNugget : public FXNugget
{
public:
	RayEffectFXNugget();
	static void buildFieldParse(MultiIniFieldParse &fieldParse);
	static void parse(INI *ini, void *instance, void *, const void *);
private:
	char m_pad[0x164];
};

extern const FieldParse RayEffectFXNuggetFieldParse[];	// 0x00BDCB58

// ?buildFieldParse@RayEffectFXNugget@@SAXAAVMultiIniFieldParse@@@Z
void RayEffectFXNugget::buildFieldParse(MultiIniFieldParse &fieldParse)
{
	fieldParse.add(RayEffectFXNuggetFieldParse);
	fieldParse.add(FXNuggetFieldParse);
}

// ?parse@RayEffectFXNugget@@SAXPAVINI@@PAX1PBX@Z
inline void RayEffectFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	RayEffectFXNugget *nugget = new RayEffectFXNugget;
	MultiIniFieldParse fieldParse;
	buildFieldParse(fieldParse);
	ini->initFromINIMulti(nugget, fieldParse);
	((FXList *)instance)->addFXNugget(nugget);
}

// "LightPulse": parse 0x001E1421, news 0x164, ctor 0x001E0321, builder 0x001DFB22
class LightPulseFXNugget : public FXNugget
{
public:
	LightPulseFXNugget();
	static void buildFieldParse(MultiIniFieldParse &fieldParse);
	static void parse(INI *ini, void *instance, void *, const void *);
private:
	char m_pad[0x164];
};

extern const FieldParse LightPulseFXNuggetFieldParse[];	// 0x00BDCBD8

// ?buildFieldParse@LightPulseFXNugget@@SAXAAVMultiIniFieldParse@@@Z
void LightPulseFXNugget::buildFieldParse(MultiIniFieldParse &fieldParse)
{
	fieldParse.add(LightPulseFXNuggetFieldParse);
	fieldParse.add(FXNuggetFieldParse);
}

// ?parse@LightPulseFXNugget@@SAXPAVINI@@PAX1PBX@Z
inline void LightPulseFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	LightPulseFXNugget *nugget = new LightPulseFXNugget;
	MultiIniFieldParse fieldParse;
	buildFieldParse(fieldParse);
	ini->initFromINIMulti(nugget, fieldParse);
	((FXList *)instance)->addFXNugget(nugget);
}

// "CameraShakerVolume": parse 0x001E1595, news 0x160, ctor 0x001E0714, builder 0x001DFBA6
class CameraShakerVolumeFXNugget : public FXNugget
{
public:
	CameraShakerVolumeFXNugget();
	static void buildFieldParse(MultiIniFieldParse &fieldParse);
	static void parse(INI *ini, void *instance, void *, const void *);
private:
	char m_pad[0x160];
};

extern const FieldParse CameraShakerVolumeFXNuggetFieldParse[];	// 0x00BDD040

// ?buildFieldParse@CameraShakerVolumeFXNugget@@SAXAAVMultiIniFieldParse@@@Z
void CameraShakerVolumeFXNugget::buildFieldParse(MultiIniFieldParse &fieldParse)
{
	fieldParse.add(CameraShakerVolumeFXNuggetFieldParse);
	fieldParse.add(FXNuggetFieldParse);
}

// ?parse@CameraShakerVolumeFXNugget@@SAXPAVINI@@PAX1PBX@Z
void CameraShakerVolumeFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	CameraShakerVolumeFXNugget *nugget = new CameraShakerVolumeFXNugget;
	MultiIniFieldParse fieldParse;
	buildFieldParse(fieldParse);
	ini->initFromINIMulti(nugget, fieldParse);
	((FXList *)instance)->addFXNugget(nugget);
}

// "ViewShake": parse 0x001E1611, news 0x14C, ctor 0x001E07DF, builder 0x001E0829
class ViewShakeFXNugget : public FXNugget
{
public:
	ViewShakeFXNugget();
	static void buildFieldParse(MultiIniFieldParse &fieldParse);
	static void parse(INI *ini, void *instance, void *, const void *);
private:
	char m_pad[0x14C];
};

extern const FieldParse ViewShakeFXNuggetFieldParse[];	// 0x00BDD7F4

// ?buildFieldParse@ViewShakeFXNugget@@SAXAAVMultiIniFieldParse@@@Z
void ViewShakeFXNugget::buildFieldParse(MultiIniFieldParse &fieldParse)
{
	fieldParse.add(ViewShakeFXNuggetFieldParse);
	fieldParse.add(FXNuggetFieldParse);
}

// ?parse@ViewShakeFXNugget@@SAXPAVINI@@PAX1PBX@Z
inline void ViewShakeFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	ViewShakeFXNugget *nugget = new ViewShakeFXNugget;
	MultiIniFieldParse fieldParse;
	buildFieldParse(fieldParse);
	ini->initFromINIMulti(nugget, fieldParse);
	((FXList *)instance)->addFXNugget(nugget);
}

// "AttachedModel": parse 0x001E168D, news 0x154, ctor 0x001E084A, builder 0x001DFBE8
class AttachedModelFXNugget : public FXNugget
{
public:
	AttachedModelFXNugget();
	static void buildFieldParse(MultiIniFieldParse &fieldParse);
	static void parse(INI *ini, void *instance, void *, const void *);
private:
	char m_pad[0x154];
};

extern const FieldParse AttachedModelFXNuggetFieldParse[];	// 0x00BDD118

// ?buildFieldParse@AttachedModelFXNugget@@SAXAAVMultiIniFieldParse@@@Z
void AttachedModelFXNugget::buildFieldParse(MultiIniFieldParse &fieldParse)
{
	fieldParse.add(AttachedModelFXNuggetFieldParse);
	fieldParse.add(FXNuggetFieldParse);
}

// ?parse@AttachedModelFXNugget@@SAXPAVINI@@PAX1PBX@Z
void AttachedModelFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	AttachedModelFXNugget *nugget = new AttachedModelFXNugget;
	MultiIniFieldParse fieldParse;
	buildFieldParse(fieldParse);
	ini->initFromINIMulti(nugget, fieldParse);
	((FXList *)instance)->addFXNugget(nugget);
}

// "TerrainScorch": parse 0x001E171C, news 0x158, ctor 0x001E08D9, builder 0x001E0965
class TerrainScorchFXNugget : public FXNugget
{
public:
	TerrainScorchFXNugget();
	static void buildFieldParse(MultiIniFieldParse &fieldParse);
	static void parse(INI *ini, void *instance, void *, const void *);
private:
	char m_pad[0x158];
};

extern const FieldParse TerrainScorchFXNuggetFieldParse[];	// 0x00BDD8A0

// ?buildFieldParse@TerrainScorchFXNugget@@SAXAAVMultiIniFieldParse@@@Z
void TerrainScorchFXNugget::buildFieldParse(MultiIniFieldParse &fieldParse)
{
	fieldParse.add(TerrainScorchFXNuggetFieldParse);
	fieldParse.add(FXNuggetFieldParse);
}

// ?parse@TerrainScorchFXNugget@@SAXPAVINI@@PAX1PBX@Z
inline void TerrainScorchFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	TerrainScorchFXNugget *nugget = new TerrainScorchFXNugget;
	MultiIniFieldParse fieldParse;
	buildFieldParse(fieldParse);
	ini->initFromINIMulti(nugget, fieldParse);
	((FXList *)instance)->addFXNugget(nugget);
}

// "ParticleSystem": parse 0x001E264F, news 0x1BC, ctor 0x001E0AEF, builder 0x001DFD15
class ParticleSystemFXNugget : public FXNugget
{
public:
	ParticleSystemFXNugget();
	static void buildFieldParse(MultiIniFieldParse &fieldParse);
	static void parse(INI *ini, void *instance, void *, const void *);
private:
	char m_pad[0x1BC];
};

extern const FieldParse ParticleSystemFXNuggetFieldParse[];	// 0x00BDD428

// ?buildFieldParse@ParticleSystemFXNugget@@SAXAAVMultiIniFieldParse@@@Z
void ParticleSystemFXNugget::buildFieldParse(MultiIniFieldParse &fieldParse)
{
	fieldParse.add(ParticleSystemFXNuggetFieldParse);
	fieldParse.add(FXNuggetFieldParse);
}

// ?parse@ParticleSystemFXNugget@@SAXPAVINI@@PAX1PBX@Z
inline void ParticleSystemFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	ParticleSystemFXNugget *nugget = new ParticleSystemFXNugget;
	MultiIniFieldParse fieldParse;
	buildFieldParse(fieldParse);
	ini->initFromINIMulti(nugget, fieldParse);
	((FXList *)instance)->addFXNugget(nugget);
}

// "FXListAtBonePos": parse 0x001E1814, news 0x150, ctor 0x001E0A57, builder 0x001DFCF4
class FXListAtBonePosFXNugget : public FXNugget
{
public:
	FXListAtBonePosFXNugget();
	static void buildFieldParse(MultiIniFieldParse &fieldParse);
	static void parse(INI *ini, void *instance, void *, const void *);
private:
	char m_pad[0x150];
};

extern const FieldParse FXListAtBonePosFXNuggetFieldParse[];	// 0x00BDD2F8

// ?buildFieldParse@FXListAtBonePosFXNugget@@SAXAAVMultiIniFieldParse@@@Z
void FXListAtBonePosFXNugget::buildFieldParse(MultiIniFieldParse &fieldParse)
{
	fieldParse.add(FXListAtBonePosFXNuggetFieldParse);
	fieldParse.add(FXNuggetFieldParse);
}

// ?parse@FXListAtBonePosFXNugget@@SAXPAVINI@@PAX1PBX@Z
inline void FXListAtBonePosFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	FXListAtBonePosFXNugget *nugget = new FXListAtBonePosFXNugget;
	MultiIniFieldParse fieldParse;
	buildFieldParse(fieldParse);
	ini->initFromINIMulti(nugget, fieldParse);
	((FXList *)instance)->addFXNugget(nugget);
}

// "CursorParticleSystem": parse 0x001E26CB, news 0x180, ctor 0x001E0C90, builder 0x001DFD36
class CursorParticleSystemFXNugget : public FXNugget
{
public:
	CursorParticleSystemFXNugget();
	static void buildFieldParse(MultiIniFieldParse &fieldParse);
	static void parse(INI *ini, void *instance, void *, const void *);
private:
	char m_pad[0x180];
};

extern const FieldParse CursorParticleSystemFXNuggetFieldParse[];	// 0x00BDD600

// ?buildFieldParse@CursorParticleSystemFXNugget@@SAXAAVMultiIniFieldParse@@@Z
void CursorParticleSystemFXNugget::buildFieldParse(MultiIniFieldParse &fieldParse)
{
	fieldParse.add(CursorParticleSystemFXNuggetFieldParse);
	fieldParse.add(FXNuggetFieldParse);
}

// ?parse@CursorParticleSystemFXNugget@@SAXPAVINI@@PAX1PBX@Z
void CursorParticleSystemFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	CursorParticleSystemFXNugget *nugget = new CursorParticleSystemFXNugget;
	MultiIniFieldParse fieldParse;
	buildFieldParse(fieldParse);
	ini->initFromINIMulti(nugget, fieldParse);
	((FXList *)instance)->addFXNugget(nugget);
}

// "DynamicDecal": parse 0x001E149D, news 0x18C, ctor 0x001E0429, builder 0x001DFB43
class DynamicDecalFXNugget : public FXNugget
{
public:
	DynamicDecalFXNugget();
	static void buildFieldParse(MultiIniFieldParse &fieldParse);
	static void parse(INI *ini, void *instance, void *, const void *);
private:
	char m_pad[0x18C];
};

extern const FieldParse DynamicDecalFXNuggetFieldParse[];	// 0x00BDCCF0

// ?buildFieldParse@DynamicDecalFXNugget@@SAXAAVMultiIniFieldParse@@@Z
void DynamicDecalFXNugget::buildFieldParse(MultiIniFieldParse &fieldParse)
{
	fieldParse.add(DynamicDecalFXNuggetFieldParse);
	fieldParse.add(FXNuggetFieldParse);
}

// ?parse@DynamicDecalFXNugget@@SAXPAVINI@@PAX1PBX@Z
void DynamicDecalFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	DynamicDecalFXNugget *nugget = new DynamicDecalFXNugget;
	MultiIniFieldParse fieldParse;
	buildFieldParse(fieldParse);
	ini->initFromINIMulti(nugget, fieldParse);
	((FXList *)instance)->addFXNugget(nugget);
}

// "Laser": parse 0x001E1519, news 0x15C, ctor 0x001E04DE, builder 0x001DFB85
class LaserFXNugget : public FXNugget
{
public:
	LaserFXNugget();
	static void buildFieldParse(MultiIniFieldParse &fieldParse);
	static void parse(INI *ini, void *instance, void *, const void *);
private:
	char m_pad[0x15C];
};

extern const FieldParse LaserFXNuggetFieldParse[];	// 0x00BDCFD8

// ?buildFieldParse@LaserFXNugget@@SAXAAVMultiIniFieldParse@@@Z
void LaserFXNugget::buildFieldParse(MultiIniFieldParse &fieldParse)
{
	fieldParse.add(LaserFXNuggetFieldParse);
	fieldParse.add(FXNuggetFieldParse);
}

// ?parse@LaserFXNugget@@SAXPAVINI@@PAX1PBX@Z
void LaserFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	LaserFXNugget *nugget = new LaserFXNugget;
	MultiIniFieldParse fieldParse;
	buildFieldParse(fieldParse);
	ini->initFromINIMulti(nugget, fieldParse);
	((FXList *)instance)->addFXNugget(nugget);
}

// "TintDrawable": parse 0x001E1798, news 0x168, ctor 0x001E0986, builder 0x001DFCD3
class TintDrawableFXNugget : public FXNugget
{
public:
	TintDrawableFXNugget();
	static void buildFieldParse(MultiIniFieldParse &fieldParse);
	static void parse(INI *ini, void *instance, void *, const void *);
private:
	char m_pad[0x168];
};

extern const FieldParse TintDrawableFXNuggetFieldParse[];	// 0x00BDD278

// ?buildFieldParse@TintDrawableFXNugget@@SAXAAVMultiIniFieldParse@@@Z
void TintDrawableFXNugget::buildFieldParse(MultiIniFieldParse &fieldParse)
{
	fieldParse.add(TintDrawableFXNuggetFieldParse);
	fieldParse.add(FXNuggetFieldParse);
}

// ?parse@TintDrawableFXNugget@@SAXPAVINI@@PAX1PBX@Z
void TintDrawableFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	TintDrawableFXNugget *nugget = new TintDrawableFXNugget;
	MultiIniFieldParse fieldParse;
	buildFieldParse(fieldParse);
	ini->initFromINIMulti(nugget, fieldParse);
	((FXList *)instance)->addFXNugget(nugget);
}

// "BuffNugget": parse 0x001E323B, news 0x190, ctor 0x001E2FCE, builder 0x001DFB64
class BuffNuggetFXNugget : public FXNugget
{
public:
	BuffNuggetFXNugget();
	static void buildFieldParse(MultiIniFieldParse &fieldParse);
	static void parse(INI *ini, void *instance, void *, const void *);
private:
	char m_pad[0x190];
};

extern const FieldParse BuffNuggetFXNuggetFieldParse[];	// 0x00BDCEB8

// ?buildFieldParse@BuffNuggetFXNugget@@SAXAAVMultiIniFieldParse@@@Z
void BuffNuggetFXNugget::buildFieldParse(MultiIniFieldParse &fieldParse)
{
	fieldParse.add(BuffNuggetFXNuggetFieldParse);
	fieldParse.add(FXNuggetFieldParse);
}

// ?parse@BuffNuggetFXNugget@@SAXPAVINI@@PAX1PBX@Z
void BuffNuggetFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	BuffNuggetFXNugget *nugget = new BuffNuggetFXNugget;
	MultiIniFieldParse fieldParse;
	buildFieldParse(fieldParse);
	ini->initFromINIMulti(nugget, fieldParse);
	((FXList *)instance)->addFXNugget(nugget);
}

// These seven parse callbacks are header inlines in copier units. The anchor
// retains this unit's row copies; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeFXListNuggetParseInlineAnchor@@YAXXZ absent-from-retail
void _bfmeFXListNuggetParseInlineAnchor()
{
	SoundFXNugget::parse(0, 0, 0, 0);
	RayEffectFXNugget::parse(0, 0, 0, 0);
	LightPulseFXNugget::parse(0, 0, 0, 0);
	ViewShakeFXNugget::parse(0, 0, 0, 0);
	TerrainScorchFXNugget::parse(0, 0, 0, 0);
	ParticleSystemFXNugget::parse(0, 0, 0, 0);
	FXListAtBonePosFXNugget::parse(0, 0, 0, 0);
}
#pragma inline_depth()

// The nugget field tables the builders above add (retail .rdata, each closed by
// a null entry). Every callback is a rowed parser; the strings are retail's
// keywords. Offsets are into the nugget object (FXNugget's own fields below
// 0x148, the derived class's from 0x148).
void Rva000B9468Parse(INI *ini, void *instance, void *store, const void *userData);
void Rva001DEE74Parse(INI *ini, void *instance, void *store, const void *userData);
void parseShakeType(INI *ini, void *instance, void *store, const void *userData);
void parseScorchType(INI *ini, void *instance, void *store, const void *userData);
void Rva001DFC2AParse(INI *ini, void *instance, void *store, const void *userData);
void iniParseObjectFilter(INI *ini, void *instance, void *store, const void *userData);

// GameType.cpp's weather names: FXNugget's Weather field indexes them.
extern char *WeatherNames[];

// The Shader index-list names of DynamicDecalFXNugget (retail .data 0x009B8DE8).
const char *DynamicDecalShaderNames[] = { "ALPHA", "ADDITIVE", 0 };

// The BuffType index-list names of BuffNuggetFXNugget (retail .rdata 0x00816F58).
extern const char *const BuffTypeNames[] =
{
	"DO_NOT_USE_THIS_TYPE", "Healing", "LeaderShip", "GloriousCharge", "Dominate",
	"Cursed", "Buff", "Debuff", "Poison", 0
};

// retail .rdata 0x007DCA18 (8 entries + terminator)
extern const FieldParse FXNuggetFieldParse[] =
{
	{ "ObjectFilter", iniParseObjectFilter, 0, 0xC },
	{ "SourceObjectFilter", iniParseObjectFilter, 0, 0x8 },
	{ "RequiredSecondaryModelConditions", Rva000B9468Parse, 0, 0xA8 },
	{ "ExcludedSecondaryModelConditions", Rva000B9468Parse, 0, 0xF4 },
	{ "RequiredSourceModelConditions", Rva000B9468Parse, 0, 0x10 },
	{ "ExcludedSourceModelConditions", Rva000B9468Parse, 0, 0x5C },
	{ "StopIfNuggetPlayed", INI::parseBool, 0, 0x144 },
	{ "Weather", INI::parseIndexList, WeatherNames, 0x140 },
	{ 0, 0, 0, 0 }
};

// retail .rdata 0x007DCAD8 (3 entries + terminator)
extern const FieldParse EvaEventFXNuggetFieldParse[] =
{
	{ "EvaEventOwner", Rva001DEE74Parse, 0, 0x148 },
	{ "EvaEventAlly", Rva001DEE74Parse, 0, 0x14C },
	{ "EvaEventEnemy", Rva001DEE74Parse, 0, 0x150 },
	{ 0, 0, 0, 0 }
};

// retail .rdata 0x007DCB18 (1 entry + terminator)
extern const FieldParse SoundFXNuggetFieldParse[] =
{
	{ "Name", INI::parseAudioEventRTS, 0, 0x148 },
	{ 0, 0, 0, 0 }
};

// retail .rdata 0x007DCB58 (3 entries + terminator)
extern const FieldParse RayEffectFXNuggetFieldParse[] =
{
	{ "Name", INI::parseAsciiString, 0, 0x148 },
	{ "PrimaryOffset", INI::parseCoord3D, 0, 0x14C },
	{ "SecondaryOffset", INI::parseCoord3D, 0, 0x158 },
	{ 0, 0, 0, 0 }
};

// retail .rdata 0x007DCBD8 (5 entries + terminator)
extern const FieldParse LightPulseFXNuggetFieldParse[] =
{
	{ "Color", INI::parseRGBColor, 0, 0x148 },
	{ "Radius", INI::parseReal, 0, 0x154 },
	{ "RadiusAsPercentOfObjectSize", INI::parsePercentToReal, 0, 0x158 },
	{ "IncreaseTime", INI::parseDurationUnsignedInt, 0, 0x15C },
	{ "DecreaseTime", INI::parseDurationUnsignedInt, 0, 0x160 },
	{ 0, 0, 0, 0 }
};

// retail .rdata 0x007DCCF0 (14 entries + terminator)
extern const FieldParse DynamicDecalFXNuggetFieldParse[] =
{
	{ "DecalName", INI::parseAsciiString, 0, 0x148 },
	{ "Shader", INI::parseIndexList, DynamicDecalShaderNames, 0x14C },
	{ "Size", INI::parseReal, 0, 0x150 },
	{ "Color", INI::parseRGBColor, 0, 0x154 },
	{ "Offset", INI::parseCoord2D, 0, 0x160 },
	{ "OrientToObject", INI::parseBool, 0, 0x168 },
	{ "OpacityStart", INI::parseUnsignedInt, 0, 0x16C },
	{ "OpacityFadeTimeOne", INI::parseReal, 0, 0x170 },
	{ "OpacityPeak", INI::parseUnsignedInt, 0, 0x174 },
	{ "OpacityPeakTime", INI::parseReal, 0, 0x178 },
	{ "OpacityFadeTimeTwo", INI::parseReal, 0, 0x17C },
	{ "OpacityEnd", INI::parseUnsignedInt, 0, 0x180 },
	{ "StartingDelay", INI::parseReal, 0, 0x184 },
	{ "Lifetime", INI::parseReal, 0, 0x188 },
	{ 0, 0, 0, 0 }
};

// retail .rdata 0x007DCEB8 (13 entries + terminator)
extern const FieldParse BuffNuggetFXNuggetFieldParse[] =
{
	{ "BuffType", INI::parseIndexList, BuffTypeNames, 0x148 },
	{ "IsComplexBuff", INI::parseBool, 0, 0x14C },
	{ "BuffThingTemplate", INI::parseAsciiString, 0, 0x154 },
	{ "BuffOrcTemplate", INI::parseAsciiString, 0, 0x158 },
	{ "BuffInfantryTemplate", INI::parseAsciiString, 0, 0x15C },
	{ "BuffCavalryTemplate", INI::parseAsciiString, 0, 0x160 },
	{ "BuffTrollTemplate", INI::parseAsciiString, 0, 0x164 },
	{ "BuffMumakilTemplate", INI::parseAsciiString, 0, 0x168 },
	{ "BuffShipTemplate", INI::parseAsciiString, 0, 0x16C },
	{ "BuffMonsterTemplate", INI::parseAsciiString, 0, 0x170 },
	{ "BuffLifeTime", INI::parseDurationUnsignedInt, 0, 0x150 },
	{ "Extrusion", INI::parseReal, 0, 0x174 },
	{ "Color", INI::parseRGBColor, 0, 0x178 },
	{ 0, 0, 0, 0 }
};

// retail .rdata 0x007DCFD8 (3 entries + terminator)
extern const FieldParse LaserFXNuggetFieldParse[] =
{
	{ "LaserName", INI::parseAsciiString, 0, 0x148 },
	{ "LaserBackwards", INI::parseBool, 0, 0x14C },
	{ "TargetPositionOffsetFallback", INI::parseCoord3D, 0, 0x150 },
	{ 0, 0, 0, 0 }
};

// retail .rdata 0x007DD040 (3 entries + terminator)
extern const FieldParse CameraShakerVolumeFXNuggetFieldParse[] =
{
	{ "Radius", INI::parseReal, 0, 0x154 },
	{ "Duration_Seconds", INI::parseReal, 0, 0x158 },
	{ "Amplitude_Degrees", INI::parseReal, 0, 0x15C },
	{ 0, 0, 0, 0 }
};

// retail .rdata 0x007DD118 (3 entries + terminator)
extern const FieldParse AttachedModelFXNuggetFieldParse[] =
{
	{ "Modelname", INI::parseAsciiString, 0, 0x148 },
	{ "RandomlyRotate", INI::parseBool, 0, 0x14C },
	{ "ExpireTimer", INI::parseInt, 0, 0x150 },
	{ 0, 0, 0, 0 }
};

// retail .rdata 0x007DD278 (6 entries + terminator)
extern const FieldParse TintDrawableFXNuggetFieldParse[] =
{
	{ "Color", Rva001DFC2AParse, 0, 0x148 },
	{ "PreColorTime", INI::parseUnsignedInt, 0, 0x154 },
	{ "PostColorTime", INI::parseUnsignedInt, 0, 0x158 },
	{ "SustainedColorTime", INI::parseUnsignedInt, 0, 0x15C },
	{ "Frequency", INI::parseReal, 0, 0x160 },
	{ "Amplitude", INI::parseReal, 0, 0x164 },
	{ 0, 0, 0, 0 }
};

// retail .rdata 0x007DD2F8 (2 entries + terminator)
extern const FieldParse FXListAtBonePosFXNuggetFieldParse[] =
{
	{ "FX", INI::parseFXList, 0, 0x148 },
	{ "BoneName", INI::parseAsciiString, 0, 0x14C },
	{ 0, 0, 0, 0 }
};

// retail .rdata 0x007DD428 (24 entries + terminator)
extern const FieldParse ParticleSystemFXNuggetFieldParse[] =
{
	{ "Name", INI::parseAsciiString, 0, 0x148 },
	{ "Count", INI::parseInt, 0, 0x14C },
	{ "Offset", INI::parseCoord3D, 0, 0x150 },
	{ "Radius", INI::parseGameClientRandomVariable, 0, 0x15C },
	{ "Height", INI::parseGameClientRandomVariable, 0, 0x168 },
	{ "InitialDelay", INI::parseGameClientRandomVariable, 0, 0x174 },
	{ "RotateX", INI::parseAngleReal, 0, 0x180 },
	{ "RotateY", INI::parseAngleReal, 0, 0x184 },
	{ "RotateZ", INI::parseAngleReal, 0, 0x188 },
	{ "OrientToObject", INI::parseBool, 0, 0x18C },
	{ "Ricochet", INI::parseBool, 0, 0x195 },
	{ "AttachToObject", INI::parseBool, 0, 0x18D },
	{ "AttachToBone", INI::parseAsciiString, 0, 0x190 },
	{ "CreateAtGroundHeight", INI::parseBool, 0, 0x194 },
	{ "CreateBoneOverride", INI::parseAsciiString, 0, 0x198 },
	{ "CreateBoneAtTarget", INI::parseBool, 0, 0x1A0 },
	{ "TargetBoneOverride", INI::parseAsciiString, 0, 0x19C },
	{ "TargetCoeff", INI::parseReal, 0, 0x1A4 },
	{ "SystemLife", INI::parseInt, 0, 0x1A8 },
	{ "UseTargetOffset", INI::parseBool, 0, 0x1AC },
	{ "SetTargetMatrix", INI::parseBool, 0, 0x1AD },
	{ "TargetOffset", INI::parseCoord3D, 0, 0x1B0 },
	{ "OnlyIfOnLand", INI::parseBool, 0, 0x1AE },
	{ "OnlyIfOnWater", INI::parseBool, 0, 0x1AF },
	{ 0, 0, 0, 0 }
};

// retail .rdata 0x007DD600 (6 entries + terminator)
extern const FieldParse CursorParticleSystemFXNuggetFieldParse[] =
{
	{ "Anim2DTemplateName", INI::parseAsciiString, 0, 0x148 },
	{ "BurstCount", INI::parseUnsignedInt, 0, 0x14C },
	{ "ParticleLife", INI::parseGameClientRandomVariable, 0, 0x150 },
	{ "SystemLife", INI::parseGameClientRandomVariable, 0, 0x15C },
	{ "DriftVelX", INI::parseGameClientRandomVariable, 0, 0x168 },
	{ "DriftVelY", INI::parseGameClientRandomVariable, 0, 0x174 },
	{ 0, 0, 0, 0 }
};

// retail .rdata 0x007DD7F4 (1 entry + terminator)
extern const FieldParse ViewShakeFXNuggetFieldParse[] =
{
	{ "Type", parseShakeType, 0, 0x148 },
	{ 0, 0, 0, 0 }
};

// retail .rdata 0x007DD8A0 (3 entries + terminator)
extern const FieldParse TerrainScorchFXNuggetFieldParse[] =
{
	{ "Type", parseScorchType, 0, 0x148 },
	{ "Radius", INI::parseReal, 0, 0x14C },
	{ "RandomRange", INI::parseICoord2D, 0, 0x150 },
	{ 0, 0, 0, 0 }
};
