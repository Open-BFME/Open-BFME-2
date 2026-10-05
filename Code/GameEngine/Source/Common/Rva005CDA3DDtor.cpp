// cl: /O1 /DNDEBUG /MD
//
// ??1Rva005CDA3D@@UAE@XZ @0x005CDA3D (22B).
// Dtor restoring vptr plus +0x0C pointer field clear plus tail-jmp base dtor.
// Evidence: deleting dtor 0x005CDB43 calls here; vtable slot 0 of 0x00C75038;
// +0x0C null-checked +0x1C clear plus pin-only base ??1Rva005E66A4;
// neighbours ctor 0x005CD9AE and wrapper.

class Rva005E66A4
{
public:
	virtual ~Rva005E66A4();
};

struct Rva005CDA3DPtr
{
	char m_pad00[0x1C];
	int m_1C;
};

class Rva005CDA3D : public Rva005E66A4
{
public:
	virtual ~Rva005CDA3D();

private:
	char m_pad04[0x0C - 0x04];
	Rva005CDA3DPtr *m_0C;
};

Rva005CDA3D::~Rva005CDA3D()
{
	if (m_0C != 0)
		m_0C->m_1C = 0;
}
