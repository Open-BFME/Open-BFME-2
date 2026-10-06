// cl: /MD /EHs
// ??1Rva000F9BD7Dtor@@QAE@XZ retail 0x000F9BD7 101B
// Non-virtual dtor with an empty body: member dtors in reverse order under EH
// states 2..0 -- the buffers at +0x38 and +0x2C (inline CRT free of each block),
// then the texture handles at +0x14 and +0x10, each releasing through the rowed
// ?Release_Ref@TextureClass@@QAEXXZ 0x0061ED10. Same handle view as
// Rva000F82F5Dtor.cpp, plus a second buffer. Names address-derived.

extern "C" void __cdecl free(void *block);

class TextureClass
{
public:
	void Release_Ref();
};

class Rva000F9BD7TextureHandle
{
public:
	~Rva000F9BD7TextureHandle()
	{
		if (m_texture)
			m_texture->Release_Ref();
	}

	TextureClass *m_texture;
};

class Rva000F9BD7Buffer
{
public:
	~Rva000F9BD7Buffer()
	{
		if (m_data)
			free(m_data);
	}

	void *m_data;
};

class Rva000F9BD7Dtor
{
public:
	~Rva000F9BD7Dtor();

private:
	char m_pad00[0x10];
	Rva000F9BD7TextureHandle m_texture10; // +0x10
	Rva000F9BD7TextureHandle m_texture14; // +0x14
	char m_pad18[0x2C - 0x18];
	Rva000F9BD7Buffer m_buffer2C; // +0x2C
	char m_pad30[0x38 - 0x30];
	Rva000F9BD7Buffer m_buffer38; // +0x38
};

Rva000F9BD7Dtor::~Rva000F9BD7Dtor()
{
}
