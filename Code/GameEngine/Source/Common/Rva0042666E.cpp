// cl: /MD
// ?rva0042666E@Rva0042666E@@QAEXPAVINI@@@Z @0x0042666E 18B evidence: caller 0x426D4D passes new 0x10 object in ecx plus INI block in ebx; forwards to rowed INI initFromINI 0x2DE78 with FieldParse table g_00C3C398
class INI;
typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
#include "../../Include/Common/INI/FieldParse.h"

#include "../../Include/Common/INI/INI.h"

extern "C" {
void __identifier("?Rva0042700FParse@@YAXPAVINI@@HPAV?$vector@UBfmeStringRecord00426A5B@@V?$allocator@UBfmeStringRecord00426A5B@@@_STL@@@_STL@@H@Z")();
void __identifier("?Rva00427068Parse@@YAXPAVINI@@HPAV?$vector@UBfmeStringRecord00426A5B@@V?$allocator@UBfmeStringRecord00426A5B@@@_STL@@@_STL@@H@Z")();
}
// The retail table at 0x0083C398: 2 entries and the null terminator; every parser is a rowed code owner.
extern const FieldParse g_00C3C398[3] = {
	{ "MissionObjectiveTag", (FieldParseProc)&__identifier("?Rva0042700FParse@@YAXPAVINI@@HPAV?$vector@UBfmeStringRecord00426A5B@@V?$allocator@UBfmeStringRecord00426A5B@@@_STL@@@_STL@@H@Z"), 0, 0x4 },
	{ "BonusMissionObjectiveTag", (FieldParseProc)&__identifier("?Rva00427068Parse@@YAXPAVINI@@HPAV?$vector@UBfmeStringRecord00426A5B@@V?$allocator@UBfmeStringRecord00426A5B@@@_STL@@@_STL@@H@Z"), 0, 0x4 },
	{ 0, 0, 0, 0 }
};

class Rva0042666E
{
public:
	void rva0042666E(class INI *ini);
};

void Rva0042666E::rva0042666E(class INI *ini)
{
	ini->initFromINI(this, g_00C3C398);
}
