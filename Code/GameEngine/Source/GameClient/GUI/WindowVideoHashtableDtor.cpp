// cl: /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// Retail RVA 0x0053F378, 57 bytes.
// ??1?$hashtable@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@PBVGameWindow@@UhashConstGameWindowPtr@WindowVideoManager@@U?$_Select1st@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@U?$equal_to@PBVGameWindow@@@2@V?$allocator@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@@_STL@@QAE@XZ
// WindowVideoMap hashtable dtor, called by WindowVideoManager dtor at 0x0053F45C.
// Same 57B direct-_free shape as the ArmorStore hashtable dtor at 0x003609BE
// (clear then free buckets, MALLOC config). Clear resolves to the pinned
// WindowVideo spelling at 0x001DBCDC, _free is rowed at 0x00030830.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <hash_map>

class GameWindow;
class WindowVideo;

class WindowVideoManager
{
public:
	struct hashConstGameWindowPtr
	{
		size_t operator()(const GameWindow *const &p) const
		{
			return (size_t)p;
		}
	};
};

typedef std::hash_map<const GameWindow *, WindowVideo *,
	WindowVideoManager::hashConstGameWindowPtr,
	std::equal_to<const GameWindow *> > WindowVideoMap;

class WindowVideoHashtableHolder
{
public:
	WindowVideoHashtableHolder();
	~WindowVideoHashtableHolder();

private:
	WindowVideoMap m_map;
};

// ??0WindowVideoHashtableHolder@@QAE@XZ present-unmatched
WindowVideoHashtableHolder::WindowVideoHashtableHolder()
{
	m_map.clear();
}

// ??1WindowVideoHashtableHolder@@QAE@XZ present-unmatched
WindowVideoHashtableHolder::~WindowVideoHashtableHolder()
{
	m_map.clear();
}
