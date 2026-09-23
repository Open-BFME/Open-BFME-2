// cl: /O1 /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// Donor STLport insertion family for LanguageFilter's map at +0xC.
// Target nodes hold pair<const UnicodeString, bool> at +0x10 and occupy 24 bytes.
// init stores through operator[]; its hint passes through the vendor insert chain.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
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
typedef _STL::map<UnicodeString, bool, UnicodeStringLessThan,
    _STL::allocator<LanguageFilterValue> > LanguageFilterMap;

template bool &LanguageFilterMap::operator[](const UnicodeString&);
