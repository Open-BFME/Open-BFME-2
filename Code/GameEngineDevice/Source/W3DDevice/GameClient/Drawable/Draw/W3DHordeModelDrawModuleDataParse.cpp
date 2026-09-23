// cl: /O1 /DNDEBUG /MD
//
// W3DHordeModelDrawModuleData parse-unit.
//
// ?buildFieldParse@W3DHordeModelDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x000793E5, 21 bytes: the own table at 0x00BC6B80 through the
// rowed MultiIniFieldParse::add at 0x2BC6E, then a tail jump to the rowed
// W3DModelDrawModuleData base proc at 0xC9240. The W3DHordeModelDraw data
// factory pushes this proc VA; ModuleFactory registers it under
// "W3DHordeModelDraw". Row supersedes the parse pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class W3DModelDrawModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class W3DHordeModelDrawModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@W3DHordeModelDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x000793E5
void W3DHordeModelDrawModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00BC6B80), 0);
	W3DModelDrawModuleData::buildFieldParse(parse);
}
