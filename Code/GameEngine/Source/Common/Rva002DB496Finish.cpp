// ?rva002DB496@Rva002DB496@@QAEPAXVAsciiString@@@Z
// cl: /EHs
//
// ?rva002DB496@Rva002DB496@@QAEPAXVAsciiString@@@Z @0x002DB496 68B. Evidence:
// StringBase<char>::compare at rowed 0x000069D6 and releaseBuffer at rowed
// 0x00036410; 4 callers; list head at this+0x0C, node string at +0x04, next at
// +0x10. The banked 72B probe carried an extra `and dword ptr [ebp-4],0`
// unwind-state init at +0xB. Declaring the leaf compareNoCase-style leaf
// `compare(...) const throw()` removes that state store while releaseBuffer
// stays a plain (potentially throwing) declaration, keeping the EH frame
// retail has. Marking releaseBuffer throw() too collapses the whole body to
// 45B (frame gone); marking neither leaves the 72B state init.
// class-gate: allow AsciiString TU-local private-derived view is required because the frame shape depends on the canary compare being declared throw() and the AsciiString dtor inline-forwarding a plain releaseBuffer; the shared header's non-throw declarations reproduce neither.

template <typename T>
class StringBase
{
    friend class AsciiString;
    friend class UnicodeString;
public:
    int compare(const StringBase<T> &other) const throw();
private:
    void releaseBuffer();
    struct Header
    {
        int ref_count;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };
    Header *m_data;
};

class AsciiString : public StringBase<char>
{
public:
    AsciiString() {}
    AsciiString(const AsciiString &other);
    __forceinline ~AsciiString() { releaseBuffer(); }
};

struct ListNode
{
    char m_pad00[4];
    AsciiString m_str04;
    char m_pad08[8];
    ListNode *m_next10;
};

class Rva002DB496
{
public:
    void *rva002DB496(AsciiString key);
private:
    char m_pad00[0xC];
    ListNode *m_head0C;
};

void *Rva002DB496::rva002DB496(AsciiString key)
{
    for (ListNode *n = m_head0C; n != 0; n = n->m_next10) {
        if (n->m_str04.compare(key) == 0)
            return n;
    }
    return 0;
}
