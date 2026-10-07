// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?Rva003ED498Count@@YAXPBX@Z @ 0x003ED498 77B
// Free bit-count walker over global RB-tree at 0x00A02E50 via rowed _M_increment 0x00024250.
// For each node tests bit m_14 in caller vector bitset and incs m_18; callers 0x003ED658/0x003ED989 pass this.
// Neighbour StringRecordCopyBFME2.cpp shares /O1 /EHsc STLport flags and vector idioms.

#include "ascii_string.h"
#include <algorithm>

namespace _STL
{
typedef bool _Rb_tree_Color_type;
struct _Rb_tree_node_base
{
	_Rb_tree_Color_type _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};
template <class Dummy> class _Rb_global
{
public:
	static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *);
};
}

class Rva003ED5A5Xfer;
struct BitRange
{
	unsigned *m_begin;
	unsigned const *m_end;
	unsigned char m_pad08[8];
	AsciiString m_str10;
	AsciiString rva003ED4E5();
	AsciiString rva00568BE2();
	void rva003ED411(const BitRange &other);
	void rva003ED5A5(Rva003ED5A5Xfer *xfer);
};
struct TreeNode
{
	_STL::_Rb_tree_node_base m_base;
	AsciiString m_10;
	unsigned m_14;
	unsigned m_18;
};
extern _STL::_Rb_tree_node_base *g_00A02E50;
// g_00A02E50: matched references place it at VA 0xe02e50 (zero-filled .bss).
_STL::_Rb_tree_node_base * g_00A02E50;
void __cdecl Rva003ED498Count(void const *arg)
{
	_STL::_Rb_tree_node_base *n = g_00A02E50->_M_left;
	if (n == g_00A02E50)
		return;
	BitRange const *r = (BitRange const *)arg;
	do
	{
		TreeNode *tn = (TreeNode *)n;
		unsigned bits = tn->m_14;
		unsigned const *begin = r->m_begin;
		unsigned const *finish = r->m_end;
		unsigned count = (unsigned)(finish - begin);
		unsigned words = bits >> 5;
		if (count > words)
		{
			unsigned mask = 1u << (bits & 31);
			if ((begin[words] & mask) != 0)
				++tn->m_18;
		}
		n = _STL::_Rb_global<bool>::_M_increment(n);
	} while (n != g_00A02E50);
}

// Whole one-body donor: Open-BFME-1 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24,
// game/GameEngine/Source/GameLogic/LargeGroupAudio/LargeGroupAudioKeyMapBuildKeyString.cpp.
// Native Ghidra 0x3ED4E5/192 shares this unit's sentinel and bit-prefix
// traversal. Narrow concat/copy/release exports prove a string at node+0x10;
// the existing retain walker independently establishes node+0x14/+0x18.
// Reconcile that previously untyped word with canonical AsciiString.
// BitRange is an existing structural prefix view, not a recovered class
// identity. The target method name is unknown; keep it address-qualified.
// The donor supplies the audio-key interpretation and source provenance.
// The donor's inline char argument occupies a four-byte stack home.
// Keep that argument shape while calling canonical StringBase directly.
// ?appendAudioKeySeparator absent-from-retail
static __forceinline void appendAudioKeySeparator(AsciiString &result, char separator)
{
    ((StringBase<char> *)&result)->concat(&separator, 1);
}

// ?rva003ED4E5@BitRange@@QAE?AVAsciiString@@XZ
AsciiString BitRange::rva003ED4E5()
{
	AsciiString result;
	TreeNode *record =
		(TreeNode *)g_00A02E50->_M_left;

	while (record != (TreeNode *)g_00A02E50)
	{
		unsigned int key = record->m_14;
		unsigned int word = key >> 5;
		unsigned int mask = 1 << (key & 0x1F);
		if (m_end - m_begin > word &&
			(m_begin[word] & mask) != 0)
		{
			if (!result.isEmpty())
				appendAudioKeySeparator(result, ' ');
			((StringBase<char> *)&result)->concat(
				*(const StringBase<char> *)&record->m_10);
		}

		record = (TreeNode *)
			_STL::_Rb_global<bool>::_M_increment(&record->m_base);
	}

	return result;
}

// ?rva00568BE2@BitRange@@QAE?AVAsciiString@@XZ 0x00568BE2 56B AsciiString getter at +0x10 with rva003ED4E5 fallback through rowed StringBase copy ctor. Callers in 0x005691DB 0x003EE23C 0x0056913D 0x003EE576.
AsciiString BitRange::rva00568BE2()
{
	if (m_str10.isEmpty())
		return rva003ED4E5();
	return m_str10;
}

// BFME1 semantic/source lead: LargeGroupAudioKeyMapRva003D36E0ClearIntersection.cpp
// at donor968ca36c3265b295297e6aed45a6bd89ffe59c40. Native target extent
// 0x003ED411..0x003ED498 RET4 additionally limits traversal to the smaller
// of the two unsigned vector sizes, then tests signed word indexes.
// The existing retain/string walkers prove the same global tree and layout;
// the target method name remains unknown.
void BitRange::rva003ED411(const BitRange &other)
{
	unsigned int ownSize = m_end - m_begin;
	unsigned int otherSize = other.m_end - other.m_begin;
	int wordCount = _STL::min(ownSize, otherSize);
	TreeNode *record = (TreeNode *)g_00A02E50->_M_left;
	TreeNode *sentinel = (TreeNode *)g_00A02E50;
	while (record != sentinel)
	{
		unsigned int bit = record->m_14;
		int word = bit >> 5;
		unsigned int mask = 1 << (bit & 31);
		if (wordCount > word &&
			(other.m_begin[word] & mask) &&
			(m_begin[word] & mask))
		{
			--record->m_18;
			m_begin[word] &= ~mask;
		}
		record = (TreeNode *)
			_STL::_Rb_global<bool>::_M_increment(&record->m_base);
	}
}

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();
	char *text;
	int tag;
};

struct Rva003ED5A5Version
{
	unsigned char version;
	unsigned char currentVersion;
};

class Rva003ED5A5Xfer
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual bool slot08();
	#define RVA3ED5A5_SLOT(n) virtual void slot##n();
	RVA3ED5A5_SLOT(0C) RVA3ED5A5_SLOT(10) RVA3ED5A5_SLOT(14)
	RVA3ED5A5_SLOT(18) RVA3ED5A5_SLOT(1C) RVA3ED5A5_SLOT(20) RVA3ED5A5_SLOT(24)
	virtual void slot28(Rva003ED5A5Version *version);
	RVA3ED5A5_SLOT(2C) RVA3ED5A5_SLOT(30) RVA3ED5A5_SLOT(34) RVA3ED5A5_SLOT(38)
	RVA3ED5A5_SLOT(3C) RVA3ED5A5_SLOT(40) RVA3ED5A5_SLOT(44) RVA3ED5A5_SLOT(48)
	RVA3ED5A5_SLOT(4C) RVA3ED5A5_SLOT(50) RVA3ED5A5_SLOT(54) RVA3ED5A5_SLOT(58)
	RVA3ED5A5_SLOT(5C) RVA3ED5A5_SLOT(60) RVA3ED5A5_SLOT(64) RVA3ED5A5_SLOT(68)
	virtual void slot6C(AsciiString *value);
	#undef RVA3ED5A5_SLOT
};

// BFME1 donor968ca36c LargeGroupAudioKeyMapXfer.cpp provides the version,
// save-only check and key-string transfer. Native target3ED5A5..3ED62B
// RET4 dispatches the final string transfer at +0x6C rather than +0x68.
// Throw metadata at VA CFFD18 independently identifies XferException.
// Use its real constructor and a C++ throw, and the existing native string
// builder, rather than the donor's explicit formatter/throw/thunk machinery.
void BitRange::rva003ED5A5(Rva003ED5A5Xfer *xfer)
{
	Rva003ED5A5Version version;
	version.version = 1;
	version.currentVersion = 1;
	xfer->slot28(&version);
	if (!xfer->slot08())
		throw XferException(5, 0);
	AsciiString value = rva003ED4E5();
	xfer->slot6C(&value);
}
