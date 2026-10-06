// cl: /DNDEBUG /MD
//
// ?rva00278C6B@Drawable@@QAEXXZ @0x00278C6B 17B: Drawable flag check at +0x44B,
// calls pinned Host 0x002783F6 with 0 when set. Evidence: packet disasm,
// neighbour Drawable flag cluster +0x447/+0x448/+0x44A/+0x44B, same Host call
// shape as Drawable::setAudible and Drawable::rva002785FB, caller 0x0023F52C.

class Rva002783F6Host
{
public:
	void rva002783F6(int v);
};

class Drawable
{
public:
	void rva00278C6B();
private:
	unsigned char m_pad00[0x44B];
	unsigned char m_44B; // +0x44B
};

void Drawable::rva00278C6B()
{
	if (m_44B != 0)
		((Rva002783F6Host *)this)->rva002783F6(0);
}
