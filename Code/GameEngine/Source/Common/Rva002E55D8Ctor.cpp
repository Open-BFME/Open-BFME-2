// cl: /MD
// ??0Rva002E55D8@@QAE@XZ @0x002E55FF 18B ctor via rowed baseConstruct 0x001B4E63 then vtable 0x00804E90.
// Evidence: stores vtable 0x00804E90 at [this] after calling baseConstruct; prev 0x002E55E3 next 0x002E5611 same flags.

class BFME2NativeNetwork
{
public:
	void baseConstruct();
};

extern const void *const g_00804E90[];

class Rva002E55D8
{
public:
	Rva002E55D8();
};

Rva002E55D8::Rva002E55D8()
{
	((BFME2NativeNetwork *)this)->baseConstruct();
	*(const void **)this = g_00804E90;
}
