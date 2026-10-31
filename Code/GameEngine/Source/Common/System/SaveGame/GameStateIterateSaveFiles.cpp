// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?iterateSaveFiles@GameState@@QAEXP6AXVUnicodeString@@PAX@Z1H@Z, retail
// 0x002DF1F1..0x002DF2DA (233 bytes, EH, RET 12). Zero Hour's and BFME 1's
// GameState::iterateSaveFiles in its BFME 2 form, which adds the save type:
// the search pattern is "*" plus that type's wide extension (0x002DBC97, the
// extension table getter; now named by its rowed GameState member), then
// the receiver-preserving view calls the existing 0x006007DA stdcall provider
// with the save directory (rowed 0x002DC267) and filename set. That provider
// ignores ECX and dispatches through the archive global's slot 7. Every name
// is handed to the callback by value with the user data.
// The set's constructor and destructor are rowed under their fold names
// (set<AsciiString> 0x000D3A71 and Rva0021C459 0x0021D5D5) and the walk uses
// the rowed _Rb_global<bool>::_M_increment. WorldBuilder's twin (0x00E6FB90)
// is unnamed.

#include "ascii_string.h"
#include "unicode_string.h"

namespace _STL
{
template <class T> struct less {};
template <class T> class allocator {};

template <class K, class C, class A>
class set
{
public:
	set();
private:
	void *m_header;
	int m_nodeCount;
	int m_compare;
};

struct _Rb_tree_node_base
{
	int _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};

template <class Dummy>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *node);
};
}

struct SaveFileNode : public _STL::_Rb_tree_node_base
{
	UnicodeString m_filename;			// +0x10
};

class Rva0021C459 : public _STL::set<AsciiString, _STL::less<AsciiString>, _STL::allocator<AsciiString> >
{
public:
	~Rva0021C459();
	_STL::_Rb_tree_node_base *header() const { return *reinterpret_cast<_STL::_Rb_tree_node_base *const *>(this); }
};

// The file-list object is Rva0021DA13 (as AptSaveLoadRva0043684C.cpp spells
// it): its destructor is the 5-byte thunk 0x0021DA13 the unwind funclet
// jumps to; the normal path expands it into ~Rva0021C459 (0x0021D5D5).
class Rva0021DA13 : public Rva0021C459
{
};

class Rva006007DAFileSystem {};
void __stdcall Rva006007DAOpen(void *,void *,void *,void *);
// The whole 81B provider ignores incoming ECX and consumes four stack words.
// Keep the native caller's unused receiver and name the existing owner.
union NativeSaveEnumerationCall {
 void (__stdcall *target)(void *,void *,void *,void *);
 void (Rva006007DAFileSystem::*member)(const UnicodeString *,const UnicodeString *,Rva0021C459 *,bool);
};
typedef char SaveEnumerationPointerWidth[sizeof(NativeSaveEnumerationCall)==4 ? 1 : -1];
extern class FileSystem *TheFileSystem;

class Rva002DC267
{
public:
	UnicodeString rva002DC267() const;		// the save directory
};

typedef void (*IterateSaveFileCallback)(UnicodeString filename, void *userData);

class GameState
{
public:
	void *rva002DBC97Get(int saveType);
	void iterateSaveFiles(IterateSaveFileCallback callback, void *userData, int saveType);
};

void GameState::iterateSaveFiles(IterateSaveFileCallback callback, void *userData, int saveType)
{
	if (callback == 0)
		return;

	UnicodeString pattern(AsciiString("*"));
	pattern += reinterpret_cast<const unsigned short *>(rva002DBC97Get(saveType));

	Rva0021DA13 filenameList;
	NativeSaveEnumerationCall enumeration={&Rva006007DAOpen};
	(reinterpret_cast<Rva006007DAFileSystem *>(TheFileSystem)->*enumeration.member)(
		&reinterpret_cast<const Rva002DC267 *>(this)->rva002DC267(), &pattern, &filenameList, true);

	for (_STL::_Rb_tree_node_base *node = filenameList.header()->_M_left; node != filenameList.header();
		node = _STL::_Rb_global<bool>::_M_increment(node))
	{
		callback(static_cast<SaveFileNode *>(node)->m_filename, userData);
	}
}
