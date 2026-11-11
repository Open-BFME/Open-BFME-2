// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?parseAIDozerAssignmentDefinition@@YAXPAVINI@@@Z, retail 0x002A92F2 115B (EH).
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

#include "../../../Include/Common/INI/INI.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

#include "../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

#include "../../../../Libraries/Source/WWVegas/WWLib/Rva002A9140.h"

#include "../../../Include/GameLogic/Rva002A8F24.h"

// The canonical header keeps +0x920 opaque (m_pad91C): reach the
// dozer-assignment map there through a TU-local view.
static __forceinline Rva002A9140 &skirmishDozerAssignments(Rva002A8F24 *manager)
{
	return *(Rva002A9140 *)&manager->m_pad91C[0x920 - 0x91C];
}

extern Rva002A8F24 *TheSkirmishAIManager;
extern const FieldParse AIDozerAssignmentFields[];

class Rva002A8BB9
{
public:
	Rva002A8BB9() {}
	~Rva002A8BB9();

	AsciiString m_0;
	AsciiString m_4;
};

void parseAIDozerAssignmentDefinition(INI *ini)
{
	Rva002A8BB9 entry;
	ini->initFromINI(&entry, AIDozerAssignmentFields);
	int key = TheNameKeyGenerator->nameToKey(entry.m_0);
	skirmishDozerAssignments(TheSkirmishAIManager).rva002A9140(key) = entry.m_4;
}
