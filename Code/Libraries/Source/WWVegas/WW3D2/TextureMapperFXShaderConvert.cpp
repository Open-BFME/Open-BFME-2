// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB
// The BFME2 texture mappers' FXShader conversion virtual (vtable +0x20; WB 0x00A33B70 by its
// strings): each checks its own Mapper_ID, rejects unsupported stages or options through the
// debug report, and otherwise appends a "TexCoordMapper_<stage>" int parameter and a vector
// parameter to the FXShader parameter list (rowed append 0x00082EB8 of the 36-byte record built
// by 0x001512F1). Scale (0x00187690) passes its scale, LinearOffset (0x00187850) adds the UV
// offset rate per second, Grid (0x00187AD0) the animation FPS, row width, last frame and frame
// offset. Stage reads go through the WW3D Get_Stage accessor, which decides the register
// choice of the second parameter block. The conversion's original name is not recovered.
// Keep MSVC's float overloads local; the inlined fabs operations remain exact.
#define inline static inline
#include <math.h>
#undef inline
#include "ascii_string.h"

bool bfmeRva000387C0();
void _bfme_debugRecordCallsite(int kind);

class Debug
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual Debug &slot38(const char *text);
	virtual void slot3C(); virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual void slot4C(int report);
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60();
	virtual void slot64(); virtual void slot68();
	virtual Debug &slot6C(int first, int second, int third);
};
extern Debug *theDebug;

struct Rva0007BB16Record
{
	~Rva0007BB16Record();
};

// The 36-byte FXShader parameter record: name and type through the rowed
// constructor, the float vector value at +0x0C and the integer value at +0x1C.
#include "../WWMath/Vector4Data.h"
struct BfmeAssignRecord36
{
	BfmeAssignRecord36(const char *name, int type);
	unsigned char m_prefix[12];
	Vector4 m_vector;
	int m_int;
	int m_20;
};
struct Rva00082EB8Rec;
struct FXOwnedParameter
{
	BfmeAssignRecord36 record;
	FXOwnedParameter(const char *name, int type) : record(name, type) {}
	~FXOwnedParameter() { reinterpret_cast<Rva0007BB16Record *>(&record)->Rva0007BB16Record::~Rva0007BB16Record(); }
	const Rva00082EB8Rec &rec() const { return *reinterpret_cast<const Rva00082EB8Rec *>(this); }
};
class Rva00082EB8 { public: void rva00082EB8(const Rva00082EB8Rec &); };

#define FX_CONVERSION_FAILED(text) 	if (bfmeRva000387C0()) 	{ 		_bfme_debugRecordCallsite(1); 		theDebug->slot60(); 		theDebug->slot6C(0, 0, 0).slot38(text).slot4C(2); 	}

class ScaleTextureMapperClass
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual int Mapper_ID(void) const;
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual bool rva00187690(Rva00082EB8 *parameters);
	int Get_Stage(void) const { return Stage; }

protected:
	int NumRefs;
	int Stage;
	float ScaleX;
	float ScaleY;
};

bool ScaleTextureMapperClass::rva00187690(Rva00082EB8 *parameters)
{
	if (Mapper_ID() == 8)
	{
		if (Get_Stage() > 1)
		{
			FX_CONVERSION_FAILED("FXShader conversion: Scale texture mapper supported in stage 0 or 1 only")
		}
		else
		{
		{
			AsciiString mapperName;
			mapperName.format("TexCoordMapper_%d", Get_Stage());
			FXOwnedParameter parameter(mapperName.str(), 6);
			parameter.record.m_int = 1;
			parameters->rva00082EB8(parameter.rec());
		}
		{
			AsciiString transformName;
			transformName.format("TexCoordTransform_%d", Get_Stage());
			FXOwnedParameter parameter(transformName.str(), 5);
			parameter.record.m_vector.X = ScaleX;
			parameter.record.m_vector.Y = ScaleY;
			parameter.record.m_vector.Z = 0.0f;
			parameter.record.m_vector.W = 0.0f;
			parameters->rva00082EB8(parameter.rec());
		}
		return true;
		}
	}
	return false;
}

class LinearOffsetTextureMapperClass
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual int Mapper_ID(void) const;
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual bool rva00187850(Rva00082EB8 *parameters);
	int Get_Stage(void) const { return Stage; }

protected:
	int NumRefs;
	int Stage;
	float ScaleX;
	float ScaleY;
	float CurrentUVOffsetX;
	float CurrentUVOffsetY;
	float UVOffsetDeltaPerMSX;
	float UVOffsetDeltaPerMSY;
	unsigned int LastUsedSyncTime;
	float UOffset;
	float VOffset;
	bool ClampFix;
};

bool LinearOffsetTextureMapperClass::rva00187850(Rva00082EB8 *parameters)
{
	if (Mapper_ID() == 1)
	{
		if (Stage > 1)
		{
			FX_CONVERSION_FAILED("FXShader conversion: LinearOffset texture mapper supported in stage 0 or 1 only")
		}
		else if (fabs(UOffset) > 0.001 || fabs(VOffset) > 0.001)
		{
			FX_CONVERSION_FAILED("FXShader conversion: Can't convert LinearOffset texture mapper due to non-zero UOffset or VOffset value")
		}
		else if (ClampFix)
		{
			FX_CONVERSION_FAILED("FXShader conversion: Can't convert LinearOffset texture mapper due to usage of ClampFix option")
		}
		else
		{
			{
				AsciiString mapperName;
				mapperName.format("TexCoordMapper_%d", Get_Stage());
				FXOwnedParameter parameter(mapperName.str(), 6);
				parameter.record.m_int = 1;
				parameters->rva00082EB8(parameter.rec());
			}
			{
				AsciiString transformName;
				transformName.format("TexCoordTransform_%d", Get_Stage());
				FXOwnedParameter parameter(transformName.str(), 5);
				parameter.record.m_vector.X = ScaleX;
				parameter.record.m_vector.Y = ScaleY;
				parameter.record.m_vector.Z = UVOffsetDeltaPerMSX * 1000.0f;
				parameter.record.m_vector.W = UVOffsetDeltaPerMSY * 1000.0f;
				parameters->rva00082EB8(parameter.rec());
			}
			return true;
		}
	}
	return false;
}

class GridTextureMapperClass
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual int Mapper_ID(void) const;
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual bool rva00187AD0(Rva00082EB8 *parameters);
	int Get_Stage(void) const { return Stage; }

protected:
	int NumRefs;
	int Stage;
	float FPS;
	unsigned int m_10;
	unsigned int m_14;
	unsigned int m_18;
	unsigned int LogGridWidth;
	unsigned int LastFrame;
	unsigned int FrameOffset;
};

bool GridTextureMapperClass::rva00187AD0(Rva00082EB8 *parameters)
{
	if (Mapper_ID() != 9)
		return false;
	if (Get_Stage() > 0)
	{
		FX_CONVERSION_FAILED("FXShader conversion: Grid texture mapper supported in stage 0 only")
		return false;
	}
	{
		AsciiString mapperName;
		mapperName.format("TexCoordMapper_%d", Get_Stage());
		FXOwnedParameter parameter(mapperName.str(), 6);
		parameter.record.m_int = 2;
		parameters->rva00082EB8(parameter.rec());
	}
	{
		AsciiString animationName;
		animationName.format("TextureAnimation_FPS_NumPerRow_LastFrame_FrameOffset_%d", Get_Stage());
		FXOwnedParameter parameter(animationName.str(), 5);
		parameter.record.m_vector.X = FPS;
		parameter.record.m_vector.Y = (float)(1 << LogGridWidth);
		parameter.record.m_vector.Z = (float)LastFrame;
		parameter.record.m_vector.W = (float)FrameOffset;
		parameters->rva00082EB8(parameter.rec());
	}
	return true;
}
