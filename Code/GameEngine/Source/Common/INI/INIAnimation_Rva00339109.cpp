// ?parseAnim2DTemplate@INI@@SAXPAV1@PAX1PBX@Z, retail 0x00339109, 123 bytes.
// Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/INI/INIAnimation.cpp (reference/open-bfme-1).
// The donor body does not place at BFME 1's flags; compiled /Os it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here; the donor's other
// definitions (parseAnim2DDefinition) are omitted.
//
// The callback stores the resolved template through the void* store slot and
// throws INIException(9, "iniParseAnim2DTemplate - TheAnim2DCollection is
// NULL") when the collection global at 0x00DFF068 is null. Unlike its sibling
// parseAnim2DDefinition, the name is passed straight to findTemplate as a
// temporary AsciiString (retail constructs it through the const-char ctor at
// 0x00037BA0) instead of being built with StringBase<char>::set.
//
// AsciiString comes from the shared compatibility shim, not a TU-local class,
// per the class gate; its release worker at 0x00036410 is this body's tail
// call, as in retail.
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

class Anim2DTemplate;

class Anim2DCollection
{
public:
	Anim2DTemplate *findTemplate(const AsciiString &name);
};

extern Anim2DCollection *TheAnim2DCollection;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	static void parseAnim2DTemplate(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseAnim2DTemplate@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseAnim2DTemplate(INI *ini, void *instance, void *store, const void *userData)
{
	const char *token = ini->getNextToken();

	if (TheAnim2DCollection)
	{
		Anim2DTemplate **anim2DTemplate = (Anim2DTemplate **)store;
		*anim2DTemplate = TheAnim2DCollection->findTemplate(AsciiString(token));
	}
	else
	{
		throw INIException(9, "iniParseAnim2DTemplate - TheAnim2DCollection is NULL");
	}
}
