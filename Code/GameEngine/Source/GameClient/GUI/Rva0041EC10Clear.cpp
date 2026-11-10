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
#include <cstddef>
// Suppress this TU's non-retail vector<void*> operator[] copy (family2-LK3 row 25):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void *&_STL::vector<void*>::operator[](size_t);
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}
#include "prerts.h"
#include "ascii_string.h"
#include "subsystem_interface.h"
#define private public
#include "window_video_manager.h"
#undef private
#include "game_window.h"
#include "video_player.h"
#include "display.h"
// bfme link decl-only begin
namespace _STL { template <> _Hashtable_node<pair<GameWindow const *const, WindowVideo *> > * _Hashtable_iterator<pair<GameWindow const *const, WindowVideo *>, GameWindow const *, WindowVideoManager::hashConstGameWindowPtr, _Select1st<pair<GameWindow const *const, WindowVideo *> >, equal_to<GameWindow const *>, allocator<pair<GameWindow const *const, WindowVideo *> > >::_M_skip_to_next(); }
namespace _STL { template <> _Ht_iterator<pair<GameWindow const *const, WindowVideo *>, _Nonconst_traits<pair<GameWindow const *const, WindowVideo *> >, GameWindow const *, WindowVideoManager::hashConstGameWindowPtr, _Select1st<pair<GameWindow const *const, WindowVideo *> >, equal_to<GameWindow const *>, allocator<pair<GameWindow const *const, WindowVideo *> > > hashtable<pair<GameWindow const *const, WindowVideo *>, GameWindow const *, WindowVideoManager::hashConstGameWindowPtr, _Select1st<pair<GameWindow const *const, WindowVideo *> >, equal_to<GameWindow const *>, allocator<pair<GameWindow const *const, WindowVideo *> > >::begin(); }
// bfme link decl-only end

class Rva0041E875 { public: ~Rva0041E875(); };
#include "../../../Include/Common/Rva004DFC20.h"
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
extern Rva0022BD9ASubsystem *TheBaseTemplateLibrary;

void Rva0041F042::rva0041EC10()
{
    WindowVideoManager::WindowVideoMap::iterator it = ((Rva0041F042 *)TheBaseTemplateLibrary)->m_map0C.begin();
    for (; it != ((Rva0041F042 *)TheBaseTemplateLibrary)->m_map0C.end(); ++it) {
        Rva0041E875 *object = (Rva0041E875 *)it->second;
        delete object;
    }
    ((Rva004DFC20 *)&((Rva0041F042 *)TheBaseTemplateLibrary)->m_map0C)->clear();
    ((Rva0041F042 *)TheBaseTemplateLibrary)->m_map20.rva0041EA88();
}
