// cl: /DNDEBUG /MD
// ?rva001514D0@Rva001514D0@@QAEPAXH@Z at 0x001514D0 (37B).
// Indexed getter with 0<=i<1 bounds plus double null guard, returns
// inner array slot at +0x24. Evidence: sibling 0x15148D outer+0/inner+0x14
// shape, single caller 0x7B9A3, unblocks 0x7B93B.

#define NULL 0

struct Inner24
{
	char m_pad00[0x24];
	void *m_items[1];
};

struct Obj14
{
	char m_pad00[0x14];
	Inner24 *m_inner;
};

class Rva001514D0
{
public:
	void *rva001514D0(int index);
private:
	Obj14 *m_ptr;
};

void *Rva001514D0::rva001514D0(int index)
{
	if (index < 0 || index >= 1)
		return NULL;
	Obj14 *obj = m_ptr;
	if (obj == NULL)
		return NULL;
	Inner24 *inner = obj->m_inner;
	if (inner == NULL)
		return NULL;
	return inner->m_items[index];
}
