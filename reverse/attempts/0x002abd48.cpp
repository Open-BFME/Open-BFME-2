// ?bfmeDetachCFF@BfmeOwnerCFF@@QAEXPAVBfmeThingCFF@@@Z
// partial score=0.95 date=2026-10-04
// cl: /O1 /DNDEBUG /MD /Oy-
// ?bfmeDetachCFF@BfmeOwnerCFF@@QAEXPAVBfmeThingCFF@@@Z, RVA 0x002ABD48, size 75.
// Evidence: LINK BONUS caller BfmeConv593 bfmeGoCFF; list at +0x32c node next+0 prev+4 data+8; DetachList struct plus thiscall freenode gives lea esi and mov ecx esi; rowed Rva002ABAC0Free is stdcall so needs row-type review; remaining redundant push-store.
// ?bfmeDetachCFF@BfmeOwnerCFF@@QAEXPAVBfmeThingCFF@@@Z present-unmatched
class BfmeThingCFF;
struct PoolNode002ABAC0
{
	PoolNode002ABAC0* m_prev;
	PoolNode002ABAC0* m_next;
};
struct DetachNode
{
	DetachNode* m_next;
	DetachNode* m_prev;
	BfmeThingCFF* m_data;
};
struct DetachList
{
	DetachNode* m_head;
	void freenode(void** out, PoolNode002ABAC0* n);
};
class BfmeOwnerCFF
{
public:
	void bfmeDetachCFF(BfmeThingCFF* what);
private:
	unsigned char m_pad[0x32c];
	DetachList m_list;
};
void BfmeOwnerCFF::bfmeDetachCFF(BfmeThingCFF* what)
{
	for (DetachNode* p = m_list.m_head->m_next; p != m_list.m_head; p = p->m_next)
	{
	}
	for (DetachNode* p = m_list.m_head->m_next; p != m_list.m_head; p = p->m_next)
	{
		if (what == p->m_data)
		{
			m_list.freenode((void**)&what, (PoolNode002ABAC0*)p);
			break;
		}
	}
	for (DetachNode* p = m_list.m_head->m_next; p != m_list.m_head; p = p->m_next)
	{
	}
}
