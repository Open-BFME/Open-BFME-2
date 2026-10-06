// cl: /DNDEBUG /MD /EHsc
// ?rva0037B146@Rva0037B146@@QAEXXZ retail 0x0037B146 70B.
// Cleanup helper: if byte at +0xE70 is set return; else walk TheCommandList
// first-message chain (+0xC) and delete nodes whose +0x10 id is in (1000,1999)
// except 1098 via virtual slot0 with 0 plus operator delete 0x0002FD60.
// Evidence: callees rowed 0x0002FD60; global TheCommandList 0x00A00954 in use;
// caller 0x0037BC71 shares +0xE70/+0xE78 class; prev/next Recorder neighbours.
class CommandList;
class GameMessage
{
public:
	virtual ~GameMessage();
	GameMessage *m_next; // +4
	char m_pad08[0x10 - 0x08];
	int m_id10; // +0x10
};

class CommandList
{
public:
	char m_pad00[0x0C];
	GameMessage *m_first; // +0x0C
};

extern CommandList *TheCommandList;

class Rva0037B146
{
public:
	void rva0037B146();
private:
	char m_pad00[0xE70];
	unsigned char m_flagE70; // +0xE70
};

void Rva0037B146::rva0037B146()
{
	if (m_flagE70 != 0)
		return;
	for (GameMessage *cur = TheCommandList->m_first; cur != 0;) {
		int id = cur->m_id10;
		GameMessage *next = cur->m_next;
		if (id <= 0x3E8)
			goto advance;
		if (id >= 0x7CF)
			goto advance;
		if (id == 0x44A)
			goto advance;
		::delete cur;
advance:
		cur = next;
	}
}
