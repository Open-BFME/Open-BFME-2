// cl: /DNDEBUG /MD /EHsc
//
// ?Set_Render_Device@WW3D@@SA_NHHHHH_N00@Z, retail 0x00116F10, 54 bytes.
// Dedicated TU: BFME2 returns a plain success flag here (retail ends with
// test al,al / setne al / ret), while the Zero Hour reference header declares
// WW3DErrorType. Declared locally as bool to reproduce the retail bytes.

class DX8Wrapper
{
protected:
	static bool Set_Render_Device(int dev, int width, int height, int bits, int windowed, bool resize_window, bool reset_device, bool restore_assets);
	friend class WW3D;
};

class WW3D
{
public:
	static bool Set_Render_Device(int dev, int width, int height, int bits, int windowed, bool resize_window, bool reset_device, bool restore_assets);
};

// ?Set_Render_Device@WW3D@@SA_NHHHHH_N00@Z
bool WW3D::Set_Render_Device(int dev, int width, int height, int bits, int windowed, bool resize_window, bool reset_device, bool restore_assets)
{
	bool success = DX8Wrapper::Set_Render_Device(dev, width, height, bits, windowed, resize_window, reset_device, restore_assets);
	if (success) {
		return true;
	} else {
		return false;
	}
}
