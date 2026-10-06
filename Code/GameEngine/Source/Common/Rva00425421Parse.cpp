// cl: /O1 /DNDEBUG /MD
// ?parse@Rva00425421@@YAXPAVINI@@PAX@Z @0x00425421 57B: INI wrapper building a 2-entry FieldParse table {"Row", 0x004251C4} + terminator on the stack and calling rowed INI::initFromINI 0x0002DE78. Evidence: stack 0x20 with token 0x00C3C084 ("Row") and proc 0x008251C4, 6 zeroed dwords, REL32 to rowed 0x0002DE78.
struct FieldParse
{
	const char *token;
	void (*parse)(void *, void *, void *, const void *);
	const void *userData;
	int offset;
};

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
};

void Rva004251C4Parse(void *a, void *b, void *c, const void *d);

void __cdecl Rva00425421Parse(INI *ini, void *what)
{
	FieldParse table[2] = {
		{ "Row", Rva004251C4Parse, 0, 0 },
		{ 0, 0, 0, 0 },
	};
	ini->initFromINI(what, table);
}
