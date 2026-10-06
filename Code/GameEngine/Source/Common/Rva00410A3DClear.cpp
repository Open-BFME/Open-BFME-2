// cl: /MD
//
// ?rva00410A3D@Rva00410A3D@@QAEXXZ, retail 0x00410A3D, 73 bytes. Chain lane:
// hashtable clear over buckets at +4/+8 with count at +0x10. Walks each chain
// via +0 next and deletes via rowed ?rva0041097B@Rva0041097B@@QAEXPAX@Z then
// zeroes buckets and count. Caller 0x00410C57.
class Rva0041097B
{
public:
	void rva0041097B(void *p);
};

struct Rva00410A3DNode
{
	Rva00410A3DNode *_M_next;
};

class Rva00410A3D
{
public:
	void rva00410A3D();

private:
	int m_pad0;
	Rva00410A3DNode **m_buckets;
	Rva00410A3DNode **m_finish;
	int m_padC;
	unsigned int m_count;
};

void Rva00410A3D::rva00410A3D()
{
	for (unsigned int i = 0; i < (unsigned int)(m_finish - m_buckets); ++i) {
		Rva00410A3DNode *cur = m_buckets[i];
		while (cur) {
			Rva00410A3DNode *next = cur->_M_next;
			((Rva0041097B *)this)->rva0041097B(cur);
			cur = next;
		}
		m_buckets[i] = 0;
	}
	m_count = 0;
}
