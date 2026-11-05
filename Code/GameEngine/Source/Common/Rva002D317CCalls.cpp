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

#include "../../Include/GameClient/Bfme2GameWindow.h"

#include "../../Include/Common/Radar.h"

// TheRadar: matched references place it at VA 0xdff070 (zero-filled .bss).
Radar * TheRadar;

class Rva002D317C
{
public:
	void rva002D317C(const float *position, const float *size, int c, int d);
private:
	char m_pad[0x64];
	GameWindow *m_window; // +0x64
	int m_rect[4]; // +0x68..+0x77 (lo.x lo.y hi.x hi.y)
};

void Rva002D317C::rva002D317C(const float *position, const float *size, int c, int d)
{
	(void)c;
	(void)d;
	int radarX = (int)(position[0] + 0.5f);
	int radarY = (int)(position[1] + 0.5f);
	int radarWidth = (int)(size[0] + 0.5f);
	int radarHeight = (int)(size[1] + 0.5f);
	int posX;
	int posY;
	int sizeW;
	int sizeH;
	int *rect = m_rect;
	m_window->winGetPosition(&posX, &posY);
	if (rect[0] != posX || rect[1] != posY)
		m_window->winSetPosition(rect[0], rect[1]);
	m_window->winGetSize(&sizeW, &sizeH);
	int windowWidth = rect[2] - rect[0];
	if (windowWidth != sizeW || (rect[3] - rect[1]) != sizeH)
		m_window->winSetSize(windowWidth, rect[3] - rect[1]);
	if (radarX == rect[0] && radarY == rect[1] && radarWidth == (rect[2] - rect[0]) && radarHeight == (rect[3] - rect[1]))
		TheRadar->draw(radarX, radarY, radarWidth, radarHeight, -1);
	else
	{
		TheRadar->rva002D7BB7(rect);
		TheRadar->draw(radarX, radarY, radarWidth, radarHeight, -1);
		TheRadar->rva002D7BD3();
	}
}
