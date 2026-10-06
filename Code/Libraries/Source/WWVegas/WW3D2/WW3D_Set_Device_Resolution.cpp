// cl: /DNDEBUG /MD /EHsc
//
// ?Set_Device_Resolution@WW3D@@SA_NHHHH_N@Z, retail 0x00116FC0, 39 bytes.
// Dedicated TU: BFME2 returns a plain success flag here (retail ends with
// test al,al / setne al / ret), while the Zero Hour reference header declares
// WW3DErrorType. Declared locally as bool to reproduce the retail bytes;
// the enum overload left in ww3d.cpp is unclaimed dead code.

class DX8Wrapper
{
protected:
	static bool Set_Device_Resolution(int width, int height, int bits, int windowed, bool resize_window);
	friend class WW3D;
};

class WW3D
{
public:
	static bool Set_Device_Resolution(int width, int height, int bits, int windowed, bool resize_window);
};

// ?Set_Device_Resolution@WW3D@@SA_NHHHH_N@Z
bool WW3D::Set_Device_Resolution(int width, int height, int bits, int windowed, bool resize_window)
{
	bool success = DX8Wrapper::Set_Device_Resolution(width, height, bits, windowed, resize_window);
	if (success) {
		return true;
	} else {
		return false;
	}
}
