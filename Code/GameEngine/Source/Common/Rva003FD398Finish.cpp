// cl: /DNDEBUG /MD /GX
// ??0Rva00064390@@QAE@XZ @0x003FD398 47B. Default ctor for the ring hero's
// shared template-state record: zeroes the four leading floats and the int at
// +0x18, then stores the shared float g_Va007C26F0 into +0x10/+0x14.
// Called as the base subobject of Rva0050406E's ctor (0x0050406E, 12B).
// Note: the body MUST be a constructor, not a plain member function -- MSVC 7.1
// keeps `this` in ecx for an ordinary member fn (emitting `and [ecx+0x18],0` and
// ecx-addressed movss) but copies `this` into eax for a default ctor, which is
// exactly retail's `mov eax,ecx` + eax-addressed shape. Callers at 0x004E1E62
// 0x00503FE6 0x00504071 0x0050464E. Unblocks 0x0050406E 0x00503FD1 0x004E1E35.
extern float g_Va007C26F0;

class Rva00064390
{
public:
	Rva00064390();
private:
	float m_00;
	float m_04;
	float m_08;
	float m_0c;
	float m_10;
	float m_14;
	int m_18;
};

Rva00064390::Rva00064390()
{
	m_18 = 0;
	m_00 = 0.0f;
	m_04 = 0.0f;
	m_08 = 0.0f;
	m_0c = 0.0f;
	float v = g_Va007C26F0;
	m_10 = v;
	m_14 = v;
}