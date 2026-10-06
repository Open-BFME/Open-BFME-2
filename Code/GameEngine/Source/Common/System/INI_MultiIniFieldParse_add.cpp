// cl: /EHsc /DNDEBUG /MD
//
// MultiIniFieldParse::add, retail 0x0002BC6E (60 bytes).
// ZH INI.cpp spells the overflow arm DEBUG_CRASH + throw ERROR_BUG;
// ERROR_BUG is 1 (BFME1 INI_stl.cpp), which is the int this body throws.
// Dedicated TU so INI_initFromINI.cpp keeps calling it out of line.

struct FieldParse;

typedef int ErrorCode;
#define ERROR_BUG ((ErrorCode)1)

class MultiIniFieldParse
{
	const void *m_fieldParse[16];
	unsigned m_extraOffset[16];
	int m_count;

public:
	void add(const FieldParse *fields, unsigned extraOffset);
};

void MultiIniFieldParse::add(const FieldParse *fields, unsigned extraOffset)
{
	if (m_count < 16)
	{
		m_fieldParse[m_count] = fields;
		m_extraOffset[m_count] = extraOffset;
		++m_count;
	}
	else
	{
		throw ERROR_BUG;
	}
}
