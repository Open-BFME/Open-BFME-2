// cl: /O2 /G6 /DNDEBUG /MD
// collisionmanager_data.cpp -- CollisionManager::Data::UpdateCoord, retail
// 0x00758590 (343 bytes). WorldBuilder names the function and its file (WB
// 0x018026A0, collisionmanager_data.cpp:60..98); its asserts are compiled
// out of retail. The data refreshes its cached bounding box from its owner
// (+0x04: frame counter slot 5, min slot 0, max slot 1) at most once per
// owner frame (+0xA0), repairs an inverted box to a unit box, writes the new
// extents into its three sort axes (each axis a max then a min 20-byte end
// point from +0x34), and returns how many sort passes the move needs: 1 for
// a move of at most 50 units on x/y, more for larger jumps, capped at 10000.
// A data already in the lists (+0x24) skips the refresh when asked to.
// Layout and constants are retail's; member names are structural.

#include "../WWVegas/WWMath/Vector3Data.h"

#include <math.h>

class CollisionObject
{
public:
	virtual void getMin(Vector3 *out) = 0;		// slot 0
	virtual void getMax(Vector3 *out) = 0;		// slot 1
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual int getFrame() = 0;					// slot 5
};

namespace CollisionManager
{
class Data
{
public:
	int UpdateCoord(bool removeAndReInsert);

private:
	void *m_vtbl;
	CollisionObject *m_object;					// +0x04
	unsigned char m_pad08[0x24 - 0x08];
	void *m_inLists;							// +0x24
	unsigned char m_pad28[0x34 - 0x28];
	float m_maxX;								// +0x34
	unsigned char m_pad38[0x48 - 0x38];
	float m_minX;								// +0x48
	unsigned char m_pad4C[0x5C - 0x4C];
	float m_maxY;								// +0x5C
	unsigned char m_pad60[0x70 - 0x60];
	float m_minY;								// +0x70
	unsigned char m_pad74[0x84 - 0x74];
	float m_maxZ;								// +0x84
	unsigned char m_pad88[0x98 - 0x88];
	float m_minZ;								// +0x98
	unsigned char m_pad9C[0xA0 - 0x9C];
	int m_lastFrame;							// +0xA0
};
}

int CollisionManager::Data::UpdateCoord(bool removeAndReInsert)
{
	if (m_object == 0)
		return 1;

	int frame = m_object->getFrame();
	if (frame != m_lastFrame)
		m_lastFrame = frame;
	else if (m_inLists != 0 && removeAndReInsert)
		return 0;

	Vector3 cmin;
	Vector3 cmax;
	m_object->getMin(&cmin);
	m_object->getMax(&cmax);

	if (cmin.X >= cmax.X || cmin.Y >= cmax.Y || cmin.Z >= cmax.Z)
	{
		cmax.X = cmin.X + 1.0f;
		cmax.Y = cmin.Y + 1.0f;
		cmax.Z = cmin.Z + 1.0f;
	}

	int passes = 1;
	// The double fabs: math.h's float overload would emit ?fabs@@YAMM@Z and
	// _fabsf copies that lose to the first copies in link order.
	float dx = fabs((double)(m_maxX - cmax.X));
	float dy = fabs((double)(m_maxY - cmax.Y));
	float d = dx > dy ? dx : dy;
	if (d > 50.0f)
	{
		passes = 11 - (int)((d - 50.0f) * -0.01f);
		if ((unsigned int)passes > 10000)
			passes = 10000;
	}

	m_minX = cmin.X;
	m_maxX = cmax.X;
	m_minY = cmin.Y;
	m_maxY = cmax.Y;
	m_minZ = cmin.Z;
	m_maxZ = cmax.Z;
	return passes;
}
