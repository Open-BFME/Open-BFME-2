// cl: /MD
// ?rva0059ADB9@Rva0059ADB9@@QAE_NXZ @0x0059ADB9 24B
// Target evidence: Ghidra boundary 0x0059ADB9..0x0059ADD1; reads a float
// at +0x0C, calls the rowed body fallback getter through the pointer at
// +0x2C, and returns the byte at +0x1C from that getter's result. The owner
// identity remains address-derived.
class Rva0033A65E
{
public:
	void *rva0033A65E();

private:
	char m_pad[0x490];
	void *m_body;
};

class Rva0059ADB9
{
public:
	bool rva0059ADB9();

private:
	char m_pad000[0x0C];
	float m_value;
	char m_pad010[0x1C];
	Rva0033A65E *m_body;
};

bool Rva0059ADB9::rva0059ADB9()
{
	if (m_value <= 0.0f)
		return false;
	return *(bool *)((char *)m_body->rva0033A65E() + 0x1C);
}
