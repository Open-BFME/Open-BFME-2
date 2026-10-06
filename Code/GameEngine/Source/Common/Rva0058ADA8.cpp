// cl: /MD
// ?rva0058ADA8@Rva0058ADA8@@QAEXH@Z 0x0058ADA8 40B evidence: leaf via vslots 8 and 0x14; m0C at +0xC m18 at +0x18; called from 0x004B333C
class Rva0058ADA8
{
public:
	virtual int v00();
	virtual int v01();
	virtual int v02();
	virtual void v03();
	virtual void v04();
	virtual void v05(int arg);
private:
	char _p04[0xC - 4];
	int m0C;
	char _p10[0x18 - 0x10];
	unsigned char m18;
public:
	void rva0058ADA8(int arg);
};

void Rva0058ADA8::rva0058ADA8(int arg)
{
	int c = m0C;
	int r = v02();
	if ((unsigned int)c < (unsigned int)r)
		return;
	m0C = 0;
	m18 = 1;
	v05(arg);
}
