// cl: /O1 /Ob2 /EHsc /DNDEBUG /MD /Ireference/shims/bfme2_ascii
// Target74104C is the79B destructor called by the existing28B deleting
// wrapper7410D0. Native stores primaryCF1648 and secondaryCF1644 vptrs;
// destroys StringBase<char> at64 through full133B36410 and its secondary
// base at8 through full111B5248D0; finally restores primary C3962C.
// The secondary provider consumes58 bytes; the primary consumed prefix is8.
// The class is W3DAptComponentColorPicker (0x80 bytes, the factory's size);
// its view follows W3DAptComponentColorPicker.cpp. The owner string at +64
// is an AsciiString, whose inline destructor is that releaseBuffer call.
// Primary base table C3962C has an existing verified provider; it is not
// the canonical Snapshot table. Its force-inline restoration adds no row:
// the base's own vptr store (CF1630) before it is dead.
struct EmitVtableTag;
extern "C" const void *const __identifier("??_7Rva0045EF90Base@@6B@")[];
class Rva0074104CBase {
public:
 // ?Rva0074104CBase::~Rva0074104CBase present-unmatched
 // LINK: the implicit default ctor's COMDAT loses to the first-in-order copy; the vtable
 // emitter ctor below calls a TU-unique no-init ctor instead. No flags touched.
 struct BfmeNoInitB19 {};
 Rva0074104CBase(BfmeNoInitB19) {}
 Rva0074104CBase() : unknown04(-1) {}
 virtual __forceinline ~Rva0074104CBase() {*(const void**)this=__identifier("??_7Rva0045EF90Base@@6B@");}
private: unsigned int unknown04;
};
#include "../../Include/GameClient/Rva005248D0.h"
#include "ascii_string.h"
class Image;
struct ColorFloatPoint {float x,y;ColorFloatPoint(float a=0,float b=0):x(a),y(b){}};
// Fields follow W3DAptComponentColorPicker.cpp's view (Init, ExternFunc, Render).
class W3DAptComponentColorPicker : public Rva0074104CBase, public Rva005248D0 {
public: W3DAptComponentColorPicker(); W3DAptComponentColorPicker(EmitVtableTag*); virtual ~W3DAptComponentColorPicker();
private:
 const Image *image;
 AsciiString owner;
 ColorFloatPoint scaleSize;
 unsigned color;
 bool sample, seek;
 char p76[2];
 int cursorX, cursorY;
};
W3DAptComponentColorPicker::~W3DAptComponentColorPicker() {}

// Target name is address-derived. The /O1 BFME 1 Q4 niladic factory is a
// unique 53-byte placement here; target relocations call operator new(0x80)
// and the constructor at 0x00740FD9. The constructor's vtable references and
// the adjacent destructor rows tie that call to this target class. The donor
// class name and source-side identity are not carried over.
W3DAptComponentColorPicker *makeRva0074104C()
{
	return new W3DAptComponentColorPicker;
}

// ?<W3DAptComponentColorPicker::W3DAptComponentColorPicker> absent-from-retail
W3DAptComponentColorPicker::W3DAptComponentColorPicker(EmitVtableTag *) : Rva0074104CBase((Rva0074104CBase::BfmeNoInitB19()))
{
}
