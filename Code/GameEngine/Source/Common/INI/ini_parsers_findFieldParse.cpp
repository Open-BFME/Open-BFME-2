// cl: /O1 /arch:SSE /Ob1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
//
// ?findFieldParse@@YAP6AXPAVINI@@PAX1PBX@ZPBUFieldParse@@PBDAAHAAPBX@Z
// retail 0x0002BC27, 71 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/Common/INI/ini_parsers.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /O1 it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
// stlport
// readable body of ??0DamDieModuleData@@: game/GameEngine/Source/GameLogic/Object/Die/DamDie.cpp
// readable body of ??0EjectPilotDieModuleData@@: game/GameEngine/Source/GameLogic/Object/Die/EjectPilotDie.cpp
// readable body of ??0HiveStructureBodyModuleData@@: game/GameEngine/Source/GameLogic/Object/Body/HiveStructureBody.cpp
// readable body of ??0JetAIUpdateModuleData@@: game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/JetAIUpdate.cpp
// readable body of ??0MinefieldBehaviorModuleData@@: game/GameEngine/Source/GameLogic/Object/Behavior/MinefieldBehavior.cpp
// readable body of ??0RailedTransportDockUpdateModuleData@@QAE@XZ: game/GameEngine/Source/GameLogic/Object/Update/DockUpdate/RailedTransportDockUpdate.cpp
// readable body of ??0RebuildHoleExposeDieModuleData@@: game/GameEngine/Source/GameLogic/Object/Die/RebuildHoleExposeDie.cpp
// readable body of ??0W3DModelDrawModuleData@@QAE@XZ: game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDraw.cpp
// readable body of ??0W3DOverlordAircraftDrawModuleData@@: game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DOverlordAircraftDraw.cpp
// readable body of ?getNextSubToken@INI@@: game/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?initFromINI@INI@@: game/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?initFromINIMultiProc@INI@@: game/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseAngleReal@INI@@: game/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseAsciiStringVector@INI@@: game/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseAsciiStringVectorAppend@INI@@: game/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseBitInInt32@INI@@: game/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseBool@INI@@: game/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseByteSizedIndexList@INI@@: game/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseColorInt@INI@@: game/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseIndexList@INI@@: game/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseInt@INI@@: game/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseLookupList@INI@@: game/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parsePercentToReal@INI@@: game/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parsePositiveNonZeroReal@INI@@: game/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseRGBAColorInt@INI@@: game/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseRGBColor@INI@@: game/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseReal@INI@@: game/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseShort@INI@@: game/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseUnsignedByte@INI@@: game/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseUnsignedInt@INI@@: game/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseUnsignedShort@INI@@: game/GameEngine/Source/Common/INI/INI_stl.cpp
//
// The other half of retail's INI reader. BFME compiles INI's field parsers in
// two translation units and the split is visible in the binary: these eleven sit
// at 0x00851050..0x00852E60 and INLINE INI::getNextToken (each carries its own
// "Expected additional data after '%s'" throw), while the template/store parsers
// -- parseScience, parseThingTemplate, parseFXList and friends -- sit in a
// different arena at 0x000B8E80..0x000BB040 and CALL it out of line. A single TU
// cannot produce both, so ini.cpp keeps that group and this file takes this one.
//
#include <string.h>
#include "ascii_string.h"

class INI;

typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);

struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

static INIFieldParseProc findFieldParse(const FieldParse *parseTable, const char *token, int &offset, const void *&userData)
{
	const FieldParse *parse;
	for (parse = parseTable; parse->token; ++parse)
	{
		if (strcmp(parse->token, token) == 0)
		{
			offset = parse->offset;
			userData = parse->userData;
			return parse->parse;
		}
	}

	if (!parse->token && parse->parse)
	{
		offset = parse->offset;
		userData = token;
		return parse->parse;
	}
	else
	{
		return 0;
	}
}

// Retail's element here is AsciiString, but the vector<AsciiString> COMDAT this
// TU reaches is the copy at 0x00063700 -- the one whose element copy calls
// StringBase<char>'s constructor out of line, which 38 retail sites encode. The
// ledger names that instantiation after its address, so spell the element with
// that name or the REL32 resolver walks to the other copy at 0x00757C70.
class Open2Elem063700
{
public:
	Open2Elem063700( const Open2Elem063700 &source )
	{
		((AsciiString *)this)->AsciiString::AsciiString( *(const AsciiString *)&source );
	}

	~Open2Elem063700()
	{
		((AsciiString *)this)->AsciiString::~AsciiString();
	}

private:
	void *m_text;
};

// Emission anchor: findFieldParse is static and its callers are not carried here.
// MSVC gives a static whose address is never taken a register calling
// convention, so it is kept alive by direct calls. Build scaffolding; it
// claims no retail bytes.
// ?findFieldParseAnchor absent-from-retail
INIFieldParseProc findFieldParseAnchor(const FieldParse* parseTable, const char* token, int& offset, const void*& userData)
{
	findFieldParse(parseTable, token, offset, userData);
	return findFieldParse(parseTable, token, offset, userData);
}
