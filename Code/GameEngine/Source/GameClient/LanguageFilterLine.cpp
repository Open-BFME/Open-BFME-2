// cl: /O1 /Ob2 /G7 /arch:SSE /Oy- /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DNDEBUG
// stlport
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// BFME1 LanguageFilter::filterLine donor, adapted to BFME2 target StringBase ABI.
// Target constructs its delimiter temporary on each loop condition and passes
// its character pointer to StringBase::nextToken; it also calls StringBase::set.
#include <map>
#include <wchar.h>

typedef int Int;
typedef bool Bool;
typedef unsigned short WideChar;
#define NEW new
#define DEBUG_CRASH(x) ((void)0)
#define DEBUG_LOG(x) ((void)0)

template<class T> class StringBase;
class UnicodeString;

template<class T>
class StringBase
{
    struct Header
    {
        int refCount;
        unsigned short length;
        unsigned short capacity;
        T text[1];
    };
    Header *m_data;
    StringBase(const StringBase &other);
    StringBase(const T *text);
    __forceinline ~StringBase() { releaseBuffer(); }
    void releaseBuffer();
    friend class UnicodeString;
public:
    void set(const T *text);
    Bool nextToken(StringBase<T> *token, const T *separators);
    int compareNoCase(const StringBase& other) const throw();
    int getLength() const { return m_data ? m_data->length : 0; }
private:
};

class UnicodeString : private StringBase<WideChar>
{
    friend class LanguageFilter;
    friend struct UnicodeStringLessThan;
public:
    __forceinline UnicodeString(const WideChar *text) : StringBase<WideChar>(text) {}
    __forceinline UnicodeString(const UnicodeString &other)
        : StringBase<WideChar>(static_cast<const StringBase<WideChar>&>(other)) {}
    __forceinline ~UnicodeString() {}
    int getLength() const { return static_cast<const StringBase<WideChar>&>(*this).getLength(); }
    const WideChar *str() const {
        static const WideChar TheNullChr = 0;
        return m_data ? m_data->text : &TheNullChr;
    }
};

struct UnicodeStringLessThan
{
    Bool operator()(UnicodeString a, UnicodeString b) const
    {
        return static_cast<const StringBase<WideChar>&>(a).compareNoCase(
            static_cast<const StringBase<WideChar>&>(b)) < 0;
    }
};
typedef _STL::pair<const UnicodeString, bool> LanguageFilterValue;
typedef _STL::map<UnicodeString, bool, UnicodeStringLessThan,
    _STL::allocator<LanguageFilterValue> > LanguageFilterMap;
typedef LanguageFilterMap::iterator LangMapIter;

class LanguageFilter
{
public:
    virtual void init();
    void filterLine(UnicodeString &line);
protected:
    void unHaxor(UnicodeString &word);
    void *opaquePrefix[2];
    LanguageFilterMap m_wordList;
};

void LanguageFilter::filterLine(UnicodeString &line)
{
    // Keep a mutable copy for replacing matches while tokenizing the original.
    WideChar *buf = NEW WideChar[line.getLength() + 1];
    wcscpy(buf, line.str());

    UnicodeString newLine(line);
    UnicodeString token(L"");

    while (static_cast<StringBase<WideChar>&>(newLine).nextToken(
        static_cast<StringBase<WideChar>*>(&token),
        UnicodeString(L" ;,.!?:=\\/><`~()&^%#\n\t").str())) {
        WideChar *pos = wcsstr(buf, token.str());
        if (pos == NULL) {
            DEBUG_CRASH(("Couldn't find the token in its own string."));
            continue;
        }

        Int len = token.getLength(); // Keep the original word length before unHaxor changes the token.
        unHaxor(token);
        LangMapIter iter = m_wordList.find(token);
        if (iter != m_wordList.end()) {
            DEBUG_LOG(("Found word %ls in bad word list. Token was %ls\n",
                (*iter).first.str(), token.str()));
            for (Int i = 0; i < len; ++i) {
                *pos = L'*';
                ++pos;
            }
        }
    }

    static_cast<StringBase<WideChar>&>(line).set(buf);
    delete[] buf;
}
