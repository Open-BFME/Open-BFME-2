// cl: /O1 /arch:SSE /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva0033C247@MyRecord@@QAEXPAX@Z at 0x0033C247 (18B). The LINK BONUS pins this name; retail delegates to INI::initFromINI with this record and the global FieldParse table.

struct FieldParse;
extern const FieldParse g_00C10550[];

class INI
{
public:
	void initFromINI(void *record, const FieldParse *fields);
};

class MyRecord
{
public:
	void rva0033C247(void *ini);
};

void MyRecord::rva0033C247(void *ini)
{
	((INI *)ini)->initFromINI(this, g_00C10550);
}
