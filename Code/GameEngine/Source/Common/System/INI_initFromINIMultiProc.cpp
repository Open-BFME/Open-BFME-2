// cl: /O1 /DNDEBUG /MD
//
// INI::initFromINIMultiProc, retail 0x0002DEB5, 56 bytes. Dedicated TU so the
// MultiIniFieldParse ctor stays out of line at 0x2BAA0.

class MultiIniFieldParse
{
	const void *m_fieldParse[16];
	unsigned m_extraOffset[16];
	int m_count;

public:
	MultiIniFieldParse();
};

typedef void (__cdecl *BuildMultiIniFieldProc)(MultiIniFieldParse &);

class INI
{
public:
	void initFromINIMulti(void *what, const MultiIniFieldParse &parseTableList);
	void initFromINIMultiProc(void *what, BuildMultiIniFieldProc proc);
};

void INI::initFromINIMultiProc(void *what, BuildMultiIniFieldProc proc)
{
	MultiIniFieldParse parse;
	proc(parse);
	initFromINIMulti(what, parse);
}
