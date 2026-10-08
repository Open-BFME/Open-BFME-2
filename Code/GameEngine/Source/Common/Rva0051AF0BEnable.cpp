// cl: /GX-
// ?Rva0051AF0BEnable@@YAXH@Z @0x0051AF0B 59B.
// One-shot enabler with stored int: if global 0x00A04910 is null or its byte
// at +0x278 is set, return; else set it, store the arg at +0x280, set the byte
// at +0x54 of global 0x00A01E48, then tail-jmp to rowed enable 0x00222479 on
// global 0x009FE4CC. Same idiom as rowed Rva0050E9D3Enable plus the stored
// value; small callers at 0x0051B11E 0x0051B502 pass 0.
// Evidence: unlock lane, unblocks 0x0051B11C 0x00435DE7 0x0051B90B 0x0051B4F7.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
struct GlobalA04910 { char pad[0x278]; unsigned char flag; char pad2[7]; int val; };
extern GlobalA04910 *g_Va00A04910;
struct GlobalA01E48 { char pad[0x54]; unsigned char flag; };
extern GlobalA01E48 *g_Va00A01E48;
class Rva00222479ByteOneSetter { public: void enable(); };
extern Rva00222479ByteOneSetter *g_Va009FE4CC;
void __cdecl Rva0051AF0BEnable(int val)
{
	GlobalA04910 *p = g_Va00A04910;
	if (!p)
		return;
	if (p->flag)
		return;
	p->flag = 1;
	g_Va00A04910->val = val;
	g_Va00A01E48->flag = 1;
	g_Va009FE4CC->enable();
}

// ?Rva0051B11CEnable@@YAXXZ @0x0051B11C 9B.
// Chain lane on 0x0051AF0B above: push 0, call it, pop ecx, ret. Callers at
// 0x00376DC7 0x004028A0 0x004028E4 0x00512E06.
void __cdecl Rva0051B11CEnable(void)
{
	Rva0051AF0BEnable(0);
}

// ?Rva0051B09BEnable@@YAXXZ retail 0x0051B09B 129 bytes.
// Chain via rowed 0x002B2B66. Selection-locked GameMessage path plus fallback.
// Calls rowed isSelectionLocked plus rowed Enable above plus rowed rva002B2B66
// plus rowed appendIntegerArgument plus rowed appendBooleanArgument.
// Globals g_009FEF10 MessageStreamSubsystem g_00E03138 TheInGameUI per packet.
// Caller at 0x0051BF1C.
class BfmeSelectionState
{
public:
	bool isSelectionLocked() const;
};
class Rva002BA8F1Logic;

class Rva002B2B66
{
public:
	int rva002B2B66();
};
class GameMessage
{
public:
	void appendIntegerArgument(int arg);
	void appendBooleanArgument(bool arg);
};
class MessageStream
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual GameMessage *v18(int type);
};
extern MessageStream *TheMessageStream;
struct UnknownE03138
{
	virtual void u0();
	virtual void u1();
	virtual void u2();
	virtual void u3();
	virtual void u4();
	virtual void u5();
	virtual void u6();
	virtual void u7();
	virtual void u8();
	virtual void u9();
	virtual void u10();
	virtual void u11();
	virtual void u12();
	virtual void u13();
	virtual void u14();
	virtual void u15();
	virtual void u16();
	virtual void u17();
	virtual bool u18();
	virtual bool u19(); // native slot4C
	virtual bool u20(); // native slot50
};
// g_00E03138: matched references place it at VA 0xe03138 (retail .data initial value 0).
UnknownE03138 * g_00E03138 = 0;
class InGameUI
{
public:
	char m_pad[0x8c5];
	unsigned char m_flag;
};
extern InGameUI *TheInGameUI;

void __cdecl Rva0051B09BEnable(void)
{
	if ((*(Rva002BA8F1Logic **)&TheLivingWorldLogic) != 0 && ((BfmeSelectionState *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic))->isSelectionLocked()) {
		Rva0051AF0BEnable(0);
		GameMessage *msg = TheMessageStream->v18(0x6b8);
		int v = ((Rva002B2B66 *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic))->rva002B2B66();
		msg->appendIntegerArgument(v);
		return;
	}
	Rva0051AF0BEnable(0);
	if (g_00E03138->u18())
		return;
	GameMessage *msg2 = TheMessageStream->v18(0x448);
	msg2->appendBooleanArgument(false);
	TheInGameUI->m_flag = 1;
}
// ?g_Va00A04910@@3PAUGlobalA04910@@A: the global at VA 0xe04910 is ?g_Va00E04910@@3HA.
#pragma comment(linker, "/alternatename:?g_Va00A04910@@3PAUGlobalA04910@@A=?g_Va00E04910@@3HA")

// Complete native37 boundary3E468F..3E46B4; same existing global provider.
// Two bool vslots at 50 and 4C, short-circuited in that order; no arguments
// or receiver are read. Original subsystem/method semantics remain unproved.
int Rva003E468FCheck()
{
 if (g_00E03138->u20() && !g_00E03138->u19())
  return 1;
 return 0;
}
