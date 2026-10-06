// cl: /DNDEBUG /MD /EHsc
//
// Registry device wrappers, retail 0x00117030/0x00117010/0x00117070.
// Dedicated TU: BFME2 keeps these as plain success flags (retail ends with
// test al,al / setne al / ret). The seven-argument saver is byte-identical to
// the BFME1 donor at 0x008FD230; the one-argument saver and two-argument
// loader follow the same proven bool shape against their DX8 callees.

class DX8Wrapper
{
public:
	static bool Registry_Save_Render_Device(const char *sub_key);
	static bool Registry_Load_Render_Device(const char *sub_key, bool resize_window);
protected:
	static bool Registry_Save_Render_Device(const char *sub_key, int device, int width, int height, int depth, bool windowed, int texture_depth);
};

// Expose the protected DX8 registry helpers to these free wrappers.
class RegistryDeviceAccess : public DX8Wrapper
{
public:
	using DX8Wrapper::Registry_Save_Render_Device;
	using DX8Wrapper::Registry_Load_Render_Device;
};

// Seven-argument registry saver: retail 0x00117030, 49 bytes.
bool SaveRenderDeviceRegistrySettings(const char *sub_key, int device, int width, int height, int depth, bool windowed, int texture_depth)
{
	bool success = RegistryDeviceAccess::Registry_Save_Render_Device(sub_key, device, width, height, depth, windowed, texture_depth);
	if (success) {
		return true;
	}
	return false;
}

// Single-argument registry saver: retail 0x00117010, 19 bytes.
bool SaveRenderDeviceRegistry(const char *sub_key)
{
	bool success = RegistryDeviceAccess::Registry_Save_Render_Device(sub_key);
	if (success) {
		return true;
	}
	return false;
}

// Two-argument registry loader: retail 0x00117070, 24 bytes.
bool LoadRenderDeviceRegistry(const char *sub_key, bool resize_window)
{
	bool success = RegistryDeviceAccess::Registry_Load_Render_Device(sub_key, resize_window);
	if (success) {
		return true;
	}
	return false;
}
