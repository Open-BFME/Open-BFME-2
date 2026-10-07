// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /O1 /arch:SSE /G7
// ??0Rva004CBEB0@@QAE@XZ, retail 0x004CBEB0, 26 bytes.
// Address-named constructor inferred from the thiscall ABI and constructor
// shape: clears the first dword and constructs 0x4C-byte members at +4/+0x50.

class Rva0042526Member
{
public:
	Rva0042526Member();

private:
	unsigned char m_pad[0x4C];
};

class Rva004CBEB0
{
public:
	Rva004CBEB0();

private:
	unsigned int m_first;
	Rva0042526Member m_member0;
	Rva0042526Member m_member1;
};

Rva004CBEB0::Rva004CBEB0()
	: m_first(0)
{
}
