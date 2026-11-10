// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva0043684C@AptSaveLoad@@QAEXXZ, retail 0x0043684C..0x00436E3B (1519
// bytes, EH, 0x2D68-byte frame); called by the rowed AptSaveLoad
// rva00436FF6. The AptSaveLoad screen's replay list fill: the BFME 2 form of
// Zero Hour's PopulateReplayFileListbox (WorldBuilder twin 0x012AF9D0 pushes
// "GUI:NewSaveReplayFile" and "GUI:LastReplay" and calls
// ParseAsciiStringToGameInfo).
//
// Body: with the map cache present it resets the game list +0x288 and the
// optional second list +0x28C, clears the item list +0x2AC (rowed
// 0x00434EC9), gives both lists four columns, lists "*" plus the replay
// extension (rowed 0x0037BA48) in the replay directory (rowed 0x0037B9D4)
// through TheFileSystem (pinned 0x006007DA), refreshes the map cache and,
// in mode 3 (+0x294), adds the "GUI:NewSaveReplayFile" row. Each file's
// header (rowed dtor 0x0037B5DF) is read by a local recorder (rowed
// 0x0037BB98 / 0x0037CBB6 / 0x0037BBED); its game options parse into a
// local replay game info (pinned ctor 0x0037BADD; rowed dtor 0x0037BB53);
// the item (pinned ctor 0x00229811; rowed dtor 0x00229840) keeps the file
// name and joins +0x2AC (rowed push_back 0x00436701); the row shows the map
// (findMap / bfme_getBaseDisplayName / translate) the file name (split by
// the 0x00BBA4EC slot) and the two time strings (rowed 0x002DC081 and
// 0x002DBFAD) grey unless the version text (getFullUnicodeVersion) and
// number (TheWritableGlobalData +0xB04) match, in the second list when the
// name is "GUI:LastReplay"; the item address is the row's data. The first
// non-empty list gets the selection.

#include "ascii_string.h"
#include "unicode_string.h"

// Retail compiles these calls as non-throwing: the "GUI:LastReplay" and
// version temporaries are live across them with no EH state of their own.
template <> int StringBase<unsigned short>::compare(const StringBase<unsigned short> &str) const throw();

class GameWindow;
void GadgetListBoxReset(GameWindow *listbox);
int GadgetListBoxGetNumColumns(GameWindow *listbox);
void GadgetListBoxSetColumnWidths(GameWindow *listbox, int count, int *widths);
int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text, int color, int row, int column, bool overwrite);
void GadgetListBoxSetItemData(GameWindow *listbox, void *data, int row, int column);
void GadgetListBoxSetSelected(GameWindow *listbox, int row);

UnicodeString Rva0037BA48Get();
UnicodeString Rva0037B9D4Get();

struct SYSTEMTIME
{
	unsigned short m_fields[8];
};
UnicodeString Rva002DBFAD(SYSTEMTIME time);
UnicodeString Rva002DC081(SYSTEMTIME time, int flags);

// MSVCR71 _wsplitpath (import slot VA 0x00BBA4EC; hint/name at RVA 0x00A7429C).
extern "C" __declspec(dllimport) void __cdecl _wsplitpath(const unsigned short *path,
		unsigned short *drive, unsigned short *dir, unsigned short *fname,
		unsigned short *ext);

#include "../../../../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;

#include "../../../../../Include/GameClient/MapMetaData.h"

#include "../../../../../Include/GameClient/MapCache.h"
extern MapCache *TheMapCache;

#include "../../../../../Include/Common/VersionClass.h"
extern Version *TheVersion;

#include "../../../../../Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;

#include "../../../../../Include/GameNetwork/GameInfo.h"
bool ParseAsciiStringToGameInfo(GameInfo *game, AsciiString options, bool includeSlots);

class Rva0037BB53 : public GameInfo
{
public:
	Rva0037BB53();
	virtual ~Rva0037BB53();
private:
	unsigned char m_pad0DC[0xE3C - 0xDC];
};

class Rva0037B5DF
{
public:
	~Rva0037B5DF();

	unsigned char m_pad00[0x20];
	AsciiString m_20; // +0x20 game options
	int m_24; // +0x24 local player index
	UnicodeString m_28; // +0x28 file name
	bool m_2C; // +0x2C
	UnicodeString m_30; // +0x30
	SYSTEMTIME m_34; // +0x34
	UnicodeString m_44; // +0x44 version text
	UnicodeString m_48; // +0x48
	unsigned int m_4C; // +0x4C version number
	unsigned char m_pad50[0x58 - 0x50];
	UnicodeString m_58; // +0x58
};

class Rva0037BBED
{
public:
	Rva0037BBED();
	virtual ~Rva0037BBED();
	bool rva0037CBB6(Rva0037B5DF &header);
private:
	unsigned char m_pad004[0xE7C - 4];
};

class Rva0037B3D1
{
public:
	void reset();
};

class BfmeSubobject0022CE19
{
public:
	virtual ~BfmeSubobject0022CE19();
	unsigned char m_pad004[0x24 - 4];
	int m_24;
	unsigned char m_pad028[0xDE8 - 0x28];
};

struct TreeHintOpaque0043671B
{
	TreeHintOpaque0043671B();
	~TreeHintOpaque0043671B();

	UnicodeString m_text;
	BfmeSubobject0022CE19 m_subobject;
	unsigned int m_wordDEC, m_wordDF0;
};

namespace _STL
{
template <class T> struct less {};
template <class T> class allocator {};

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

struct _List_node_base
{
	_List_node_base *_M_next;
	_List_node_base *_M_prev;
};

template <class T, class A>
class _List_base
{
public:
	void clear();
	_List_node_base *_M_node;
};

template <class T, class A = allocator<T> >
class list : public _List_base<T, A>
{
public:
	void push_back(const T &value);
	T &back() { return *(T *)(this->_M_node->_M_prev + 1); }
};
}

struct ReplayFileNode : public _STL::_Rb_tree_node_base
{
	UnicodeString m_filename; // +0x10
};

class Rva0021C459 : public _STL::set<AsciiString, _STL::less<AsciiString>, _STL::allocator<AsciiString> >
{
public:
	~Rva0021C459();
	_STL::_Rb_tree_node_base *header() const { return *reinterpret_cast<_STL::_Rb_tree_node_base *const *>(this); }
};

class Rva0021DA13 : public Rva0021C459
{
};

#include "../../../../../Include/Common/Rva006007DAFileSystem.h"
void __stdcall Rva006007DAOpen(void *,void *,void *,void *);
// The whole 81B provider ignores incoming ECX and consumes four stack words.
// Keep the native caller's unused receiver and name the existing owner.
union NativeSaveEnumerationCall {
 void (__stdcall *target)(void *,void *,void *,void *);
 void (Rva006007DAFileSystem::*member)(const UnicodeString *,const UnicodeString *,Rva0021C459 *,bool);
};
typedef char SaveEnumerationPointerWidth[sizeof(NativeSaveEnumerationCall)==4 ? 1 : -1];
extern class FileSystem *TheFileSystem;

class AptSaveLoad
{
public:
	void rva0043684C();

private:
	unsigned char m_pad000[0x288];
	GameWindow *m_gameList; // +0x288
	GameWindow *m_autoSaveList; // +0x28C
	unsigned char m_pad290[0x294 - 0x290];
	int m_294;
	unsigned char m_pad298[0x2AC - 0x298];
	_STL::list<TreeHintOpaque0043671B> m_items; // +0x2AC
};

void AptSaveLoad::rva0043684C()
{
	if (!TheMapCache)
		return;

	GadgetListBoxReset(m_gameList);
	if (m_autoSaveList)
		GadgetListBoxReset(m_autoSaveList);
	m_items.clear();

	int widths[4] = { 0x1C, 0x24, 0x13, 0x11 };
	if (GadgetListBoxGetNumColumns(m_gameList) != 4)
		GadgetListBoxSetColumnWidths(m_gameList, 4, widths);
	if (m_autoSaveList && GadgetListBoxGetNumColumns(m_autoSaveList) != 4)
		GadgetListBoxSetColumnWidths(m_autoSaveList, 4, widths);

	UnicodeString search(AsciiString("*"));
	search += Rva0037BA48Get();

	Rva0021DA13 files;
	NativeSaveEnumerationCall enumeration={&Rva006007DAOpen};
	(reinterpret_cast<Rva006007DAFileSystem *>(TheFileSystem)->*enumeration.member)(&Rva0037B9D4Get(), &search, &files, true);

	TheMapCache->updateCache();

	unsigned int gameCount = 0;
	unsigned int lastCount = 0;
	if (m_294 == 3) {
		UnicodeString text = TheGameText->fetch("GUI:NewSaveReplayFile");
		int row = GadgetListBoxAddEntryText(m_gameList, text, 0xFFC8C8C8, -1, -1, true);
		GadgetListBoxSetItemData(m_gameList, 0, row, 0);
		++gameCount;
	}

	for (_STL::_Rb_tree_node_base *node = files.header()->_M_left; node != files.header();
		node = _STL::_Rb_global<bool>::_M_increment(node))
	{
		Rva0037B5DF header;
		header.m_2C = false;
		header.m_28 = static_cast<ReplayFileNode *>(node)->m_filename;
		Rva0037BBED recorder;
		if (TheMapCache && recorder.rva0037CBB6(header)) {
			Rva0037BB53 info;
			if (ParseAsciiStringToGameInfo(&info, header.m_20, true)) {
				bool isLast = false;
				TreeHintOpaque0043671B item;
				item.m_text = header.m_28;
				item.m_subobject.m_24 = 7;
				item.m_wordDEC = 0;
				item.m_wordDF0 = 0;
				m_items.push_back(item);

				unsigned short fileName[0x100];
				_wsplitpath(header.m_28.str(), 0, 0, fileName, 0);
				UnicodeString name(fileName);
				if (name.compare(TheGameText->fetch("GUI:LastReplay")) == 0)
					isLast = true;

				UnicodeString timeText = Rva002DBFAD(header.m_34);
				UnicodeString dateText = Rva002DC081(header.m_34, 0);
				UnicodeString mapText;
				const MapMetaData *md = TheMapCache->findMap(info.getMap());
				if (!md)
					mapText.translate(info.getMap());
				else
					mapText = const_cast<MapMetaData *>(md)->bfme_getBaseDisplayName();

				bool goodVersion = header.m_44.compare(TheVersion->getFullUnicodeVersion()) == 0
					&& header.m_4C == TheWritableGlobalData->field0B04;
				int color;
				if (goodVersion) {
					if (header.m_24 >= 0)
						color = 0xFFFFFFFF;
					else
						color = 0xFFFFFFFF;
				} else {
					if (header.m_24 >= 0)
						color = 0xFF808080;
					else
						color = 0xFF808080;
				}
				GameWindow *list = m_gameList;
				if (isLast)
					list = m_autoSaveList;
				int row = GadgetListBoxAddEntryText(list, mapText, color, -1, 0, true);
				GadgetListBoxAddEntryText(list, name, color, row, 1, true);
				GadgetListBoxAddEntryText(list, dateText, color, row, 2, true);
				GadgetListBoxAddEntryText(list, timeText, color, row, 3, true);
				GadgetListBoxSetItemData(list, &m_items.back(), row, 0);
				if (isLast)
					++lastCount;
				else
					++gameCount;
			}
			reinterpret_cast<Rva0037B3D1 *>(&recorder)->reset();
		}
	}

	if (gameCount > 0) {
		GadgetListBoxSetSelected(m_gameList, 0);
		GadgetListBoxSetSelected(m_autoSaveList, -1);
	} else if (lastCount > 0) {
		GadgetListBoxSetSelected(m_gameList, -1);
		GadgetListBoxSetSelected(m_autoSaveList, 0);
	} else {
		GadgetListBoxSetSelected(m_gameList, -1);
		GadgetListBoxSetSelected(m_autoSaveList, -1);
	}
}
