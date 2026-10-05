// cl: /O1 /DNDEBUG /MD
//
// ??0Rva000A217F@@QAE@PAX@Z @0x000A217F 24B.
// Rva000A217F ctor forwarding void* to base Rva000A2137 then storing vtable
// g_00BC9020. Evidence: pin name, LINK BONUS 116B via factory Rva0008FABBCreate
// in Rva0008F8EBFactories.cpp, rowed/pinned base ctor 0x000A2137, callers 1.
class Rva000A2137
{
public:
	Rva000A2137(void *context);
};
extern const void *const g_00BC9020[];
class Rva000A217F : public Rva000A2137
{
public:
	Rva000A217F(void *context);
};
Rva000A217F::Rva000A217F(void *context) : Rva000A2137(context)
{
	*(const void **)this = g_00BC9020;
}
