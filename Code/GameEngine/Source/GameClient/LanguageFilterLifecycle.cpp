// cl: /O1 /Ob2 /EHs /MD /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DNDEBUG /D_CRTIMP=
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

typedef bool Bool;
typedef unsigned short WideChar;

template<class T> class StringBase;
class UnicodeString;
struct UnicodeStringLessThan;

template<class T>
class StringBase
{
    void *m_data;
    StringBase(const StringBase& other);
    StringBase(const T *text);
    __forceinline ~StringBase() { releaseBuffer(); }
    void releaseBuffer();
    friend class UnicodeString;
public:
    int compareNoCase(const StringBase& other) const throw();
};

class UnicodeString : private StringBase<WideChar>
{
    friend struct UnicodeStringLessThan;
public:
    __forceinline UnicodeString(const WideChar *text) : StringBase<WideChar>(text) {}
    __forceinline UnicodeString(const UnicodeString &other)
        : StringBase<WideChar>(static_cast<const StringBase<WideChar>&>(other)) {}
    __forceinline ~UnicodeString() {}
};

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

class SubsystemInterface
{
public:
    SubsystemInterface();
    virtual ~SubsystemInterface();
    virtual void init();
protected:
    void *m_name[2];
};

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

