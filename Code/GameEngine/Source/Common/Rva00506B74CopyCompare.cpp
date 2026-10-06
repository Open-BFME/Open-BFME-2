// cl: /MD
// ?rva00506B74@Rva00506B74@@QAE_NPAUCoord3D@@@Z @0x00506B74 34B: copy member
// Coord3D at +0x28 to *out via three movsd then return !m_28.equals(global
// 0x00DD0870). Callers 0x004EBF4B (ecx+4 forwarding) 0x00507522 (flag +0x24
// guard plus second call 0x0050722A) 0x004EA54C. Prev row 0x00506B2F same
// /O1 /MD. Honest address-derived name; Coord3D block copy plus rowed equals.

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

struct Coord3D : public Coord3DBase
{
	bool equals(const Coord3DBase &that) const;
};

// Retail .data at VA 0x00DD0870 stores the three -1.0f components of the
// 12-byte Coord3DBase value used by the matched comparison.
Coord3DBase Gen00DD0870 = { -1.0f, -1.0f, -1.0f };

class Rva00506B74
{
public:
	bool rva00506B74(Coord3D *out);
private:
	char m_pad[0x28];
	Coord3D m_28;
};

bool Rva00506B74::rva00506B74(Coord3D *out)
{
	*out = *(Coord3D *)&m_28;
	return !m_28.equals(Gen00DD0870);
}
