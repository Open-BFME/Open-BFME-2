// cl: /DNDEBUG /MD
// ?rva0028B595@Object@@QAEXPAPAV1@0@Z @0x0028B595 89B: Object intrusive
// doubly-linked unlink via +0x8C prev and +0x90 next. When prev non-null its
// +0x90 is set to next else second out-param takes next; when next non-null
// its +0x8C is set to prev else first out-param takes prev; then both links
// cleared. Evidence: retail mov/test/je plus [eax+0x90]/[eax+0x8C] stores
// plus [esp+4]/[esp+8] out-params plus and [ecx+...],0 zeroing; ret 8.
class Object
{
public:
	void rva0028B595(Object **a, Object **b);

private:
	char m_pad8C[0x8C];
	Object *m_prev8C;
	Object *m_next90;
};

void Object::rva0028B595(Object **a, Object **b)
{
	if (m_prev8C != 0)
		m_prev8C->m_next90 = m_next90;
	else
		*b = m_next90;
	if (m_next90 != 0)
		m_next90->m_prev8C = m_prev8C;
	else
		*a = m_prev8C;
	m_next90 = 0;
	m_prev8C = 0;
}
