// cl: /O1 /arch:SSE
//
// getIdNoCase and isEqualNoCase, split out of PooledString.cpp for one flag.
// Both select the case-folded alias with a conditional move, and cl 13.10
// emits one only under /arch - not at /O1, /O2, /Ox, /G6, /G7 or /GB, and not
// for any rewriting of the ternary. The rest of PooledString.cpp matches at
// plain /O1 and stays there, so these two live here.
//
// isEqualNoCase is this body inlined twice and compared, which is why it was
// blocked behind the same thing and lands with it.

struct PooledStringEntry
{
    void *m_unknown0;
    PooledStringEntry *m_noCase;
    char m_text[1];
};

class PooledString
{
public:
    unsigned int getIdNoCase() const;
    bool isEqualNoCase(const PooledString &that) const;

private:
    PooledStringEntry *m_entry;
};

unsigned int PooledString::getIdNoCase() const
{
    return (unsigned int)(m_entry->m_noCase ? m_entry->m_noCase : m_entry);
}

bool PooledString::isEqualNoCase(const PooledString &that) const
{
    return getIdNoCase() == that.getIdNoCase();
}
