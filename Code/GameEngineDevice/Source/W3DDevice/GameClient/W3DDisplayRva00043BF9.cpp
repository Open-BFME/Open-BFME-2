// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
// ?rva00043BF9@W3DDisplay@@QAEXXZ, retail 0x00043BF9, 240 bytes.
// W3DDisplay per-line color pass over the 25 debug strings at +0x1D0: each
// present line gets a severity color picked by its index (sparse switch with
// shared arms; other indices keep the running color, initially -1), then
// color(color, black), place(3, acc, 1, 1) and size(&w, &h), accumulating the
// width into acc from 3. Same BfmeDrawString006e interface (color/place/size
// at +0x28/+0x38/+0x3c) and same W3DDisplay home as the rowed sibling
// 0x0004387E (16 strings at +0x18c); the 25-table at +0x1D0 is proven by this
// body alone. Unblocks the 0x0004A3C4 dispatcher, whose arm1 tail-jumps here.
class BfmeDrawString006e
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void color006e(int a, unsigned int b);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual void place006e(int a, int b, int c, int d);
	virtual void size006e(int *w, int *h);
};

class W3DDisplay
{
public:
	void rva00043BF9(void);

private:
	unsigned char m_pad0[0x18c];
	BfmeDrawString006e *m_strings16[16];
	unsigned int m_pad1CC;
	BfmeDrawString006e *m_lines25[25];
};

void W3DDisplay::rva00043BF9(void)
{
	int color = -1;
	int acc = 3;
	for (int i = 0; i < 0x19; ++i)
	{
		if (m_lines25[i] == 0)
			continue;
		switch (i)
		{
		case 4:
			color = 0xFFFF9696;
			break;
		case 5:
			color = 0xFF64FF64;
			break;
		case 6:
			color = 0xFFA0A0FF;
			break;
		case 8:
			color = 0xFFFFFF00;
			break;
		case 10:
			color = 0xE164FF64;
			break;
		case 11:
			color = 0xE1FFFF00;
			break;
		case 13:
			color = 0xE164FF64;
			break;
		case 14:
			color = 0xD7FFFF00;
			break;
		case 16:
			color = 0xE164FF64;
			break;
		case 17:
			color = 0xCDFFFF00;
			break;
		case 19:
			color = 0xE164FF64;
			break;
		case 20:
			color = 0xC3FFFF00;
			break;
		case 22:
			color = 0xE164FF64;
			break;
		case 23:
			color = 0xB9FFFF00;
			break;
		}
		m_lines25[i]->color006e(color, 0xFF000000);
		m_lines25[i]->place006e(3, acc, 1, 1);
		int w;
		int h;
		m_lines25[i]->size006e(&w, &h);
		acc += h;
	}
}
