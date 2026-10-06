// cl: /DNDEBUG /MD
//
// ??0Rva005E16DA@@QAE@H@Z, retail 0x005E16DA, 35 bytes.
//
// Address-derived constructor: the base is constructed with the one stack
// argument, the +0 word is set to the class's own table address, then the three
// words at +8/+0xc/+0x10 are zeroed.
//
//   5e16da: push esi
//           push [esp+8]           ; the one stack argument
//           mov  esi,ecx
//           call 0x00221635        ; base ctor, same argument
//           xor  eax,eax
//           mov  [esi],0x00C77A30  ; this class's table, written FIRST
//           mov  [esi+8],eax
//           mov  [esi+0xc],eax
//           mov  [esi+0x10],eax
//           mov  eax,esi
//           pop  esi
//           ret  4
//
// The whole of the banked 0.95 attempt's residual was store order: MSVC emitted
// the three zeroes first and the +0 store last. What moves it is NOT the class's
// polymorphism -- that was the banked hypothesis, and it is refuted below --
// but the TYPE of the three zeroed words. As three scalar members of the derived
// class, initialised in a mem-initializer list, MSVC emits the scalar stores
// before the compiler's vptr set. As ONE member subobject whose own constructor
// zeroes three pointers, the inlined subobject constructor is emitted AFTER the
// vptr set, and the order is retail's exactly. Measured on this toolchain, the
// two differ only in that order, so the shape is the finding.
//
// REFUTED, recorded so the next seat does not re-spend it: modelling +0 as an
// ordinary first member of a NON-polymorphic class -- initialised to a pinned
// global, and separately to a raw immediate -- puts the +0 store LAST both
// times. The declaration-order argument does not hold under /O1; the pointer
// store is sunk below the three zero stores whatever its encoding.
//
// The base at 0x00221635 is unrowed, so it is named from its address; its
// target is established by decaying retail's own call, not by this TU's shape:
// 0x005E16E1 + 5 - 3932337 = 0x00221635, and its `ret 4` matches one int arg.
// Target evidence that it is polymorphic: its body writes a vptr at +0 and a
// word at +4, which is why the derived members begin at +8.
//
// Boundary is proven: ghidra carries `0x5E16DA,35,FUN_009e16da` and the address
// was unclaimed. Identity is NOT recovered: the names and member offsets are
// address-derived, and the packet's LaserUpdate.cpp lead is one of five ZH
// candidates the sweep aligns equally well. The +0 table address never enters
// the comparison -- that store is a DIR32 relocation and the gate copies those
// bytes out of retail -- so the table is declared, never defined, here.

class Rva00221635
{
public:
	Rva00221635(int arg);
	virtual void Rva00221635_pure() = 0; // vptr at +0
	int m_4;                             // +0x04
};

struct Rva005E16DAVec
{
	void *m_8;  // +0x08
	void *m_c;  // +0x0c
	void *m_10; // +0x10

	Rva005E16DAVec() : m_8(0), m_c(0), m_10(0) {}
};

class Rva005E16DA : public Rva00221635
{
	Rva005E16DAVec m_vec; // +0x08, twelve bytes

public:
	Rva005E16DA(int arg);
	virtual ~Rva005E16DA();
};

Rva005E16DA::Rva005E16DA(int arg)
	: Rva00221635(arg)
{
}
