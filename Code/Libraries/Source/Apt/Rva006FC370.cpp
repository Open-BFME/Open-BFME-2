// cl: /O2 /MD /EHsc
// Target evidence: the 762-byte Ghidra body calls the matched AptValue
// predicates at 0x006DC170, 0x006DC210, 0x006DC0D0, 0x006DC010 and 0x006DBFA0;
// its string path constructs an EAStringC, calls the matched toString body at
// 0x006DD6C0, then uses the matched EAStringC accessors and the target imports
// strtol (0x00629ABA) and isdigit (0x00629982). Its caller at 0x006FF5D0 passes
// the top Apt stack value. The address-derived pin records that call path.
// Structural inference: the body is a numeric-string predicate; no named
// source identity is claimed. The grammar and exceptional type path below
// follow the retail branch structure, including its edge cases.

class EAStringC
{
    unsigned int m_data;

public:
    EAStringC();
    ~EAStringC();
    unsigned int rva006D3750() const;
    int GetAt(int index) const;
    const char *rva00620090() const;
};

class AptValue
{
public:
    bool isInteger() const;
    bool isFloat() const;
    bool isString() const;
    bool isUndefined() const;
    bool isNone() const;
    void toString(EAStringC &out) const;
};

int Rva006CD220Get();
extern "C" long __cdecl strtol(const char *, char **, int);

// Retail calls the six-byte target import thunk at 0x00629982. Its existing
// ledger pin uses the generated no-argument wrapper name, so call that pinned
// symbol through the typed ABI the target call site establishes.
void ji_00629982();
typedef int (__cdecl *Rva00629982Digit)(int);
#define digitAt00629982(value) \
    (reinterpret_cast<Rva00629982Digit>(&ji_00629982)(value))

bool rva006fc370(AptValue *value)
{
    if (value->isInteger())
        return false;
    if (value->isFloat())
        return false;

    if (value->isString()) {
        EAStringC string;
        value->toString(string);

        if (string.rva006D3750() == 0)
            return true;

        if (string.GetAt(0) == '0' &&
            static_cast<int>(string.rva006D3750()) > 2 &&
            string.GetAt(1) == 'x') {
            char *end;
            strtol(string.rva00620090(), &end, 16);
            if (*end == '\0')
                return false;
        }

        bool decimalPointSeen = false;
        char last = static_cast<char>(
            string.GetAt(static_cast<int>(string.rva006D3750()) - 1));
        if (last != '-' && last != '+' && last != 'e' && last != '.' &&
            !digitAt00629982(last))
            return true;

        if (string.GetAt(0) != '.' && string.GetAt(0) != '-' &&
            string.GetAt(0) != '+' &&
            !digitAt00629982(string.GetAt(0)))
            return true;

        for (int index = 1;
             index < static_cast<int>(string.rva006D3750()); ++index) {
            if (string.GetAt(index) == '.') {
                if (!decimalPointSeen) {
                    decimalPointSeen = true;
                    continue;
                }
            }

            if (string.GetAt(index) == 'e' && index != 1) {
                if (index == 2) {
                    if (string.GetAt(0) == '+')
                        goto invalid_string;
                    if (string.GetAt(0) == '-')
                        goto invalid_string;
                }

                int next = index + 1;
                if (next < static_cast<int>(string.rva006D3750())) {
                    char exponent = static_cast<char>(string.GetAt(next));
                    if (exponent == '-' || exponent == '+') {
                        index = next;
                    } else {
                        if (!digitAt00629982(exponent))
                            goto invalid_string;
                        index = next;
                    }
                }
                continue;
            }

            if (!digitAt00629982(string.GetAt(index))) {
                goto invalid_string;
            }
        }

        return false;

    invalid_string:
        return true;
    } else if (value->isUndefined() || value->isNone()) {
        int version = Rva006CD220Get();
        if (version == 7)
            return true;
        return false;
    }

    return true;
}
