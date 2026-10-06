// cl: /MD
//
// ?rva00318B94@Rva00318B94@@QAEEXZ at 0x00318B94, 17 bytes.
// Leaf thiscall: holder = [ecx+0x88] (same outer offset as Drawable::getWheelInfo
// 0x00318B83 in DrawableFields.cpp); returns byte at [holder+0x5c] or 0.
// Honest address name; layout from retail loads.

class Rva00318B94
{
public:
	unsigned char rva00318B94();
private:
	unsigned char m_pre88[0x88];
	void *m_holder;
};

unsigned char Rva00318B94::rva00318B94()
{
	unsigned char *holder = *(unsigned char **)((unsigned char *)this + 0x88);
	if (holder)
		return holder[0x5c];
	return 0;
}
