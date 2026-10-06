// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva004F4927@Rva004F4927@@QAEXXZ @0x004F4927 59B.
// Probe-gated quad dispatch: unless the pinned 0x002A8AB1 lookup on the
// 0x00DFEEF8 world hits for +0x0C, run virtual slots 16-19 on this, then
// tail-call the pinned 0x004F418A worker on this.
struct Rva002A8AB1Record;

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *key);
};

extern Rva002A8F24 *g_00DFEEF8;

class Rva004F418A
{
public:
	void rva004F418A();
};

class Rva004F4927
{
public:
	void rva004F4927();
	virtual void vf00(); virtual void vf01(); virtual void vf02(); virtual void vf03();
	virtual void vf04(); virtual void vf05(); virtual void vf06(); virtual void vf07();
	virtual void vf08(); virtual void vf09(); virtual void vf10(); virtual void vf11();
	virtual void vf12(); virtual void vf13(); virtual void vf14(); virtual void vf15();
	virtual void vf16(); virtual void vf17(); virtual void vf18(); virtual void vf19();
	char m_pad04[0x0C - 0x04];
	int m_C;
};

void Rva004F4927::rva004F4927()
{
	if (((Rva002A8F24 *)g_00DFEEF8)->rva002A8AB1((void *)m_C))
		return;
	vf16();
	vf17();
	vf18();
	vf19();
	((Rva004F418A *)this)->rva004F418A();
}
