// cl: /MD
// ?Rva0050AD97BuildFieldParse@@YAXAAVMultiIniFieldParse@@@Z retail 0x0050AD97 34B two adds.
// Evidence: callees rowed 0x00507552 0x0002BC6E; data VA 0x00864B60; caller 0x0050ADB9 pushes one parse ref.
struct FieldParse
{
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *entry, unsigned int index);
};

int Rva00507552Get();

static const FieldParse s_table0050AD97;

void Rva0050AD97BuildFieldParse(MultiIniFieldParse &parse)
{
	parse.add((const FieldParse *)Rva00507552Get(), 0);
	parse.add(&s_table0050AD97, 0);
}
