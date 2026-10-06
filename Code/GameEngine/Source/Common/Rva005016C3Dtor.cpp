// cl: /EHs /MD
// ??1Rva005016C3Dtor@@QAE@XZ @0x005016C3 135B: dtor destroying tree at +0x4c plus five null-checked frees; evidence rowed tree dtor 0x00500E05 rowed free 0x00030830 rowed EH_prolog 0x00629188 and jmp member 0x0050174A
extern "C" void __cdecl free(void *block);

struct Rva00500804
{
	~Rva00500804();
	char m_data[8];
};

struct Rva005016C3Buf
{
	char *m_ptr;
	~Rva005016C3Buf()
	{
		if (m_ptr)
			free(m_ptr);
	}
};

struct Rva005016C3Dtor
{
	char m_pad0[0x10];
	Rva005016C3Buf m_10;
	char m_pad1[0x8];
	Rva005016C3Buf m_1c;
	char m_pad2[0x8];
	Rva005016C3Buf m_28;
	char m_pad3[0x8];
	Rva005016C3Buf m_34;
	char m_pad4[0x8];
	Rva005016C3Buf m_40;
	char m_pad5[0x8];
	Rva00500804 m_4c;
	~Rva005016C3Dtor();
};

Rva005016C3Dtor::~Rva005016C3Dtor()
{
}
