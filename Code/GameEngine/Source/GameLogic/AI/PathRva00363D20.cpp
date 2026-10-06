// cl: /DNDEBUG /MD
//
// ?rva00363D20@Rva00363D20@@QAENXZ @0x00363D20 (84B).
// Unlock path-length sum over consecutive PathNode positions (+0xC) via
// rowed Rva00363C71Approx 0x00363C71 plus BfmeZeroRange float 0. Evidence:
// sibling PathDistance proves Coord3D shape and Approx double clearly,
// PathCtor proves /O1 flags, callers 7 unclaimed large bodies need length.

struct Coord3D
{
	float x;
	float y;
	float z;
};

double __cdecl Rva00363C71Approx(const Coord3D *a, const Coord3D *b);
double __cdecl Rva00363CF3Distance(const Coord3D *a, const Coord3D *b);
extern const float BfmeZeroRange; // ?BfmeZeroRange@@3MB

struct PathNode
{
	char m_pad00[8];
	PathNode *m_next; // +8
	Coord3D m_pos; // +0xC
};

struct Rva00363D20Head
{
	char m_pad00[8];
	PathNode *m_first; // +8
};

class Rva00363D20
{
public:
	double rva00363D20();
	double rva00363D74();

private:
	Rva00363D20Head *m_head; // +0
	Coord3D m_start; // +4
};

double Rva00363D20::rva00363D20()
{
	PathNode *first = 0;
	if (m_head != 0)
		first = m_head->m_first;
	if (first != 0) {
		float acc = Rva00363C71Approx(&first->m_pos, &m_start);
		PathNode *cur = m_head->m_first;
		while (cur->m_next != 0) {
			acc += Rva00363C71Approx(&cur->m_next->m_pos, &cur->m_pos);
			cur = cur->m_next;
		}
		return acc;
	}
	return BfmeZeroRange;
}

// ?rva00363D74@Rva00363D20@@QANXZ, retail 0x00363D74, 84 bytes: the same path-length
// loop over the rowed Rva00363CF3Distance instead of Rva00363C71Approx, the only
// difference from rva00363D20's bytes.
double Rva00363D20::rva00363D74()
{
	PathNode *first = 0;
	if (m_head != 0)
		first = m_head->m_first;
	if (first != 0) {
		float acc = Rva00363CF3Distance(&first->m_pos, &m_start);
		PathNode *cur = m_head->m_first;
		while (cur->m_next != 0) {
			acc += Rva00363CF3Distance(&cur->m_next->m_pos, &cur->m_pos);
			cur = cur->m_next;
		}
		return acc;
	}
	return BfmeZeroRange;
}
