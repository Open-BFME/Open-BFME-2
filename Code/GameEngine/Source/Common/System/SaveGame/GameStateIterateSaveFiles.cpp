// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?iterateSaveFiles@GameState@@QAEXP6AXVUnicodeString@@PAX@Z1H@Z, retail
// 0x002DF1F1..0x002DF2DA (233 bytes, EH, RET 12). Zero Hour's and BFME 1's
// GameState::iterateSaveFiles in its BFME 2 form, which adds the save type:
// the search pattern is "*" plus that type's wide extension (0x002DBC97, the
// extension table getter; its body never reads ECX, so it is reached through
// a thiscall pin), TheFileSystem lists the save directory (rowed 0x002DC267)
// into a filename set (0x006007DA, likewise pinned as the FileSystem method it
// is), and every name is handed to the callback by value with the user data.
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

class Rva006007DAFileSystem
{
public:
	void rva006007DA(const UnicodeString *directory, const UnicodeString *pattern, Rva0021C459 *list, bool recurse);
};
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
	const unsigned short *rva002DBC97(int saveType);
	void iterateSaveFiles(IterateSaveFileCallback callback, void *userData, int saveType);
};

void GameState::iterateSaveFiles(IterateSaveFileCallback callback, void *userData, int saveType)
{
	if (callback == 0)
		return;

	UnicodeString pattern(AsciiString("*"));
	pattern += rva002DBC97(saveType);

	Rva0021C459 filenameList;
	reinterpret_cast<Rva006007DAFileSystem *>(TheFileSystem)->rva006007DA(
		&reinterpret_cast<const Rva002DC267 *>(this)->rva002DC267(), &pattern, &filenameList, true);

	for (_STL::_Rb_tree_node_base *node = filenameList.header()->_M_left; node != filenameList.header();
		node = _STL::_Rb_global<bool>::_M_increment(node))
	{
		callback(static_cast<SaveFileNode *>(node)->m_filename, userData);
	}
}
