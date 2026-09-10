// cl: /O1 /DNDEBUG /MD
//
// MultiIniFieldParse::MultiIniFieldParse, retail 0x0002BAA0, 26 bytes.
// Dedicated TU so INI wrappers cannot inline this zeroing loop.

class MultiIniFieldParse
{
	const void *m_fieldParse[16];
	unsigned m_extraOffset[16];
	int m_count;

public:
	MultiIniFieldParse();
};

MultiIniFieldParse::MultiIniFieldParse()
	: m_count(0)
{
	for (int i = 0; i < 16; i++)
	{
		m_extraOffset[i] = 0;
		m_fieldParse[i] = 0;
	}
}
