// cl: /Oy- /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX-
// ?rva0005C892@Rva0005C892@@QAEXXZ @0x0005C892 41B.
// Zero the float at +0x90, default-construct the 8-byte Rva00052B3D helper
// (rowed ctor ??0Rva00052B3D@@QAE@XZ) in an 8-byte frame slot, then call the
// unrowed thiscall helper at 0x0005C23C with its address. The helper keeps an
// address-derived pin read from this call site's REL32; identity unproven.
// Target facts: xorps-zero movss store precedes the ctor call; the helper
// call takes the single local-pointer argument; /Oy- frame with leave.
class Rva00052B3D
{
public:
	Rva00052B3D();
private:
	int m_a;
	int m_b;
};

class Rva0005C892
{
public:
	void rva0005C892();
	void rva0005C23C(Rva00052B3D *tmp);
private:
	char m_pad00[0x90];
	float m_vol90;
};

void Rva0005C892::rva0005C892()
{
	m_vol90 = 0.0f;
	Rva00052B3D tmp;
	rva0005C23C(&tmp);
}
