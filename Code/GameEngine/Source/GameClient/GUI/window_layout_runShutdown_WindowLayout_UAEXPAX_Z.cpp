// cl: -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI
// WindowLayout::runShutdown is an inline in the BFME1 donor
// game/GameEngine/Source/GameClient/window_layout.h:
//     virtual void runShutdown(void *userData)
//     { if (m_shutdown) m_shutdown(this, userData); }
// The donor window_layout.cpp only emits it through the class vtable, so there
// is no donor .cpp definition to copy. Retail 0x0040FDA2 tests the callback at
// this+0x20 and calls it, which fixes the offset; the header body is emitted
// out-of-line here.
typedef void (*WindowLayoutFunc)(void *layout, void *userData);

class WindowLayout
{
public:
	virtual void runShutdown(void *userData);

private:
	char m_pad[0x1c];		// after the vptr
	WindowLayoutFunc m_shutdown;		// this+0x20
};

void WindowLayout::runShutdown(void *userData)
{
	if (m_shutdown)
		m_shutdown(this, userData);
}
