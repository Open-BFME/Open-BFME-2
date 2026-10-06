// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?buildFieldParse@Rva005088CE@@SAXAAVMultiIniFieldParse@@@Z retail 0x005088CE 34B
// Static buildFieldParse registering two INI tables: one via table getter
// 0x00507552 returning 0x00C63FD0 plus one direct FieldParse table at
// 0x00864180 same as Get 0x005088C8. Same two-add shape as rowed
// FXListDieModuleData buildFieldParse 0x0050B107 first two adds without
// the third with /O1 reloading no-esi shape. Evidence: callers 0x0050890B
// in 0x005088F0 parseDamageNugget path plus 0x0050BE08 plus unblocks
// 0x005088F0 and 0x0050BDED.
struct FieldParse
{
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *entry, unsigned int index);
};

int __cdecl Rva00507552Get();

static const FieldParse s_table64180;

class Rva005088CE
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void Rva005088CE::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add((const FieldParse *)Rva00507552Get(), 0);
	parse.add(&s_table64180, 0);
}
