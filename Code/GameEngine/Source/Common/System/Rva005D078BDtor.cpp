// cl: /Ireference/shims/bfme2_ascii /EHsc
// ??1Rva005D078B@@UAE@XZ @ 0x005D078B 86B: MI virtual dtor unregistering the
// second base via rowed erase 0x002B7250 on holder at g_009FEF10+0x6C then
// pinned base dtor 0x005CF8E3. Evidence: deleting-dtor caller 0x005D0A9F;
// vtable stores 0x00C75574 0x00C75570 then 0x00C7528C; sibling shape of
// Rva0056B126/Rva00575125.
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
	char m_pad[0x6C];
	Rva002B7250 m_holder6C;
};

class Rva005CF8E3
{
public:
	virtual ~Rva005CF8E3();
private:
	char m_pad[0x0C];
};
class Rva005D078BSecond
{
public:
	virtual ~Rva005D078BSecond() {}
};
class Rva005D078B : public Rva005CF8E3, public Rva005D078BSecond
{
public:
	virtual ~Rva005D078B();
};
Rva005D078B::~Rva005D078B()
{
	(*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->m_holder6C.rva002B7250((CreateAHeroData *)(Rva005D078BSecond *)this);
}
