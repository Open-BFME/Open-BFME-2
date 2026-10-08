// cl: /DNDEBUG /MD
//
// ??0Rva0053B8FF@@QAE@XZ, retail 0x0053B8FF, 16 bytes.
// Default ctor over the rowed Rva0024C7B3Member zeroing helper at 0x24C7B3
// (member at +0x00, 0x1C bytes) plus a byte at +0x1C cleared. Owning class
// identity is unproven; the Rva prefix is the address-derived placeholder.

class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member();

private:
	char m_bytes[0x1C];
};

class Rva0053B8FF
{
public:
	Rva0053B8FF();

private:
	Rva0024C7B3Member m_00;
	char m_1C;
};

Rva0053B8FF::Rva0053B8FF()
{
	m_1C = 0;
}
