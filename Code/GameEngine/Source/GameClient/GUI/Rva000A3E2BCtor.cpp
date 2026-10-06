// cl: /MD
// ??0Rva000A3E2B@@QAE@PAX@Z @0x000A3E2B 24B ctor forwards void arg to rowed base 0x000A3DE3 stores vtable 0x007C9180 returns this evidence callers 0x0008F82A chain from 0x000A3DE3 unblocks 0x0008F803
class Rva000A3DE3
{
public:
	Rva000A3DE3(void *ctx);
};

extern const void *const g_00BC9180[];

class Rva000A3E2B : public Rva000A3DE3
{
public:
	Rva000A3E2B(void *ctx);
};

Rva000A3E2B::Rva000A3E2B(void *ctx)
	: Rva000A3DE3(ctx)
{
	*(const void **)this = g_00BC9180;
}
