// cl: /DNDEBUG /MD /EHsc
//
// 0x000456F0 is a 24B wrapper: forward this and both RectClass references,
// duplicate the color into four arguments, call 0x00042719, then ret 0xC.
// The BFME1 donor names the target helper Render2DClass::Add_Quad, but target
// owner identity is not independently established, so this wrapper stays
// address-derived.

class RectClass;

class Render2DClass
{
public:
	void Add_Quad(const RectClass &screen, const RectClass &uv,
		unsigned long color0, unsigned long color1,
		unsigned long color2, unsigned long color3);
};

struct Rva000456F0
{
	void rva000456F0(const RectClass &screen, const RectClass &uv, unsigned long color);
};

void Rva000456F0::rva000456F0(const RectClass &screen, const RectClass &uv,
	unsigned long color)
{
	((Render2DClass *)this)->Add_Quad(screen, uv, color, color, color, color);
}
