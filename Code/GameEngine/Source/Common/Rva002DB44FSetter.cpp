// cl: /MD
//
// ?rva002DB44F@Rva002DB44F@@QAEXHABUOpaqueRefElement4@@@Z, retail 0x002DB44F, 20 bytes.
// __thiscall array setter storing via rowed OpaqueRefElement4::operator=
// 0x00239099 into this+0x64+i*4. Leaf (one rowed callee). Caller 0x002DB7B8.
// Prev 0x002DAC27 dword setter / next BfmeMapPictureTexture ctor. Honest
// address name; owner class unproven.
struct OpaqueRefElement4
{
	struct OpaqueRefCounted *referent;
	~OpaqueRefElement4();
	struct OpaqueRefElement4 &operator=(const struct OpaqueRefElement4 &other);
};

struct Rva002DB44F
{
	char m_pad[0x64];
	struct OpaqueRefElement4 m_arr[1];
	void rva002DB44F(int i, const struct OpaqueRefElement4 &v);
};

void Rva002DB44F::rva002DB44F(int i, const struct OpaqueRefElement4 &v)
{
	m_arr[i] = v;
}

// ?rva002DB463@Rva002DB463@@QAEXHABUOpaqueRefElement4@@@Z, retail 0x002DB463, 23 bytes.
// Same array-setter recipe as 0x002DB44F above via rowed OpaqueRefElement4::operator=
// 0x00239099 into this+0xD4+i*4 (0xD4 needs 32-bit disp, hence 3 bytes longer).
// Leaf. Caller 0x002DB7C3. Honest address name; owner class unproven.
struct Rva002DB463
{
	char m_pad[0xD4];
	struct OpaqueRefElement4 m_arr[1];
	void rva002DB463(int i, const struct OpaqueRefElement4 &v);
};

void Rva002DB463::rva002DB463(int i, const struct OpaqueRefElement4 &v)
{
	m_arr[i] = v;
}
