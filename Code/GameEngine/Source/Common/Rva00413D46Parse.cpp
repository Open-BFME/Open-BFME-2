// cl: /DNDEBUG /MD /GX-
// ?rva00413D46@Rva00413D46@@QAEXPAVINI@@@Z, retail 0x00413D46, 18 bytes.
// INI table forward: ini->initFromINI(this) through table 0x00839D54 (rowed
// 0x0002DE78). Same recipe as sibling Rva00413DCCParse without the throw
// check. Evidence: unlock lane; retail push-imm plus push-ecx plus
// mov-ecx-[esp+0xc] plus call plus ret-4; caller 0x00413DA0.
struct FieldParse
{
 const char *name;
 void (*parse)(class INI *, void *, void *, const char *);
 const void *userData;
 int offset;
};
void Rva00413C02Parse(INI *, void *, void *, const char *);
#include "../../Include/Common/INI/INI.h"
// A single null-name default parser terminates this table. The
// callback's fourth argument is the unmatched INI key (see its rowed body).
extern const FieldParse g_00C39D54 = { 0, Rva00413C02Parse, 0, 0 };
class Rva00413D46
{
public:
	void rva00413D46(INI *ini);
};

// ?rva00413D46@Rva00413D46@@QAEXPAVINI@@@Z
void Rva00413D46::rva00413D46(INI *ini)
{
	ini->initFromINI(this, &g_00C39D54);
}
