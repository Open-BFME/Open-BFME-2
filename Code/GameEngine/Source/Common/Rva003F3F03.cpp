// cl: /O1 /MD
//
// ?rva003F3F03@Rva003F3F03@@QAEXPAVINI@@@Z @0x003F3F03 36B.
// INI-load tail: run the rowed INI::initFromINI at 0x002DE78 over this with
// the TU-private FieldParse table at 0x00C36560 (named extern plus pin; the
// commit gate rejects literal image addresses), then run the two
// unclaimed no-arg members at 0x003F2F24 and 0x003F3B4F (range-19 target).
// Evidence: retail push esi / mov esi,ecx / mov ecx,[esp+8] /
// push &Rva003F3F03Table / push esi / call 0x002DE78 / mov ecx,esi /
// call 0x003F2F24 / mov ecx,esi / call 0x003F3B4F / pop esi / ret 4.
struct FieldParse;

extern const FieldParse Rva003F3F03Table;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
};

class Rva003F3F03
{
public:
	void rva003F3F03(INI *ini);
	void rva003F2F24();
	void rva003F3B4F();
};

void Rva003F3F03::rva003F3F03(INI *ini)
{
	ini->initFromINI(this, &Rva003F3F03Table);
	rva003F2F24();
	rva003F3B4F();
}
