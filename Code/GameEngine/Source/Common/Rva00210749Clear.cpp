// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii
// stlport
//
// ?rva00210749@Rva00210749@@QAEXXZ, retail 0x00210749, 38 bytes.
// Clears the AsciiString vector at +0x20 via rowed erase 0x0002CCFC then
// zeroes six dwords at +0x08..+0x1C. Evidence: single caller 0x002109E2,
// lea ecx,[esi+0x20] plus push [ecx+4]/[ecx] shape, local reference forces
// the lea before both pushes (else MSVC pushes [esi+0x24] early). Layout
// from retail offsets (vptr +0x00 plus pad +0x04 plus six ints). BFME1 donor
// none (structural clear). No fallback paths.
#include <vector>

#include "ascii_string.h"

class Rva00210749
{
public:
	virtual void f() = 0;
	void rva00210749();

private:
	char m_pad04[4]; // +0x04
	int m_08; // +0x08
	int m_0C; // +0x0C
	int m_10; // +0x10
	int m_14; // +0x14
	int m_18; // +0x18
	int m_1C; // +0x1C
	_STL::vector<AsciiString> m_vec20; // +0x20
};

void Rva00210749::rva00210749()
{
	_STL::vector<AsciiString> &v = m_vec20;
	v.erase(v.begin(), v.end());
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
}
