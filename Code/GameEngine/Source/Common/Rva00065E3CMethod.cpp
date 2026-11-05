// cl: /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ?rva00065E3C@Rva0065CA4@@QAEXM@Z @0x00065E3C 153B accumulates float into list items and purges thresholded ones via temp Rva0065CA4 list
// Evidence: calls rowed ??0GenericMultiListClass 0x65815 Internal_Add 0x6107A0 Internal_Remove 0x610930 Internal_Remove_List_Head 0x6109A0; temp vtable 0x7C5C78 with dtor pin ??1Rva0065CA4 0x65CA4; outer head at +4/next at +8 with item ptr at node+0xC and floats at +0x18/+0x20; delete via slot0 with 1
#include "../../../Libraries/Source/WWVegas/WWLib/MultiListObjectClass.h"
#include "../../../Libraries/Source/WWVegas/WWLib/GenericMultiListClass.h"
// The temporary dead-item list is ZH's MultiListClass<CameraShakerClass>,
// whose destructor is rowed at 0x00065CA4 (camerashakesystem.cpp).
class CameraShakeSystemClass
{
public:
	class CameraShakerClass;
};
template <class ObjectType> class MultiListClass : public GenericMultiListClass
{
public:
	MultiListClass() {}
	virtual ~MultiListClass();
	using GenericMultiListClass::Internal_Add;
	using GenericMultiListClass::Internal_Remove_List_Head;
};
class Rva0065CA4 : public GenericMultiListClass
{
public:
	Rva0065CA4() {}
	virtual ~Rva0065CA4();
	void rva00065E3C(float value);
};
struct Rva00065E3CNode
{
	void *m_prev00;
	Rva00065E3CNode *m_next04;
	void *m_unk08;
	MultiListObjectClass *m_obj0C;
};
class Rva00065E3CItem : public MultiListObjectClass
{
public:
	char m_pad08[16];
	float m_thresh18;
	float m_unk1C;
	float m_accum20;
};
void Rva0065CA4::rva00065E3C(float value)
{
	MultiListClass<CameraShakeSystemClass::CameraShakerClass> tmp;
	for (Rva00065E3CNode *node = (Rva00065E3CNode *)Head.Next; node != (Rva00065E3CNode *)&Head; node = node->m_next04) {
		Rva00065E3CItem *item = (Rva00065E3CItem *)node->m_obj0C;
		item->m_accum20 += value;
		if (item->m_accum20 >= item->m_thresh18) {
			tmp.Internal_Add(item, true);
		}
	}
	while (tmp.Head.Next != &tmp.Head) {
		MultiListObjectClass *obj = tmp.Internal_Remove_List_Head();
		Internal_Remove(obj);
		delete obj;
	}
}
