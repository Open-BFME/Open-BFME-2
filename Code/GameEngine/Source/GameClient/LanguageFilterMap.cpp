// cl: /O1 /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// The target word map is at LanguageFilter+0xC. Its 24-byte nodes contain
// the UnicodeString/bool pair at +0x10; filterLine calls _M_find at 0x3881F8.
// String copies and cleanup use the independently matched StringBase helpers.
#include <map>

template<class T>
class StringBase
{
    void *m_data;
    friend class UnicodeString;
    StringBase(const StringBase &other);
    __forceinline ~StringBase() { releaseBuffer(); }
    void releaseBuffer();
public:
    int compareNoCase(const StringBase &other) const throw();
};

class UnicodeString : private StringBase<unsigned short>
{
    friend struct UnicodeStringLessThan;
public:
    __forceinline UnicodeString(const UnicodeString &other)
        : StringBase<unsigned short>(static_cast<const StringBase<unsigned short>&>(other)) {}
    __forceinline ~UnicodeString() {}
};

struct UnicodeStringLessThan
{
    bool operator()(UnicodeString a, UnicodeString b) const
    {
        return static_cast<const StringBase<unsigned short>&>(a).compareNoCase(
            static_cast<const StringBase<unsigned short>&>(b)) < 0;
    }
};

typedef _STL::pair<const UnicodeString, bool> LanguageFilterValue;
typedef _STL::_Rb_tree<UnicodeString, LanguageFilterValue,
    _STL::_Select1st<LanguageFilterValue>, UnicodeStringLessThan,
    _STL::allocator<LanguageFilterValue> > LanguageFilterTree;

template _STL::_Rb_tree_node<LanguageFilterValue>*
LanguageFilterTree::_M_find<UnicodeString>(const UnicodeString&) const;

template _STL::_Rb_tree_node<LanguageFilterValue>*
LanguageFilterTree::_M_lower_bound(const UnicodeString&) const;

template void LanguageFilterTree::_M_erase(_STL::_Rb_tree_node<LanguageFilterValue>*);
template void LanguageFilterTree::clear();
