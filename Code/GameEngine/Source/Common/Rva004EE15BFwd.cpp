// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva004EE15B@Rva004EE15B@@QAEXPAURva004EE15BObj@@@Z @0x004EE15B 78B.
// Triple-forward: run the argument's slot-0x28 hook on a paired 1-byte
// scratch, then its slot-0x84 hook on the +0x04/+0x06/+0x08 addresses in
// turn. Only the two slot signatures and the three addresses are proven;
// member extents are minimal-contiguous placeholders.
class Rva004EE15BObj
{
public:
	virtual void vf00(); virtual void vf01(); virtual void vf02(); virtual void vf03();
	virtual void vf04(); virtual void vf05(); virtual void vf06(); virtual void vf07();
	virtual void vf08(); virtual void vf09(); virtual void vf10(char *p); virtual void vf11();
	virtual void vf12(); virtual void vf13(); virtual void vf14(); virtual void vf15();
	virtual void vf16(); virtual void vf17(); virtual void vf18(); virtual void vf19();
	virtual void vf20(); virtual void vf21(); virtual void vf22(); virtual void vf23();
	virtual void vf24(); virtual void vf25(); virtual void vf26(); virtual void vf27();
	virtual void vf28(); virtual void vf29(); virtual void vf30(); virtual void vf31();
	virtual void vf32(); virtual void vf33(void *p);
};

class Rva004EE15B
{
public:
	void rva004EE15B(Rva004EE15BObj *o);
private:
	char m_pad[4];
	char m_4[2];
	char m_6[2];
	int m_8;
};

void Rva004EE15B::rva004EE15B(Rva004EE15BObj *o)
{
	char scratch[2] = { 1, 1 };
	o->vf10(&scratch[0]);
	o->vf33(&m_4);
	o->vf33(&m_6);
	o->vf33(&m_8);
}
