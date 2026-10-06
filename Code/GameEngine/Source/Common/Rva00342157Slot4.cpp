// cl: /DNDEBUG /MD /EHsc
//
// ?rva003421B2@Rva00342157@@UAEHXZ, retail 0x003421B2, 66 bytes.
// Virtual slot 4 (offset 0x10) of vtable 0x008118B0, the class whose dtor
// ??1Rva00342157@@UAE@XZ is rowed in Rva00342157Dtor.cpp (same // cl: line).
// Body: m_ptr20 = m_ptr18->slot9() (call [eax+0x24]); m_24 =
// TheGameLogic->m_frame + GetGameLogicRandomValue(0, Int00DBA4E4*3,
// file, 0x3C4F) (rowed int twin 0x00233FF4); tail-call m_ptr20->slot7()
// (jmp [eax+0x1C]). TheGameLogic 0x00DFE78C (+0x40 frame) per
// GameLogicRva003BC6C7Wrapper precedent; the tripled hi bound is the dword
// at retail VA 0x00DBA4E4 (align_diff proved the read; the packet's
// "= data 0x009BA4E4" note was garbled). The file literal at retail VA
// 0x00812248 is "C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\
// GameLogic\AI\AIStates.cpp" (gate string-ref proved it after a placeholder
// failed verification); the class is therefore AI-state shaped but keeps its
// honest Rva00342157 name since identity rests on vtable 0x008118B0 only.

extern int g_Va00DBA4E4;

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

class GameLogic
{
public:
	unsigned char m_pad00[0x40];
	unsigned int m_40;
};
extern GameLogic *TheGameLogic;

#define Int00DBA4E4 g_Va00DBA4E4

class Rva00342157Member;

class Rva00342157Ref18
{
public:
	virtual void _pad00();
	virtual void _pad01();
	virtual void _pad02();
	virtual void _pad03();
	virtual void _pad04();
	virtual void _pad05();
	virtual void _pad06();
	virtual void _pad07();
	virtual void _pad08();
	virtual Rva00342157Member *getPtr20();
};

class Rva00342157Member
{
public:
	virtual void *scalarDeletingDestructor(unsigned int flags);
	virtual void _pad01();
	virtual void _pad02();
	virtual void _pad03();
	virtual void _pad04();
	virtual void _pad05();
	virtual void _pad06();
	virtual int method1C();
};

class Rva0049B47C
{
public:
	virtual ~Rva0049B47C();

private:
	char m_pad04[8];
};

class Rva00342157 : public Rva0049B47C
{
public:
	virtual void _slot01();
	virtual void _slot02();
	virtual void _slot03();
	virtual int rva003421B2();

private:
	char m_pad0C[0x18 - 0x0C];
	Rva00342157Ref18 *m_ptr18;
	char m_pad1C[0x20 - 0x1C];
	Rva00342157Member *m_ptr20;
	unsigned int m_24;
};

int Rva00342157::rva003421B2()
{
	m_ptr20 = m_ptr18->getPtr20();
	int hi = Int00DBA4E4 * 3;
	int r = GetGameLogicRandomValue(0, hi, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\AI\\AIStates.cpp", 0x3C4F);
	m_24 = TheGameLogic->m_40 + r;
	return m_ptr20->method1C();
}
