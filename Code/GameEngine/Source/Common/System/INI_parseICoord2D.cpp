// cl: /Oy /DNDEBUG /MD /GX- /Oi-
//
// ?parseICoord2D@INI@@SAXPAV1@PAX1PBX@Z, retail 0x002F5BA, 58 bytes.
// Dedicated frameless TU (same INI verb family as INI_parseIndexList.cpp).
//
// BFME1 reference (reference/open-bfme-1/Code/GameEngine/Source/Common/INI/INI_stl.cpp,
// INI::parseICoord2D): X/Y via getNextSubToken plus scanInt into the two int
// slots. BFME2 is verbatim (the X/Y literals are folded with parseCoord2D's
// at 0x7BE3C8/0x7BE3C4). Name proven by the InGameUI FieldParse table
// (MessagePosition/MilitaryCaptionPosition).

struct ICoord2D
{
	int x;
	int y;
};

class INI
{
public:
	const char *getNextSubToken(const char *expected);
	int scanInt(const char *token);
	static void parseICoord2D(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseICoord2D@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseICoord2D(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	ICoord2D *theCoord = (ICoord2D *)store;

	theCoord->x = ini->scanInt(ini->getNextSubToken("X"));
	theCoord->y = ini->scanInt(ini->getNextSubToken("Y"));
}
