// ?AdvancePastPortal@Path@@QAEXW4ScienceType@@PAV?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@@Z
// partial score=0.93 date=2026-10-01
// cl: /DNDEBUG /MD /Oy-
// ?AdvancePastPortal@Path@@QAEXW4ScienceType@@PAV?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@@Z retail 0x0036617B 129B
// Unlock over rowed vector<ScienceType>::push_back 0x002E01C6. Evidence: search
// list via +8 for +0x20==st then push range filtering 0x7fffffff; slot reuse
// st as push temp (&[ebp+8]); float at +0x14 zeroed via movss; caller 0x1E7542.
enum ScienceType
{
	SCIENCE_INVALID = 0x7fffffff
};

namespace _STL
{
	template<typename T> class allocator;
	template<typename T, typename A> class vector
	{
	public:
		void push_back(const T &v);
	};
}

struct Rva0036617BNode
{
	char m_pad00[8];
	Rva0036617BNode *m_next08;
	char m_pad0C[20];
	ScienceType m_value20;
};

class Path
{
	void *m_00;
	void *m_head04;
	void *m_08;
	void *m_pad0C;
	Rva0036617BNode *m_cur10;
	float m_14;
public:
	void AdvancePastPortal(ScienceType st, _STL::vector<ScienceType, _STL::allocator<ScienceType> > *vec);
};

void Path::AdvancePastPortal(ScienceType st, _STL::vector<ScienceType, _STL::allocator<ScienceType> > *vec)
{
	Rva0036617BNode *nil = 0;
	if ((Rva0036617BNode *)m_head04 == nil || m_cur10 == nil)
		return;
	if (st == SCIENCE_INVALID)
		return;
search:
	if (m_cur10->m_value20 == st)
		goto push_phase;
	{
		Rva0036617BNode *next = m_cur10->m_next08;
		m_cur10 = next;
		if (next != nil)
			goto search;
	}
push_phase:
	while (m_cur10 != nil) {
		Rva0036617BNode *node = m_cur10;
		ScienceType v = node->m_value20;
		if (v == SCIENCE_INVALID)
			break;
		Rva0036617BNode *next = node->m_next08;
		if (next == nil)
			goto push;
		if (next->m_value20 == SCIENCE_INVALID)
			break;
push:
		st = v;
		vec->push_back(st);
		m_cur10 = m_cur10->m_next08;
	}
	if (m_cur10 != nil)
		goto done;
	m_cur10 = (Rva0036617BNode *)m_08;
done:
	m_14 = 0.0f;
}
