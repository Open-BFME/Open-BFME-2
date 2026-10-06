// cl: /MD
// ?rva0042666E@Rva0042666E@@QAEXPAVINI@@@Z @0x0042666E 18B evidence: caller 0x426D4D passes new 0x10 object in ecx plus INI block in ebx; forwards to rowed INI initFromINI 0x2DE78 with FieldParse table g_00C3C398
class INI;
struct FieldParse;

class INI
{
public:
	void initFromINI(void *p, const struct FieldParse *fields);
};

extern const struct FieldParse g_00C3C398[];

class Rva0042666E
{
public:
	void rva0042666E(class INI *ini);
};

void Rva0042666E::rva0042666E(class INI *ini)
{
	ini->initFromINI(this, g_00C3C398);
}
