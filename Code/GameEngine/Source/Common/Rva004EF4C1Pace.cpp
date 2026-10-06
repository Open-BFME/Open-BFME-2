// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva004EF4C1@Rva004EF4C1@@QAEXXZ @0x004EF4C1 95B.
// Frame-rate pacer: unless the +0x0C chain's +0x338 flag is set, count the
// +0x14 budget down (clearing +0x24 and latching +0x10 at zero) clamped to
// three logic frames per second, then count +0x24 down and on expiry run
// the pinned 0x004F46A9 tail on this plus slot-0x68 when latched, reseeding
// +0x24 to two logic frames per second.
extern int g_Va00DBA4E4;
#define LogicFramesPerSecond g_Va00DBA4E4

class Rva004EF4C1C
{
public:
	char m_pad[0x338];
	unsigned char m_338;
};

class BfmeThingDTK
{
public:
	void bfmeTailDTK();
};

class Rva004EF4C1
{
public:
	void rva004EF4C1();
	virtual void vf00(); virtual void vf01(); virtual void vf02(); virtual void vf03();
	virtual void vf04(); virtual void vf05(); virtual void vf06(); virtual void vf07();
	virtual void vf08(); virtual void vf09(); virtual void vf10(); virtual void vf11();
	virtual void vf12(); virtual void vf13(); virtual void vf14(); virtual void vf15();
	virtual void vf16(); virtual void vf17(); virtual void vf18(); virtual void vf19();
	virtual void vf20(); virtual void vf21(); virtual void vf22(); virtual void vf23();
	virtual void vf24(); virtual void vf25(); virtual void vf26();
private:
	char m_pad04[0x0C - 0x04];
	Rva004EF4C1C *m_C;
	unsigned char m_10;
	char m_pad11[0x14 - 0x11];
	int m_14;
	char m_pad18[0x24 - 0x18];
	int m_24;
};

void Rva004EF4C1::rva004EF4C1()
{
	if (m_C->m_338 == 0)
		return;
	if (m_10 == 0) {
		if (--m_14 <= 0) {
			m_24 = 0;
			m_10 = 1;
		}
		int limit = LogicFramesPerSecond;
		limit = 3 * limit;
		if (m_14 > limit)
			m_14 = limit;
	}
	if (--m_24 < 1) {
		((BfmeThingDTK *)this)->bfmeTailDTK();
		if (m_10 != 0)
			vf26();
		m_24 = LogicFramesPerSecond * 2;
	}
}
