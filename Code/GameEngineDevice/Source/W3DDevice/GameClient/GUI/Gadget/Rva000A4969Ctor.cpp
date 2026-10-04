// cl: /O1 /DNDEBUG /MD
// ??0Rva000A4969@@QAE@PAX@Z @0x000A4969 24B: Gadget window ctor via Rva000A4916 base plus vtable 0x00BC9230
// Evidence: base ??0Rva000A4916@@QAE@PAX@Z row 0x000A4916 with void arg plus vptr 0x00BC9230 g_00BC9230 callers 0x0008F7B6 0x0008FF45
extern const void *const g_00BC9230[];

class Rva000A4916
{
public:
	Rva000A4916(void *context);
};

class Rva000A4969 : public Rva000A4916
{
public:
	Rva000A4969(void *context);
};

Rva000A4969::Rva000A4969(void *context)
	: Rva000A4916(context)
{
	*(const void **)this = g_00BC9230;
}
