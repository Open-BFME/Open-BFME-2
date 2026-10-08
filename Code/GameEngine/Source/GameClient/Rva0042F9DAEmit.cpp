// cl: /MD
// ?Rva0042F9DAEmit@@YAXXZ, retail 0x0042F9DA, 39 bytes.
// Free emit of MSG 0x3EC with bool true then tail to InGameUI slot 0x110.
// Evidence: globals MessageStreamSubsystem TheInGameUI; rowed appendBooleanArgument 0x0030F963; slots 0x48 0x110 per ControlBarToggle0031AFDE precedent.
class GameMessage
{
public:
	void appendBooleanArgument(bool arg);
};

class MessageStream
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual GameMessage *appendType(int type);
};

class InGameUI
{
public:
	virtual void w00();
	virtual void w01();
	virtual void w02();
	virtual void w03();
	virtual void w04();
	virtual void w05();
	virtual void w06();
	virtual void w07();
	virtual void w08();
	virtual void w09();
	virtual void w10();
	virtual void w11();
	virtual void w12();
	virtual void w13();
	virtual void w14();
	virtual void w15();
	virtual void w16();
	virtual void w17();
	virtual void w18();
	virtual void w19();
	virtual void w20();
	virtual void w21();
	virtual void w22();
	virtual void w23();
	virtual void w24();
	virtual void w25();
	virtual void w26();
	virtual void w27();
	virtual void w28();
	virtual void w29();
	virtual void w30();
	virtual void w31();
	virtual void w32();
	virtual void w33();
	virtual void w34();
	virtual void w35();
	virtual void w36();
	virtual void w37();
	virtual void w38();
	virtual void w39();
	virtual void w40();
	virtual void w41();
	virtual void w42();
	virtual void w43();
	virtual void w44();
	virtual void w45();
	virtual void w46();
	virtual void w47();
	virtual void w48();
	virtual void w49();
	virtual void w50();
	virtual void w51();
	virtual void w52();
	virtual void w53();
	virtual void w54();
	virtual void w55();
	virtual void w56();
	virtual void w57();
	virtual void w58();
	virtual void w59();
	virtual void w60();
	virtual void w61();
	virtual void w62();
	virtual void w63();
	virtual void w64();
	virtual void w65();
	virtual void w66();
	virtual void w67();
	virtual void notify();
};

extern class MessageStream *TheMessageStream;
extern InGameUI *TheInGameUI;

void Rva0042F9DAEmit()
{
	GameMessage *msg = TheMessageStream->appendType(0x3EC);
	msg->appendBooleanArgument(true);
	TheInGameUI->notify();
}
