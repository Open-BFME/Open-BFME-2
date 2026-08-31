// cl: /O1

#define _DLL
#include <string.h>

class Debug
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual Debug &operator<<(const char *value);
    virtual Debug &operator<<(int value);
    virtual Debug &operator<<(unsigned int value);
    virtual Debug &operator<<(unsigned char value);
    virtual Debug &operator<<(short value);
    virtual Debug &operator<<(unsigned short value);
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual Debug &operator<<(float value);
};

// getIdNoCase (0x0060B820) and isEqualNoCase (0x0060B82B) are NOT here: both
// select the alias with cmovne and MSVC 7.1 will only emit the shorter
// test/je/mov for this shape at /O1, while /O2 - which does reach for cmov -
// breaks every other body in this unit. Banked at reverse/attempts/.

// A pooled entry is shared by every string with the same text. The alias at +4
// points at the case-folded twin when there is one, which is what makes the two
// id accessors differ, and the text itself starts at +8.
struct PooledStringEntry
{
    void *m_unknown0;
    PooledStringEntry *m_noCase;
    char m_text[1];
};

// The entry every default-constructed PooledString points at. isEmpty is a
// pointer comparison against it rather than a length test.
extern PooledStringEntry ThePooledStringEmptyEntry;

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
    PooledString(const AsciiString &that);

    PooledString();
    PooledString(const char *text);

    PooledString &operator=(const char *text);
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

    int getLength() const;
    bool isEmpty() const;
    bool isNotEmpty() const;

    friend Debug &operator<<(Debug &debug, const PooledString &str);

private:
    void setString(const char *text);

    PooledStringEntry *m_entry;
};

PooledString::PooledString()
{
    m_entry = &ThePooledStringEmptyEntry;
}

PooledString::PooledString(const char *text)
{
    m_entry = 0;
    setString(text);
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

void PooledString::clear()
{
    m_entry = &ThePooledStringEmptyEntry;
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
    const PooledStringEntry *entry = that.m_entry;

    return compare(entry->m_text, (int)strlen(entry->m_text));
}

int PooledString::compareNoCase(const PooledString &that) const
{
    const PooledStringEntry *entry = that.m_entry;

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

int PooledString::getLength() const
{
    return (int)strlen(m_entry->m_text);
}

bool PooledString::isEmpty() const
{
    return m_entry == &ThePooledStringEmptyEntry;
}

bool PooledString::isNotEmpty() const
{
    return m_entry != &ThePooledStringEmptyEntry;
}

Debug &operator<<(Debug &debug, const PooledString &str)
{
    debug << str.m_entry->m_text;

    return debug;
}
