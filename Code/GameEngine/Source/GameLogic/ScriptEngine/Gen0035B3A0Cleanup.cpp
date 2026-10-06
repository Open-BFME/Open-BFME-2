// cl: /DNDEBUG /MD /EHsc
//
// Ported from Open-BFME-1 GameEngine/Source/GameLogic/ScriptEngine/Gen0035B3A0Cleanup.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?cleanup@Gen0035B3A0@@QAEXXZ 0x003B7362 (39B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).

class NestedAt0C
{
public:
	void cleanup(void);
};

class NestedAt2C
{
public:
	void cleanup(void);
};

class Gen0035B3A0
{
public:
	void cleanup(void);
	void unlink(void *slot);

private:
	void *m_unused0;
	int m_slot4;
	unsigned char m_pad[0xC - 8];
	NestedAt0C m_at0C;
	unsigned char m_pad2[0x2C - 0xC - sizeof(NestedAt0C)];
	NestedAt2C m_at2C;
};

// @?cleanup@Gen0035B3A0@@QAEXXZ 0x0035B3A0
void Gen0035B3A0::cleanup(void)
{
	unlink(this ? &m_slot4 : 0);
	m_at0C.cleanup();
	m_at2C.cleanup();
}
