// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfme_windowvideo /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Source/GameClient /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
// ?rva0041E971@Rva0041E971@@QAEPAVGameWindow@@PAVWindowVideo@@@Z @0x0041E971 51B.
// Reverse lookup over the WindowVideoManager playing map (+0xC): begin(),
// compare second (WindowVideo*) to arg, return first (GameWindow*), else null.
// Uses the real WindowVideoManager::WindowVideoMap type (private made public
// TU-locally) so begin/++ mangle to the rowed 0x00427195/0x0041E832 bodies.
// Layout pad 0xC reproduces retail add ecx,0xC. Evidence: callees rowed in
// window_video_manager.cpp, caller at 0x005AE117.

#include <map>
#include <hash_map>
#include "prerts.h"
#include "ascii_string.h"
#include "subsystem_interface.h"
#define private public
#include "window_video_manager.h"
#undef private
#include "game_window.h"
#include "video_player.h"
#include "display.h"

class Rva0041E971
{
public:
	GameWindow *rva0041E971(WindowVideo *vid);
private:
	char m_pad[12];
	WindowVideoManager::WindowVideoMap m_map;
};

GameWindow *Rva0041E971::rva0041E971(WindowVideo *vid)
{
	WindowVideoManager::WindowVideoMap::iterator it = m_map.begin();
	for (; it != m_map.end(); ++it)
	{
		if (it->second == vid)
			return (GameWindow *)it->first;
	}
	return NULL;
}
