// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfme_windowvideo /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Source/GameClient /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
// ?rva0041E9A4@Rva0041F042@@UAEXXZ @0x0041E9A4 46B
// Evidence: ref lane VTABLE slot 9 of 0x0083AF78 (Rva0041F042 vtable); iterates WindowVideoMap at +0xC
// via rowed begin 0x00427195 and ++ 0x0041E832 calling rowed notifyAll 0x0041E717 on each second.
// Uses real WindowVideoMap type like sibling Rva0041E971Find; class proven by vtable.
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

class Rva0041E717Broadcast
{
public:
	void notifyAll();
};

class Rva0041F042
{
public:
	virtual void rva0041E9A4();
private:
	char m_pad04[12 - 4];
	WindowVideoManager::WindowVideoMap m_map0C;
};

void Rva0041F042::rva0041E9A4()
{
	WindowVideoManager::WindowVideoMap::iterator it = m_map0C.begin();
	for (; it != m_map0C.end(); ++it)
	{
		WindowVideo *v = it->second;
		((Rva0041E717Broadcast *)v)->notifyAll();
	}
}
