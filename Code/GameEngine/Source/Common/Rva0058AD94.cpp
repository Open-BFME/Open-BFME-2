// cl: /MD
// ?rva0058AD94@Rva0058AD94@@QAEXH@Z 0x0058AD94 11B evidence: m0C at +0xC shared with Rva0058ADA8 neighbour; v04 slot 0x10; ret 4 int arg unused
class Rva0058AD94
{
public:
	virtual int v00();
	virtual int v01();
	virtual int v02();
	virtual void v03();
	virtual void v04();
private:
	char _pad04[0xC - 4];
	int m0C;
public:
	void rva0058AD94(int arg);
};

void Rva0058AD94::rva0058AD94(int arg)
{
	(void)arg;
	++m0C;
	v04();
}
