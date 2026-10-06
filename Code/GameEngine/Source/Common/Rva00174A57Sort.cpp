// cl: /O1 /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// Dump-lane range 5: sort-then-forward at 0x174A57 (51B). Early-out when
// +0x18==+0x1C; else cdecl sort(a,b,0x57368A), thiscall 0x17438B(a,b),
// tail-jump to 0x17437D. Address-derived names.

// ?rva00174870@@YAXHHH@Z
void rva00174870(int a, int b, int c);
class Rva0017438B
{
public:
	void rva0017438B(int a, int b);
};
class Rva0017437D
{
public:
	void rva0017437D();
};
class Rva00174A57
{
public:
	void rva00174A57();
private:
	char m_pad[0x18];
	int m_18;
	volatile int m_1C;
};

// ?rva00174A57@Rva00174A57@@QAEXXZ
void Rva00174A57::rva00174A57()
{
	if (m_18 == m_1C)
		return;
	::rva00174870(m_18, m_1C, 0x57368A);
	((Rva0017438B *)this)->rva0017438B(m_18, m_1C);
	return ((Rva0017437D *)this)->rva0017437D();
}
