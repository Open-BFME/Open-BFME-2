// cl: /DNDEBUG /MD /EHsc
//
// Intrusive list remove-plus-recycle helper used by the InGameUI slot-96
// find-and-remove body at 0x0029F77E (sole E8 caller, verified by raw
// scan). Unlinks the node through its prev/next words, pushes it onto the
// freelist at 0x00DB8FF4 and reports the predecessor through the out
// parameter. Frameless stdcall leaf with no calls; the freelist rides a
// TU-local extern (DIR32 patches from retail, no pin). Semantic class
// membership is unproven so it rides an address-derived free name;
// opaque behavior.

struct ListNode
{
	void *m_prev;
	void *m_next;
};

extern void *g_freeList001EB130;

// ?removeRecycleRva0029DFC5@@YGXPAX0@Z
void __stdcall removeRecycleRva0029DFC5(void *outParam, void *nodeParam)
{
	ListNode *node = (ListNode *)nodeParam;
	ListNode *next = (ListNode *)node->m_next;
	ListNode *prev = (ListNode *)node->m_prev;
	next->m_prev = prev;
	prev->m_next = next;
	node->m_prev = g_freeList001EB130;
	g_freeList001EB130 = node;
	*(void **)outParam = prev;
}
