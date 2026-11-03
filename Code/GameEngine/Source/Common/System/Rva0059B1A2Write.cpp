// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// ?copyToBuffer@Rva0059B1A2@@QAEHPAD@Z @0x0059B1A2 (37 bytes).
// Identity is address-derived: two callers are unclaimed, and the body
// composes the rowed AsciiStringPlusText and Rva000B3F84Pair writers.
class AsciiStringPlusText
{
public:
	int write(char *dst);
private:
	const void *m_string;
};

#include "../../../Include/Common/Rva000B3F84Pair.h"

class Rva0059B1A2 : public AsciiStringPlusText
{
public:
	int copyToBuffer(char *dst);
private:
	char at04[8];
	Rva000B3F84Pair m_pair;
};

int Rva0059B1A2::copyToBuffer(char *dst)
{
	int first = AsciiStringPlusText::write(dst);
	return first + m_pair.write(dst + first);
}

class Rva0059B1C7 : public Rva0059B1A2
{
public:
	int copyToBuffer(char *dst);
private:
	Rva000B3F84Pair m_pair;
};

int Rva0059B1C7::copyToBuffer(char *dst)
{
	int first = Rva0059B1A2::copyToBuffer(dst);
	return first + m_pair.write(dst + first);
}
