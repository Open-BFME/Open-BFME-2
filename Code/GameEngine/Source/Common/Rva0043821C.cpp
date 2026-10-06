// cl: /MD
//
// ?rva0043821C@Rva0043821C@@QAEXXZ @0x0043821C 18B
// Leaf: frameless __thiscall clearing dword at +0x14 (and [ecx+14h],0) and
// storing shared 1.0f from 0xBBB8D8 at +0x10 via movss. Owner unproven,
// honest Rva name. Own TU because it needs /arch:SSE for movss, which the
// neighbour Rva00438144Update.cpp (/O1) does not use. Caller 0x00244120.

class Rva0043821C
{
public:
	void rva0043821C();
private:
	char m_pad00[0x10];
	float m_10;
	int m_14;
};

void Rva0043821C::rva0043821C()
{
	float v = 1.0f;
	m_14 = 0;
	m_10 = v;
}
