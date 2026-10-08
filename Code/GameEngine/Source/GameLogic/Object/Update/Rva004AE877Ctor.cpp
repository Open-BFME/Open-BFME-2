// cl: /DNDEBUG /MD
//
// ??0Rva004AE877@@QAE@XZ, retail 0x004AE877, 12 bytes.
// Default ctor whose only work is the rowed Rva0042526Member ctor at +0x00
// followed by the return-this epilogue. Owning class identity is unproven;
// the Rva prefix is the address-derived placeholder.

class Rva0042526Member
{
public:
	Rva0042526Member();

private:
	char m_bytes[0x4C];
};

class Rva004AE877
{
public:
	Rva004AE877();

private:
	Rva0042526Member m_00;
};

Rva004AE877::Rva004AE877()
{
}
