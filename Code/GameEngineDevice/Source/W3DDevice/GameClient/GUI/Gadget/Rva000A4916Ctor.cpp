// cl: /O1 /DNDEBUG /MD
// ??0Rva000A4916@@QAE@PAX@Z @0x000A4916 24B: Gadget window ctor via Host base plus vtable 0x00BC9204
// Evidence: base ??0Rva0078D310Host@@QAE@PAX@Z row 0x00104F8F with void arg plus vptr 0x00BC9204 g_00BC9204 callers 0x0008F77C 0x000A4970
extern const void *const g_00BC9204[];

class Rva0078D310Host
{
public:
	Rva0078D310Host(void *context);
};

class Rva000A4916 : public Rva0078D310Host
{
public:
	Rva000A4916(void *context);
};

Rva000A4916::Rva000A4916(void *context)
	: Rva0078D310Host(context)
{
	*(const void **)this = g_00BC9204;
}
