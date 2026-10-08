// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva0035A994@Rva00359853@@QAEXHH@Z, retail 0x0035A994..0x0035A9C1 (45
// bytes, RET 8): slot 1 of Rva00359853's vtable (its deleting destructor is
// rowed). It counts the attempt (+0x10), runs the +0x04 object's 0x0035A4A3
// (not yet rowed; pinned) with both arguments, the +0x08 value, 0, the +0x18
// flag and the +0x0C value, and counts a success (+0x14). WorldBuilder's twin
// (0x00E5F9D0) is unnamed.

class Rva0035A4A3
{
public:
	bool rva0035A4A3(int a, int b, int c, int zero, bool flag, int d);
};

class Rva00359853
{
public:
	void rva0035A994(int a, int b);
private:
	void *m_vtable00;
	Rva0035A4A3 *m_04;
	int m_08;
	int m_0C;
	int m_attempts10;
	int m_successes14;
	bool m_18;
};

void Rva00359853::rva0035A994(int a, int b)
{
	++m_attempts10;
	if (m_04->rva0035A4A3(a, b, m_08, 0, m_18, m_0C))
		++m_successes14;
}
