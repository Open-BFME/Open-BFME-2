// cl: /O1 /arch:SSE /G7 /MD
// ?rva005CD737@Rva005CD737@@QAEEPAX@Z
//
// ?rva005CD737@Rva005CD737@@QAEEPAX@Z, retail 0x005CD737, 43 bytes.
// Thiscall uchar method with one void* param: if rowed get 0x005CCB3E on the
// param is nonzero return 1; if rowed Peek_Texture 0x005CCB37 on the param is
// not (TextureClass*)1 return 1; else store 1 at +0x04 and return 0.
// Evidence: table slot 0x0087500C neighbours; same shape as stdcall sibling
// ?Rva005CD762Get@@YGEPAX@Z in Rva005CD762.cpp; callees all rowed; ret 4.
class Rva005CCB3EByteChaseField
{
public:
	unsigned char get() const;
};

class TextureClass;
class Font3DInstanceClass
{
public:
	TextureClass *Peek_Texture();
};

class Rva005CD737
{
public:
	unsigned char rva005CD737(void *p);
private:
	char m_pad[4];
	unsigned char m_4;
};

unsigned char Rva005CD737::rva005CD737(void * volatile p)
{
	if (((Rva005CCB3EByteChaseField *)p)->get() != 0)
		return 1;
	TextureClass *t = ((Font3DInstanceClass *)p)->Peek_Texture();
	if (t == (TextureClass *)1)
	{
		m_4 = (unsigned char)(unsigned int)t;
		return 0;
	}
	return 1;
}
