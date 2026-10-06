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

// ?rva0059ADF4@Rva0059ADF4@@QAEXH@Z @0x0059ADF4 29B
// Target evidence: the direct call at VA 0x0099AE04 resolves to executable
// code at VA 0x009DB045; the call target has a thiscall frame and ret 0x10.
// The owner pointer read at +0x24 and callee identity remain address-derived.
class Rva005DB045
{
public:
	void rva005DB045(float value, int first, int second, int third);
};

class Rva0059ADF4
{
public:
	void rva0059ADF4(int value);

private:
	char m_pad[0x24];
	Rva005DB045 *m_component;
};

void Rva0059ADF4::rva0059ADF4(int value)
{
	float converted = (float)value;
	m_component->rva005DB045(converted, 1, 1, 0);
}

// ?rva0059AE55@Rva0059AE55@@QAEXPAXPAPAX@Z @0x0059AE55 29B
// Target evidence: copies five dwords from the first stack argument into
// this, then dereferences the second stack argument and stores it at +0x14.
// The structure identity remains address-derived.
struct Rva0059AE55Prefix
{
	unsigned int m_words[5];
};

class Rva0059AE55
{
public:
	void rva0059AE55(void *source, void **slot);

private:
	Rva0059AE55Prefix m_prefix;
	void *m_value;
};

void Rva0059AE55::rva0059AE55(void *source, void **slot)
{
	m_prefix = *(Rva0059AE55Prefix *)source;
	m_value = *slot;
}
