// cl: /EHsc
// ?rva00237E45@Rva00237E45@@QAEXHHHH@Z 0x00237E45 30B
// Evidence: leaf four-dword setter, __thiscall, ret 0x10. The arguments are
// copied through eax, which /O1 /arch:SSE emits for integer parameters only (a
// float setter there is movss; that body is Vector4::Set at 0x0004256D), so this
// is an int setter. Sole caller 0x005AE5EE (REL32 at 0x005AE603) passes four
// integer fields of a response record into the 16-byte slot at this+0x90.
// Neighbours Rva00237E1F (m_00 << 16 | m_04) and Rva00237E28 (16-byte copy out)
// work on the same four-int layout. Name unknown; formerly rowed as
// Vector4::Set by masked byte-scan.

class Rva00237E45
{
public:
	void rva00237E45(int a, int b, int c, int d);
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
};

void Rva00237E45::rva00237E45(int a, int b, int c, int d)
{
	m_00 = a;
	m_04 = b;
	m_08 = c;
	m_0C = d;
}
