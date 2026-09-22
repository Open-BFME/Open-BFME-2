// cl: /Ireference/shims/bfmelist /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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
struct FieldParse;
class MultiIniFieldParse
{
public:
	MultiIniFieldParse();
	void add(const FieldParse *f, unsigned int extraOffset = 0);
private:
	char m_storage[0x84];
};

class INI
{
public:
	void initFromINIMulti(void *what, const MultiIniFieldParse &parse);
};

class FXNugget;

class FXList
{
public:
	void addFXNugget(FXNugget *fxn) { m_nuggets.push_back(fxn); }
private:
	int m_unused00;
	_STL::list<FXNugget *> m_nuggets;	// +0x04
};

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
	static void buildFieldParse(MultiIniFieldParse &p);
	static void parse(INI *ini, void *instance, void *, const void *);
private:
	char m_pad[0x14C];
};

extern const FieldParse SoundFXNuggetFieldParse[];	// 0x00BDCB18

// ?buildFieldParse@SoundFXNugget@@SAXAAVMultiIniFieldParse@@@Z
void SoundFXNugget::buildFieldParse(MultiIniFieldParse &p)
{
	p.add(SoundFXNuggetFieldParse);
	p.add(FXNuggetFieldParse);
}

// ?parse@SoundFXNugget@@SAXPAVINI@@PAX1PBX@Z
void SoundFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	SoundFXNugget *nugget = new SoundFXNugget;
	MultiIniFieldParse p;
	buildFieldParse(p);
	ini->initFromINIMulti(nugget, p);
	((FXList *)instance)->addFXNugget(nugget);
}

// "EvaEvent": parse 0x001E12AD, news 0x154, ctor 0x001DFFFA, builder 0x001DFABF
class EvaEventFXNugget : public FXNugget
{
public:
	EvaEventFXNugget();
	static void buildFieldParse(MultiIniFieldParse &p);
	static void parse(INI *ini, void *instance, void *, const void *);
private:
	char m_pad[0x154];
};

extern const FieldParse EvaEventFXNuggetFieldParse[];	// 0x00BDCAD8

// ?buildFieldParse@EvaEventFXNugget@@SAXAAVMultiIniFieldParse@@@Z
void EvaEventFXNugget::buildFieldParse(MultiIniFieldParse &p)
{
	p.add(EvaEventFXNuggetFieldParse);
	p.add(FXNuggetFieldParse);
}

// ?parse@EvaEventFXNugget@@SAXPAVINI@@PAX1PBX@Z
void EvaEventFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	EvaEventFXNugget *nugget = new EvaEventFXNugget;
	MultiIniFieldParse p;
	buildFieldParse(p);
	ini->initFromINIMulti(nugget, p);
	((FXList *)instance)->addFXNugget(nugget);
}

// "RayEffect": parse 0x001E13A5, news 0x164, ctor 0x001E01B2, builder 0x001DFB01
class RayEffectFXNugget : public FXNugget
{
public:
	RayEffectFXNugget();
	static void buildFieldParse(MultiIniFieldParse &p);
	static void parse(INI *ini, void *instance, void *, const void *);
private:
	char m_pad[0x164];
};

extern const FieldParse RayEffectFXNuggetFieldParse[];	// 0x00BDCB58

// ?buildFieldParse@RayEffectFXNugget@@SAXAAVMultiIniFieldParse@@@Z
void RayEffectFXNugget::buildFieldParse(MultiIniFieldParse &p)
{
	p.add(RayEffectFXNuggetFieldParse);
	p.add(FXNuggetFieldParse);
}

// ?parse@RayEffectFXNugget@@SAXPAVINI@@PAX1PBX@Z
void RayEffectFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	RayEffectFXNugget *nugget = new RayEffectFXNugget;
	MultiIniFieldParse p;
	buildFieldParse(p);
	ini->initFromINIMulti(nugget, p);
	((FXList *)instance)->addFXNugget(nugget);
}

// "LightPulse": parse 0x001E1421, news 0x164, ctor 0x001E0321, builder 0x001DFB22
class LightPulseFXNugget : public FXNugget
{
public:
	LightPulseFXNugget();
	static void buildFieldParse(MultiIniFieldParse &p);
	static void parse(INI *ini, void *instance, void *, const void *);
private:
	char m_pad[0x164];
};

extern const FieldParse LightPulseFXNuggetFieldParse[];	// 0x00BDCBD8

// ?buildFieldParse@LightPulseFXNugget@@SAXAAVMultiIniFieldParse@@@Z
void LightPulseFXNugget::buildFieldParse(MultiIniFieldParse &p)
{
	p.add(LightPulseFXNuggetFieldParse);
	p.add(FXNuggetFieldParse);
}

// ?parse@LightPulseFXNugget@@SAXPAVINI@@PAX1PBX@Z
void LightPulseFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	LightPulseFXNugget *nugget = new LightPulseFXNugget;
	MultiIniFieldParse p;
	buildFieldParse(p);
	ini->initFromINIMulti(nugget, p);
	((FXList *)instance)->addFXNugget(nugget);
}

// "CameraShakerVolume": parse 0x001E1595, news 0x160, ctor 0x001E0714, builder 0x001DFBA6
class CameraShakerVolumeFXNugget : public FXNugget
{
public:
	CameraShakerVolumeFXNugget();
	static void buildFieldParse(MultiIniFieldParse &p);
	static void parse(INI *ini, void *instance, void *, const void *);
private:
	char m_pad[0x160];
};

extern const FieldParse CameraShakerVolumeFXNuggetFieldParse[];	// 0x00BDD040

// ?buildFieldParse@CameraShakerVolumeFXNugget@@SAXAAVMultiIniFieldParse@@@Z
void CameraShakerVolumeFXNugget::buildFieldParse(MultiIniFieldParse &p)
{
	p.add(CameraShakerVolumeFXNuggetFieldParse);
	p.add(FXNuggetFieldParse);
}

// ?parse@CameraShakerVolumeFXNugget@@SAXPAVINI@@PAX1PBX@Z
void CameraShakerVolumeFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	CameraShakerVolumeFXNugget *nugget = new CameraShakerVolumeFXNugget;
	MultiIniFieldParse p;
	buildFieldParse(p);
	ini->initFromINIMulti(nugget, p);
	((FXList *)instance)->addFXNugget(nugget);
}

// "ViewShake": parse 0x001E1611, news 0x14C, ctor 0x001E07DF, builder 0x001E0829
class ViewShakeFXNugget : public FXNugget
{
public:
	ViewShakeFXNugget();
	static void buildFieldParse(MultiIniFieldParse &p);
	static void parse(INI *ini, void *instance, void *, const void *);
private:
	char m_pad[0x14C];
};

extern const FieldParse ViewShakeFXNuggetFieldParse[];	// 0x00BDD7F4

// ?buildFieldParse@ViewShakeFXNugget@@SAXAAVMultiIniFieldParse@@@Z
void ViewShakeFXNugget::buildFieldParse(MultiIniFieldParse &p)
{
	p.add(ViewShakeFXNuggetFieldParse);
	p.add(FXNuggetFieldParse);
}

// ?parse@ViewShakeFXNugget@@SAXPAVINI@@PAX1PBX@Z
void ViewShakeFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	ViewShakeFXNugget *nugget = new ViewShakeFXNugget;
	MultiIniFieldParse p;
	buildFieldParse(p);
	ini->initFromINIMulti(nugget, p);
	((FXList *)instance)->addFXNugget(nugget);
}

// "AttachedModel": parse 0x001E168D, news 0x154, ctor 0x001E084A, builder 0x001DFBE8
class AttachedModelFXNugget : public FXNugget
{
public:
	AttachedModelFXNugget();
	static void buildFieldParse(MultiIniFieldParse &p);
	static void parse(INI *ini, void *instance, void *, const void *);
private:
	char m_pad[0x154];
};

extern const FieldParse AttachedModelFXNuggetFieldParse[];	// 0x00BDD118

// ?buildFieldParse@AttachedModelFXNugget@@SAXAAVMultiIniFieldParse@@@Z
void AttachedModelFXNugget::buildFieldParse(MultiIniFieldParse &p)
{
	p.add(AttachedModelFXNuggetFieldParse);
	p.add(FXNuggetFieldParse);
}

// ?parse@AttachedModelFXNugget@@SAXPAVINI@@PAX1PBX@Z
void AttachedModelFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	AttachedModelFXNugget *nugget = new AttachedModelFXNugget;
	MultiIniFieldParse p;
	buildFieldParse(p);
	ini->initFromINIMulti(nugget, p);
	((FXList *)instance)->addFXNugget(nugget);
}

// "TerrainScorch": parse 0x001E171C, news 0x158, ctor 0x001E08D9, builder 0x001E0965
class TerrainScorchFXNugget : public FXNugget
{
public:
	TerrainScorchFXNugget();
	static void buildFieldParse(MultiIniFieldParse &p);
	static void parse(INI *ini, void *instance, void *, const void *);
private:
	char m_pad[0x158];
};

extern const FieldParse TerrainScorchFXNuggetFieldParse[];	// 0x00BDD8A0

// ?buildFieldParse@TerrainScorchFXNugget@@SAXAAVMultiIniFieldParse@@@Z
void TerrainScorchFXNugget::buildFieldParse(MultiIniFieldParse &p)
{
	p.add(TerrainScorchFXNuggetFieldParse);
	p.add(FXNuggetFieldParse);
}

// ?parse@TerrainScorchFXNugget@@SAXPAVINI@@PAX1PBX@Z
void TerrainScorchFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	TerrainScorchFXNugget *nugget = new TerrainScorchFXNugget;
	MultiIniFieldParse p;
	buildFieldParse(p);
	ini->initFromINIMulti(nugget, p);
	((FXList *)instance)->addFXNugget(nugget);
}

// "ParticleSystem": parse 0x001E264F, news 0x1BC, ctor 0x001E0AEF, builder 0x001DFD15
class ParticleSystemFXNugget : public FXNugget
{
public:
	ParticleSystemFXNugget();
	static void buildFieldParse(MultiIniFieldParse &p);
	static void parse(INI *ini, void *instance, void *, const void *);
private:
	char m_pad[0x1BC];
};

extern const FieldParse ParticleSystemFXNuggetFieldParse[];	// 0x00BDD428

// ?buildFieldParse@ParticleSystemFXNugget@@SAXAAVMultiIniFieldParse@@@Z
void ParticleSystemFXNugget::buildFieldParse(MultiIniFieldParse &p)
{
	p.add(ParticleSystemFXNuggetFieldParse);
	p.add(FXNuggetFieldParse);
}

// ?parse@ParticleSystemFXNugget@@SAXPAVINI@@PAX1PBX@Z
void ParticleSystemFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	ParticleSystemFXNugget *nugget = new ParticleSystemFXNugget;
	MultiIniFieldParse p;
	buildFieldParse(p);
	ini->initFromINIMulti(nugget, p);
	((FXList *)instance)->addFXNugget(nugget);
}

// "FXListAtBonePos": parse 0x001E1814, news 0x150, ctor 0x001E0A57, builder 0x001DFCF4
class FXListAtBonePosFXNugget : public FXNugget
{
public:
	FXListAtBonePosFXNugget();
	static void buildFieldParse(MultiIniFieldParse &p);
	static void parse(INI *ini, void *instance, void *, const void *);
private:
	char m_pad[0x150];
};

extern const FieldParse FXListAtBonePosFXNuggetFieldParse[];	// 0x00BDD2F8

// ?buildFieldParse@FXListAtBonePosFXNugget@@SAXAAVMultiIniFieldParse@@@Z
void FXListAtBonePosFXNugget::buildFieldParse(MultiIniFieldParse &p)
{
	p.add(FXListAtBonePosFXNuggetFieldParse);
	p.add(FXNuggetFieldParse);
}

// ?parse@FXListAtBonePosFXNugget@@SAXPAVINI@@PAX1PBX@Z
void FXListAtBonePosFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	FXListAtBonePosFXNugget *nugget = new FXListAtBonePosFXNugget;
	MultiIniFieldParse p;
	buildFieldParse(p);
	ini->initFromINIMulti(nugget, p);
	((FXList *)instance)->addFXNugget(nugget);
}

// "CursorParticleSystem": parse 0x001E26CB, news 0x180, ctor 0x001E0C90, builder 0x001DFD36
class CursorParticleSystemFXNugget : public FXNugget
{
public:
	CursorParticleSystemFXNugget();
	static void buildFieldParse(MultiIniFieldParse &p);
	static void parse(INI *ini, void *instance, void *, const void *);
private:
	char m_pad[0x180];
};

extern const FieldParse CursorParticleSystemFXNuggetFieldParse[];	// 0x00BDD600

// ?buildFieldParse@CursorParticleSystemFXNugget@@SAXAAVMultiIniFieldParse@@@Z
void CursorParticleSystemFXNugget::buildFieldParse(MultiIniFieldParse &p)
{
	p.add(CursorParticleSystemFXNuggetFieldParse);
	p.add(FXNuggetFieldParse);
}

// ?parse@CursorParticleSystemFXNugget@@SAXPAVINI@@PAX1PBX@Z
void CursorParticleSystemFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	CursorParticleSystemFXNugget *nugget = new CursorParticleSystemFXNugget;
	MultiIniFieldParse p;
	buildFieldParse(p);
	ini->initFromINIMulti(nugget, p);
	((FXList *)instance)->addFXNugget(nugget);
}

// "DynamicDecal": parse 0x001E149D, news 0x18C, ctor 0x001E0429, builder 0x001DFB43
class DynamicDecalFXNugget : public FXNugget
{
public:
	DynamicDecalFXNugget();
	static void buildFieldParse(MultiIniFieldParse &p);
	static void parse(INI *ini, void *instance, void *, const void *);
private:
	char m_pad[0x18C];
};

extern const FieldParse DynamicDecalFXNuggetFieldParse[];	// 0x00BDCCF0

// ?buildFieldParse@DynamicDecalFXNugget@@SAXAAVMultiIniFieldParse@@@Z
void DynamicDecalFXNugget::buildFieldParse(MultiIniFieldParse &p)
{
	p.add(DynamicDecalFXNuggetFieldParse);
	p.add(FXNuggetFieldParse);
}

// ?parse@DynamicDecalFXNugget@@SAXPAVINI@@PAX1PBX@Z
void DynamicDecalFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	DynamicDecalFXNugget *nugget = new DynamicDecalFXNugget;
	MultiIniFieldParse p;
	buildFieldParse(p);
	ini->initFromINIMulti(nugget, p);
	((FXList *)instance)->addFXNugget(nugget);
}

// "Laser": parse 0x001E1519, news 0x15C, ctor 0x001E04DE, builder 0x001DFB85
class LaserFXNugget : public FXNugget
{
public:
	LaserFXNugget();
	static void buildFieldParse(MultiIniFieldParse &p);
	static void parse(INI *ini, void *instance, void *, const void *);
private:
	char m_pad[0x15C];
};

extern const FieldParse LaserFXNuggetFieldParse[];	// 0x00BDCFD8

// ?buildFieldParse@LaserFXNugget@@SAXAAVMultiIniFieldParse@@@Z
void LaserFXNugget::buildFieldParse(MultiIniFieldParse &p)
{
	p.add(LaserFXNuggetFieldParse);
	p.add(FXNuggetFieldParse);
}

// ?parse@LaserFXNugget@@SAXPAVINI@@PAX1PBX@Z
void LaserFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	LaserFXNugget *nugget = new LaserFXNugget;
	MultiIniFieldParse p;
	buildFieldParse(p);
	ini->initFromINIMulti(nugget, p);
	((FXList *)instance)->addFXNugget(nugget);
}

// "TintDrawable": parse 0x001E1798, news 0x168, ctor 0x001E0986, builder 0x001DFCD3
class TintDrawableFXNugget : public FXNugget
{
public:
	TintDrawableFXNugget();
	static void buildFieldParse(MultiIniFieldParse &p);
	static void parse(INI *ini, void *instance, void *, const void *);
private:
	char m_pad[0x168];
};

extern const FieldParse TintDrawableFXNuggetFieldParse[];	// 0x00BDD278

// ?buildFieldParse@TintDrawableFXNugget@@SAXAAVMultiIniFieldParse@@@Z
void TintDrawableFXNugget::buildFieldParse(MultiIniFieldParse &p)
{
	p.add(TintDrawableFXNuggetFieldParse);
	p.add(FXNuggetFieldParse);
}

// ?parse@TintDrawableFXNugget@@SAXPAVINI@@PAX1PBX@Z
void TintDrawableFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	TintDrawableFXNugget *nugget = new TintDrawableFXNugget;
	MultiIniFieldParse p;
	buildFieldParse(p);
	ini->initFromINIMulti(nugget, p);
	((FXList *)instance)->addFXNugget(nugget);
}

// "BuffNugget": parse 0x001E323B, news 0x190, ctor 0x001E2FCE, builder 0x001DFB64
class BuffNuggetFXNugget : public FXNugget
{
public:
	BuffNuggetFXNugget();
	static void buildFieldParse(MultiIniFieldParse &p);
	static void parse(INI *ini, void *instance, void *, const void *);
private:
	char m_pad[0x190];
};

extern const FieldParse BuffNuggetFXNuggetFieldParse[];	// 0x00BDCEB8

// ?buildFieldParse@BuffNuggetFXNugget@@SAXAAVMultiIniFieldParse@@@Z
void BuffNuggetFXNugget::buildFieldParse(MultiIniFieldParse &p)
{
	p.add(BuffNuggetFXNuggetFieldParse);
	p.add(FXNuggetFieldParse);
}

// ?parse@BuffNuggetFXNugget@@SAXPAVINI@@PAX1PBX@Z
void BuffNuggetFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	BuffNuggetFXNugget *nugget = new BuffNuggetFXNugget;
	MultiIniFieldParse p;
	buildFieldParse(p);
	ini->initFromINIMulti(nugget, p);
	((FXList *)instance)->addFXNugget(nugget);
}
