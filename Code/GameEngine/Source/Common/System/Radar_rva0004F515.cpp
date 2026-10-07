// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
//
// ?rva0004F515@Radar@@QAEXHHHH@Z @0x0004F515 107B
// Target boundary 0x0044F515-0x0044F57F. The same ECX reaches rowed
// Radar::rva002D782C at 0x4F53B; the body then walks a sentinel-style chain
// rooted at +0x1500 (next +0, data +8), reads a Coord3D access view at data
// +0x14, converts it through 0x4DB76, and calls rowed 0x2D3366 through data
// +0x20. Caller 0x5053E passes its Radar this after rowed findDrawPositions.
// Marker and list field names/layouts here describe observed accesses only.

#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Libraries/Include/Lib/Coord2D.h"

struct RadarMarkerNode
{
	RadarMarkerNode *next;
	RadarMarkerNode *previous;
	void *data;
};

struct RadarDrawMarker
{
	unsigned char pad00[0x14];
	Coord3D world;
	class Rva002D3366 *window;
};

class Rva002D3366
{
public:
	virtual void m_spare0();
	virtual void m_spare1();
	virtual void m_slot8(float a, float b);
	void rva002D3366(float a, float b);
};

class Radar
{
public:
	bool rva002D782C(const Coord3D *world, Coord2D *radar);
	void rva0004DB76(const Coord2D *radar, Coord2D *pixel,
		int originX, int originY, int width, int height);
	void rva0004F515(int originX, int originY, int width, int height);
private:
	unsigned char m_pad[0x24];
	float m_xSample;
	float m_ySample;
	unsigned char m_pad2[0x1500 - 0x2C];
	RadarMarkerNode *m_markerHead;
};

void Radar::rva0004F515(int originX, int originY, int width, int height)
{
	RadarMarkerNode *head = m_markerHead;
	RadarMarkerNode *node = head->next;
	while (node != head) {
		RadarDrawMarker *marker = (RadarDrawMarker *)node->data;
		Coord2D radar;
		Coord2D pixel;
		rva002D782C(&marker->world, &radar);
		rva0004DB76(&radar, &pixel, originX, originY, width, height);
		marker->window->rva002D3366(pixel.x, pixel.y);
		node = node->next;
	}
}
