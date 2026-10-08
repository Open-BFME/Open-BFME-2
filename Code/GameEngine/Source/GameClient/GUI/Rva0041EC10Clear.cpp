// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfme_windowvideo /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Source/GameClient /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
// Native 0041EC10..0041EC73 drains mapped objects in the global registry,
// then clears tables at +0C and +20. The verified sibling 41E9A4 establishes
// this iterator representation and the shared begin/increment helpers.
// WindowVideoMap is only that established 32-bit key/pointer ABI view;
// it does not establish WindowVideoManager or WindowVideo as target identities.
// Native mapped objects are the independently rowed Rva0041E875 destructor.
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

class Rva0041E875 { public: ~Rva0041E875(); };
class Rva001DBCDCTarget { public: void rva001DBCDC(); };
class Rva0041EA88 {
public: void rva0041EA88();
private: int m_functors; void **m_begin, **m_end, **m_capacity; unsigned m_count;
};
class Rva0041F042 {
public: void rva0041EC10();
private:
    char m_subsystem[12];
    WindowVideoManager::WindowVideoMap m_map0C;
    Rva0041EA88 m_map20;
};
class Rva0022BD9ASubsystem;
extern Rva0022BD9ASubsystem *g_00E03124;

void Rva0041F042::rva0041EC10()
{
    WindowVideoManager::WindowVideoMap::iterator it = ((Rva0041F042 *)g_00E03124)->m_map0C.begin();
    for (; it != ((Rva0041F042 *)g_00E03124)->m_map0C.end(); ++it) {
        Rva0041E875 *object = (Rva0041E875 *)it->second;
        delete object;
    }
    ((Rva001DBCDCTarget *)&((Rva0041F042 *)g_00E03124)->m_map0C)->rva001DBCDC();
    ((Rva0041F042 *)g_00E03124)->m_map20.rva0041EA88();
}
