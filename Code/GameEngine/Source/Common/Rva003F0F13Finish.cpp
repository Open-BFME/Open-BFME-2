// cl: /MD
// stlport
// ?rva003F0F13@Rva003F0F13@@QAEXPAURva003F0F13Elem@@@Z, retail 0x003F0F13, 53 bytes.
// __thiscall copy-first-or-zero helper over an _STL::vector of 8-byte elements
// at +0xF0. The `size() > 0` spelling is load-bearing: `!= 0` / implicit bool
// let cl strength-reduce the count compare to `test ecx,0xFFFFFFF8`, while
// retail keeps the arithmetic `sar ecx,3` + `je`.
#include <vector>

struct Rva003F0F13Elem {
	float a;
	float b;
};

class Rva003F0F13 {
public:
	void rva003F0F13(Rva003F0F13Elem *out);
private:
	char m_pad[0xF0];
	_STL::vector<Rva003F0F13Elem> m_vec;
};

void Rva003F0F13::rva003F0F13(Rva003F0F13Elem *out)
{
	if (m_vec.size() > 0) {
		*out = m_vec[0];
	} else {
		out->a = 0.0f;
		out->b = 0.0f;
	}
}
