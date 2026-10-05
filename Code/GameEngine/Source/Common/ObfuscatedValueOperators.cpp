// cl: -DNDEBUG -MD -EHs-c- /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
// ??9Rva00077710Value@@QBE_NABV0@@Z
// retail 0x0022CF4C, 34 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/ObfuscatedValueOperators.cpp
// (reference/open-bfme-1 @ 6d943426). Compiled /Os the donor body is
// byte-identical to retail once relocations are masked (unique hit on unclaimed
// .text). Only the placed body is defined here; the donor's other nine
// definitions are omitted.
//
// The donor's whole argument applies. The value never appears in the clear: it
// is held at this+4 and every read goes through the compare wrapper, whose
// result is tested against the sentinel 0xA590217B rather than against zero --
// nothing but a deliberately obfuscated comparison returns a magic word. Both
// operands are loaded into NAMED locals before the call; written as one
// expression MSVC keeps the operand pointer live and picks a fresh register for
// the value, which costs a different encoding at this site.

typedef int Int;

extern "C++"
{
	Int Rva00077140(Int a, Int b);
	Int Rva0022CBB5Hook(Int a, Int b);
}

class Rva00077710Value
{
public:
	bool operator!=(const Rva00077710Value &other) const;
	Rva00077710Value operator+(const Rva00077710Value &other) const;

private:
	Rva00077710Value(Int value) { m_value = value; }

	Int m_unreconstructed_00;							///< retail this+0x00
	Int m_value;										///< retail this+0x04
};

bool Rva00077710Value::operator!=(const Rva00077710Value &other) const
{
	Int rhs = other.m_value;
	Int lhs = m_value;

	return Rva00077140(lhs, rhs) != (Int)0xA590217B;
}

Rva00077710Value Rva00077710Value::operator+(const Rva00077710Value &other) const
{
	Int rhs = other.m_value;
	Int lhs = m_value;

	return Rva00077710Value(Rva0022CBB5Hook(lhs, rhs));
}