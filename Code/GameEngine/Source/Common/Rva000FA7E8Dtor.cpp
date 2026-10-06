// cl: /MD /EHs
// ??1Rva000FA7E8Dtor@@QAE@XZ retail 0x000FA7E8 83B
// Non-virtual dtor with an empty body: member dtors in reverse order under EH
// states 1..0 -- the texture handles at +0x5C and +0x58, each releasing through
// the rowed
// ?Release_Ref@TextureClass@@QAEXXZ 0x0061ED10, then the buffer at +0x34 (inline
// CRT free of its block). Same recipe as Rva000F82F5Dtor.cpp and
// W3DRoadBufferRoadTypeDtor.cpp. Names address-derived.

extern "C" void __cdecl free(void *block);

class TextureClass
{
public:
	void Release_Ref();
};

class Rva000FA7E8TextureHandle
{
public:
	~Rva000FA7E8TextureHandle()
	{
		if (m_texture)
			m_texture->Release_Ref();
	}

	TextureClass *m_texture;
};

class Rva000FA7E8Buffer
{
public:
	~Rva000FA7E8Buffer()
	{
		if (m_data)
			free(m_data);
	}

	void *m_data;
};

class Rva000FA7E8Dtor
{
public:
	~Rva000FA7E8Dtor();

private:
	char m_pad00[0x34];
	Rva000FA7E8Buffer m_buffer34; // +0x34
	char m_pad38[0x58 - 0x38];
	Rva000FA7E8TextureHandle m_texture58; // +0x58
	Rva000FA7E8TextureHandle m_texture5C; // +0x5C
};

Rva000FA7E8Dtor::~Rva000FA7E8Dtor()
{
}
