// Cold-slice B8-imm32 const-int returners (twin-free TU).
//
// Same 6-byte shape as ConstIntGetters8.cpp (mov eax,<IMM32> / ret).
// Every body below is strict-clean: previous byte is a ret (C3),
// no branch targets the B8 in the 16B window, and the next bytes open
// a new function. Opaque address-derived names witness only the address
// and the returned constant. Fresh TU to avoid hot-file contention.
// No // cl: line (defaults match the frameless 6-byte shape).

// The address-valued constants below name the globals the ledger defines there
// (reverse/data_ledger.csv), so the unit carries no hard-coded image address.
struct FieldParse
{
	const char *token;
	void *parse;
	const void *userData;
	int offset;
};
class FireEffect
{
public:
	static const FieldParse m_fieldParseTable[];
};
class CommandSet
{
public:
	static const FieldParse m_commandSetFieldParseTable[];
};
class ThingTemplate
{
	friend int Rva0033A43EGet(void);
	static const FieldParse s_objectFieldParseTable[];
};
struct Rva002E36D5Node;
extern Rva002E36D5Node *g_00DFF0B8;
extern const char *g_rva0033A3F4Table[];


// ?Rva00309E2AGet@@YAHXZ @ 0x00309e2a (6B): returns 0x00c084c0.
// Third of a mov-ret triple with rowed 0x00309e1e/0x00309e24.
// Opaque address-derived name.
int Rva00309E2AGet(void)
{
	return (int)FireEffect::m_fieldParseTable;
}

// ?Rva0031A9ECGet@@YAHXZ @ 0x0031a9ec (6B): returns 0x00c38dd0.
// Follows a ret (xor/cmp/sete/ret). Next opens a new function.
// Opaque address-derived name.
int Rva0031A9ECGet(void)
{
	return (int)CommandSet::m_commandSetFieldParseTable;
}

// ?Rva00328A5FGet@@YAHXZ @ 0x00328a5f (6B): returns 0x00dff0b8.
// Follows leave/ret; next is a separate global getter.
// Opaque address-derived name.
int Rva00328A5FGet(void)
{
	return (int)&g_00DFF0B8;
}

// ?Rva0033A3EEGet@@YAHXZ @ 0x0033a3ee (6B): returns 0x00dbe9b0.
// Follows leave/ret; next opens a new function.
// Opaque address-derived name.
int Rva0033A3EEGet(void)
{
	return (int)g_rva0033A3F4Table;
}

// ?Rva0033A43EGet@@YAHXZ @ 0x0033a43e (6B): returns 0x00dbecd8.
// Follows a movsx/ret tiny getter; next is a movzx/ret getter.
// Opaque address-derived name.
int Rva0033A43EGet(void)
{
	return (int)ThingTemplate::s_objectFieldParseTable;
}

// ?Rva00531295Get@@YAHXZ @ 0x00531295 (6B): returns -666 (0xfffffd66).
// Follows and/ret; next opens a switch-dispatch function.
// Opaque address-derived name.
int Rva00531295Get(void)
{
	return -666;
}
