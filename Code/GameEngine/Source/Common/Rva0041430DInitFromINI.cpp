// cl: /DNDEBUG /MD
// 0x0041430D, 18B: forwards the caller's object and INI pointer to the
// rowed INI initializer with the field table referenced by retail.

struct FieldParse;

class INI
{
public:
	void initFromINI(void *object, const FieldParse *fields);
};

class Rva0041430D
{
public:
	void rva0041430D(INI *ini);
};

extern const FieldParse g_00C39FF8[];

void Rva0041430D::rva0041430D(INI *ini)
{
	ini->initFromINI(this, g_00C39FF8);
}
