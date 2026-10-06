// cl: /O1 /MD
// ?Rva005CD762Get@@YGEPAX@Z @0x005CD762 41B: stdcall uchar always-1 wrapper checking rowed get 0x005CCB3E then rowed Peek_Texture 0x005CCB37 vs 1 then rowed 0x005CCB63; evidence rows and ret-4 with mov-al-1
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

class Rva005CCB63
{
public:
	void rva005CCB63();
};

unsigned char __stdcall Rva005CD762Get(void *p)
{
	if (((Rva005CCB3EByteChaseField *)p)->get() != 0)
		return 1;
	if (((Font3DInstanceClass *)p)->Peek_Texture() != (TextureClass *)1)
		return 1;
	((Rva005CCB63 *)p)->rva005CCB63();
	return 1;
}
