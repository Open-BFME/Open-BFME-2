// Identity correction: FXListDie factory 0x253AB4 pushes parser 0x253A92.
// This distinct 0x50B107 parser retains an address-derived name; the former
// FXListDie attribution is withdrawn. Its three table registrations are exact.
// Rva0050B107::buildFieldParse -- registers the module's INI field
// tables with the shared MultiIniFieldParse walker. Retail (0x50B107, 51B)
// issues three add() calls: two via the DieMuxData table getters
// (pins 0x507552/0x5088C8, each returning a .data table address) and one
// naming a .data FieldParse table directly (0xC64C08, DIR32-patched).

#include "../../../../Include/Common/INI/FieldParse.h"


struct Rva00507552
{
	static void *opaqueCall();
};

struct Rva005088C8
{
	static void *opaqueCall();
};

static const FieldParse s_extraFieldTable;

class Rva0050B107
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@Rva0050B107@@SAXAAVMultiIniFieldParse@@@Z @0x0050B107
void Rva0050B107::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add((const FieldParse *)Rva00507552::opaqueCall(), 0);
	parse.add((const FieldParse *)Rva005088C8::opaqueCall(), 0);
	parse.add(&s_extraFieldTable, 0);
}
