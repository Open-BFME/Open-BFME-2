// cl: /MD
// ?rva00406EFD@Rva00406EFD@@QAE_NH@Z @0x00406EFD 21B: conditional setter comparing stack arg with +0x10 and setting bit 2 at +0x38. Caller 0x00407012 passes 0. Owner unknown so honest-address name.
// ?rva00407004@Rva00406EFD@@QAE_NH@Z @0x00407004 28B: when the argument
// differs from +0x0C, stores it, calls rva00406EFD(0) and ORs 0xEF into the
// flags at +0x38 (cl narrows the dword OR to a byte); returns true. Caller
// 0x0040937F. Retail keeps this in ecx across the rva00406EFD call, which cl
// only does when that callee was compiled earlier in the same TU.
class Rva00406EFD
{
	int m_00[3];
	int m_0c;
	int m_10;
	int m_14[9];
	int m_38;
public:
	bool rva00406EFD(int v);
	bool rva00407004(int v);
};
bool Rva00406EFD::rva00406EFD(int v)
{
	if (v != m_10) {
		m_38 |= 2;
		m_10 = v;
	}
	return true;
}
bool Rva00406EFD::rva00407004(int v)
{
	if (v != m_0c) {
		m_0c = v;
		rva00406EFD(0);
		m_38 |= 0xEF;
	}
	return true;
}
