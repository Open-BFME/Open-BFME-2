// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// stlport
// INI::parseMappedImageDefinition @0x001ED63C (178B): Zero Hour
// INIMappedImage.cpp's body. Identity from the INI block table: the
// "MappedImage" token's entry names this address. The body reads the name
// token, returns without TheMappedImageCollection, looks the image up with
// the rowed findImageByName 0x002D92F6, and on a miss news a 0x34-byte Image
// (rowed ctor 0x002D8FE4), names it (the +0x04 AsciiString) and files it
// with the rowed addImage 0x002D9457. The image is filled from Image's
// field-parse table 0x00C036E8 (the ledger's g_00C036E8).
#include "ascii_string.h"

struct FieldParse;

#include "../../../Include/Common/INI/INI.h"

extern const FieldParse m_imageFieldParseTable[];

#include "../../../Include/GameClient/ImageClass.h"

#include "../../../Include/GameClient/Image.h"

void INI::parseMappedImageDefinition(INI *ini)
{
	AsciiString name;

	const char *c = ini->getNextToken();
	name.set(c);

	if (!TheMappedImageCollection)
	{
		return;
	}
	Image *image = const_cast<Image *>(TheMappedImageCollection->findImageByName(name));

	if (image == 0)
	{
		image = new Image;
		image->setName(name);
		TheMappedImageCollection->addImage(image);
	}

	ini->initFromINI(image, image->getFieldParse());
}

// INI block registration. BFME's INI keeps its block types on a list of
// 12-byte BlockParse nodes; each unit links its own nodes onto
// theBlockParseList from a file-scope object whose inline constructor does the
// link. MSVC 7.1 builds token and parse in .data, so each node's .text$yc
// initializer is only the 21-byte link (retail .CRT$XCU 0x007AD37C,
// node 0x00DB9004).
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

BlockParse theMappedImageBlockParse( "MappedImage", INI::parseMappedImageDefinition );
