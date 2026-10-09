// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// W3DShrubBuffer::addShrub, retail 0x000E91CE (1254 bytes, ret 0x2C). Donor: Open-BFME-1
// W3DShrubBufferRva00720D10.cpp (BFME1 0x00720D10). BFME2 layout read from retail.
#include "ascii_string.h"
#include "vector3.h"
#include "matrix3d.h"
#include "sphere.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"

// Retail's global at 0x012ED5C8 is EA's GlobalData *TheWritableGlobalData, defined
// once in Common/GlobalData.cpp. Only the field this body reads is described on a
// TU-local view; the real class is never redeclared.
class GlobalData;
struct Rva000E91CEGlobalData
{
	unsigned char m_pad00[0x1c];
	bool m_flag1c;
};

extern GlobalData *TheWritableGlobalData;

struct Rva000E91CEData
{
	unsigned char prefix[8];
	AsciiString modelName, nameC;
	unsigned int framesToMoveOutward;
	unsigned char gap14[0x3d - 0x14];
	bool doTopple;
	unsigned char gap3e[0x48 - 0x3e];
	AsciiString name48;
	unsigned char gap4c[8];
	bool flag54;
};

struct Rva000E91CEType
{
	void *mesh;
	Vector3 offset;
	SphereClass bounds;
	const Rva000E91CEData *data;
	unsigned char gap24[0x58 - 0x24];
	int field58;
};

struct Rva000E91CETree
{
	Vector3 location;
	float scale;
	Matrix3D transform;
	int treeType;
	bool visible;
	bool flag45;
	bool flag46;
	unsigned char alignment47;
	SphereClass bounds;
	unsigned int drawableID;
	float pushAside;
	float pushAsideDelta;
	float pushAsideSin;
	float pushAsideCos;
	unsigned int pushAsideSource;
	unsigned int lastFrame;
	int nextInPartition;
	int swayType;
	int firstIndex;
	int bufferIndex;
	int toppleState;
	int uprightType;
	int toppledType;
	unsigned int sinkFrames;
	void *toppleObject;
	void *pushAsideObject;
	int fielda0;
};

extern float GetGameClientRandomValueReal(float, float, char *, int);
extern int GetGameClientRandomValue(int, int, char *, int);

static inline void translateBounds(Vector3 &center, const Vector3 &position)
{
	// Preserve the observed x87 load order for this alias-sensitive aggregate update.
	const volatile float &x = position.X;
	center.X += x;
	center.Y = position.Y + center.Y;
	center.Z = position.Z + center.Z;
}

struct FloatPair
{
	float x;
	float y;
};

class W3DShrubBuffer
{
public:
	int addTreeType(const AsciiString &, const AsciiString &, const void *, int, const AsciiString &, const AsciiString &);
	int rva000E8F9D(const AsciiString &, int, const AsciiString &);
	void rva000E91CE(unsigned int id, Coord3D location, float scale, const Matrix3D *transform, float randomScaleAmount,
		const Rva000E91CEData *data, int shadowKind, const AsciiString &textureName, const AsciiString &nameD);
	int getPartitionBucket(const FloatPair *location);

private:
	unsigned char prefix[0x5c0];
	// Native DoXferE96B4 and WB898B00 clear2500 shorts; the following
	// four-float bounds at1948 are transferred separately atE9A8A.
	short areaPartition[2500];
	float bounds1948[4];
	Rva000E91CETree trees[2000];
	int numTrees;
	unsigned char gap4[2];
	bool changed;
	unsigned char gap7[0xd];
	bool initialized;
	unsigned char gap15[1];
	bool needUpdate;
	unsigned char gap17[1];
	Rva000E91CEType types[64];
	int numTypes;
};

// ?rva000E91CE@W3DShrubBuffer@@QAEXIUCoord3D@@MPBVMatrix3D@@MPBURva000E91CEData@@HABVAsciiString@@3@Z
void W3DShrubBuffer::rva000E91CE(unsigned int id, Coord3D location, float scale, const Matrix3D *transform,
	float randomScaleAmount, const Rva000E91CEData *data, int shadowKind, const AsciiString &textureName,
	const AsciiString &nameD)
{
	if (!((const Rva000E91CEGlobalData *)TheWritableGlobalData)->m_flag1c) return;
	if (numTrees >= 2000) return;
	if (!initialized) return;
	int type = -2;
	for (int i = 0; i < numTypes; ++i) {
		if (((const StringBase<char> *)&types[i].data->modelName)->compareNoCase(*(const StringBase<char> *)&data->modelName) == 0 &&
			((const StringBase<char> *)&types[i].data->nameC)->compareNoCase(*(const StringBase<char> *)&data->nameC) == 0) { type = i; break; }
	}
	if (type < 0) {
		type = addTreeType(data->modelName, data->nameC, data, shadowKind, textureName, nameD);
		if (type < 0) return;
		needUpdate = true;
	}
	types[type].field58 = rva000E8F9D(data->name48, shadowKind, textureName);
	if (data->framesToMoveOutward > 0 || data->doTopple) {
		short bucket = getPartitionBucket((const FloatPair *)&location);
		trees[numTrees].nextInPartition = areaPartition[bucket];
		areaPartition[bucket] = numTrees;
	} else {
		trees[numTrees].nextInPartition = -1;
	}
	float randomScale = GetGameClientRandomValueReal(1.0f - randomScaleAmount, 1.0f + randomScaleAmount,
		"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\W3DShrubBuffer.cpp", 0x32d);
	trees[numTrees].transform = *transform;
	if (randomScaleAmount > 0.0f) trees[numTrees].scale = scale * randomScale;
	else trees[numTrees].scale = scale;
	trees[numTrees].location = (const Vector3 &)location;
	trees[numTrees].treeType = type;
	trees[numTrees].uprightType = type;
	trees[numTrees].toppledType = types[type].field58;
	trees[numTrees].fielda0 = 1;
	trees[numTrees].bounds = types[type].bounds;
	{ float sc = trees[numTrees].scale; Vector3 &c = trees[numTrees].bounds.Center; c.X = sc * c.X; c.Y *= sc; c.Z *= sc; }
	trees[numTrees].bounds.Radius *= trees[numTrees].scale;
	translateBounds(trees[numTrees].bounds.Center, trees[numTrees].location);
	trees[numTrees].visible = false;
	trees[numTrees].drawableID = id;
	trees[numTrees].firstIndex = 0;
	trees[numTrees].bufferIndex = -1;
	trees[numTrees].swayType = data->flag54 ? 0 : GetGameClientRandomValue(1, 10,
		"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\W3DShrubBuffer.cpp", 0x348);
	trees[numTrees].pushAside = 0;
	trees[numTrees].lastFrame = 0;
	trees[numTrees].pushAsideSource = 0;
	trees[numTrees].pushAsideDelta = 0;
	trees[numTrees].pushAsideCos = 1;
	trees[numTrees].pushAsideSin = 1;
	trees[numTrees].toppleState = 0;
	trees[numTrees].toppleObject = 0;
	trees[numTrees].pushAsideObject = 0;
	trees[numTrees].flag45 = false;
	trees[numTrees].flag46 = false;
	trees[numTrees].sinkFrames = 0;
	++numTrees;
	changed = true;
}

