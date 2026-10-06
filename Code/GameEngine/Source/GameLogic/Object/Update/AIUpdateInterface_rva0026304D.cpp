// cl: /DNDEBUG /MD
//
// ?rva0026304D@AIUpdateInterface@@QAEXH@Z, retail 0x0026304D, 20 bytes.
// Leaf setter beside AIUpdateInterface tail: stores int at +0x21C then clears
// byte at +0x3BC. Neighbour rva00262804 proves AIUpdateInterface with +0x3B9
// flag and +0x1F4 field; this pair uses +0x21C/+0x3BC in same tail range.
// Callers at 0x369755 0x36FD10 0x3729DE. No callees.

class AIUpdateInterface
{
	char m_pad00[0x21C];
	int m_field21C;
	char m_pad220[0x3BC - 0x220];
	unsigned char m_flag3BC;
public:
	void rva0026304D(int val);
};

void AIUpdateInterface::rva0026304D(int val)
{
	m_field21C = val;
	m_flag3BC = 0;
}
