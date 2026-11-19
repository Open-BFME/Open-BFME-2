// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHs /MD /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DNDEBUG /D_CRTIMP=
// stlport
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// Reference: BFME1 GameEngine/Source/GameClient/LanguageFilter.cpp.
// Target ctor/dtor layout is supported by init at RVA 0x38873F and filterLine
// at RVA 0x388102: each UnicodeString/bool map object is 12 bytes at this+0xC
// and this+0x18; its tree nodes are 24 bytes.
#include <map>

#include "../../Include/Common/ScalarTypes.h"
#include "../../Include/Common/ScalarTypes/WideChar.h"

template<class T> class StringBase;
class UnicodeString;
struct UnicodeStringLessThan;

#include "unicode_string.h"
// bfme link decl-only begin
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<UnicodeString const,bool> > * allocator<_STL::_Rb_tree_node<_STL::pair<UnicodeString const,bool> > >::allocate(unsigned int,void const *) const; }
// bfme link decl-only end


struct UnicodeStringLessThan
{
    Bool operator()(UnicodeString a, UnicodeString b) const
    {
        return static_cast<const StringBase<WideChar>&>(a).compareNoCase(
            static_cast<const StringBase<WideChar>&>(b)) < 0;
    }
};
typedef _STL::pair<const UnicodeString, Bool> LanguageFilterValue;
typedef _STL::map<UnicodeString, Bool, UnicodeStringLessThan,
    _STL::allocator<LanguageFilterValue> > LanguageFilterMap;

#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class LanguageFilter : public SubsystemInterface
{
public:
    LanguageFilter();
    virtual ~LanguageFilter();
    virtual void init();
protected:
    LanguageFilterMap m_wordList;
    LanguageFilterMap m_subWordList;
};

LanguageFilter::LanguageFilter()
{
    // Target sequence initializes the inherited base, then both donor maps.
}

LanguageFilter::~LanguageFilter()
{
    m_wordList.clear();
}

LanguageFilter *createLanguageFilter()
{
    return new LanguageFilter;
}
