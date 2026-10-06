// cl: /DNDEBUG /MD /EHsc
//
// Intrusive list remove-plus-recycle twin of 0x0029DFC5 for freelist at 0x00DBA5E8.
// Unlinks node, pushes onto freelist, reports predecessor. Caller 0x0029F3A6. Unlocks 0x0029F34F.
struct ListNode0029DFE9
{
	void *m_prev;
	void *m_next;
};
extern void *g_freeList00239380;
void __stdcall removeRecycleRva0029DFE9(void *outParam, void *nodeParam)
{
	ListNode0029DFE9 *node = (ListNode0029DFE9 *)nodeParam;
	ListNode0029DFE9 *next = (ListNode0029DFE9 *)node->m_next;
	ListNode0029DFE9 *prev = (ListNode0029DFE9 *)node->m_prev;
	next->m_prev = prev;
	prev->m_next = next;
	node->m_prev = g_freeList00239380;
	g_freeList00239380 = node;
	*(void **)outParam = prev;
}
