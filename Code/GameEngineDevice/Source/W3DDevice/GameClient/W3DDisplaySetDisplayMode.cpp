// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// ?setDisplayMode@W3DDisplay@@UAE_NIII_N@Z @0x00043240 256B
// W3DDisplay::setDisplayMode donor ZH W3DDisplay.cpp Bool setDisplayMode UnsignedInt xres yres bitdepth Bool windowed. Calls WW3D Set_Device_Resolution then Render2D Set_Coordinate_Range via +0x168 then Display setDisplayMode 0x0025C262. Failure restores old Display values. Evidence: slot22 vtable 0x007C3C80; rowed Set_Device_Resolution 0x00116FC0 and setDisplayMode 0x0025C262 and Set_Coordinate_Range 0x001188C0; Display slots +0x40 +0x44 +0x4C +0x54 per W3DDisplayResetD3DDevice; m_render2D +0x168 per W3DDisplayRva000433AC; caller none.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

void __cdecl BFME_DX8_Thread_Lock(void);
bool __cdecl BFME_DX8_Thread_Assert(void);

class DX8DeviceGuard
{
public:
	DX8DeviceGuard(void)
	{
		BFME_DX8_Thread_Lock();
	}
	~DX8DeviceGuard(void)
	{
		BFME_DX8_Thread_Assert();
	}
};

class RectClass
{
public:
	RectClass(float x, float y, float w, float h) : X(x), Y(y), Width(w), Height(h) {}
	float X;
	float Y;
	float Width;
	float Height;
};

class Render2DClass
{
public:
	void Set_Coordinate_Range(const RectClass &range);
};

class Display
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual int getWidth();
	virtual int getHeight();
	virtual void slot48();
	virtual unsigned int getBitDepth();
	virtual void slot50();
	virtual bool getWindowed();
	virtual Bool setDisplayMode(UnsignedInt xres, UnsignedInt yres, UnsignedInt bitdepth, Bool windowed);
};

class WW3D
{
public:
	static bool Set_Device_Resolution(int width, int height, int bits, int windowed, bool resize_window);
};

class W3DDisplay : public Display
{
public:
	virtual Bool setDisplayMode(UnsignedInt xres, UnsignedInt yres, UnsignedInt bitdepth, Bool windowed);
private:
	char m_pad04[0x164];
	Render2DClass *m_render2D;
};

Bool W3DDisplay::setDisplayMode(UnsignedInt xres, UnsignedInt yres, UnsignedInt bitdepth, Bool windowed)
{
	DX8DeviceGuard lock;
	if (WW3D::Set_Device_Resolution(xres, yres, bitdepth, windowed, true) == true)
	{
		m_render2D->Set_Coordinate_Range(RectClass(0.0f, 0.0f, (float)xres, (float)yres));
		Display::setDisplayMode(xres, yres, bitdepth, windowed);
		return true;
	}
	WW3D::Set_Device_Resolution(getWidth(), getHeight(), getBitDepth(), getWindowed(), true);
	Display::setDisplayMode(getWidth(), getHeight(), getBitDepth(), getWindowed());
	return false;
}
