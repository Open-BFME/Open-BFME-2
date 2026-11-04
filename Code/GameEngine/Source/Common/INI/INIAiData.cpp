// cl: /DNDEBUG /MD
//
// INI::parseAIDataDefinition, retail 0x001D8E7A (5 bytes): Zero Hour's
// GameEngine/Source/Common/INI/INIAiData.cpp body unchanged, a tail jump to
// AI::parseAiDataDefinition (rowed at 0x002FFF72). Identity: the "AIData"
// BlockParse entry at 0x009B8938 (theAIDataBlockParse) holds this address in
// its parse slot.

#include "../../../Include/Common/INI/INI.h"

#include "../../../Include/GameLogic/AI.h"

void INI::parseAIDataDefinition(INI *ini)
{
	AI::parseAiDataDefinition(ini);
}

// INI block registration. BFME's INI keeps its block types on a list of
// 12-byte BlockParse nodes; each unit links its own nodes onto
// theBlockParseList from a file-scope object whose inline constructor does the
// link. MSVC 7.1 builds token and parse in .data, so each node's .text$yc
// initializer is only the 21-byte link (retail .CRT$XCU 0x007ACFD0,
// node 0x00DB8934).
typedef void (*INIBlockParse)( INI *ini );
extern struct BlockParse *theBlockParseList;
struct BlockParse
{
	BlockParse *next;
	const char *token;
	INIBlockParse parse;

	BlockParse( const char *token, INIBlockParse parse ) : next(theBlockParseList), token(token), parse(parse)
	{
		theBlockParseList = this;
	}
};

BlockParse theAIDataBlockParse( "AIData", INI::parseAIDataDefinition );
