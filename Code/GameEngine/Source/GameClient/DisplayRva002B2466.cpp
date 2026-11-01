// cl: /DNDEBUG /MD /EHsc

// ?rva002B2466@Display@@QAEXMMMM@Z, RVA 0x002B2466, 138 bytes.
// Display method scaling four normalized floats by the display dimensions.
// Evidence: five callers pass TheDisplay (0x009FE9D8) as this with four float
// stack args (three pass 0,0,1,1 full-screen; 0x00356724 passes constants at
// RVA 0x00814F7C); body calls own vtable slots 0x40/0x44 alternating, the
// proven BFME2 Display getWidth/getHeight slots (Mouse::setMouseLimits precedent
// plus BFMEDisplayWidthSlot); unsigned-to-float conversion shape (fild plus jge
// plus fadd 2^32) proves UnsignedInt returns; stores four floats at
// this+0xFC/0x100/0x104/0x108. Honest-address name: owner proven Display,
// signature void __thiscall(float,float,float,float) from ret 0x10.

#include "../../Include/GameClient/Display.h"

void Display::rva002B2466(float a, float b, float c, float d)
{
	fieldFC = (float)getWidth() * a;
	field100 = (float)getHeight() * b;
	field104 = (float)getWidth() * c;
	field108 = (float)getHeight() * d;
}
