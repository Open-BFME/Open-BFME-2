// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?Rva002A92F2Parse@@YAXPAVINI@@@Z, retail 0x002A92F2 115B (EH).
// The "AIDozerAssignment" block parser (registration VA 0x00DBBC1C in
// Rva007ABBF6BlockParseInits.cpp; table entry 0x009BBC24 next to the
// SkirmishAIData parser Rva002A8A31Parse). Reads a stack pair of AsciiStrings
// (the rowed ??1Rva002A8BB9 0x002A8BB9 tears it down) with the rowed
// INI::initFromINI against the field table at VA 0x00BFD7C0 (two string
// fields at +0 and +4). It keys the first string through
// TheNameKeyGenerator (rowed nameToKey 0x0009FA65) and stores the second
// into the +0x920 key-to-string map of the singleton at 0x00DFEEF8 (rowed
// operator[] style lookup rva002A9140 0x002A9140 then AsciiString assignment).
// Identities unproven; address-derived names.
#include "ascii_string.h"

struct FieldParse;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Rva002A9140
{
public:
	AsciiString &rva002A9140(const int &key);
};

class Rva002A8F24
{
public:
	char m_unreconstructed_00[0x920];
	Rva002A9140 m_dozerAssignments; // +0x920
};

extern Rva002A8F24 *g_00DFEEF8;
extern const FieldParse AIDozerAssignmentFields[];

class Rva002A8BB9
{
public:
	Rva002A8BB9() {}
	~Rva002A8BB9();

	AsciiString m_0;
	AsciiString m_4;
};

void Rva002A92F2Parse(INI *ini)
{
	Rva002A8BB9 entry;
	ini->initFromINI(&entry, AIDozerAssignmentFields);
	int key = TheNameKeyGenerator->nameToKey(entry.m_0);
	g_00DFEEF8->m_dozerAssignments.rva002A9140(key) = entry.m_4;
}
