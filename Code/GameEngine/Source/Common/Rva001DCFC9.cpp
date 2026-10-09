// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?rva001DCFC9@Eva@@QAEXPAVINI@@PAX@Z @0x001DCFC9 28B evidence: callers 0x001DEB43 0x001DF688; FieldParse table VA 0x00BDC078; callee initFromINI 0x0002DE78 rowed
struct FieldParse;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
};

extern const FieldParse g_00BDC078;

class Eva { public: void rva001DCFC9(INI *ini, void *obj); };

void Eva::rva001DCFC9(INI *ini, void *obj)
{
	ini->initFromINI(obj, &g_00BDC078);
	((char *)obj)[0x2e] = 0;
}
