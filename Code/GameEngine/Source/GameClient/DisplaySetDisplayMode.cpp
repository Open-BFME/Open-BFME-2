// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /Oy-
// ?setDisplayMode@Display@@UAE_NIII_N@Z, retail 0x0025C262, 278 bytes.
// Display::setDisplayMode donor from Zero Hour GeneralsMD
// Code/GameEngine/Source/GameClient/Display.cpp (Bool Display::setDisplayMode
// UnsignedInt xres yres bitdepth Bool windowed): saves Display getHeight/getWidth
// plus TacticalView getWidth/getHeight/getOrigin, stores xres/yres via
// Display setWidth/setHeight, rescales View setWidth/setHeight/setOrigin by
// oldView/oldDisplay ratios, returns TRUE. Retail ignores bitdepth/windowed
// (still ret 0x10) and uses unsigned fild+bias for Display/xres/yres and
// signed fild plus __ftol2 for View values. Evidence: slot 22 (+0x58) of
// Display vtable (getWidth +0x40 getHeight +0x44 getBitDepth +0x4C getWindowed
// +0x54 per W3DDisplayResetD3DDevice); View slots setWidth +0x38 getWidth +0x3C
// setHeight +0x40 getHeight +0x44 setOrigin +0x48 getOrigin +0x4C per View.h;
// TheTacticalView 0x009FEA3C owner View.cpp; caller 0x00043240 passes
// xres yres bitdepth windowed and checks Set_Device_Resolution first.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

class Display
{
public:
	virtual void pad00();
	virtual void pad01();
	virtual void pad02();
	virtual void pad03();
	virtual void pad04();
	virtual void pad05();
	virtual void pad06();
	virtual void pad07();
	virtual void pad08();
	virtual void pad09();
	virtual void pad10();
	virtual void pad11();
	virtual void pad12();
	virtual void pad13();
	virtual void setWidth(UnsignedInt width);
	virtual void setHeight(UnsignedInt height);
	virtual UnsignedInt getWidth();
	virtual UnsignedInt getHeight();
	virtual void pad18();
	virtual void pad19();
	virtual void pad20();
	virtual Bool getWindowed();
	virtual Bool setDisplayMode(UnsignedInt xres, UnsignedInt yres, UnsignedInt bitdepth, Bool windowed);
};

class View
{
public:
	virtual void pad00();
	virtual void pad01();
	virtual void pad02();
	virtual void pad03();
	virtual void pad04();
	virtual void pad05();
	virtual void pad06();
	virtual void pad07();
	virtual void pad08();
	virtual void pad09();
	virtual void pad10();
	virtual void pad11();
	virtual void pad12();
	virtual void pad13();
	virtual void setWidth(Int width);
	virtual Int getWidth();
	virtual void setHeight(Int height);
	virtual Int getHeight();
	virtual void setOrigin(Int x, Int y);
	virtual void getOrigin(Int *x, Int *y);
};

extern View *TheTacticalView;

Bool Display::setDisplayMode(UnsignedInt xres, UnsignedInt yres, UnsignedInt bitdepth, Bool windowed)
{
	UnsignedInt oldDisplayHeight = getHeight();
	UnsignedInt oldDisplayWidth = getWidth();
	Int oldViewWidth = TheTacticalView->getWidth();
	Int oldViewHeight = TheTacticalView->getHeight();
	Int oldViewOriginX;
	Int oldViewOriginY;
	TheTacticalView->getOrigin(&oldViewOriginX, &oldViewOriginY);
	setWidth(xres);
	setHeight(yres);
	TheTacticalView->setWidth((Real)oldViewWidth / (Real)oldDisplayWidth * (Real)xres);
	TheTacticalView->setHeight((Real)oldViewHeight / (Real)oldDisplayHeight * (Real)yres);
	TheTacticalView->setOrigin((Real)oldViewOriginX / (Real)oldDisplayWidth * (Real)xres, (Real)oldViewOriginY / (Real)oldDisplayHeight * (Real)yres);
	return true;
}
