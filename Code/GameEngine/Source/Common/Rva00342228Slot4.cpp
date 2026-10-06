// cl: /DNDEBUG /MD /EHsc
//
// ?rva0034230C@Rva00342228@@UAEHXZ, retail 0x0034230C, 64 bytes.
// Virtual slot 4 (offset 0x10) of vtable 0x00811900, the class whose dtor
// ??1Rva00342228@@UAE@XZ is rowed in Rva00342228Dtor.cpp (same // cl: line,
// sibling of the landed Rva00342157 slot-4 body at 0x003421B2). Body:
// m_ptr20 = m_ptr18->slot9() (call [eax+0x24]); frame = TheGameLogic->m_frame
// (kept in edi across the next call); r = GetGameLogicRandomValue(0,
// Int00DBA4E4, AIStates.cpp, 0x3D75) (rowed int twin 0x00233FF4); m_24 =
// r + frame; tail-call m_ptr20->slot7() (jmp [eax+0x1C]). TheGameLogic
// 0x00DFE78C (+0x40 frame) per GameLogicRva003BC6C7Wrapper precedent; the hi
// bound is the dword at retail VA 0x00DBA4E4 (proved by the sibling landing;
// the packet's "= data 0x009BA4E4" note is garbled); the file literal at
// retail VA 0x00812248 is GameLogic\AI\AIStates.cpp (proved by the sibling
// landing's string-ref gate).

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

class Rva00342228Member;

class Rva00342228Ref18
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
	virtual Rva00342228Member *getPtr20();
};

class Rva00342228Member
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

class Rva00342228 : public Rva0049B47C
{
public:
	virtual void _slot01();
	virtual void _slot02();
	virtual void _slot03();
	virtual int rva0034230C();

private:
	char m_pad0C[0x18 - 0x0C];
	Rva00342228Ref18 *m_ptr18;
	char m_pad1C[0x20 - 0x1C];
	Rva00342228Member *m_ptr20;
	unsigned int m_24;
};

int Rva00342228::rva0034230C()
{
	m_ptr20 = m_ptr18->getPtr20();
	unsigned int frame = TheGameLogic->m_40;
	int r = GetGameLogicRandomValue(0, Int00DBA4E4, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\AI\\AIStates.cpp", 0x3D75);
	m_24 = r + frame;
	return m_ptr20->method1C();
}
