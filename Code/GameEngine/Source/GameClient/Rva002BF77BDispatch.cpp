// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfme_windowvideo /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Source/GameClient /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
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

// Native [2BF77B,2BF7AC): table at98, mapped receiver at node8,
// virtual slot1C with no arguments. Only the 32-bit key/pointer container
// ABI is borrowed from WindowVideoMap; application types remain unknown.
class Rva002BF77BTarget {public:
#define V(n) virtual void slot##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6)
#undef V
 virtual void dispatch();
};
class Rva002BF77B {public:void rva002BF77B();private:char prefix[0x98];WindowVideoManager::WindowVideoMap table;};
void Rva002BF77B::rva002BF77B(){
 WindowVideoManager::WindowVideoMap::iterator it=table.begin();
 for(;it!=table.end();++it)reinterpret_cast<Rva002BF77BTarget*>(it->second)->dispatch();
}
