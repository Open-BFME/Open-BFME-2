// cl: /MD
// ?Rva005CD78BGet@@YGEPAX@Z @0x005CD78B 41B: stdcall uchar always-1 wrapper checking rowed get 0x005CCB3E then rowed Peek_Texture 0x005CCB37 vs 1 then rowed 0x005CCB6B; evidence rows and ret-4 with mov-al-1 sibling 0x005CD762
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

class Rva005CCB6B
{
public:
	void rva005CCB6B();
};

unsigned char __stdcall Rva005CD78BGet(void *p)
{
	if (((Rva005CCB3EByteChaseField *)p)->get() != 0)
		return 1;
	if (((Font3DInstanceClass *)p)->Peek_Texture() != (TextureClass *)1)
		return 1;
	((Rva005CCB6B *)p)->rva005CCB6B();
	return 1;
}
