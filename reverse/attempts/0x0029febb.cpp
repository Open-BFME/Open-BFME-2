// ?rva0029FEBB@Rva0029FEBB@@QAEXHH@Z
// partial score=0.93 date=2026-10-05
// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /arch:SSE
// stlport
// ?rva0029FEBB@Rva0029FEBB@@QAEXHH@Z retail 0x0029FEBB 324B
// Leaf drag-box tracker: list<BfmeSpecialPowerTimer8> at +0x910 with IRegion bounds at +0x914/+0x918/+0x91c/+0x920. Evidence: rowed list push_back 0x004DE74D, Coord3D length 0x3571 normalize 0x35B6, TheMouse 0xDFDCA0 field 0x12e8, floats at 0xBC2428 0xBFD26C.
#include <list>

struct BfmeSpecialPowerTimer8
{
	unsigned int m_templateID;
	unsigned int m_readyFrame;
};

class Coord3D
{
public:
	float x;
	float y;
	float z;
	float length() const;
	void normalize();
};

class Mouse
{
public:
	char _pad[0x12e8];
	unsigned int m_12e8;
};

extern Mouse *TheMouse;
extern float g_Va00BC2428;
extern float g_00BFD26C;

class Rva0029FEBB
{
public:
	void rva0029FEBB(int x, int y);
private:
	char _pad[0x910];
	_STL::list<BfmeSpecialPowerTimer8> m_list;
	int m_minX;
	int m_minY;
	int m_maxX;
	int m_maxY;
};

// ?rva0029FEBB@Rva0029FEBB@@QAEXHH@Z present-unmatched
void Rva0029FEBB::rva0029FEBB(int x, int y)
{
	BfmeSpecialPowerTimer8 t;
	t.m_readyFrame = (unsigned int)y;
	t.m_templateID = (unsigned int)x;
	if (m_list.size() == 0)
	{
		m_minX = x;
		m_maxX = x;
		m_minY = y;
		m_maxY = y;
	}
	else
	{
		BfmeSpecialPowerTimer8 &last = m_list.back();
		int threshInt = (int)(TheMouse->m_12e8 / 3);
		float thresh = (float)threshInt;
		int dx = x - (int)last.m_templateID;
		int dy = y - (int)last.m_readyFrame;
		Coord3D delta;
		delta.x = (float)dx;
		delta.y = (float)dy;
		delta.z = 0.0f;
		if (delta.length() < thresh)
			return;
		if (delta.length() > thresh * g_Va00BC2428)
		{
			delta.normalize();
			float scaled = thresh * g_00BFD26C;
			x = (int)last.m_templateID + (int)(scaled * delta.x);
			y = (int)last.m_readyFrame + (int)(scaled * delta.y);
			t.m_templateID = (unsigned int)x;
			t.m_readyFrame = (unsigned int)y;
		}
		if (x < m_minX)
			m_minX = x;
		else if (x > m_maxX)
			m_maxX = x;
		if (y < m_minY)
			m_minY = y;
		else if (y > m_maxY)
			m_maxY = y;
	}
	m_list.push_back(t);
}
