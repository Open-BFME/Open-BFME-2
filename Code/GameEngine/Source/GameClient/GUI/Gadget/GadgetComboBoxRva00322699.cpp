// cl: /DNDEBUG /MD
// ?Rva00322699@@YAXPAVGameWindow@@H@Z, retail 0x00322699 (38B).
// Null-checks the window and its user data, ORs the Int arg into the data
// dword at +0x0C, then copies that dword to the child at +0x14 (+0x0C) when
// present. Callers pass 4 (0x00570522/0x0057F7EE with Reset+SetMaxChars).
// True owner and field names unknown; layout is honest offsets only.

typedef int Int;

class GameWindow
{
public:
	void *winGetUserData();
};

struct Rva00322699Child
{
	char pad0[0x0C];
	Int flags;
};

struct Rva00322699Parent
{
	char pad0[0x0C];
	Int flags;
	char pad1[0x04];
	Rva00322699Child *child;
};

void Rva00322699(GameWindow *window, Int value)
{
	if (!window)
		return;
	Rva00322699Parent *data = (Rva00322699Parent *)window->winGetUserData();
	if (!data)
		return;
	data->flags |= value;
	Int f = data->flags;
	Rva00322699Child *c = data->child;
	if (!c)
		return;
	c->flags = f;
}
