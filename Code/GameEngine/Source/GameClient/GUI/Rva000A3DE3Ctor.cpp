// cl: /MD
// ??0Rva000A3DE3@@QAE@PAX@Z @0x000A3DE3 24B ctor forwards void arg to rowed base 0x00104F8F stores vtable 0x007C9154 returns this evidence callers 0x0008F7F0 0x000A3E32 neighbours WinInstanceDataTextLength and W3DGadgetWindowDrawSlots unblocks 0x0008F7C9 0x000A3E2B
class Rva0078D310Host
{
public:
	Rva0078D310Host(void *ctx);
};

extern const void *const g_00BC9154[];

class Rva000A3DE3 : public Rva0078D310Host
{
public:
	Rva000A3DE3(void *ctx);
};

Rva000A3DE3::Rva000A3DE3(void *ctx)
	: Rva0078D310Host(ctx)
{
	*(const void **)this = g_00BC9154;
}
