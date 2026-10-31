// cl: /DNDEBUG /MD /EHsc /O2 /arch:SSE /G7
// platformsdk
// ?Start_Movie_Capture@WW3D@@SAXPBDMH_N@Z @ 0x00118530 213B.
// Evidence: ZH ww3d.cpp Start_Movie_Capture (stop a running capture, set IsCapturing,
// size the movie from the window rect, allocate Movie); BFME 2 adds the frame count and
// compression flag, forwarded by Toggle_Movie_Capture (0x00118610).

#include <windows.h>

extern void *g_WW3D_Hwnd;
class FrameGrabClass;
// FramGrab.cpp's view of the movie object: its own vptr and 0x20 bytes, which
// Zero Hour's larger FrameGrabClass in framgrab.h cannot be a base of.
class BfmeThingTXA
{
public:
	virtual ~BfmeThingTXA();
	BfmeThingTXA(const char *filename, int width, int height, int bitcount, float framerate, int count, bool compressed);
	int m_imageSize;
	int m_count;
	void *m_buf;
	int m_reserved0;
	int m_reserved1;
	void *m_file;
	void *m_stream;
};
// ww3d.cpp defines WW3D's statics private (?IsCapturing@WW3D@@0_NA, ...); spell them so.
class WW3D
{
public:
	static void Start_Movie_Capture(const char *filename_base, float frame_rate, int count, bool compressed);
	static void Stop_Movie_Capture();
private:
	static bool IsCapturing;
	static bool PauseRecord;
	static FrameGrabClass *Movie;
};
void WW3D::Start_Movie_Capture(const char *filename_base, float frame_rate, int count, bool compressed)
{
	if (IsCapturing)
		Stop_Movie_Capture();
	IsCapturing = true;
	RECT bounds;
	GetWindowRect((HWND)g_WW3D_Hwnd, &bounds);
	int height = bounds.bottom - bounds.top;
	int width = bounds.right - bounds.left;
	if (frame_rate == 0.0f)
	{
		frame_rate = 1.0f;
		PauseRecord = true;
	}
	else
	{
		PauseRecord = false;
	}
	Movie = reinterpret_cast<FrameGrabClass *>(new BfmeThingTXA(filename_base, width, height, 24, frame_rate, count, compressed));
}
