// Target facts: WinDrawData is a nonvirtual aggregate with no bases or rowed methods.
// WinInstanceData::init (RVA 0x00322174, loop 0x00322186..0x003221AD) initializes
// nine elements per state at +0x18, +0x84 and +0xF0 with a 0x0C stride. Each
// element is three dwords: a null image at +0, colors 0x00FFFFFF at +4 and +8.
// GameWindow setters at RVAs 0x003143B9/0x003143DD/0x003143FF store image,
// color and borderColor at window+0x48/+0x4C/+0x50 plus index*0x0C. Disabled
// setters 0x00314421/0x00314445/0x0031446A use +0xB4/+0xB8/+0xBC; hilite
// setters 0x0031448F/0x003144B3/0x003144D8 use +0x120/+0x124/+0x128.
// Thus sizeof is 0x0C with no vptr. WinInstanceData's ctor/dtor at RVAs
// 0x0032225A/0x003222B8 store table VA 0x00C0D830 at the enclosing object's +0,
// outside its draw arrays. No constructor/destructor table belongs to WinDrawData.
// Donor names and struct key: Zero Hour GameClient/WinInstanceData.h. Its Color
// is Int (int); the retail setter signatures prove int and const Image *.

#pragma once

class Image;

struct WinDrawData
{
	const Image *image;
	int color;
	int borderColor;
};
