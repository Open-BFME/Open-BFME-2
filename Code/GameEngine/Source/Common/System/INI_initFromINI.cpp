// cl: /O1 /DNDEBUG /MD
//
// INI::initFromINI, retail 0x0002DE78, 61 bytes. Dedicated TU so the
// MultiIniFieldParse ctor and add stay out of line.

struct FieldParse;

class MultiIniFieldParse
{
	const void *m_fieldParse[16];
	unsigned m_extraOffset[16];
	int m_count;

public:
	MultiIniFieldParse();
	void add(const FieldParse *fields, unsigned extraOffset);
};

class INI
{
public:
	void initFromINIMulti(void *what, const MultiIniFieldParse &parseTableList);
	void initFromINI(void *what, const FieldParse *parseTable);
};

void INI::initFromINI(void *what, const FieldParse *parseTable)
{
	MultiIniFieldParse parse;
	parse.add(parseTable, 0);
	initFromINIMulti(what, parse);
}
