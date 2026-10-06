// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva00415C56@Rva00415C56@@QAEXPAVINI@@@Z, retail 0x00415C56 (18B).
// INI parse wrapper over rowed ?initFromINI@INI@@QAEXPAXPBUFieldParse@@@Z
// with CrowdResponse field table 0x00C3A304. Caller at 0x00415E2A in
// CrowdResponse block parse 0x00415D33 passes INI in +8 and object in esi.
// Same shape as rowed FX parsers at 0x0055CA78. Owner unproven so
// honest-address class Rva00415C56.
struct FieldParse;
class INI
{
public:
	void initFromINI(void *what, const struct FieldParse *table);
};
class Rva00415C56
{
public:
	void rva00415C56(INI *ini);
};
void Rva00415C56::rva00415C56(INI *ini)
{
	ini->initFromINI(this, (const struct FieldParse *)0x00C3A304);
}
