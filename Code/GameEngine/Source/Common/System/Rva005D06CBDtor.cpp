// cl: /Ireference/shims/bfme2_ascii /EHsc
// ??1Rva005D06CB@@UAE@XZ @ 0x005D06CB 103B: MI virtual dtor with three bases
// unregistering the second base via rowed erase 0x002B7250 on holder at
// g_009FEF10+0x2C then pinned third-base dtor 0x005EB753. Evidence:
// deleting-dtor caller 0x005D0A67; vtable stores 0x00C75554 0x00C75548
// 0x00C75540 then 0x00C62A14 0x00C75290; chain sibling of 0x005D078B.
class Rva002BA8F1Logic;
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class CreateAHeroData;
class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *p);
};
class Rva002BA8F1Logic
{
public:
	char m_pad[0x2C];
	Rva002B7250 m_holder2C;
};

class Rva005D06CBB1
{
public:
	virtual ~Rva005D06CBB1() {}
private:
	int m_04;
};
class Rva005D06CBB2
{
public:
	virtual ~Rva005D06CBB2() {}
};
class Rva005EB753
{
public:
	virtual ~Rva005EB753();
};
class Rva005D06CB : public Rva005D06CBB1, public Rva005D06CBB2, public Rva005EB753
{
public:
	virtual ~Rva005D06CB();
};
Rva005D06CB::~Rva005D06CB()
{
	(*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->m_holder2C.rva002B7250((CreateAHeroData *)(Rva005D06CBB2 *)this);
}
