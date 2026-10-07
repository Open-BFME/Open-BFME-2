// cl: /DNDEBUG /MD /EHsc /O2 /arch:SSE /G7
// ?Rva00118530Start@@YAXPBDMH_N@Z @ 0x00118530 213B. Retail Start_Movie_Capture shape.
// Evidence: ZH ww3d.cpp Start_Movie_Capture donor; callers: 0x00118635 forwards 4 args;
// callees Stop_Movie_Capture GetWindowRect operator-new BfmeThingTXA-ctor; globals IsCapturing PauseRecord Movie g_WW3D_Hwnd.
struct WinRect00118530
{
	long left;
	long top;
	long right;
	long bottom;
};
extern "C" __declspec(dllimport) int __stdcall GetWindowRect(void *hwnd, WinRect00118530 *rect);
extern void *g_WW3D_Hwnd;
class FrameGrabClass
{
public:
	virtual ~FrameGrabClass();
};
class BfmeThingTXA : public FrameGrabClass
{
public:
	BfmeThingTXA(const char *filename, int width, int height, int bitcount, float framerate, int count, bool compressed);
	int m_imageSize;
	int m_count;
	void *m_buf;
	int m_reserved0;
	int m_reserved1;
	void *m_file;
	void *m_stream;
};
class WW3D
{
public:
	static bool IsCapturing;
	static FrameGrabClass *Movie;
	static void Stop_Movie_Capture();
private:
	static bool PauseRecord;
public:
	static void SetPauseRecord(bool v) { PauseRecord = v; }
};
void Rva00118530Start(const char *filename_base, float frame_rate, int count, bool compressed)
{
	if (WW3D::IsCapturing)
		WW3D::Stop_Movie_Capture();
	WW3D::IsCapturing = true;
	WinRect00118530 bounds;
	GetWindowRect(g_WW3D_Hwnd, &bounds);
	int height = bounds.bottom - bounds.top;
	int width = bounds.right - bounds.left;
	if (frame_rate == 0.0f)
	{
		frame_rate = 1.0f;
		WW3D::SetPauseRecord(true);
	}
	else
	{
		WW3D::SetPauseRecord(false);
	}
	WW3D::Movie = new BfmeThingTXA(filename_base, width, height, 24, frame_rate, count, compressed);
}
