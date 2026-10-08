// cl: /MD

class LivingWorldLogic; extern LivingWorldLogic *TheLivingWorldLogic;
class LivingWorldManager; extern LivingWorldManager *TheLivingWorldManager;

class Rva00DFE1C8Host {
public:
	void rva00213171(int a, void *p, int b);
};

class Rva003F409F {
public:
	void rva003F409F(bool b);
};

struct Rva003F43D3Holder {
	char m_pad[0x2C];
	int m_2c;
};

struct RvaLogicHolder {
	char m_pad[0xB0];
	Rva003F43D3Holder *m_holder;
};

class Rva003F43D3 {
public:
	void rva003F43D3();
private:
	char m_pad[0x28];
	char m_28[8];
	int m_30;
};

void Rva003F43D3::rva003F43D3()
{
	RvaLogicHolder *logic = (RvaLogicHolder *)TheLivingWorldLogic;
	Rva003F43D3Holder *holder = logic->m_holder;
	int value = ++holder->m_2c;
	m_30 = value;
	((Rva00DFE1C8Host *)TheLivingWorldManager)->rva00213171(value, m_28, 0);
	((Rva003F409F *)this)->rva003F409F(true);
}
