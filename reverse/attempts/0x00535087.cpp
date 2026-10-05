// ?Rva00535087Parse@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.9 date=2026-10-05
// cl: /O1 /G7 /GX- /DNDEBUG /MD
// ?Rva00535087Parse@@YAXPAVINI@@PAX1PBX@Z, retail 0x00535087 (51B): PlayerPosition
// FieldParse proc (0x00C68C58). 1-based atoi slot selects the 0x14-byte record at
// instance + 0xB0, filled through initFromINI with the table at 0x00C68D78.
// Near miss: cl folds (slot - 1) * 0x14 + 0xB0 into slot * 0x14 + 0x9C; retail
// keeps the dec before the imul and loads instance first.
struct FieldParse;
class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	void initFromINI(void *what, const FieldParse *parseTable);
};
extern "C" __declspec(dllimport) int __cdecl atoi(const char *text);
extern const FieldParse g_00C68D78[];
struct Rva00535087Position { unsigned char m_unreconstructed_00[0x14]; };
struct Rva00535087Owner { unsigned char m_unreconstructed_00[0xB0]; Rva00535087Position m_positions[1]; };
void Rva00535087Parse(INI *ini, void *instance, void *, const void *)
{
	int slot = atoi(ini->getNextToken());
	ini->initFromINI(&((Rva00535087Owner *)instance)->m_positions[slot - 1], g_00C68D78);
}
