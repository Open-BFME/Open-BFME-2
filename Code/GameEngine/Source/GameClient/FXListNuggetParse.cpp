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
class MultiIniFieldParse
{
public:
	MultiIniFieldParse();
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

// ?parse@BuffNuggetFXNugget@@SAXPAVINI@@PAX1PBX@Z
void BuffNuggetFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	BuffNuggetFXNugget *nugget = new BuffNuggetFXNugget;
	MultiIniFieldParse p;
	buildFieldParse(p);
	ini->initFromINIMulti(nugget, p);
	((FXList *)instance)->addFXNugget(nugget);
}
