// cl: /O1 /Ob2 /EHs /MD
// ??1Rva00420110@@UAE@XZ, retail 0x004201FA, 62 bytes. Derived dtor of
// Rva00420110 over Rva0041FE0E over GameEngineDeletingBase: installs derived
// vtable 0x00C3BA28 then calls rowed this->rva00420110 0x00420110 then
// installs base vtable 0x00C3B988 via inlined base dtor then calls rowed
// GameEngineDeletingBase dtor 0x001B4E74 with __EH_prolog 0x00629188.
// Evidence: sole caller deleting-dtor 0x00420238 calls this; callee 0x00420110
// takes same this; base ctor 0x0041FDF8 sets vtable 0x00C3B988 and caller
// 0x0042017F overwrites to 0x00C3BA28; layout +0x10/+0x85 matches neighbours.

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
};

class Rva0041FE0E : public GameEngineDeletingBase
{
public:
	virtual ~Rva0041FE0E();
	int m_0C;
};

inline Rva0041FE0E::~Rva0041FE0E()
{
}

class Rva00420110 : public Rva0041FE0E
{
public:
	virtual ~Rva00420110();
	void rva00420110();
};

Rva00420110::~Rva00420110()
{
	rva00420110();
}
