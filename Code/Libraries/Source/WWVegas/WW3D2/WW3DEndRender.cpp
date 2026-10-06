// cl: /arch:SSE /G7 /DNDEBUG /MD
//
// WW3D::End_Render, retail 0x00117410 (72B), from the WorldBuilder lead
// (ww3d.cpp) and the Zero Hour / BFME1 ww3d.cpp donor. BFME2 differences
// carried from retail: the result is a bool (true), Debug_Statistics::
// End_Statistics runs only for a flipped frame, and a frame-time accumulator
// (0x00129690, address-named) runs before the snapshot flag is cleared and the
// cached render states are invalidated.
//
// Target facts: IsInitted 0x00DEC3D4, IsRendering 0x00DEC3D5, FrameCount
// 0x00DEC3E0, SnapshotActivated 0x00DEC3FD; SortingRendererClass::Flush
// 0x0012F190 and DX8Wrapper::End_Scene 0x00122BE0 (the device EndScene slot
// 0xA8 then present) are identified from their bodies.

class SortingRendererClass
{
public:
	static void Flush();
};

class DX8Wrapper
{
public:
	static void End_Scene(bool flip_frame);
	static void Invalidate_Cached_Render_States();
};

namespace Debug_Statistics
{
	void End_Statistics();
}

void Rva00129690();

class WW3D
{
public:
	static bool End_Render(bool flip_frame);
	static void Activate_Snapshot(bool b) { SnapshotActivated = b; }

private:
	static bool IsInitted;
	static bool IsRendering;
	static unsigned int FrameCount;
	static bool SnapshotActivated;
};

bool WW3D::End_Render(bool flip_frame)
{
	if (IsInitted) {
		SortingRendererClass::Flush();
		IsRendering = false;
		DX8Wrapper::End_Scene(flip_frame);
		FrameCount++;
		if (flip_frame)
			Debug_Statistics::End_Statistics();
		Rva00129690();
		Activate_Snapshot(false);
		DX8Wrapper::Invalidate_Cached_Render_States();
	}
	return true;
}
