// cl: /O1 /DNDEBUG /MD
// ??0Rva000A3307@@QAE@PAX@Z @0x000A3307 24B: Gadget window ctor via Host base plus vtable 0x00BC90FC
// Evidence: base ??0Rva0078D310Host@@QAE@PAX@Z row 0x00104F8F with void arg plus vptr 0x00BC90FC g_00BC90FC callers 0x0008F8D8 0x000A3356 prev 0x000A3143 next 0x000A331F same flags
extern const void *const g_00BC90FC[];

class Rva0078D310Host
{
public:
	Rva0078D310Host(void *context);
};

class Rva000A3307 : public Rva0078D310Host
{
public:
	Rva000A3307(void *context);
};

Rva000A3307::Rva000A3307(void *context)
	: Rva0078D310Host(context)
{
	*(const void **)this = g_00BC90FC;
}

extern const void *const g_00BC9128[];

class Rva000A334F : public Rva000A3307
{
public:
	Rva000A334F(void *context);
};

Rva000A334F::Rva000A334F(void *context)
	: Rva000A3307(context)
{
	*(const void **)this = g_00BC9128;
}
