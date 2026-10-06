// cl: /MD /EHs
// ??1Rva000F82F5Dtor@@QAE@XZ retail 0x000F82F5 83B
// Non-virtual dtor with an empty body: member dtors in reverse order under EH
// states 1..0 -- the buffer at +0x2C (inline CRT free of its block), then the
// texture handles at +0x14 and +0x10, each releasing through the rowed
// ?Release_Ref@TextureClass@@QAEXXZ 0x0061ED10. Same handle view as
// W3DRoadBufferRoadTypeDtor.cpp. Names address-derived.

extern "C" void __cdecl free(void *block);

class TextureClass
{
public:
	void Release_Ref();
};

class Rva000F82F5TextureHandle
{
public:
	~Rva000F82F5TextureHandle()
	{
		if (m_texture)
			m_texture->Release_Ref();
	}

	TextureClass *m_texture;
};

class Rva000F82F5Buffer
{
public:
	~Rva000F82F5Buffer()
	{
		if (m_data)
			free(m_data);
	}

	void *m_data;
};

class Rva000F82F5Dtor
{
public:
	~Rva000F82F5Dtor();

private:
	char m_pad00[0x10];
	Rva000F82F5TextureHandle m_texture10; // +0x10
	Rva000F82F5TextureHandle m_texture14; // +0x14
	char m_pad18[0x2C - 0x18];
	Rva000F82F5Buffer m_buffer2C; // +0x2C
};

Rva000F82F5Dtor::~Rva000F82F5Dtor()
{
}
