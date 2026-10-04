// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?Rva003ED498Count@@YAXPBX@Z @ 0x003ED498 77B
// Free bit-count walker over global RB-tree at 0x00A02E50 via rowed _M_increment 0x00024250.
// For each node tests bit m_14 in caller vector bitset and incs m_18; callers 0x003ED658/0x003ED989 pass this.
// Neighbour StringRecordCopyBFME2.cpp shares /O1 /EHsc STLport flags and vector idioms.

#include "ascii_string.h"

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

struct BitRange
{
	unsigned const *m_begin;
	unsigned const *m_end;
	AsciiString rva003ED4E5();
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
