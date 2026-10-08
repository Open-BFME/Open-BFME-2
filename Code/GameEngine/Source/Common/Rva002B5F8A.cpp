// cl: /MD
// ?rva002B5F8A@Rva002B5F8A@@QAE_NXZ @0x002B5F8A 98B: __thiscall bool emit.
// When +0xF4 is below 6 and the pinned 0x2B5EB5 probe passes, builds a
// message through the established MessageStreamSubsystem slot-18
// appendMessage(0x6A6), appends +0xFC, +0xF4 and the +0x98 object's +0x14
// through rowed 0x30F936, sets +0x10A and returns true.
// Evidence: retail
//   push esi; mov esi,ecx; cmp [esi+0xF4],6; jge FAIL
//   call 0x2B5EB5; test al,al; je FAIL
//   mov ecx,[0xE00950]; mov eax,[ecx]; push edi; push 0x6A6
//   call [eax+0x48]; push [esi+0xFC]; mov edi,eax; mov ecx,edi
//   call 0x30F936; push [esi+0xF4]; mov ecx,edi; call 0x30F936
//   mov eax,[esi+0x98]; push [eax+0x14]; mov ecx,edi; call 0x30F936
//   pop edi; mov byte [esi+0x10A],1; mov al,1; pop esi; ret
//   FAIL: xor al,al; pop esi; ret
// Boundary: 98B [0x2B5F8A,0x2B5FEC); prev ret, next jmp (0x2B5FEC).
// The slot-18 view and MessageStreamSubsystem name follow the established
// GameWindowTransitionsHandlerState pattern. 0x6A6 passes as int (same push).
class GameMessage
{
public:
	enum Type
	{
		T_6A6 = 0x6A6
	};
	void appendIntegerArgument(int arg);
};

class MessageStream
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17();
	virtual GameMessage *appendMessage(GameMessage::Type type);
};

extern class MessageStream *TheMessageStream;

struct Rva002B5F8AHolder98
{
	char m_pad[0x14];
	int m_14; // +0x14
};

class Rva002B5EB5
{
public:
	bool rva002B5EB5();
};

class Rva002B5F8A
{
public:
	bool rva002B5F8A();
private:
	char m_pad[0x98];
	Rva002B5F8AHolder98 *m_ptr98; // +0x98
	char m_pad9C[0xF4 - 0x9C];
	int m_f4; // +0xF4
	char m_padF8[0xFC - 0xF8];
	int m_fc; // +0xFC
	char m_pad100[0x10A - 0x100];
	unsigned char m_10A; // +0x10A
};

bool Rva002B5F8A::rva002B5F8A()
{
	if (m_f4 < 6) {
		if (((Rva002B5EB5 *)this)->rva002B5EB5()) {
			GameMessage *m = TheMessageStream->appendMessage(GameMessage::T_6A6);
			m->appendIntegerArgument(m_fc);
			m->appendIntegerArgument(m_f4);
			m->appendIntegerArgument(m_ptr98->m_14);
			m_10A = 1;
			return true;
		}
	}
	return false;
}
