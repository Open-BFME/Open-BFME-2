// cl: /MD
//
// ??0Rva004523F5@@QAE@XZ, retail 0x004523F5, 12 bytes.
// Gap between 0x004523B6 (stopHealing) and 0x00452401 (xfer).
// Default ctor over the rowed Rva0024C7B3Member zeroing helper at 0x24C7B3
// (member at +0x00, 0x1C bytes) with no trailing members.
// Evidence: rowed callee plus no-caller gap plus byte-exact /O1 shape.
// Honest address name: owning class identity unproven.

class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member();

private:
	char m_bytes[0x1C];
};

class Rva004523F5
{
public:
	Rva004523F5();

private:
	Rva0024C7B3Member m_00;
};

Rva004523F5::Rva004523F5()
{
}
