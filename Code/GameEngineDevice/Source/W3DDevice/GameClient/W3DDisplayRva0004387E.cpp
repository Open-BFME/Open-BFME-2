// cl: /DNDEBUG /MD /EHsc
// ?rva0004387E@W3DDisplay@@QAEXXZ, retail 0x0004387E, 77 bytes.
// W3DDisplay debug-string row draw: 16 strings at +0x18c, each color(-1, black),
// place(3, y, 1, 1), size(&w, &h), y += h from y=3.
// Evidence: BFME1 donor W3DDisplayDrawStrings006e8790.cpp (same 3 virtuals at
// +0x28/+0x38/+0x3c, same constants, 15 at +0x18c); retail loops 0x10;
// neighbours in same GameClient dir; caller 0x0004A3C4 jumps here.
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
	void rva0004387E(void);

private:
	unsigned char m_unmodelled[0x18c];
	BfmeDrawString006e *m_strings[16];
};

void W3DDisplay::rva0004387E(void)
{
	int x = 3;
	BfmeDrawString006e **p = m_strings;
	int n = 16;
	do
	{
		int height;
		int width;
		(*p)->color006e(-1, 0xff000000);
		(*p)->place006e(3, x, 1, 1);
		(*p)->size006e(&width, &height);
		x += height;
		++p;
		--n;
	} while (n);
}
