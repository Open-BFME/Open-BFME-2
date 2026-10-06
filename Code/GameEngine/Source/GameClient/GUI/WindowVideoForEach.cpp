// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfme_windowvideo /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Source/GameClient /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
// ?Rva000AACE4ForEach@@YAXXZ @0x000AACE4 34B for_each over WindowVideoMap
// Evidence: calls rowed Ht_iterator prefix ++ 0x0041E832; cmp [ebp+8] vs [ebp+0x10] is inlined !=; add eax 4 push is inlined * passing pair& to indirect deleter at [ebp+0x18]; returns deleter; callers 0x000AAEA6 0x000AAED1 in dtor 0x000AAE59 pass begin/end plus funcs 0x000A97C9 0x000A9DA8 with add esp 0x14; honest Rva free-function name
#include <hash_map>
class GameWindow;
class WindowVideo;
class WindowVideoManager
{
public:
	typedef const GameWindow *ConstGameWindowPtr;
	struct hashConstGameWindowPtr
	{
		size_t operator()(ConstGameWindowPtr p) const
		{
			return (size_t)p;
		}
	};
};
typedef std::hash_map<const GameWindow *, WindowVideo *, WindowVideoManager::hashConstGameWindowPtr, std::equal_to<const GameWindow *> > WindowVideoMap;
typedef void (__cdecl *WindowVideoPairDeleter)(WindowVideoMap::value_type &);
WindowVideoPairDeleter Rva000AACE4ForEach(WindowVideoMap::iterator first, WindowVideoMap::iterator last, WindowVideoPairDeleter f)
{
	for (; first != last; ++first)
		f(*first);
	return f;
}
