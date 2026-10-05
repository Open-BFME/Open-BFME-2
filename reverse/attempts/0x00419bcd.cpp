// ?Rva00419BCDCreate@@YAPAXXZ
// partial score=0.9 date=2026-10-05
// cl: /O1 /MD
//
// ?Rva00419BFAInit@@YAXXZ, retail 0x00419BFA, 105 bytes.
// Singleton init registering the game command group and the stringbuf IO
// factory, then issuing "debug.io stringbuf add". Evidence: vtable store
// 0x0083ABB8 for 4-byte cmd object kept in g_00E030C8, AddCommands at slot
// 0x84 with "game", AddIOFactory at slot 0x80 with "stringbuf" plus factory
// 0x00419BCD, Command at slot 0x8C, single caller 0x002301F1.
// ?Rva00419BCDCreate@@YAPAXXZ, retail 0x00419BCD, 45 bytes. Stringbuf IO
// singleton factory kept in g_00E030C4, 12-byte object with byte+4 and
// dword+8 zeroed.

class Debug
{
public:
	virtual void _M_slot_00();
	virtual void _M_slot_04();
	virtual void _M_slot_08();
	virtual void _M_slot_0c();
	virtual void _M_slot_10();
	virtual void _M_slot_14();
	virtual void _M_slot_18();
	virtual void _M_slot_1c();
	virtual void _M_slot_20();
	virtual void _M_slot_24();
	virtual void _M_slot_28();
	virtual void _M_slot_2c();
	virtual void _M_slot_30();
	virtual void _M_slot_34();
	virtual void _M_slot_38();
	virtual void _M_slot_3c();
	virtual void _M_slot_40();
	virtual void _M_slot_44();
	virtual void _M_slot_48();
	virtual void _M_slot_4c();
	virtual void _M_slot_50();
	virtual void _M_slot_54();
	virtual void _M_slot_58();
	virtual void _M_slot_5c();
	virtual void _M_slot_60();
	virtual void _M_slot_64();
	virtual void _M_slot_68();
	virtual void _M_slot_6c();
	virtual void _M_slot_70();
	virtual void _M_slot_74();
	virtual void _M_slot_78();
	virtual void _M_slot_7c();
	virtual bool _M_slot_80(const char *a, const char *b, void *(__cdecl *func)());
	virtual bool _M_slot_84(const char *a, void *b);
	virtual void _M_slot_88();
	virtual void Command(const char *cmd);
};

extern Debug *theDebug;
extern void *g_00E030C4;
extern void *g_00E030C8;

class Rva00419BCD_IO
{
public:
	virtual ~Rva00419BCD_IO() {}
	bool m_04;
	int m_08;
	Rva00419BCD_IO() : m_04(false), m_08(0) {}
};

class Rva00419BFA_Cmd
{
public:
	virtual ~Rva00419BFA_Cmd() {}
};

// ?Rva00419BCDCreate@@YAPAXXZ present-unmatched
void *__cdecl Rva00419BCDCreate()
{
	if (g_00E030C4)
		return g_00E030C4;
	Rva00419BCD_IO *p = new Rva00419BCD_IO;
	g_00E030C4 = p;
	return p;
}

void __cdecl Rva00419BFAInit()
{
	if (g_00E030C8)
		return;
	Rva00419BFA_Cmd *p = new Rva00419BFA_Cmd;
	g_00E030C8 = p;
	theDebug->_M_slot_84("game", p);
	theDebug->_M_slot_80("stringbuf", "internal string buffer", Rva00419BCDCreate);
	theDebug->Command("debug.io stringbuf add");
}
