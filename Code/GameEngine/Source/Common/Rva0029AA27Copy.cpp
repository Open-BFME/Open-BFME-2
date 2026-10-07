// cl: /O1 /G7 /arch:SSE /MD
// ?rva0029AA27@Rva0029AA27@@QAEXPBUS12_0029AA27@@@Z @0x0029AA27 24B
// Guarded 12-byte copy via movsd string; caller at 0x00432145; unlock.
struct S12_0029AA27
{
	int a;
	int b;
	int c;
};
class Rva0029AA27
{
public:
	void rva0029AA27(const S12_0029AA27 *src);
private:
	char m_pad[0x9B8];
	S12_0029AA27 m_9B8;
};
void Rva0029AA27::rva0029AA27(const S12_0029AA27 *src)
{
	if (src != 0)
		m_9B8 = *src;
}

// Native 0045F2C1/20B, RET4: three words copied from the argument to +0x310.
// No original record type or receiver identity asserted.
struct Rva0045F2C1Record { unsigned int words[3]; };
class Rva0045F2C1 {
    char m_pad[0x310];
    Rva0045F2C1Record value;
public:
    void assign(const Rva0045F2C1Record *source);
};
void Rva0045F2C1::assign(const Rva0045F2C1Record *source) { value=*source; }

// Native 00210CA2/20B, RET4: three words copied from the argument to +0xA0.
// No original record type or receiver identity asserted.
struct Rva00210CA2Record { unsigned int words[3]; };
class Rva00210CA2 {
    char m_pad[0xA0];
    Rva00210CA2Record value;
public:
    void assign(const Rva00210CA2Record *source);
};
void Rva00210CA2::assign(const Rva00210CA2Record *source) { value=*source; }
