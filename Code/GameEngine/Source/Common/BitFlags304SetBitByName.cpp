// cl: /DNDEBUG /MD
// ?setBitByName@?$BitFlags@$0BDA@@@QAE_NPBD@Z, retail 0x000B65CE, 47 bytes.
// BitFlags<304>::setBitByName: static getSingleBitFromName 0x000B42CA then
// set(i) as words[i>>5] |= 1u << (i&31), bool true/false. Donor ZH
// BitFlags.h setBitByName. Callers include 0x000BB801 0x004CA8E0 0x004CC3FF.
// Real name via donor and callee.
template <unsigned NUMBITS>
class BitFlags
{
public:
	static int getSingleBitFromName(const char *token);
	bool setBitByName(const char *token);

private:
	unsigned m_words[(NUMBITS + 31) / 32];
};

// ?setBitByName@?$BitFlags@$0BDA@@@QAE_NPBD@Z
template <>
bool BitFlags<304>::setBitByName(const char *token)
{
	int i = getSingleBitFromName(token);
	if (i >= 0)
	{
		unsigned u = (unsigned)i;
		m_words[u >> 5] |= 1u << (u & 31);
		return true;
	}
	else
	{
		return false;
	}
}

// The same body for two narrower flag sets, each calling its own rowed
// getSingleBitFromName (one flag word, so the code matches BitFlags<304>'s):
// BitFlags<15> at 0x00318559 and BitFlags<21> at 0x004BE0F1.

// ?setBitByName@?$BitFlags@$0P@@@QAE_NPBD@Z @0x00318559 47B
template <>
bool BitFlags<15>::setBitByName(const char *token)
{
	int i = getSingleBitFromName(token);
	if (i >= 0)
	{
		unsigned u = (unsigned)i;
		m_words[u >> 5] |= 1u << (u & 31);
		return true;
	}
	else
	{
		return false;
	}
}

// ?setBitByName@?$BitFlags@$0BF@@@QAE_NPBD@Z @0x004BE0F1 47B
template <>
bool BitFlags<21>::setBitByName(const char *token)
{
	int i = getSingleBitFromName(token);
	if (i >= 0)
	{
		unsigned u = (unsigned)i;
		m_words[u >> 5] |= 1u << (u & 31);
		return true;
	}
	else
	{
		return false;
	}
}
