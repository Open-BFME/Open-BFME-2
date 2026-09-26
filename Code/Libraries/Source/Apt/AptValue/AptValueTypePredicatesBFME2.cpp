// cl: /O2 /MD
// PC predicates named by the corresponding checked-cast assertion strings.
// Signed seven-bit type occupies bits25..31; this is PC evidence, not PDB layout.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class BfmeAptValue006DCD20 {
    virtual void vtableSlot0();
    struct { unsigned int unknown : 25; int type : 7; } flags;
public:
    bool isUndefined() const;
    int isLookup() const;
    int isInteger() const;
    int isRegister() const;
    int isFloat() const;
    int isString() const;
    int isBoolean() const;
    int isNativeFunction() const;
};
// Corresponding checked casts at 6DCD50/90/D0 and 6DCE10/50 assert these
// exact predicate names. Type numbers are independently decoded from PC.
// Godfather final PDB corroborates names but is structurally incompatible:
// its AptValue is4B and enum ends36; PC stores flags+4 and permits types<47.
// In particular PC isString accepts1 or42; do not copy the other enum wholesale.

int BfmeAptValue006DCD20::isLookup() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",1459);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (flags.type == 8 && !isUndefined()) return 1;
    return 0;
}

int BfmeAptValue006DCD20::isInteger() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",1535);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (flags.type == 7 && !isUndefined()) return 1;
    return 0;
}

int BfmeAptValue006DCD20::isRegister() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",1560);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (flags.type == 4 && !isUndefined()) return 1;
    return 0;
}

int BfmeAptValue006DCD20::isFloat() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",1585);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (flags.type == 6 && !isUndefined()) return 1;
    return 0;
}

int BfmeAptValue006DCD20::isString() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",1484);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if ((flags.type == 1 || flags.type == 42) && !isUndefined()) return 1;
    return 0;
}

int BfmeAptValue006DCD20::isBoolean() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",1510);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (flags.type == 5 && !isUndefined()) return 1;
    return 0;
}

int BfmeAptValue006DCD20::isNativeFunction() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",1610);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (flags.type == 9 && !isUndefined()) return 1;
    return 0;
}
