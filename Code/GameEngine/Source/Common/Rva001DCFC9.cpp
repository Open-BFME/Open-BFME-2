// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?Rva001DCFC9Parse@@YGXPAVINI@@PAX@Z @0x001DCFC9 28B evidence: callers 0x001DEB43 0x001DF688; FieldParse table VA 0x00BDC078; callee initFromINI 0x0002DE78 rowed
struct FieldParse;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
};

extern const FieldParse g_00BDC078;

void __stdcall Rva001DCFC9Parse(INI *ini, void *obj)
{
	ini->initFromINI(obj, &g_00BDC078);
	((char *)obj)[0x2e] = 0;
}
