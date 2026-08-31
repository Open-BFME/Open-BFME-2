// cl: /O2

// The AsciiString and UnicodeString members retail emits from a translation
// unit built for speed, the same split string_base_inline.cpp records for
// StringBase itself. ascii_string.cpp and unicode_string.cpp are /O1: recompiled
// at /O2 every one of their forwarding wrappers stops matching, while these four
// only match at /O2 - the tail jump into the sibling overload with the argument
// slot rewritten in place is the giveaway, since /O1 emits a push and a call.

typedef unsigned short wchar_t;

class AsciiString;
class UnicodeString;

// Both format members forward into StringBase's formatter, not a member of
// their own: the retail call targets are the exported
// ?format_va@?$StringBase@[DG]@@QAEXPB[DG]PAD@Z pair.
template <typename T>
class StringBase
{
public:
    void format_va(const T *format, char *args);
};

// Only the buffer pointer matters here; the header block is read for the text.
struct StringHeader
{
    int ref_count;
    unsigned short length;
    unsigned short capacity;
    char data[1];
};

struct WideStringHeader
{
    int ref_count;
    unsigned short length;
    unsigned short capacity;
    wchar_t data[1];
};

class AsciiString
{
public:
    // A member cdecl varargs function: `this` is the first stack argument, so
    // the argument pointer comes off the format parameter and not off a
    // register-passed this.
    void __cdecl format(const char *format, ...);
    void translate(const wchar_t *text);
    void translate(const UnicodeString &that);

private:
    StringHeader *m_data;
};

class UnicodeString
{
public:
    void __cdecl format(const wchar_t *format, ...);
    void translate(const char *text);
    void translate(const AsciiString &that);

private:
    WideStringHeader *m_data;
};

void __cdecl AsciiString::format(const char *format, ...)
{
    ((StringBase<char> *)this)->format_va(format, (char *)(&format + 1));
}

void AsciiString::translate(const UnicodeString &that)
{
    const WideStringHeader *header = *(const WideStringHeader *const *)&that;

    translate(header ? &header->data[0] : L"");
}

void __cdecl UnicodeString::format(const wchar_t *format, ...)
{
    ((StringBase<wchar_t> *)this)->format_va(format, (char *)(&format + 1));
}

void UnicodeString::translate(const AsciiString &that)
{
    const StringHeader *header = *(const StringHeader *const *)&that;

    translate(header ? &header->data[0] : "");
}
