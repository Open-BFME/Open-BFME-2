// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
#include "Coord2D.h"
#include "Coord3D.h"

class Rva002D3627Host
{
public:
	bool rva002BF5B0(const Coord2D *input, Coord3D *output);
};
extern Rva002D3627Host *g_00DFEF18;

class Rva00319AA0Target
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5(const Coord3D *position);
};

class Rva00319AA0
{
public:
	void rva00319AA0(const Coord2D *position);
	void rva003197B7();
private:
	unsigned char m_head[0x44];
	Coord2D m_position;
	unsigned char m_unknown4C[0x3C];
	Rva00319AA0Target *m_target;
};

// Native 0x00319AA0..0x00319B0A ends RET 4. It copies the two coordinate
// words to +0x44/+0x48, calls the 55-byte same-receiver helper 0x003197B7,
// then, when +0x88 is nonnull, maps a zero-height local through 0x002BF5B0
// and passes it to target vslot 5. The helper's own native tail calls the
// RET-0 0x003195C9 without stack arguments. All receiver, target and helper
// names are address-derived ABI views; original class identities are unknown.
void Rva00319AA0::rva00319AA0(const Coord2D *position)
{
	m_position = *position;
	rva003197B7();
	if (m_target)
	{
		Coord3D world = { m_position.x, m_position.y, 0.0f };
		g_00DFEF18->rva002BF5B0(&m_position, &world);
		m_target->slot5(&world);
	}
}
