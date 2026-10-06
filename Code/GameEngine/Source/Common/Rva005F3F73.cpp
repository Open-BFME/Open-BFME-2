// cl: /DNDEBUG /MD /O1 /arch:SSE /G7
// ??0Rva005F3F73@@QAE@PAX0@Z, RVA 0x005F3F73, 39 bytes.
// Address-derived class; called with a 0x18-byte allocation by 0x005F412B.
extern const void *const g_00C79438[];

class Rva005F3F73
{
public:
	Rva005F3F73(void *first, void *second);

private:
	const void *m_vtable;
	void *m_first;
	void *m_second;
	int m_zero0C;
	int m_zero10;
	char m_zero14;
	char m_zero15;
};

Rva005F3F73::Rva005F3F73(void *first, void *second)
	: m_vtable(g_00C79438), m_first(first), m_second(second),
	  m_zero0C(0), m_zero10(0), m_zero14(0), m_zero15(0)
{
}
