// cl: /DNDEBUG /MD
// ?rva0057E59B@Rva0057E97A@@QAEXH_N@Z @0x0057E59B 26B
// Window enable helper of the Rva0057E97A holder: w = m_begin[index] at +0x7C,
// if w is null skip, else w->winEnable(enable) via rowed 0x00313BEC.
// Same class and flags as the neighbour 0x0057E97A TU. Evidence: packet
// disasm, single caller 0x0043DBE0, prev/next rows.
class GameWindow
{
public:
	int winEnable(bool enable);
};

class Rva0057E97A
{
public:
	void rva0057E59B(int index, bool enable);
private:
	char m_pad0[0x7C]; // +0x00..+0x7B
	class GameWindow **m_begin; // +0x7C
};

void Rva0057E97A::rva0057E59B(int index, bool enable)
{
	class GameWindow *w = m_begin[index];
	if (w != 0)
		w->winEnable(enable);
}
