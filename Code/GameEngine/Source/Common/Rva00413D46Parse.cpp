// cl: /DNDEBUG /MD /GX-
// ?rva00413D46@Rva00413D46@@QAEXPAVINI@@@Z, retail 0x00413D46, 18 bytes.
// INI table forward: ini->initFromINI(this) through table 0x00839D54 (rowed
// 0x0002DE78). Same recipe as sibling Rva00413DCCParse without the throw
// check. Evidence: unlock lane; retail push-imm plus push-ecx plus
// mov-ecx-[esp+0xc] plus call plus ret-4; caller 0x00413DA0.
struct FieldParse;
class INI
{
public:
	void initFromINI(void *what, const FieldParse *table);
};
extern const FieldParse g_00C39D54;
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
