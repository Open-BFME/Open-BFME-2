// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
//
// ??0BfmeAssignRecord36@@QAE@PBDH@Z, retail 0x001512F1, 69 bytes.
// BfmeAssignRecord36 two-arg ctor: AsciiString defaults zero +0/+8 then rowed
// init 0x00151248 clears both strings and tails then StringBase<char>::set
// row 0x000055F5 sets +0 from arg1 and int +4 from arg2. Returns this ret 8.
// Evidence: prev 0x00151288 SetPath same dir next 0x00151336 operator= same
// 36B layout with identical tails; 34 callers; LINK BONUS 8B.
#include "ascii_string.h"

class Rva00151248
{
public:
	void rva00151248();
};

struct BfmeAssignRecord36
{
public:
	BfmeAssignRecord36(const char *s, int v);

private:
	AsciiString m_s00;
	int m_04;
	AsciiString m_s08;
	char m_0c[16];
	int m_1c;
	unsigned char m_20;
	char m_pad21[3];
};

BfmeAssignRecord36::BfmeAssignRecord36(const char *s, int v)
{
	((Rva00151248 *)this)->rva00151248();
	((StringBase<char> &)m_s00).set(s);
	m_04 = v;
}
