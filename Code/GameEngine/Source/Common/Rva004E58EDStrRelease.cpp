// 0x004E58ED (8B): add ecx, 0x10, jmp 0x00036E70.
// 0x00036E70 is the matched StringBase<wchar_t>::releaseBuffer (133B).
// Reads as a dtor whose only teardown is releasing the string member at
// +0x10: adjust this, tail jump releaseBuffer. Spelled with an opaque member
// type plus an opaque alias pin for the callee (same body as the rowed
// releaseBuffer); the real StringBase template lives behind a header whose
// private releaseBuffer is not callable from here. Owner identity unproven;
// the names are address-derived.

class Rva00036E70Releaser
{
public:
	void release();
};

struct Rva004E58EDStr
{
	char x[8];
};

class Rva004E58ED
{
public:
	~Rva004E58ED();

private:
	char m_pad[0x10];
	Rva004E58EDStr m_str;
};

Rva004E58ED::~Rva004E58ED()
{
	((Rva00036E70Releaser *)&m_str)->release();
}
