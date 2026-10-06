// cl: /DNDEBUG /MD
//
// ?rva0049CD24@Rva0049CD24@@QAEXPAVObject@@@Z @0x0049CD24 43B.
// When the argument, the pointer at this+8, and the dword at that
// object's +0x45C are all nonzero, forwards them to GameLogic::rva0023D0C2.
// TheGameLogic is the global at VA 0x00DFE78C.

class Object;

class Holder
{
public:
	char m_pad[0x45C];
	int m_handle;
};

class GameLogic
{
public:
	void rva0023D0C2(Object *obj, int handle);
};

extern GameLogic *TheGameLogic;

class Rva0049CD24
{
public:
	void rva0049CD24(Object *obj);

private:
	char m_pad[8];
	Holder *m_holder;
};

void Rva0049CD24::rva0049CD24(Object *obj)
{
	if (obj == 0)
		return;
	Holder *holder = m_holder;
	if (holder == 0)
		return;
	int handle = holder->m_handle;
	if (handle == 0)
		return;
	TheGameLogic->rva0023D0C2(obj, handle);
}
