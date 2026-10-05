// cl: /O1 /MD /EHsc
//
// Retail 0x00131DFC (86 bytes). The constructor call at +0x37 targets the
// established Rva00131BE5 constructor at 0x00131B57; the returned 0x3C-byte
// object is passed to BfmeMapPictureTexture::Set_Texture.
typedef unsigned int size_t;
void *__cdecl operator new(size_t bytes);

class GenBase009EB7D0
{
public:
	GenBase009EB7D0();
	virtual ~GenBase009EB7D0();
};

class StringClass
{
public:
	StringClass(int value, bool flag);
	~StringClass();
	char *m_Buffer;
};

class Gen_00920A20
{
public:
	Gen_00920A20(int mode);
	~Gen_00920A20();
	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
	int m_bfmeD;
	int m_bfmeE;
};

class Rva0013107A
{
public:
	Rva0013107A() throw();
	virtual ~Rva0013107A();
	char m_pad[0x54];
};

class Rva00131BE5 : public GenBase009EB7D0
{
public:
	Rva00131BE5(void *first, void *second, void *third, void *fourth,
		int fifth, int sixth);
	virtual ~Rva00131BE5();
	char m_pad04[0x10];
	Rva0013107A *m_14;
	StringClass m_str;
	Gen_00920A20 m_gen;
	int m_30;
	void *m_34;
	int m_38;
};

class TextureClass;
class BfmeMapPictureTexture
{
public:
	void Set_Texture(TextureClass *texture);
};

class Rva00131DFC
{
public:
	void rva00131DFC(void *a, void *b, void *c, void *d, int e, int f);
};

void Rva00131DFC::rva00131DFC(void *a, void *b, void *c, void *d, int e, int f)
{
	((BfmeMapPictureTexture *)this)->Set_Texture(
		(TextureClass *)new Rva00131BE5(a, b, c, d, e, f));
}
