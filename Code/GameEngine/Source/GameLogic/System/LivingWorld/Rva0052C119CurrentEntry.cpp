// cl: /O1 /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfme2_ascii
// stlport
// Native 0x0052C119..0x0052C161, RET0. Existing caller 0x003B8D06
// passes a campaign entry through this receiver and then reads its name.
// Native stride B8 and begin/end at C/10 establish the vector view.
// Original identities and unused fields remain unknown.
#include <vector>
#include "ascii_string.h"
class Rva00564DF2NameView
{
public:
    AsciiString rva00564DF2() const;
private:
    char unknown[0xB8];
};
class Rva0052BFE1
{
public:
    Rva00564DF2NameView *getCurrentEntry();
    bool hasEntryNamed(const AsciiString &key);
private:
    char unknown00[8];
    int index;
    _STL::vector<Rva00564DF2NameView> entries;
};

Rva00564DF2NameView *Rva0052BFE1::getCurrentEntry()
{
    int current = index;
    if (current >= 0 && (unsigned int)current < entries.size())
        return &entries[current];
    return &entries[entries.size() - 1];
}

// Raw begin/end view of the entries vector: the stride-search sibling
// (LivingWorldCampaignStrideSearch.cpp) reads the same members through an
// equivalent reinterpretation because _M_start/_M_finish are protected.
// Native 0x0052C72B..0x0052C7A2 (119B) and 0x0052C7A2..0x0052C823 (129B) are
// twin scans over the 0xB8 records: each entry's +0x04 AsciiString (the
// rowed Image::getName body at 0x00564DF2, pinned for this view) is compared
// with the key through the rowed AsciiString::compare at 0x000069D6, and the
// temporary is torn down through releaseBuffer at 0x00036410. The count is
// the entries.size() pointer difference (the rowed 0x0052C119 sibling shows
// the same inline idiv shape), recomputed every pass; the first body returns
// whether any entry matches, the second the matching entry or null.
struct Rva0052BFE1RawVec
{
    const char *m_start;
    const char *m_finish;
    const char *m_end;
};

bool Rva0052BFE1::hasEntryNamed(const AsciiString &key)
{
    const volatile Rva0052BFE1RawVec *vec = (const volatile Rva0052BFE1RawVec *)&entries;
    unsigned i = 0;
    if (i < entries.size())
    {
        int offset = 0;
        do
        {
            const Rva00564DF2NameView *rec = (const Rva00564DF2NameView *)(vec->m_start + offset);
            bool match = (rec->rva00564DF2().compare(key) == 0);
            if (match)
                return true;
            ++i;
            offset += sizeof(Rva00564DF2NameView);
        } while (i < entries.size());
    }
    return false;
}

// 0x00564DF2 (27B): the by-value getter of the record's +0x04 AsciiString,
// the body retail folds Image::getName and the other +4 name getters into.
// Out of line so the scans above keep their call.
__declspec(noinline) AsciiString Rva00564DF2NameView::rva00564DF2() const
{
    return *(const AsciiString *)(unknown + 4);
}
