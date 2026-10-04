// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common -DNDEBUG -DWIN32 -D_WINDOWS -MD /Os
// Drain the node at +0x10. When +0xC is null and +0x7C is set, run
// BfmeThingCDE::bfmeGoCDE on that pointer; otherwise the sibling at 0x006BD1A0.

class BfmeThingCDE
{
public:
	void bfmeGoCDE();
};
class Rva006BDB00Node
{
public:
	char m_pad0C[0xC];
	void *m_alt;
	char m_pad7C[0x7C - 0x10];
	BfmeThingCDE *m_thing;
	char m_pad80[0x110 - 0x80];
	Rva006BDB00Node *m_next;
	Rva006BDB00Node *m_prev;
};

// Only the head field drain reads is declared; handleNode is the sibling body
// at 0x006BD1A0, called but not placed here.
class Rva006BDB00
{
public:
	void drain();

private:
	char m_pad0C[0xC];
	Rva006BDB00Node *m_tail;
	Rva006BDB00Node *m_head;
	void handleNode(Rva006BDB00Node *node);
};

void Rva006BDB00::drain()
{
	Rva006BDB00Node *node = m_head;
	while (node)
	{
		if (node->m_alt == 0 && node->m_thing != 0)
			node->m_thing->bfmeGoCDE();
		else
			handleNode(node);
		node = m_head;
	}
}
