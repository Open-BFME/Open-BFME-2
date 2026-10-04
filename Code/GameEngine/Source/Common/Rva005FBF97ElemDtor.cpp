// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// ??1Rva005FBF97Elem@@QAE@XZ @ 0x005FBF97 78B
// Non-virtual dtor: audio remove-event helper 0x005FBEBA (handle at +0x24) then members +0x10 Rva0052413E +0x0C UnicodeString +0x08 AsciiString in reverse. Callers in OpaqueScalarDeletingDtors use it for clear and deleting dtor.
#include "ascii_string.h"
#include "unicode_string.h"
class Rva005FBEBA
{
public:
	void rva005FBEBA();
};
class Rva0052413E
{
public:
	~Rva0052413E();
private:
	char m_pad[12];
};
class Rva005FBF97Elem
{
public:
	~Rva005FBF97Elem();
private:
	char m_pad00[8];
	AsciiString m_08;
	UnicodeString m_0C;
	Rva0052413E m_10;
	char m_pad1C[8];
	unsigned int m_24;
};
Rva005FBF97Elem::~Rva005FBF97Elem()
{
	((Rva005FBEBA*)this)->rva005FBEBA();
}
