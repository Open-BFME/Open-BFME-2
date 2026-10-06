// cl: /O1 /DNDEBUG /MD
//
// ?rva0049C51A@Rva0049C51A@@QAEXHHHHH@Z @0x0049C51A 57B.
// Look up the id at +0x20 through GameLogic::findObjectByID. Forward the
// five arguments to 0x004500A3 when that object is missing or the byte
// at +0x69 is clear.

enum ObjectID
{
	OBJECT_ID_NONE = 0
};

class Object;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class Rva004500A3
{
public:
	void rva004500A3(int a, int b, int c, int d, int e);
};

class Rva0049C51A
{
public:
	void rva0049C51A(int a, int b, int c, int d, int e);

private:
	char m_pad[0x20];
	ObjectID m_id;
	char m_pad24[0x69 - 0x24];
	unsigned char m_flag69;
};

void Rva0049C51A::rva0049C51A(int a, int b, int c, int d, int e)
{
	Object *found = TheGameLogic->findObjectByID(m_id);
	if (found == 0 || m_flag69 == 0)
		((Rva004500A3 *)this)->rva004500A3(a, b, c, d, e);
}
