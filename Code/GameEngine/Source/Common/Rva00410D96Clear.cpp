// cl: /MD
//
// ?rva00410D96@Rva00410D96@@QAEXXZ, retail 0x00410D96, 73 bytes. Chain lane:
// hashtable clear over buckets at +4/+8 with count at +0x10. Walks each chain
// via +0 next and deletes via the 0x00410AAB node free helper then zeroes
// buckets and count. Same 73B shape as rowed ?rva00410A3D@Rva00410A3D@@QAEXXZ
// (Rva00410A3DClear.cpp); only the node-free callee differs (0x00410AAB vs
// 0x0041097B). The call keeps the member shape (push node, mov ecx,this), so
// the helper is invoked through a member-shaped alias pinned in symbols.csv
// to the rowed ?Rva00410AABFree@@YGXPAX@Z body.
class Rva00410AABHelper
{
public:
	void rva00410AAB(void *p);
};

struct Rva00410D96Node
{
	Rva00410D96Node *_M_next;
};

class Rva00410D96
{
public:
	void rva00410D96();

private:
	int m_pad0;
	Rva00410D96Node **m_buckets;
	Rva00410D96Node **m_finish;
	int m_padC;
	unsigned int m_count;
};

void Rva00410D96::rva00410D96()
{
	for (unsigned int i = 0; i < (unsigned int)(m_finish - m_buckets); ++i) {
		Rva00410D96Node *cur = m_buckets[i];
		while (cur) {
			Rva00410D96Node *next = cur->_M_next;
			((Rva00410AABHelper *)this)->rva00410AAB(cur);
			cur = next;
		}
		m_buckets[i] = 0;
	}
	m_count = 0;
}
