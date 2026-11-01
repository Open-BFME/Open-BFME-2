// Target facts: FieldParse has no virtual functions or bases. Its table at RVA 0x009BECD8 has 0x10-byte entries; findFieldParse (RVA 0x0002BC27) compares token at +0, returns parse at +4, and reads userData at +8 and offset at +0x0C. Zero Hour Common/INI.h proves these names, the callback signature and set().
// Target facts: MultiIniFieldParse has no virtual functions or bases. Its constructor (RVA 0x0002BAA0) zeroes 16 pointers at +0, 16 unsigned offsets at +0x40 and the count at +0x80; INI::initFromINI (RVA 0x0002DE78) reserves 0x84 bytes and calls it out of line. add (RVA 0x0002BC6E) checks count < 16; getNthFieldParse (RVA 0x0002BABA) and getNthExtraOffset (RVA 0x0002BAC4) read the arrays. Zero Hour Common/INI.h proves the field names and getCount().
// Target facts: INIException has no virtual functions or bases. Its constructor (RVA 0x0002F681) stores the message pointer at +0 and an int at +4; its destructor (RVA 0x0002BD30) deletes the pointer. ThrowInfo at RVA 0x008FE2FC names that destructor and CatchableType at RVA 0x008FE2D8 proves sizeof 8, no base adjustment, and copy constructor RVA 0x000588C5, which calls assignment RVA 0x0002F6D6. Zero Hour Common/INIException.h proves mFailureMessage; the second member's original name is unproven.
#pragma once

class INI;

typedef void (*INIFieldParseProc)(INI *, void *, void *, const void *);

struct FieldParse
{
    const char *token;
    INIFieldParseProc parse;
    const void *userData;
    int offset;

    void set(const char *t, INIFieldParseProc p, const void *u, int o)
    {
        token = t;
        parse = p;
        userData = u;
        offset = o;
    }
};

class MultiIniFieldParse
{
public:
    enum { MAX_MULTI_FIELDS = 16 };

    MultiIniFieldParse();
    void add(const FieldParse *fields, unsigned int extraOffset = 0);
    int getCount() const { return m_count; }
    const FieldParse *getNthFieldParse(int i) const;
    unsigned int getNthExtraOffset(int i) const;

    const FieldParse *m_fieldParse[MAX_MULTI_FIELDS];
    unsigned int m_extraOffset[MAX_MULTI_FIELDS];
    int m_count;
};

class INIException
{
public:
    INIException(int code, const char *format, ...);
    INIException(const INIException &that);
    ~INIException();
    INIException &operator=(const INIException &that);

    char *mFailureMessage;
    int field04;
};
