// cl: /DNDEBUG /MD
//
// ?screenPixelToWorld@Radar@@QAE_NPBUICoord2D@@PAUCoord3D@@@Z,
// retail 0x002D82E4, 106 bytes. Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/Common/System/Radar.cpp,
// matched 126 bytes there): null-guard the arguments, bail when there is no
// radar window, translate the screen pixel into a window-local pixel via the
// GameWindow, then fold through the local-pixel-to-radar and radar-to-world
// helpers. BFME2 keeps the radar window at Radar+0x1430 (proven by the
// landed Radar::newMap); the 20-byte delta is under investigation.

struct ICoord2D
{
	int x;
	int y;
};

#define NULL 0

struct Coord3D
{
	float x;
	float y;
	float z;
};

class GameWindow
{
public:
	int winGetScreenPosition(int *x, int *y);
};

class Radar
{
public:
	bool screenPixelToWorld(const ICoord2D *pixel, Coord3D *world);
	bool localPixelToRadar(const ICoord2D *pixel, ICoord2D *radar);
	bool radarToWorld(const ICoord2D *radar, Coord3D *world);

private:
	char m_pad[0x1430];
	GameWindow *m_radarWindow; // +0x1430
};

// ?screenPixelToWorld@Radar@@QAE_NPBUICoord2D@@PAUCoord3D@@@Z
bool Radar::screenPixelToWorld(const ICoord2D *pixel, Coord3D *world)
{
	if (pixel == NULL || world == NULL)
		return false;

	if (m_radarWindow == NULL)
		return false;

	ICoord2D localPixel;
	ICoord2D screenPos;
	m_radarWindow->winGetScreenPosition(&screenPos.x, &screenPos.y);
	localPixel.x = pixel->x - screenPos.x;
	localPixel.y = pixel->y - screenPos.y;

	ICoord2D radar;
	if (localPixelToRadar(&localPixel, &radar) == false)
		return false;

	return radarToWorld(&radar, world);
}
