// cl: /O1 /DNDEBUG /MD
// ??0Rva000A0D3A@@QAE@PAX@Z @0x000A0D3A 24B: Gadget window ctor via Rva000A0CE7 base plus vtable 0x00BC8D30
// Evidence: base ??0Rva000A0CE7@@QAE@PAX@Z row 0x000A0CE7 with void arg plus vptr 0x00BC8D30 g_00BC8D30 caller 0x0008FB56
extern const void *const g_00BC8D30[];

class Rva000A0CE7
{
public:
	Rva000A0CE7(void *context);
};

class Rva000A0D3A : public Rva000A0CE7
{
public:
	Rva000A0D3A(void *context);
};

Rva000A0D3A::Rva000A0D3A(void *context)
	: Rva000A0CE7(context)
{
	*(const void **)this = g_00BC8D30;
}
