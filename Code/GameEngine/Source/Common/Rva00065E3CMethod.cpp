// cl: /MD /EHsc
// ?rva00065E3C@Rva0065CA4@@QAEXM@Z @0x00065E3C 153B accumulates float into list items and purges thresholded ones via temp Rva0065CA4 list
// Evidence: calls rowed ??0GenericMultiListClass 0x65815 Internal_Add 0x6107A0 Internal_Remove 0x610930 Internal_Remove_List_Head 0x6109A0; temp vtable 0x7C5C78 with dtor pin ??1Rva0065CA4 0x65CA4; outer head at +4/next at +8 with item ptr at node+0xC and floats at +0x18/+0x20; delete via slot0 with 1
class MultiListObjectClass
{
public:
	virtual ~MultiListObjectClass();
	void *m_listNode04;
};
class GenericMultiListClass
{
public:
	GenericMultiListClass();
	virtual ~GenericMultiListClass();
protected:
	bool Internal_Add(MultiListObjectClass *obj, bool onlyonce);
	bool Internal_Remove(MultiListObjectClass *obj);
	MultiListObjectClass *Internal_Remove_List_Head();
public:
	void *m_headPrev04;
	void *m_headNext08;
	void *m_headNextList0C;
	void *m_headObject10;
	void *m_headList14;
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
	Rva0065CA4 tmp;
	for (Rva00065E3CNode *node = (Rva00065E3CNode *)m_headNext08; node != (Rva00065E3CNode *)&m_headPrev04; node = node->m_next04) {
		Rva00065E3CItem *item = (Rva00065E3CItem *)node->m_obj0C;
		item->m_accum20 += value;
		if (item->m_accum20 >= item->m_thresh18) {
			tmp.Internal_Add(item, true);
		}
	}
	while (tmp.m_headNext08 != &tmp.m_headPrev04) {
		MultiListObjectClass *obj = tmp.Internal_Remove_List_Head();
		Internal_Remove(obj);
		delete obj;
	}
}
