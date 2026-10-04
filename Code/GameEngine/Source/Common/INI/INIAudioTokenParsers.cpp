// cl: /O1 /DNDEBUG /MD
//
// Three FieldParse procs that read one token and hand it, with the store, to
// a cdecl audio-event token parser (each parser checks "NoSound"; the 0x339235
// family also takes "EVA:" and "dynamic:" prefixes, and 0x33939F rejects EVA
// sounds with "This is not a valid place to use the EVA: sound syntax: %s").
// Referenced from 73 / 46 / 35 FieldParse rows. Original names unproven, so
// the procs and helpers keep their address names:
//
// ?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z 24B @0x003393DF -> 0x00339235
// ?Rva003393F7Parse@@YAXPAVINI@@PAX1PBX@Z 24B @0x003393F7 -> 0x0033939F
// ?Rva00339900Parse@@YAXPAVINI@@PAX1PBX@Z 24B @0x00339900 -> 0x00339184

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
};

void Rva00339235(const char *token, void *store);
void Rva0033939F(const char *token, void *store);
void Rva00339184(const char *token, void *store);

void Rva003393DFParse(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextToken();
	Rva00339235(token, store);
}

void Rva003393F7Parse(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextToken();
	Rva0033939F(token, store);
}

void Rva00339900Parse(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextToken();
	Rva00339184(token, store);
}
