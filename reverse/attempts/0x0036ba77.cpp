// ?rva0036BA77@Rva0036BA77@@QAEXPBVWaypoint@@0@Z
// partial score=0.98 date=2026-10-06
// cl: /O1 /DNDEBUG /MD /arch:SSE2 /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0036BA77@Rva0036BA77@@QAEXPBVWaypoint@@0@Z, RVA 0x0036BA77, 184 bytes.
// Evidence: chain lane caller of rowed Rva003697F9 0x003697F9; vector<Coord3D> local via rowed Vector_base pin + rowed push_back 0x002CE7DC + free 0x00030830; EH prolog; movss via arch:SSE; +0x1f0/+0x540/+0x550 and Waypoint +0xc/+0x10/+0x14/+0x20/+0x4c from retail.
#include <vector>

struct Coord3D
{
	float x;
	float y;
	float z;
	Coord3D() {}
	Coord3D(const Coord3D &that) throw();
};

class Object
{
public:
	char m_pad[4];
};

class Waypoint
{
public:
	char m_pad0[0x0c];
	float m_x0c;
	float m_y10;
	float m_z14;
	char m_pad18[0x20 - 0x18];
	const Waypoint *m_next20;
	char m_pad24[0x4c - 0x24];
	int m_flag4c;
};

struct Rva0035149F
{
	Coord3D *m_start;
	Coord3D *m_finish;
	Coord3D *m_end;
};

class Rva003697F9
{
public:
	void rva003697F9(const Rva0035149F &path, const Object *obstacle, const Waypoint *goal, int unk);
};

struct Sub1F0
{
	char m_pad[0x48];
	float m_f48;
	float getF48() const { return m_f48; }
};

class Rva0036BA77
{
public:
	void rva0036BA77(const Waypoint *head, const Waypoint *goal);
private:
	char m_pad0[0x1f0];
	Sub1F0 *m_p1f0;
	char m_pad1f4[0x540 - 0x1f4];
	float m_f540;
	char m_pad544[0x550 - 0x544];
	bool m_b550;
};

void Rva0036BA77::rva0036BA77(const Waypoint *head, const Waypoint *goal)
{
	if (m_p1f0 != 0)
		m_f540 = m_p1f0->getF48();
	m_b550 = false;
	_STL::vector<Coord3D> path;
	const Waypoint *cur = head;
	if (cur != 0)
	{
		do
		{
			Coord3D tmp;
			tmp.x = cur->m_x0c;
			tmp.y = cur->m_y10;
			tmp.z = cur->m_z14;
			path.push_back(tmp);
			if (cur->m_flag4c == 0)
				goto done;
			cur = cur->m_next20;
		} while (cur != head);
		m_b550 = true;
	}
done:
	((Rva003697F9 *)this)->rva003697F9(*(const Rva0035149F *)&path, (const Object *)0, goal, 0);
}
