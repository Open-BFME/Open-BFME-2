// ?rva003B241A@Rva003B241A@@QAEXXZ @0x003B241A 18B
// cl: /MD
// Leaf forwarder: vtable store plus handle call. Evidence: vtable VA 0x00BC9574 no name yet; callee 0x00306D7B rowed Q1Forwardee handle; offsets 0x4 0x8; callers 40 plus unclaimed; prev 0x003B23F7 next 0x003B242C.
extern const void *const g_00BC9574[];

class Q1Forwardee0000871A
{
public:
	void handle(int value);
};

class Rva003B241A
{
public:
	void rva003B241A();
private:
	char m_pad0[4];
	Q1Forwardee0000871A *m_4;
	int m_8;
};

void Rva003B241A::rva003B241A()
{
	int arg = m_8;
	*(const void **)this = g_00BC9574;
	m_4->handle(arg);
}
