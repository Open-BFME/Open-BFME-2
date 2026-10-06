// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
//
// ?rva00355290@ArmorTemplate@@QAE_NXZ @0x00355290 45B. Non-empty circular-list
// check at +4 with first-node +8 compared against +8.
// Evidence: caller 0x003552DD passes the rowed ArmorTemplate find result
// (?rva0035516C@Rva0035516C@@QBEPBVArmorTemplate@@W4NameKeyType@@@Z) as this;
// retail walks [ecx+4] circular list counting nodes then compares
// [[ecx+4]]+8 with [ecx+8]; layout matches Rva0035516CArmorFind TU.
struct ArmorListNode
{
	ArmorListNode *m_next; // +0
	int m_4; // +4
	int m_8; // +8
};

class ArmorTemplate
{
public:
	int rva00355290();

private:
	void *m_ptr; // +0
	ArmorListNode *m_head; // +4 circular list head
	int m_check; // +8 compared with first node m_8
};

int ArmorTemplate::rva00355290()
{
	ArmorListNode *cur = m_head->m_next;
	ArmorListNode *head = m_head;
	unsigned int count = 0;
	if (cur != head) {
		do {
			cur = cur->m_next;
			++count;
		} while (cur != head);
		if (count <= 0)
			return false;
		ArmorListNode *first = m_head->m_next;
		if (first->m_8 != m_check)
			return 1;
	}
	return 0;
}
