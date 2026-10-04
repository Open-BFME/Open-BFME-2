// cl: /O1 /MD
//
// Opaque destructor tail-calling Rva002D22CA::~Rva002D22CA at 0x002D22CA
// (matched opaque derived dtor in GameEngineDeletingBaseDerived.cpp, itself
// tail-calling GameEngineDeletingBase; only declared here so the tail-call
// resolves to the ledger address instead of a same-TU definition). The
// class below stores its own vtable (0xBC4C20, DIR32 auto-patch) and
// tail-jumps to the base destructor. Owner identity is unproven (opaque
// Rva name). One ledger row per destructor, landed one commit at a time.

class Rva002D22CA
{
public:
	Rva002D22CA();
	virtual ~Rva002D22CA();
	virtual bool rva002D2457();
	void rva002D23ED(void *table, int index);
};

class Rva0004CA4C : public Rva002D22CA
{
public:
	Rva0004CA4C();
	virtual ~Rva0004CA4C();
	virtual void rva0004CA57();
};

Rva0004CA4C::~Rva0004CA4C()
{
}

Rva0004CA4C::Rva0004CA4C()
{
}

// g_00DB3D18: passed as an empty registration table at VA 0xdb3d18; zero-filled at retail like its siblings below.
char g_00DB3D18[12];
// g_00DE1CD8: matched references place it at VA 0xde1cd8; zero-filled at retail, sized to the
// 0xc-byte gap before the next known global there.
char g_00DE1CD8[12];
// g_00DE1CE4: matched references place it at VA 0xde1ce4; zero-filled at retail, sized to the
// 0x164-byte gap before the next known global there.
char g_00DE1CE4[356];

void Rva0004CA4C::rva0004CA57()
{
	Rva002D22CA::rva002D2457();
	rva002D23ED(g_00DB3D18, 3);
	rva002D23ED(g_00DE1CD8, 8);
	rva002D23ED(g_00DE1CE4, 5);
}
