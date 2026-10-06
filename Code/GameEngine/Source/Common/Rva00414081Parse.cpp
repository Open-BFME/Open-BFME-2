// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva00414081@Rva00414081@@QAEXPAVINI@@@Z, retail 0x00414081, 18 bytes.
// INI parse wrapper over rowed ?initFromINI@INI@@QAEXPAXPBUFieldParse@@@Z with table 0x00C39EB8.
// Caller at 0x004142D7 in 0x0041428F passes INI in esi and object in ecx; same 18B shape as rowed 0x00415C56.
// Owner unproven so honest-address class Rva00414081.
struct FieldParse;
extern const struct FieldParse g_00C39EB8[];
class INI
{
public:
	void initFromINI(void *what, const struct FieldParse *table);
};
class Rva00414081
{
public:
	void rva00414081(INI *ini);
};
void Rva00414081::rva00414081(INI *ini)
{
	ini->initFromINI(this, g_00C39EB8);
}
