// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// ?rva0059B1A2@Rva0059B1A2@@QAEHPAD@Z @0x0059B1A2 (37 bytes).
// Identity is address-derived: two callers are unclaimed, and the body
// composes the rowed AsciiStringPlusText and Rva000B3F84Pair writers.
class AsciiStringPlusText
{
public:
	int write(char *dst);
private:
	const void *m_string;
};

class Rva000B3F84Pair
{
public:
	int write(char *dst);
private:
	const char *m_ptr;
	int m_len;
};

class Rva0059B1A2 : public AsciiStringPlusText
{
public:
	int rva0059B1A2(char *dst);
private:
	char at04[8];
	Rva000B3F84Pair m_pair;
};

int Rva0059B1A2::rva0059B1A2(char *dst)
{
	int first = AsciiStringPlusText::write(dst);
	return first + m_pair.write(dst + first);
}
