// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0030BDEE@Rva0030BDEE@@QAEXHHPAUBfmeE8@@@Z @0x0030BDEE 83B
// Chain setter with float compare then virtual slot 0x28.
// Evidence: callers none; callees rowed getter 0x005382A6 setter 0x005382D2; member Rva005382A6 at +0x68; SSE compare via ucomiss lahf; virtual call [eax+0x28]; ret 0xC.
// Precedent Rva005382D2Setter for BfmeE8 and Rva0030BF0CEqual for SSE compare.
struct BfmeE8
{
	float x;
	float y;
};

class Rva005382A6
{
public:
	void *rva005382A6(int i, int off);
	void rva005382D2(int i, int off, BfmeE8 *src);
private:
	void *m_base;
};

class Rva0030BDEE
{
public:
	virtual ~Rva0030BDEE();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	void rva0030BDEE(int i, int off, BfmeE8 *src);
private:
	char m_pad[0x64];
	Rva005382A6 m_68;
};

void Rva0030BDEE::rva0030BDEE(int i, int off, BfmeE8 *src)
{
	Rva005382A6 &slot = m_68;
	BfmeE8 *cur = (BfmeE8 *)slot.rva005382A6(i, off);
	if (src->x != cur->x || src->y != cur->y)
	{
		slot.rva005382D2(i, off, src);
		v10();
	}
}
