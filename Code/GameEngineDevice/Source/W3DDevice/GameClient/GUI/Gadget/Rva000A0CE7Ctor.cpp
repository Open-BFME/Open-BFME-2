// cl: /O1 /DNDEBUG /MD
// ??0Rva000A0CE7@@QAE@PAX@Z @0x000A0CE7 24B: Gadget window ctor via Host base plus vtable 0x00BC8D04
// Evidence: base Rva0078D310Host ctor row 0x00104F8F with void arg plus vptr 0x00BC8D04 g_00BC8D04 slot 3 Rva000A0D5EDraw callers 0x0008FB1C 0x000A0D41
extern const void *const g_00BC8D04[];

class Rva0078D310Host
{
public:
	Rva0078D310Host(void *context);
};

class Rva000A0CE7 : public Rva0078D310Host
{
public:
	Rva000A0CE7(void *context);
};

Rva000A0CE7::Rva000A0CE7(void *context)
	: Rva0078D310Host(context)
{
	*(const void **)this = g_00BC8D04;
}
