// cl: /O1 /DNDEBUG /MD
// ??0Rva000A15FE@@QAE@PAX@Z @0x000A15FE 24B. Ctor forwards void* to base
// Rva0078D310Host 0x00104F8F then stores vtable 0x007C8DB4 (same as
// Rva000A1616Window input/system vtable in W3DGadgetWindowDrawSlots).
// Evidence: gap between 0x000A15EC/0x000A1616 rows sharing these flags;
// callees rowed base ctor and vtable extern g_00BC8DB4; callers 0x0008FC04
// 0x000A164D.
class Rva0078D310Host
{
public:
	Rva0078D310Host(void *context);
};

extern const void *const g_00BC8DB4[];

class Rva000A15FE : public Rva0078D310Host
{
public:
	Rva000A15FE(void *context);
};

Rva000A15FE::Rva000A15FE(void *context)
	: Rva0078D310Host(context)
{
	*(const void **)this = g_00BC8DB4;
}

extern const void *const g_00BC8DE0[];

class Rva000A1646 : public Rva000A15FE
{
public:
	Rva000A1646(void *context);
};

Rva000A1646::Rva000A1646(void *context)
	: Rva000A15FE(context)
{
	*(const void **)this = g_00BC8DE0;
}
