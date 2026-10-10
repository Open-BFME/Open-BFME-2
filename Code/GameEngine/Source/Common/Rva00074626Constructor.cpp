// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE /G7
//
// ??0Rva00985E4@@QAE@XZ, retail 0x0030AFC4..0x0030AFFB (55 bytes).
// Subsystem with vtable 0x00BC8318, whose slot 0 is ??_GRva00985E4 (0x0009864B),
// so the class is Rva00985E4 (vtable 0x00BC65A8 with slot 0 0x00074626 is
// Rva00074626's): SubsystemInterface base
// (rowed ctor 0x001B4E63), then ints and floats cleared. Each field is a tiny
// struct with an inline zeroing constructor: that is what makes MSVC keep the
// vftable store before the integer zero register and the declaration-order
// interleave of int and float stores. Names address-derived.
class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
private:
	char m_pad04[0x0C - 0x04];
};

struct Zero { int v; __forceinline Zero() : v(0) {} };
struct ZeroF { float v; __forceinline ZeroF() : v(0.0f) {} };
class Rva00985E4 : public SubsystemInterface
{
public:
	Rva00985E4();
	virtual ~Rva00985E4();
private:
	Zero m_0C, m_10;
	char m_pad14[0x30 - 0x14];
	Zero m_30; ZeroF m_34, m_38; Zero m_3C; ZeroF m_40, m_44;
};
Rva00985E4::Rva00985E4() {}
