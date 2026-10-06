// cl: /EHsc /MD
//
// ??1Rva005CD651@@UAE@XZ retail 0x005CD6A9 67B dtor with Enable plus conditional erase.
// Evidence: vtable 0x00874FF4 same as ctor 0x005CD651; calls Enable 0x0052340D rowed; reads +8 then Rva002B7250::rva 0x002B7250 rowed; second vtable 0x0086E330 base.
void Rva0052340DEnable(void);
// The base installs vftable 0x0086E330 (VA 0x00C6E330). CreateAHeroData's own is
// 0x00838D88 (its rowed ctor and dtor), so the base is named after its vftable;
// spelling it CreateAHeroData gave that vftable symbol two addresses (full-gate
// DIR32 consistency). The erase callee is rowed with a CreateAHeroData pointer.
class CreateAHeroData;
class Rva0086E330Base
{
public:
	virtual ~Rva0086E330Base() {}
};
class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};
struct Holder005CD6A9
{
	int m_0;
	Rva002B7250 m_4;
};
struct Rva005CD651 : public Rva0086E330Base
{
	virtual ~Rva005CD651();
	Rva005CD651(int v);
	void rva005CD6EC(int unused);
	int m_4;
	Holder005CD6A9 *m_8;
	bool m_C;
};
Rva005CD651::~Rva005CD651()
{
	Rva0052340DEnable();
	if (m_8 != 0)
		m_8->m_4.rva002B7250((CreateAHeroData *)this);
}
void Rva005CD651::rva005CD6EC(int unused)
{
	(void)unused;
	Rva0052340DEnable();
	m_8->m_4.rva002B7250((CreateAHeroData *)this);
	m_8 = 0;
}
