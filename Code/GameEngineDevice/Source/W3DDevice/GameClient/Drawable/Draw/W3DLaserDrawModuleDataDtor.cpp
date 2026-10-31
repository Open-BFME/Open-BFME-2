// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata /ICode/GameEngine/Include/Common
// stlport
//
// ??1W3DLaserDrawModuleData@@UAE@XZ, retail 0x000C9AE7, 54 bytes.
// ModuleData dtor: reinstalls the vtable 0x00BCB960, tears down the Texture
// vector at +0x2C through the rowed vector<AsciiString> dtor at 0x0002CC70,
// then restores the Snapshot base vtable 0x00BBB554 through the shared base
// dtor. Single EH state for the one vector member; frameless
// companion ctor at 0x000C9A6F proves the layout (vptr +0, vector +0x2C,
// size 0x74 per the factory at 0x00064962). Table 0x00BCB840 names the
// members; the ??_G caller at 0x000C9CC9 is the slot-0 deleting dtor. Shape
// follows the landed W3DLightDrawModuleDataDtor and W3DStreakDrawModuleDataDtor
// TUs; the own vtable resolves through the ??_7 pin at 0x00BCB960.

#include <vector>

class Xfer;
#include "Common/Snapshot.h"
#include "BfmeModuleData.h"
// Vtable 0x00BCB960 is the shared 31-slot ModuleData table; teardown restores
// Snapshot's table 0x00BBB554 (as in Rva004ABFD9Dtor.cpp).
inline ModuleData::~ModuleData() { reinterpret_cast<Snapshot *>(this)->Snapshot::~Snapshot(); }

#include "ascii_string.h"

class MultiIniFieldParse;

typedef unsigned int Color;

typedef unsigned int UnsignedInt;

typedef float Real;

struct OrnamentData
{
	OrnamentData *init() throw();
	unsigned char m_pad00[0x0C];
	int m_reset0C;
	unsigned char m_pad10[0x24 - 0x10];
	int m_reset24;
};


class W3DLaserDrawModuleDataBase
{
public:
	W3DLaserDrawModuleDataBase()
		: m_innerColor((Color)-1),
		  m_outerColor((Color)-1)
	{
	}

private:
	unsigned char m_pad04[4];	// +0x04
	Color m_innerColor;		// +0x08 InnerColor
	Color m_outerColor;		// +0x0C OuterColor
};


class W3DLaserDrawModuleData : public ModuleData, public W3DLaserDrawModuleDataBase
{
public:
	W3DLaserDrawModuleData();
public:
	virtual ~W3DLaserDrawModuleData();
private:
	Real m_innerBeamWidth;
private:
	Real m_outerBeamWidth;
private:
	Real m_scrollRate;
private:
	bool m_tile;
private:
	UnsignedInt m_numBeams;
private:
	UnsignedInt m_maxIntensityFrames;
private:
	UnsignedInt m_fadeFrames;
private:
	_STL::vector<AsciiString> m_textureName; // +0x2C Texture
private:
	// +0x38..+0x73
	UnsignedInt m_segments;
private:
	Real m_arcHeight;
private:
	Real m_segmentOverlapRatio;
private:
	Real m_tilingScalar;
private:
	Real m_fanWidth;
private:
	OrnamentData m_envelope;
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

typedef char AsciiExtent[sizeof(AsciiString) == 4 ? 1 : -1];

W3DLaserDrawModuleData::~W3DLaserDrawModuleData()
{
}
