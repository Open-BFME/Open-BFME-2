// The BFME1 donor baked its table VA as a literal, which cannot transfer:
// the address of a sacrificial anchor stands in (mov-imm-DIR32, patched).
extern "C" char __identifier("??_7Rva00808CB0LanGameEntry@@6B@");

struct Rva7F4CC0Child
{
	Rva7F4CC0Child();
	__forceinline void normalize()
	{
		second = 0;
		third = 0;
		first = 0;
		table = (unsigned int)&__identifier("??_7Rva00808CB0LanGameEntry@@6B@");
	}

	volatile unsigned int table;
	volatile unsigned int first;
	volatile unsigned int second;
	volatile unsigned int third;
};

struct Rva7F4CC0Primary
{
	Rva7F4CC0Primary() : first(0), second(0), third(0), fourth(0), enabled(false) {}

	unsigned int first;
	unsigned int second;
	unsigned int third;
	unsigned int fourth;
	bool enabled;
};

struct Rva7F4CC0ConstructorThunk : Rva7F4CC0Primary, Rva7F4CC0Child
{
	Rva7F4CC0ConstructorThunk();
};

// ??0Rva7F4CC0ConstructorThunk@@QAE@XZ
// (BFME1 ledger calls this body d_007f4cc0: their dump row at 0x007F4CC0.)
Rva7F4CC0ConstructorThunk::Rva7F4CC0ConstructorThunk()
{
	Rva7F4CC0Child::normalize();
}
