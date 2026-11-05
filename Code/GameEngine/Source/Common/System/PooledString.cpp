// flags: region default (reverse/retail_inventory/flag_regions.csv)

#define _DLL
#include <string.h>

#include "../debug.h"

// getIdNoCase (0x0060B820) and isEqualNoCase (0x0060B82B) are NOT here: both
// select the alias with cmovne, and cl 13.10 emits a conditional move only
// under /arch, which this unit cannot take without breaking its other bodies.
// They live in pooled_string_nocase.cpp at /O1 /arch:SSE and both match.

class AsciiString;

// The same one-byte trait object and shared workers string_base.cpp uses; the
// pooled comparisons hand them the pooled text and its strlen.
struct CharCompare
{
    char m_unused;
};

int compareRange(const char *a, int alen, const char *b, int blen, CharCompare tag);
int compareRangeNoCase(const char *a, int alen, const char *b, int blen, CharCompare tag);

class PooledString
{
public:
    // A pooled entry is shared by every string with the same text. +0 chains
    // the hash bucket (setString walks it), the alias at +4 points at the
    // case-folded twin when there is one, which is what makes the two id
    // accessors differ, and the text itself starts at +8.
    struct StringEntry
    {
        StringEntry *m_next;
        StringEntry *m_noCase;
        char m_text[1];
    };

    PooledString(const AsciiString &that);

    PooledString();
    PooledString(const char *text);
    PooledString(const PooledString &that);

    PooledString &operator=(const char *text);
    PooledString &operator=(const PooledString &that);
    PooledString &operator=(const AsciiString &that);

    void clear();

    int compare(const char *str, int len) const;
    int compare(const char *str) const;
    int compare(const PooledString &that) const;
    int compare(const AsciiString &that) const;
    int compareNoCase(const char *str, int len) const;
    int compareNoCase(const char *str) const;
    int compareNoCase(const PooledString &that) const;
    int compareNoCase(const AsciiString &that) const;

    unsigned int getId() const;
    bool isEqual(const PooledString &that) const;

    int getLength() const;
    bool isEmpty() const;
    bool isNotEmpty() const;

    friend Debug &operator<<(Debug &debug, const PooledString &str);

    static const PooledString TheEmptyString;

private:
    template<class T> friend struct DataRowPrivateProbe;

    void setString(const char *text);

    // The entry every empty PooledString points at. isEmpty is a pointer
    // comparison against it rather than a length test. Retail exports it as
    // ?m_null@PooledString@@0UStringEntry@1@A (VA 0xe1768c, zero-filled).
    static StringEntry m_null;

    StringEntry *m_entry;
};

PooledString::StringEntry PooledString::m_null;

// Retail exports ?TheEmptyString@PooledString@@2V1@B (VA 0xddc018, .data holding
// &m_null).
const PooledString PooledString::TheEmptyString;

PooledString::PooledString()
{
    m_entry = &m_null;
}

PooledString::PooledString(const char *text)
{
    m_entry = 0;
    setString(text);
}

// Retail exports the plain copy pair, the id accessor and the identity test,
// and /OPT:ICF folded each onto an identical body elsewhere: the copy ctor and
// copy assignment onto 0x0027EA56, getId onto 0x00421795 and isEqual onto
// 0x001F4325. A pooled string is one entry pointer, so all four only move or
// compare that pointer.
PooledString::PooledString(const PooledString &that)
{
    m_entry = that.m_entry;
}

PooledString &PooledString::operator=(const PooledString &that)
{
    m_entry = that.m_entry;

    return *this;
}

unsigned int PooledString::getId() const
{
    return (unsigned int)m_entry;
}

bool PooledString::isEqual(const PooledString &that) const
{
    return m_entry == that.m_entry;
}

// AsciiString is only ever read through its buffer pointer here, so this unit
// models the header block rather than pulling the class in.
struct AsciiStringHeader
{
    int ref_count;
    unsigned short length;
    unsigned short capacity;
    char data[1];
};

PooledString::PooledString(const AsciiString &that)
{
    const AsciiStringHeader *const *slot = (const AsciiStringHeader *const *)&that;

    m_entry = 0;
    setString(*slot ? &(*slot)->data[0] : "");
}

PooledString &PooledString::operator=(const AsciiString &that)
{
    const AsciiStringHeader *header = *(const AsciiStringHeader *const *)&that;

    setString(header ? &header->data[0] : "");

    return *this;
}

int PooledString::compare(const char *str, int len) const
{
    const CharCompare tag = CharCompare();
    const int mylen = (int)strlen(m_entry->m_text);

    return compareRange(m_entry->m_text, mylen, str, len, tag);
}

int PooledString::compareNoCase(const char *str, int len) const
{
    const CharCompare tag = CharCompare();
    const int mylen = (int)strlen(m_entry->m_text);

    return compareRangeNoCase(m_entry->m_text, mylen, str, len, tag);
}

int PooledString::compare(const char *str) const
{
    return compare(str, str ? (int)strlen(str) : 0);
}

int PooledString::compareNoCase(const char *str) const
{
    return compareNoCase(str, str ? (int)strlen(str) : 0);
}

// The entry has to be named and the text NOT: with a local for the text as well
// MSVC schedules the entry load after the register saves and writes
// `mov esi, [eax]; add esi, 8`, where retail dereferences into eax and leas.
// Two names, one for each level of indirection, is one name too many.
int PooledString::compare(const PooledString &that) const
{
    const StringEntry *entry = that.m_entry;

    return compare(entry->m_text, (int)strlen(entry->m_text));
}

int PooledString::compareNoCase(const PooledString &that) const
{
    const StringEntry *entry = that.m_entry;

    return compareNoCase(entry->m_text, (int)strlen(entry->m_text));
}

int PooledString::compare(const AsciiString &that) const
{
    const AsciiStringHeader *header = *(const AsciiStringHeader *const *)&that;

    return compare(header ? &header->data[0] : "", header ? header->length : 0);
}

int PooledString::compareNoCase(const AsciiString &that) const
{
    const AsciiStringHeader *header = *(const AsciiStringHeader *const *)&that;

    return compareNoCase(header ? &header->data[0] : "", header ? header->length : 0);
}

PooledString &PooledString::operator=(const char *text)
{
    setString(text);

    return *this;
}

Debug &operator<<(Debug &debug, const PooledString &str)
{
    debug << str.m_entry->m_text;

    return debug;
}
