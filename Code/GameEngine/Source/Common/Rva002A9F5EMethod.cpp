// cl: /DNDEBUG /MD
// ?rva002A9F5E@Rva002A9F5E@@QAEXH@Z @0x002A9F5E 66B chain lane: guarded accumulate plus money add plus ControlBar refresh.
// Evidence: callees rowed 0x0039B668 Rva0039B668::rva0039B668 plus 0x0038027B Rva00380200::rva0038027B plus 0x0031B5A3 ControlBar::rva0031B5A3; global g_bfmeWorldRV ?g_bfmeWorldRV@@3PAUBfmeWorldRV@@A; offsets +0x3B4 +0x1C plus Player at this-8; neighbours share /O1.
class Rva0039B668
{
public:
	void rva0039B668(int amount);
};

class Rva00380200
{
public:
	void rva0038027B(int v);
};

class Player;
class ControlBar
{
public:
	void rva0031B5A3(const Player *player);
};

struct BfmeWorldRV;
extern class ControlBar *TheControlBar;

class Rva002A9F5E
{
public:
	void rva002A9F5E(int v);
private:
	char m_pad00[0x1c];
	int m_001C;
	char m_pad20[0x3b4 - 0x20];
	Rva0039B668 m_03B4;
};

void Rva002A9F5E::rva002A9F5E(int v)
{
	if (v > 0)
		m_03B4.rva0039B668(v);
	int saved = m_001C;
	((Rva00380200 *)(void *)this)->rva0038027B(v);
	if (saved != m_001C)
	{
		if ((*(BfmeWorldRV **)&TheControlBar))
			((ControlBar *)(void *)(*(BfmeWorldRV **)&TheControlBar))->rva0031B5A3((const Player *)(const void *)((const char *)(const void *)this - 8));
	}
}
