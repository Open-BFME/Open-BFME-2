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

#include "../../../Include/GameLogic/KindOfMaskType.h"

#include "ascii_string.h"


// Coord3D: shared header/view; no private copy.
#include "../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../Include/Common/DataChunkOutput.h"

#include "../../../Include/GameLogic/ScriptParameter.h"

// ?WriteParameter@Parameter@@QAEXAAVDataChunkOutput@@@Z
void Parameter::WriteParameter(DataChunkOutput &chunkWriter)
{
	chunkWriter.writeInt(m_paramType);
	if (m_paramType == KIND_OF_PARAM) {
		m_string.set(KindOfMaskType::getNameFromSingleBit(m_int));
	}
	if (m_paramType == COORD3D) {
		chunkWriter.writeReal(m_coord.x);
		chunkWriter.writeReal(m_coord.y);
		chunkWriter.writeReal(m_coord.z);
	} else {
		chunkWriter.writeInt(m_int);
		chunkWriter.writeReal(m_real);
		chunkWriter.writeAsciiString(m_string);
	}
}
