// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?buildFieldParse@Rva0033A8FC@@SAXAAVMultiIniFieldParse@@@Z @0x0033A8FC 36B
// Static buildFieldParse registering two FieldParse tables via rowed
// MultiIniFieldParse::add at 0x0002BC6E: table VA 0x00DBECD8 extra 0 plus
// table VA 0x00C100C0 extra 0x124 (RVAs 0x009BECD8 and 0x008100C0). Same two-add shape as Rva005088CE and the
// ModuleDataBuildFieldParse family. Caller at 0x002D1D16 constructs a
// MultiIniFieldParse and passes it here. Opaque Rva class: owning ModuleData
// behind these tables is unproven.
struct FieldParse
{
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *entry, unsigned int extra);
};

class Rva0033A8FC
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void Rva0033A8FC::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00DBECD8), 0);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C100C0), 0x124);
}
