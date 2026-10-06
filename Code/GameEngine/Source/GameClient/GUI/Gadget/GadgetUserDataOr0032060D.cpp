// cl: /Ob0
// ?Rva0032060D@@YAXPAVGameWindow@@H@Z @0x0032060D 25B.
// ORs mask into gadget user data +0xC. Null window or null user data returns.
// Callers pass 8 and 0x21. winGetUserData 0x005C4ACD rowed.

class GameWindow
{
public:
	void *winGetUserData();
};

#ifndef NULL
#define NULL 0
#endif

struct Rva0032060DData
{
	char m_pad[0xC];
	int m_flags;
};

void __cdecl Rva0032060D(GameWindow *window, int value)
{
	Rva0032060DData *data;

	if (window == NULL)
		return;
	data = (Rva0032060DData *)window->winGetUserData();
	if (data == NULL)
		return;
	data->m_flags |= value;
}
