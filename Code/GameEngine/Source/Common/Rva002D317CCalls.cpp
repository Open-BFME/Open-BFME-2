// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva002D317C@Rva002D317C@@QAEXPBMPBMHH@Z, retail 0x002D317C, 295 bytes.
// Chain (calls 0x002D7BB7 ready). Evidence: TheRadar virtual [0x1C] with 5
// ints plus rowed ?rva002D7BB7@Radar@@QAEXPBX@Z and ?rva002D7BD3@Radar@@QAEXXZ;
// GameWindow winGetPosition/winSetPosition/winGetSize/winSetSize rowed;
// float global 0.5f; cvttss2si float-to-int Erin shape; ret 0x10 =
// this + 4 args (2 float pairs + 2 unused ints); this+0x64 GameWindow* and
// this+0x68 rect. Honest owner-unknown method name.

struct FieldParse;

class GameWindow
{
public:
	int winGetPosition(int *x, int *y);
	int winSetPosition(int x, int y);
	int winGetSize(int *w, int *h);
	int winSetSize(int w, int h);
};

class Radar
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void unk1C(int a, int b, int c, int d, int e);
	void rva002D7BB7(void const *src);
	void rva002D7BD3();
};

extern Radar *TheRadar;
// TheRadar: matched references place it at VA 0xdff070 (zero-filled .bss).
Radar * TheRadar;

class Rva002D317C
{
public:
	void rva002D317C(const float *a, const float *b, int c, int d);
private:
	char m_pad[0x64];
	GameWindow *m_window; // +0x64
	int m_rect[4]; // +0x68..+0x77 (lo.x lo.y hi.x hi.y)
};

void Rva002D317C::rva002D317C(const float *a, const float *b, int c, int d)
{
	(void)c;
	(void)d;
	int ix0 = (int)(a[0] + 0.5f);
	int iy0 = (int)(a[1] + 0.5f);
	int ix1 = (int)(b[0] + 0.5f);
	int iy1 = (int)(b[1] + 0.5f);
	int posX;
	int posY;
	int sizeW;
	int sizeH;
	int *rect = m_rect;
	m_window->winGetPosition(&posX, &posY);
	if (rect[0] != posX || rect[1] != posY)
		m_window->winSetPosition(rect[0], rect[1]);
	m_window->winGetSize(&sizeW, &sizeH);
	int w = rect[2] - rect[0];
	if (w != sizeW || (rect[3] - rect[1]) != sizeH)
		m_window->winSetSize(w, rect[3] - rect[1]);
	if (ix0 == rect[0] && iy0 == rect[1] && ix1 == (rect[2] - rect[0]) && iy1 == (rect[3] - rect[1]))
		TheRadar->unk1C(ix0, iy0, ix1, iy1, -1);
	else
	{
		TheRadar->rva002D7BB7(rect);
		TheRadar->unk1C(ix0, iy0, ix1, iy1, -1);
		TheRadar->rva002D7BD3();
	}
}
