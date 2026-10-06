// cl: /MD /EHs
//
// ??1Rva00383D71@@QAE@XZ @0x00383D71 271B base dtor: 6x Rva0038201D at +0x4,
// two 6x arrays via eh vector destructor at +0x4c/+0x94, 8x Rva0038204A at
// +0xdc. Callees rowed in Rva0046A93EDtor.cpp, arrays use rowed element
// dtors via 0x00629110. Callers 0x003844D7/0x0038454E tail-call as base.
class Rva0038201D
{
public:
	~Rva0038201D();
private:
	void *m_head;
	int m_count;
	int m_extra;
};

class Rva0038204A
{
public:
	~Rva0038204A();
private:
	void *m_head;
	int m_count;
	int m_extra;
};

class Rva00383D71
{
public:
	~Rva00383D71();
private:
	int m_00;
	Rva0038201D m_04;
	Rva0038201D m_10;
	Rva0038201D m_1c;
	Rva0038201D m_28;
	Rva0038201D m_34;
	Rva0038201D m_40;
	Rva0038201D m_4c[6];
	Rva0038201D m_94[6];
	Rva0038204A m_dc;
	Rva0038204A m_e8;
	Rva0038204A m_f4;
	Rva0038204A m_100;
	Rva0038204A m_10c;
	Rva0038204A m_118;
	Rva0038204A m_124;
	Rva0038204A m_130;
	char m_pad[24];
};

Rva00383D71::~Rva00383D71()
{
}
