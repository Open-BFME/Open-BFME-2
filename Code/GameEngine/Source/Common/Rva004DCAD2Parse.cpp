// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva004DCAD2@Rva004DCAD2@@QAEXPAVINI@@@Z, retail 0x004DCAD2, 18 bytes.
// INI parse wrapper over rowed ?initFromINI@INI@@QAEXPAXPBUFieldParse@@@Z with table 0x00C61310.
// Callers at 0x004B218F 0x004DCBC1 0x004DCC17 in 0x004B2087 and 0x004DCAE4. Same 18B shape as rowed 0x00414081.
// Owner unproven so honest-address class Rva004DCAD2.
struct FieldParse;
extern const struct FieldParse g_00C61310[];
class INI
{
public:
	void initFromINI(void *what, const struct FieldParse *table);
};
class Rva004DCAD2
{
public:
	void rva004DCAD2(INI *ini);
};
void Rva004DCAD2::rva004DCAD2(INI *ini)
{
	ini->initFromINI(this, g_00C61310);
}
