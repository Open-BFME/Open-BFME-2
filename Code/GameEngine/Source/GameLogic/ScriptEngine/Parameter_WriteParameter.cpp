// cl: /Ireference/shims/bfme2_ascii
//
// Parameter::WriteParameter, retail 0x003B3A38, 129 bytes.
//
// Ported from the exact BFME1 reconstruction
// (Code/GameEngine/Source/GameLogic/ScriptEngine/Parameter_WriteParameter_Thunk.cpp).
// BFME2 keeps the same Parameter layout (type at +0x00, int at +0x08,
// real at +0x0C, string at +0x10, coord at +0x14) and the same
// KindOf/COORD3D branches; the KindOf table grew from 181 to 218 entries
// (see KindOfGetNameFromSingleBit.cpp) and the float/string writers are
// out-of-line here.

typedef int Int;
typedef float Real;

enum { COORD3D = 0x10, KIND_OF_PARAM = 0x1B };

class KindOfMaskType
{
public:
	static const char *getNameFromSingleBit(int bitIndex);
};

#include "ascii_string.h"


struct Coord3D
{
	Real coordX;
	Real coordY;
	Real coordZ;
};

class DataChunkOutput
{
public:
	void writeInt(Int value);
	void writeReal(Real value);
	void writeAsciiString(const AsciiString &textValue);
};

class Parameter
{
public:
	void WriteParameter(DataChunkOutput &chunkWriter);

private:
	Int paramType; ///< retail this+0x00
	unsigned char gapParam04[4];
	Int intValue; ///< retail this+0x08
	Real realValue; ///< retail this+0x0C
	AsciiString stringValue; ///< retail this+0x10
	Coord3D coordValue; ///< retail this+0x14
};

// ?WriteParameter@Parameter@@QAEXAAVDataChunkOutput@@@Z
void Parameter::WriteParameter(DataChunkOutput &chunkWriter)
{
	chunkWriter.writeInt(paramType);
	if (paramType == KIND_OF_PARAM) {
		stringValue.set(KindOfMaskType::getNameFromSingleBit(intValue));
	}
	if (paramType == COORD3D) {
		chunkWriter.writeReal(coordValue.coordX);
		chunkWriter.writeReal(coordValue.coordY);
		chunkWriter.writeReal(coordValue.coordZ);
	} else {
		chunkWriter.writeInt(intValue);
		chunkWriter.writeReal(realValue);
		chunkWriter.writeAsciiString(stringValue);
	}
}
