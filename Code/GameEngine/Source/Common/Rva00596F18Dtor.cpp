// cl: /DNDEBUG /MD /EHsc
// ??1Rva00596F18@@UAE@XZ @0x00596F18 11B
// Derived dtor: stores its own vtable 0x00870B38, then tail-jumps to the rowed
// base dtor ??1Rva00573F03@@UAE@XZ. Empty body, no new members.
// Evidence: mov [ecx] 0x00870B38 then jmp 0x00573F03; caller at 0x00597014.
struct Rva00573F03
{
	virtual ~Rva00573F03();
};
struct Rva00596F18 : Rva00573F03
{
	virtual ~Rva00596F18();
};
Rva00596F18::~Rva00596F18()
{
}
