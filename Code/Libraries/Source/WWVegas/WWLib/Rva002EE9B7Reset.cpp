// cl: /MD
// ?rva002EE9B7@Rva002EE9B7@@QAEXXZ @0x002EE9B7 41B: pool-block reset releases list at +4 via 0x002EADB4 then self-links +8/+12 and clears flags. Evidence: same 41B shape as Rva002EB416::rva002EE9E0 plus caller 0x002F0B67 plus LINK BONUS via 0x003983D4.
struct _Rva002EADB4Node {
    void *_m_link;
    int _m_unk4;
    _Rva002EADB4Node *_m_next;
    _Rva002EADB4Node *_m_child;
};
struct Rva002EADB4 {
    void rva002EADB4(_Rva002EADB4Node *p);
};
class Rva002EE9B7
{
public:
	void rva002EE9B7();
private:
	_Rva002EADB4Node *m_head;
	int m_flag;
};
void Rva002EE9B7::rva002EE9B7()
{
	if (m_flag == 0)
		return;
	((Rva002EADB4 *)this)->rva002EADB4((_Rva002EADB4Node *)m_head->_m_unk4);
	m_head->_m_next = m_head;
	m_head->_m_unk4 = 0;
	m_head->_m_child = m_head;
	m_flag = 0;
}
