// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
// ?rva001E11F8@Rva001E11F8@@QAEXHH@Z retail 0x001E11F8 41B
// Evidence: unlock lane adjacent to Gen_00428090 bfmeContains 0x001E11D6 with same list at +4 and node next +0 item +8. Caller 0x000CED4B forwards same two ints as notify HH. Virtual slot 0xC.
class Rva001E11F8_Item
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void f(int a, int b);
};

struct Rva001E11F8_Node
{
	Rva001E11F8_Node *m_next;
	int m_gap;
	Rva001E11F8_Item *m_item;
};

class Rva001E11F8
{
public:
	void rva001E11F8(int a, int b);
private:
	int m_head;
	Rva001E11F8_Node *m_list;
};

void Rva001E11F8::rva001E11F8(int a, int b)
{
	for (Rva001E11F8_Node *node = m_list->m_next; node != (Rva001E11F8_Node *)m_list; node = node->m_next)
		node->m_item->f(a, b);
}
