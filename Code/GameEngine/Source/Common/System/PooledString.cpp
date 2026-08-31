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

class PooledString
{
public:
    PooledString();
    PooledString(const char *text);

    PooledString &operator=(const char *text);

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
