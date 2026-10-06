// cl: /DNDEBUG /MD /EHsc
//
// ScriptActions slot 15 helper, retail 0x003BA8C4 (25 bytes, ret 4):
// stores argument byte into [ecx+0xC] (m_suppressNewWindows), then checks
// global 0x00E03138 and dispatches virtual method at offset +0x60.
// Caller is ScriptActions vtable slot 15 at 0x0081FE84 (VA 0x00C1FE84).

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
	virtual void u18();
	virtual void u19();
	virtual void u20();
	virtual void u21();
	virtual void u22();
	virtual void u23();
	virtual void u24();
};

extern UnknownE03138 *g_00E03138;

struct ScriptActionsRva003BA8C4
{
	char m_pad[0xC];
	bool m_suppressNewWindows;
	void setSuppressNewWindows(bool suppress);
};

// ?setSuppressNewWindows@ScriptActionsRva003BA8C4@@QAEX_N@Z
void ScriptActionsRva003BA8C4::setSuppressNewWindows(bool suppress)
{
	m_suppressNewWindows = suppress;
	if (g_00E03138 != 0)
	{
		g_00E03138->u24();
	}
}
