// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva0028C6FB@Rva0028C6FB@@QAEPAXI@Z @0x0028C6FB 42B
// Bit-present table lookup: if bit (idx&31) of word (idx>>5) at +0 is set return table[idx] else 0.
// Evidence: test [this+word*4] mask plus mov eax [idx*4+VA 0x00DC828C]; sole caller 0x00292414;
// neighbours V3PolyCopyCtors and ConstIntGetters5 give TU and flags.
// DisabilityTypeNames: the retail string table at VA 0x00DC828C (defined in
// Code/GameEngine/Source/GameLogic/Object/Update/Rva0049D67F.cpp).
extern const char *DisabilityTypeNames[11]; ///< retail [0x00DC828C]

class Rva0028C6FB
{
public:
	void *rva0028C6FB(unsigned int idx);

private:
	unsigned int m_bits[8];
};

void *Rva0028C6FB::rva0028C6FB(unsigned int idx)
{
	return (m_bits[idx >> 5] & (1u << (idx & 31))) ? (void *)DisabilityTypeNames[idx] : 0;
}

// Five more copies of this lookup, each over a named BitFlags name table (the
// operand the load reads), otherwise the same 42 bytes. Owners keep addresses.

extern const char *const ModelConditionNames[];

class Rva000454F3
{
public:
	void *rva000454F3(unsigned int idx);

private:
	unsigned int m_bits[8];
};

void *Rva000454F3::rva000454F3(unsigned int idx)
{
	return (m_bits[idx >> 5] & (1u << (idx & 31))) ? (void *)ModelConditionNames[idx] : 0;
}

extern const char *SpecialPowerNames[];

class Rva0028C783
{
public:
	void *rva0028C783(unsigned int idx);

private:
	unsigned int m_bits[8];
};

void *Rva0028C783::rva0028C783(unsigned int idx)
{
	return (m_bits[idx >> 5] & (1u << (idx & 31))) ? (void *)SpecialPowerNames[idx] : 0;
}

extern const char *TheKindOfBitNames[];

class Rva002AA2CF
{
public:
	void *rva002AA2CF(unsigned int idx);

private:
	unsigned int m_bits[8];
};

void *Rva002AA2CF::rva002AA2CF(unsigned int idx)
{
	return (m_bits[idx >> 5] & (1u << (idx & 31))) ? (void *)TheKindOfBitNames[idx] : 0;
}

extern const char *CommandSetNames[];

class Rva0031852F
{
public:
	void *rva0031852F(unsigned int idx);

private:
	unsigned int m_bits[8];
};

void *Rva0031852F::rva0031852F(unsigned int idx)
{
	return (m_bits[idx >> 5] & (1u << (idx & 31))) ? (void *)CommandSetNames[idx] : 0;
}

extern const char *VeterancyLevelNames[];

class Rva004BE0C7
{
public:
	void *rva004BE0C7(unsigned int idx);

private:
	unsigned int m_bits[8];
};

void *Rva004BE0C7::rva004BE0C7(unsigned int idx)
{
	return (m_bits[idx >> 5] & (1u << (idx & 31))) ? (void *)VeterancyLevelNames[idx] : 0;
}
