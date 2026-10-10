// ?Rva00206DA4Enum@@YGXPAX@Z
// partial score=0.88 date=2026-10-10
// cl: /Ob1 /Oy- /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfme_windowvideo /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Source/GameClient /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
// ?Rva00206DA4Enum@@YGXPAX@Z, retail 0x00206DA4, 91 bytes, stdcall ret 4.
// Visits every entry of the map at +0x0C of the FXListStore global (VA
// 0x00DFDC3C): begin via the rowed hashtable 0x00427195, prefix ++ via 0x0041E832,
// and for each entry's value calls the visitor's vtable slot 0 with the C string
// of the AsciiString at value+0x0C (empty literal when unset). The map is viewed as
// the rowed hash_map instantiation because the retail iterator code is shared
// (ICF) with the window-video map; the visitor/value views are neutral and the
// visitor's own class is not recovered.
#include <hash_map>

class GameWindow;
class WindowVideo;

class WindowVideoManager
{
public:
	typedef const GameWindow *ConstGameWindowPtr;
	struct hashConstGameWindowPtr
	{
		size_t operator()(ConstGameWindowPtr const &) const;
	};
};

typedef std::hash_map<const GameWindow *, WindowVideo *, WindowVideoManager::hashConstGameWindowPtr, std::equal_to<const GameWindow *> > WindowVideoMap;

struct Rva00206DA4IterHelper
{
	void *m_current;
	void *m_owner;
};

struct Rva00206DA4Visitor
{
	virtual void visit(const char *name);
};

struct Rva00206DA4Entry
{
	char m_pad[0x0C];
	const char *m_text;
};

struct Rva00206DA4Store
{
	char m_pad[0x0C];
	WindowVideoMap m_map;
};

class FXListStore;
extern FXListStore *TheFXListStore;

struct Rva00206DA4Node
{
	Rva00206DA4Node *m_next;
	const GameWindow *m_key;
	Rva00206DA4Entry *m_value;
};

void __stdcall Rva00206DA4Enum(void *visitorArg)
{
	Rva00206DA4Visitor *visitor = (Rva00206DA4Visitor *)visitorArg;
	WindowVideoMap &map = reinterpret_cast<Rva00206DA4Store *>(TheFXListStore)->m_map;
	WindowVideoMap::iterator it = map.begin();
	while (((volatile Rva00206DA4IterHelper *)&it)->m_current != 0)
	{
		Rva00206DA4Entry *entry = (Rva00206DA4Entry *)it->second;
		visitor->visit(entry->m_text ? entry->m_text + 8 : "");
		++it;
	}
}
