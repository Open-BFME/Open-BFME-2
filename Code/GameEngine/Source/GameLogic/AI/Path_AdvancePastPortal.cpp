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

#include "../../../Include/GameLogic/PathNode.h"
#include "../../../Include/GameLogic/PathfindPath.h"

void Path::AdvancePastPortal(ScienceType st, _STL::vector<ScienceType, _STL::allocator<ScienceType> > *vec)
{
	PathNode *nil = 0;
	if (m_path == nil || field_10 == nil)
		return;
	if (st == SCIENCE_INVALID)
		return;
search:
	if (field_10->m_portalID == st)
		goto push_phase;
	{
		PathNode *next = field_10->m_nextOpti;
		field_10 = next;
		if (next != nil)
			goto search;
	}
push_phase:
	while (field_10 != nil) {
		PathNode *node = field_10;
		int v = node->m_portalID;
		if (v == SCIENCE_INVALID)
			break;
		PathNode *next = node->m_nextOpti;
		if (next == nil)
			goto push;
		if (next->m_portalID == SCIENCE_INVALID)
			break;
push:
		st = (ScienceType)v;
		vec->push_back(st);
		field_10 = field_10->m_nextOpti;
	}
	if (field_10 != nil)
		goto done;
	field_10 = m_pathTail;
done:
	field_14 = 0.0f;
}
