// cl: /MD
// ?rva00587375@Rva00587375@@QAEXPBV1@@Z @0x00587375 70B
// Struct copy 0x3C bytes: dwords +0 +4 +8, byte +0xC, dword +0x10,
// 8-dword block +0x14 via struct assign (rep movsd 8), dword +0x34,
// bytes +0x38 +0x39. Unblocks 0x00587410 0x00587DCD.
// Evidence: callers 0x0058741C 0x00587DFF, size 0x3C via neighbour 0x00587311.
struct Rva00587375Block8 { int v[8]; };
class Rva00587375
{
public:
	void rva00587375(const Rva00587375 *src);
private:
	int m00;
	int m04;
	int m08;
	unsigned char m0c;
	int m10;
	Rva00587375Block8 m14;
	int m34;
	unsigned char m38;
	unsigned char m39;
};
void Rva00587375::rva00587375(const Rva00587375 *src)
{
	m00 = src->m00;
	m04 = src->m04;
	m08 = src->m08;
	m0c = src->m0c;
	m10 = src->m10;
	m14 = src->m14;
	m34 = src->m34;
	m38 = src->m38;
	m39 = src->m39;
}
