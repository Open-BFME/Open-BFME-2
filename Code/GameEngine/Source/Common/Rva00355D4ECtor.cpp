// cl: /O1 /MD /EHsc
//
// ??0Rva00355D66@@QAE@XZ @0x00355D4E 24B. Derived ctor of Rva00355D66 calling
// base ??0Gen_004902A0@@QAE@XZ then zeroing +8 and setting byte +0xC to 1 with
// derived vtable 0x00814E5C. Evidence: retail mov edx,ecx plus call 0x00355C60
// plus and [edx+8],0 plus mov [edx],0x00814E5C plus mov byte [edx+0xC],1 plus
// mov eax,edx plus ret; dtor at 0x00355D66 clears +8 via TheWindowManager;
// chain from 0x00355C60; unblocks 0x003560A2 and siblings.
class Gen_004902A0
{
public:
	__declspec(noinline) Gen_004902A0();
	virtual ~Gen_004902A0();
	Gen_004902A0 *m_next;
};

extern Gen_004902A0 *g_00E01E1C;

__declspec(noinline) Gen_004902A0::Gen_004902A0()
{
	m_next = g_00E01E1C;
	g_00E01E1C = this;
}

class GameWindow;

class Rva00355D66 : public Gen_004902A0
{
public:
	Rva00355D66();
	virtual ~Rva00355D66();
protected:
	GameWindow *m_win;
private:
	bool m_flag;
};

Rva00355D66::Rva00355D66() : m_win(0), m_flag(true)
{
}
