// ?rva002AE3F4@Rva002AE3F4@@QAEXW4ObjectID@@@Z
// partial score=0.93 date=2026-10-04
// cl: /O1 /MD /GX-
// stlport
// ?rva002AE3F4@Rva002AE3F4@@QAEXW4ObjectID@@@Z @0x002AE3F4 65B
// Evidence: unlock lane, add-if-missing list at +0x754 via rowed find 0x0029B694 and pinned Bridge push_back 0x002A1B6F, caller 0x0048A14E, same pattern as Rva002A1111.
// ?rva002AE3F4@Rva002AE3F4@@QAEXW4ObjectID@@@Z present-unmatched
#include <list>

enum ObjectID
{
	OBJECTID_NONE = 0
};

namespace _STL
{
template <class _InputIter, class _Tp>
_InputIter find(_InputIter __first, _InputIter __last, const _Tp &__val);
}

class BridgeBehaviorObjectIDList
{
public:
	void push_back(const ObjectID &value);
};

class Rva002AE3F4
{
public:
	void rva002AE3F4(ObjectID val);
private:
	char _pad[0x754];
	_STL::list<ObjectID> m_list;
};

void Rva002AE3F4::rva002AE3F4(ObjectID val)
{
	if (_STL::find(m_list.begin(), m_list.end(), val) == m_list.end())
		((BridgeBehaviorObjectIDList &)m_list).push_back(val);
}
