// cl: /O1 /MD
// ?rva0053DB02@Rva0053DB02@@QAEXXZ @0x0053DB02 43B
// __thiscall clearing 32 GameWindow slots at +0xDC via rowed Rva003284ED with 0
// plus int array at +0x15C. Evidence: push 0x20 pop edi loop with esi from ecx+0xDC
// plus and [esi+0x80] 0 plus call 0x003284ED plus pop ecx pops; caller at 0x0053DE4C.
class GameWindow;
void __cdecl Rva003284ED(GameWindow *window, int value);

class Rva0053DB02
{
public:
	void rva0053DB02();
private:
	char m_pad[0xDC];
	GameWindow *m_windows[32];
	int m_values[32];
};

void Rva0053DB02::rva0053DB02()
{
	GameWindow **slot = m_windows;
	for (int i = 0; i < 32; ++i, ++slot) {
		GameWindow *w = *slot;
		*(int *)((char *)slot + 0x80) = 0;
		if (w)
			Rva003284ED(w, 0);
	}
}
