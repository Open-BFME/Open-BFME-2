// cl: /MD
//
// ?rva0041EA88@Rva0041EA88@@QAEXXZ @0x0041EA88 73B via hashtable clear twin of 0x00410A3D
// Retail walks buckets at +4/+8 with count at +0x10. Walks each chain via +0
// next and deletes via rowed ?rva0041EA2C@Rva0041EA2C@@QAEXPAX@Z then zeroes
// buckets and count. Evidence: callee rowed 0x0041EA2C Locomotor pair free;
// callers 0x0041EBE7 0x0041EC6C 0x0041EBCD; chain from 0x0041EA2C.
class Rva0041EA2C
{
public:
	void rva0041EA2C(void *p);
};

struct Rva0041EA88Node
{
	Rva0041EA88Node *_M_next;
};

class Rva0041EA88
{
public:
	void rva0041EA88();

private:
	int m_pad0;
	Rva0041EA88Node **m_buckets;
	Rva0041EA88Node **m_finish;
	int m_padC;
	unsigned int m_count;
};

void Rva0041EA88::rva0041EA88()
{
	for (unsigned int i = 0; i < (unsigned int)(m_finish - m_buckets); ++i) {
		Rva0041EA88Node *cur = m_buckets[i];
		while (cur) {
			Rva0041EA88Node *next = cur->_M_next;
			((Rva0041EA2C *)this)->rva0041EA2C(cur);
			cur = next;
		}
		m_buckets[i] = 0;
	}
	m_count = 0;
}
