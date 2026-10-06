// cl: /DNDEBUG /MD
// ?rva0029091E@Object@@QBE_NI@Z, retail 0x0029091E, 69 bytes.
// Object bit-gate: builds 16-byte BitFlags<117> mask via memset plus single-bit set then calls rowed finder wrapper 0x0033DCD1 via ptr at +4.
// Evidence: callers 0x004770C7 0x00477322 0x00478CAE; prev rva002903EF Object next isAbleToAttack Object; same memset-plus-OR shape as rowed ObjectRva0028D491.
#include <string.h>

struct ModelConditionInfo;

template <int Bits>
class BitFlags
{
public:
	unsigned int m_words[4];
};

typedef BitFlags<117> ModelConditionSetFlags;

struct Rva0033DCD1
{
	const ModelConditionInfo *rva0033DCD1(const ModelConditionSetFlags &flags) const;
};

class Object
{
public:
	bool rva0029091E(unsigned int bit) const;
private:
	char m_pad[4];
	const Rva0033DCD1 *m_04;
};

bool Object::rva0029091E(unsigned int bit) const
{
	ModelConditionSetFlags flags;
	memset(&flags, 0, 0x10);
	flags.m_words[bit >> 5] |= 1u << (bit & 0x1F);
	const ModelConditionInfo *info = m_04->rva0033DCD1(flags);
	return info;
}
