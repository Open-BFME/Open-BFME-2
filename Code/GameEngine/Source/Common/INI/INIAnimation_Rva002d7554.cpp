// ?parseAnim2DDefinition@INI@@SAXPAV1@@Z, retail 0x002D7554, 114 bytes.
// Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/INI/INIAnimation.cpp (reference/open-bfme-1).
// The donor body does not place at BFME 1's flags; compiled /Os it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here; the donor's other
// definitions (parseAnim2DTemplate) are omitted.
//
// The collection pointer is the global TheAnim2DCollection at 0x00DFF068; when
// it is null the parse returns without touching the collection. findTemplate
// (retail 0x002D752D) is a tree walk returning null when the name is absent,
// and only then is newTemplate (retail 0x002D7283) called and initFromINI run
// against the static field-parse table.
//
// AsciiString comes from the shared compatibility shim, not a TU-local class:
// name.set(token) reaches the rowed StringBase<char>::set at 0x000055F5 and the
// scope exit the releaseBuffer worker at 0x00036410, both as retail calls them.
// cl: /Ireference/shims/bfme2_ascii -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common/INI

#include "ascii_string.h"

typedef int Int;
struct FieldParse;

// BFME adds an integer after the message pointer; its meaning is unresolved.
class INIException
{
public:
	INIException(Int, const char *, ...);
	INIException(const INIException &);
	~INIException();

private:
	char *m_message;
	Int m_unreconstructed04;
};

class Anim2DTemplate
{
public:
	static const FieldParse s_anim2DFieldParseTable[];
};

class Anim2DCollection
{
public:
	Anim2DTemplate *findTemplate(const AsciiString &name);
	Anim2DTemplate *newTemplate(const AsciiString &name);
};

extern Anim2DCollection *TheAnim2DCollection;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	void initFromINI(void *what, const FieldParse *parseTable);
	static void parseAnim2DDefinition(INI *ini);
};

// ?parseAnim2DDefinition@INI@@SAXPAV1@@Z
void INI::parseAnim2DDefinition( INI *ini )
{
	AsciiString name;
	Anim2DTemplate *animTemplate;

	const char *token = ini->getNextToken();
	name.set( token );

	if( !TheAnim2DCollection )
		return;

	animTemplate = TheAnim2DCollection->findTemplate( name );
	if( animTemplate == 0 )
	{
		animTemplate = TheAnim2DCollection->newTemplate( name );
		ini->initFromINI( animTemplate, Anim2DTemplate::s_anim2DFieldParseTable );
	}
}
