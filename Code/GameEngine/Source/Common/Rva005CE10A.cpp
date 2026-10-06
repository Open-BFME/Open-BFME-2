// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva005CE10A@Rva005CE10A@@QAEXXZ, retail 0x005CE10A, 27 bytes.
// Helper-then-validate-then-tail: calls +0x18 member rva004E0750, validates this as StringBase<G>, tail-jumps +0x18 member rva004E0741.
// Evidence: packet disassembly push esi mov esi ecx mov ecx [esi+0x18] call 0x4E0750 mov ecx esi call validate 0xB3FD0 mov ecx [esi+0x18] pop esi jmp 0x4E0741, VTABLE slot 4 table 0x00875158, callees rowed.
#include "ascii_string.h"
template <> class StringBase<unsigned short>
{
	friend class Rva005CE10A;
	void validate() const;
};
class Rva004E0750
{
public:
	void rva004E0750() const;
};
class Rva004E0741
{
public:
	void rva004E0741() const;
};
class Rva005CE10A
{
public:
	void rva005CE10A();
private:
	char m_pad[0x18];
	Rva004E0750 *m_18;
};
void Rva005CE10A::rva005CE10A()
{
	m_18->rva004E0750();
	((StringBase<unsigned short> *)this)->validate();
	((Rva004E0741 *)m_18)->rva004E0741();
}
