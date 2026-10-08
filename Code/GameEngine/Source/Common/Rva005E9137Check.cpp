// cl: /MD
// ?Rva005E9137Check@@YAEPAVRva00318F42@@@Z @0x005E9137 44B
// Evidence: retail checks g_009FEF10 null then +0xF4 then Rva002B280C::check then tail to 0x00318F42.
// Callers at 0x005E9169 0x005E9180 test al as bool.

class Rva002BA8F1Logic;
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
struct Arg54;
class Rva00318F42
{
public:
	char m_pad[0x20];
	int m_20;
};
class Mbr002E0B30
{
public:
	unsigned char pred();
};
class Rva002B280C
{
public:
	bool rva002B280C(struct Arg54 *a);
};
class Rva002BA8F1Logic
{
public:
	char m_pad[0xF4];
	int m_0F4;
};
unsigned char __cdecl Rva005E9137Check(class Rva00318F42 *a)
{
	class Rva002BA8F1Logic *logic = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic);
	if (logic == 0)
		return 0;
	if (logic->m_0F4 != 0)
		return 0;
	if (((class Rva002B280C *)logic)->rva002B280C((struct Arg54 *)a))
		return ((class Mbr002E0B30 *)a)->pred();
	return 0;
}
// ?rva005E917A@Rva005E917A@@QAEXXZ @0x005E917A 47B
// Evidence: calls Rva005E9137Check then MessageStreamSubsystem slot 0x48 appendType 0x6a9 then GameMessage::appendIntegerArgument.
// Chain on 0x005E9137.
class GameMessage
{
public:
	void appendIntegerArgument(int arg);
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
	virtual class GameMessage *appendType(int type);
};
extern class MessageStream *TheMessageStream;
class Rva005E917A
{
public:
	char m_pad[0x14];
	class Rva00318F42 *m_14;
	void rva005E917A();
};
void Rva005E917A::rva005E917A()
{
	if (Rva005E9137Check(m_14) == 0)
		return;
	class GameMessage *msg = TheMessageStream->appendType(0x6a9);
	msg->appendIntegerArgument(m_14->m_20);
}
