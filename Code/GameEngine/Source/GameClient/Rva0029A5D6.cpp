// cl: /DNDEBUG /MD /EHsc
// ?rva0029A5D6@Rva0029A5D6@@QAEXH@Z @0x0029A5D6 54B. TheMouse null-checked v19 then filtered store at +0x800. Evidence: global TheMouse 0x00DFDCA0 slot 0x4C callers 0x0029A814 pattern DisplaySetHeight.
class Mouse
{
public:
#define V(n) virtual void pad##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10)
	V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18)
#undef V
	virtual void v19(int arg);
};
extern Mouse *TheMouse;
class Rva0029A5D6
{
public:
	void rva0029A5D6(int arg);
private:
	unsigned char m_pad[0x7FC];
	int m_7FC;
	int m_800;
};

void Rva0029A5D6::rva0029A5D6(int arg)
{
	Mouse *mouse = TheMouse;
	if (mouse == 0)
		return;
	mouse->v19(arg);
	if (m_7FC != 2)
		return;
	if (arg == 2)
		return;
	if (arg == 3)
		return;
	m_800 = arg;
}
