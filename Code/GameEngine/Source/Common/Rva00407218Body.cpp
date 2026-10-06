// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
// ?rva00407218@Rva00407218@@QAEXPAX0@Z, retail 0x00407218, 186 bytes.
// Chain from 0x0040718F: three CommandButton INI string temps then gap and RvaUpdate.
// Evidence: same TU family and flags; string literals CommandBotton ExpLevel ButtonIndex;
// callers in 0x00408C11; prev StringRecordCopy same /O1 /EHsc.
#include "ascii_string.h"

class Rva00407137;
class Rva00406FBF;

void Rva0040718FForward(void *v, const AsciiString &s, int dummy, Rva00407137 *r);
void __cdecl Rva0040707EUpdate(void *a1, void *a2, void *a3_unused, Rva00406FBF *a4);

class Rva00407218
{
public:
	void rva00407218(void *v, void *r);
private:
	void *m_00;
	void *m_04;
	void *m_08;
};

void Rva00407218::rva00407218(void *v, void *r)
{
	{
		AsciiString s("CommandBotton");
		Rva0040718FForward(v, *(const AsciiString *)&m_00, (int)&s, (Rva00407137 *)r);
	}
	{
		AsciiString s("ExpLevel");
		Rva0040707EUpdate(v, &m_04, &s, (Rva00406FBF *)r);
	}
	{
		AsciiString s("ButtonIndex");
		Rva0040707EUpdate(v, &m_08, &s, (Rva00406FBF *)r);
	}
}
