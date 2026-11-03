// cl: /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// Bodies ported from Open-BFME-1's GameEngineDevice/Source/MilesAudioDevice/Rv
// a006AD9B0GetAllowAudioReinitialize.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// MilesAudioManager::rva006AD9B0 0x00059646 (163B). Callee addresses are read
// off retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
// Open-BFME: ?rva006AD9B0@MilesAudioManager@@QAE_NXZ, retail 0x006AD9B0, 234 bytes.
//
// __thiscall member that ignores `this`: both retail callers load ecx right
// before calling ILT 0x0002F1D5, and the matched MilesAudioManager::rva006B86D0
// models the call as a MilesAudioManager member. The body builds a fresh
// OptionPreferences (which loads Options.ini in its own constructor), looks up
// the AllowAudioReinitialize key, and returns false only when the stored value
// case-insensitively equals "false" or "no"; a missing key, or any other value,
// returns true. ecx is never read. The method name is not proven, so it keeps
// its address token.
//
// callers: ?rva006B86D0@MilesAudioManager@@UAEXI@Z (via ILT) and the
// ?d_006b9c90@@YAXXZ dump.
//
// callees, in body order:
//   OptionPreferences::OptionPreferences(void) via ILT 0x0003713C -> 0x000904E0
//   StringBase<char>(const char *) 0x00888BC0 (the key temporary)
//   PreferenceMap::find via ILT 0x0000AEAC -> 0x00080600 (STLport _M_find<AsciiString>)
//   StringBase<char>::releaseBuffer 0x00887940 (key temporary destructor)
//   StringBase<char>(const StringBase &) 0x00887B60 (value copy)
//   AsciiString::compareNoCase(const char *) via ILT 0x000405E8 -> 0x00075E00
//   StringBase<char>::releaseBuffer 0x00887940 (value destructor)
//   OptionPreferences::~OptionPreferences() via ILT 0x00001307 -> 0x00090450
//
// string literals verified against the retail image: key = 0x0111C2A8
// "AllowAudioReinitialize", compares = 0x0111C2A0 "false", 0x010EBA88 "no"
//
// Frame (retail, after push esi): value esp+4, key esp+8, prefs esp+0xc..0x20.
// OptionPreferences is 20 bytes (vptr, 12-byte map, one trailing dword), as
// upstream UserPreferences.h has it. The key is the by-value temporary the
// find() call builds from the literal, and the value is a function-scope local
// after an early return; together they give the two strings separate slots,
// which a named key in a nested block (sharing the value's slot) does not.

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

// Retail calls the rowed StringBase text comparator with no unwind state.
template <> int StringBase<char>::compareNoCase(const char *text) const throw();

class PreferenceMap;

namespace _STL
{
template <class _T1, class _T2> struct pair;
template <class _Pair> struct _Select1st;
template <class _Tp> struct less;
template <class _Tp> class allocator;
template <class _Value> struct _Rb_tree_node;

// The tree under the map: only its private key-search worker, the shared
// AsciiString-keyed _M_find rowed at 0x001F8437, is named here.
template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
class _Rb_tree
{
	friend class ::PreferenceMap;

private:
	template <class _KT> _Rb_tree_node<_Value> *_M_find(const _KT &) const throw();
};
}

typedef _STL::pair<const AsciiString, AsciiString> PreferencePair;
typedef _STL::_Rb_tree<AsciiString, PreferencePair, _STL::_Select1st<PreferencePair>,
	_STL::less<AsciiString>, _STL::allocator<PreferencePair> > PreferenceTree;

struct PreferenceNode
{
	unsigned char m_unreconstructed_00[0x14];
	AsciiString m_value;								///< retail this+0x14
};

class PreferenceMap
{
public:
	PreferenceNode *find(const AsciiString &key) const
	{
		return (PreferenceNode *)((const PreferenceTree *)this)->_M_find(key);
	}
	PreferenceNode *end(void) const { return m_end; }

	PreferenceNode *m_end;
	unsigned char m_unreconstructed_04[8];
};

class OptionPreferences
{
public:
	OptionPreferences(void);
	virtual ~OptionPreferences();

	PreferenceMap m_prefs;
	unsigned char m_unreconstructed_10[4];
};

class PreferenceIterator
{
public:
	PreferenceIterator(PreferenceNode *node) : m_node(node) {}

	bool operator==(PreferenceNode *node) const
	{
		return m_node == node;
	}

	PreferenceNode *operator->(void) const
	{
		return m_node;
	}

private:
	PreferenceNode *m_node;
};

#include "../../Include/MilesAudioDevice/MilesAudioManager.h"

bool MilesAudioManager::rva006AD9B0(void)
{
	OptionPreferences prefs;
	PreferenceIterator it = prefs.m_prefs.find("AllowAudioReinitialize");
	if (it == prefs.m_prefs.end())
		return true;

	AsciiString value(it->m_value);
	// Both native calls target StringBase<char>::compareNoCase at 0x00037980.
	// Use that existing provider through the donor's one-pointer base view.
	const StringBase<char> *comparison = (const StringBase<char> *)&value;
	if (comparison->compareNoCase("false") == 0 || comparison->compareNoCase("no") == 0)
		return false;

	return true;
}
