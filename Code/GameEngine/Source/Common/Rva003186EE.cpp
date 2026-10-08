// cl: /MD
// ?rva003186EE@Rva003186EE@@QAEXHHH@Z @0x003186EE 43B
// Leaf __thiscall 3-arg setter: if this+0x10 != arg1, store arg1, store arg3 to +0x28,
// store arg2 to [TheTriggerManager+0x98], then rowed 0x003184B8 with same this.
// Evidence: callee 0x003184B8 rowed Rva003184B8 same offsets; global VA 0x00DFEC68; callers 0x00318799 0x004943B1.
class Rva00285D34;
class Rva002872BA;
extern Rva002872BA *TheTriggerManager;

class Rva003184B8
{
public:
	void rva003184B8();
};

class Rva003186EE
{
public:
	void rva003186EE(int a, int b, int c);
private:
	unsigned char m_pre10[0x10];
	int m_10;
	unsigned char m_pad14[0x28 - 0x14];
	int m_28;
};

void Rva003186EE::rva003186EE(int a, int b, int c)
{
	if (m_10 == a)
		return;
	m_10 = a;
	m_28 = c;
	*(int *)((char *)TheTriggerManager + 0x98) = b;
	((Rva003184B8 *)this)->rva003184B8();
}
