// cl: /O1 /Ob2 /EHsc /DNDEBUG /MD /Ireference/shims/bfme2_ascii
//
// ??0W3DAptComponentColorPicker@@QAE@XZ, retail 0x00740FD9..0x00741044 (107 bytes, EH,
// ret 0). Constructor of the 0x80-byte object the factory 0x0074109B builds
// (class named by its rowed destructor 0x0074104C and deleting destructor
// 0x007410D0; layout from that destructor file, OpaqueScalarDeletingDtorsB19.cpp):
// the primary base (vptr 0x00CF1630, then 0x00CF1648 as the final vptr)
// keeps -1 at +4, the Apt window half (0x002D2C34) sits at +8 under vptr
// 0x00CF1644, and the tail +0x60..+0x7C is cleared (floats at +0x68/+0x6C).
// The tail follows W3DAptComponentColorPicker.cpp's view (Init, ExternFunc, Render).
#include "ascii_string.h"

class Rva0074104CBase
{
public:
	Rva0074104CBase() : unknown04(-1) {}
	virtual ~Rva0074104CBase();
private:
	unsigned int unknown04;
};

#include "../../Include/GameClient/Rva005248D0.h"

class Image;
struct ColorFloatPoint {float x,y;ColorFloatPoint(float a=0,float b=0):x(a),y(b){}};

class W3DAptComponentColorPicker : public Rva0074104CBase, public Rva005248D0
{
public:
	W3DAptComponentColorPicker();
	virtual ~W3DAptComponentColorPicker();
private:
	const Image *image;
	AsciiString owner;
	ColorFloatPoint scaleSize;
	unsigned color;
	bool sample, seek;
	char p76[2];
	int cursorX, cursorY;
};

W3DAptComponentColorPicker::W3DAptComponentColorPicker()
	: image(0), color(0), sample(false), seek(false), cursorX(0), cursorY(0)
{
}
