// cl: /Ireference/shims/bfme2_ascii -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/GameEngine/Source/GameClient
// Open-BFME5: lift the ParseObjectsDataChunk MASM dump to clean C++.
//
// Zero Hour's version is MapUtil.cpp:178 and BFME kept the shape, but changed
// registerParser: retail passes `info` itself and a trailing zero where the
// reference passes info->label and stops at three arguments.
//
// MSVC reuses the dead first-parameter slot for the AsciiString temporary, which
// is why the constructor's `this` and the later destructor both point at the
// incoming argument area rather than at fresh stack.

class DataChunkInput;
struct DataChunkInfo;
class AsciiString;
class UserParser;

#include "string_base.h"

// class-gate: allow AsciiString the donor's TU-local StringBase-derived view; retail reuses the dead first-parameter slot for this temporary, so its constructor and destructor must be exactly this inline pair
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

typedef bool (*DataChunkParser)(DataChunkInput &file, DataChunkInfo *info, void *userData);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
#include "../../Include/Common/DataChunk.h"

bool ParseObjectDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData);

// ?ParseObjectsDataChunk@@YA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z
bool ParseObjectsDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	file.m_currentObject = 0;
	file.registerParser(AsciiString("Object"), *(const AsciiString *)info, ParseObjectDataChunk, 0);

	return file.parse(userData);
}
