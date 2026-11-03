// cl: /DNDEBUG /MD
//
// ?q4Notify002CC7DE@@YAXPAXPAVMade002CC7DE@@HH@Z @0x005095AE (77B).
// WeaponOCLNugget field parser: MultiIni tmp, add table from getter
// 0x00507552 with index 0, add FieldParse table at 0x00864568 with
// index 0, then INI initFromINIMulti. Caller parseWeaponOCLNugget
// at 0x002CC823. Same tail as q4Notify002CCBCA precedent.

class Made002CC7DE;

class INI;

#include "../../../Include/Common/INI/FieldParse.h"

int __cdecl Rva00507552Get();


#include "../../../Include/Common/INI/INI.h"

// The table pushed at 0x00C64568 (.rdata): 1 16-byte records and the
// null terminator read from retail, parsers resolved to their ledger
// names, userData null, nugget offsets 0x12C-0x12C. The table name is
// descriptive; the original spelling is unknown.
extern const FieldParse WeaponOCLFieldTable[] =
{
    { "WeaponOCLName", &INI::parseAsciiString,  0, 0x12C },
    { 0, 0, 0, 0 }
};

void q4Notify002CC7DE(void *ini, Made002CC7DE *nugget, int c, int d)
{
    MultiIniFieldParse m_fieldParse;
    m_fieldParse.add((const FieldParse *)Rva00507552Get(), 0);
    m_fieldParse.add(WeaponOCLFieldTable, 0);
    ((INI *)ini)->initFromINIMulti(nugget, m_fieldParse);
}
