// cl: /DNDEBUG /MD
// ?rva002D4688@Rva002D4688@@QAEHPAD@Z @ 0x002D4688 (37B).
// Writes buffer via WinMainTitlePair at +0 then Rva000B3F84Pair at +0x10
// advancing by the first count. Callees rowed 0x00109D3A and 0x000B44F0.
// Caller 0x002D5155. Layout from WinMainPairUnicode pair sizes.

struct Rva000B3F84Pair
{
	const char *m_ptr;
	int m_len;
	int write(char *dst);
};

struct WinMainTitlePair : Rva000B3F84Pair
{
	Rva000B3F84Pair m_secondPair;
	int write(char *dst);
};

class Rva002D4688
{
public:
	int rva002D4688(char *buffer);

private:
	WinMainTitlePair m_00;
	Rva000B3F84Pair m_10;
};

int Rva002D4688::rva002D4688(char *buffer)
{
	int first = m_00.write(buffer);
	int second = m_10.write(buffer + first);
	return first + second;
}
