// cl: /O1 /G7 /MD
// Native5414C2..5414E535B is the lookup wrapper used by the LookAt track.
// The66-byte provider5413B0 compares key0 and ignores its one-byte comparator.
// Its ABI declaration uses the existing provider spelling; precise source
// comparator/wrapper identity is unknown, so retain an address-derived name.
// Value initialization follows independently verified sibling540301.
struct BfmePod28 { int key; char frame[24]; };
// Native sibling54150A uses the same comparator/tag ABI and a20-byte record;
// its separate66-byte provider5413F2 independently establishes stride and key0.
struct BfmePod20 { int key; char frame[16]; };
// STLport's __lower_bound halving loop, defined here: its copies are
// retail's 0x005413B0 (Pod28) and 0x005413F2 (Pod20), and with the body
// visible the locator below reloads its address-taken key at both tail
// compares as retail does (a declaration alone lets cl hoist the load).
namespace _STL {
template<class T> struct less
{
    bool operator()(const T &a,const T &b) const { return a.key < b.key; }
};
template<class F,class T,class C,class D>
F __lower_bound(F first,F last,const T &val,C comp,D *)
{
    D len = last - first;
    D half;
    F middle;
    while (len > 0) {
        half = len >> 1;
        middle = first;
        middle += half;
        if (comp(*middle, val)) {
            first = middle;
            ++first;
            len = len - half - 1;
        }
        else
            len = half;
    }
    return first;
}
}
BfmePod28 *rva005414C2(BfmePod28 *first,BfmePod28 *last,const BfmePod28 &key)
{
    return _STL::__lower_bound(first,last,key,_STL::less<BfmePod28>(),(int *)0);
}
BfmePod20 *rva0054150A(BfmePod20 *first,BfmePod20 *last,const BfmePod20 &key)
{
    return _STL::__lower_bound(first,last,key,_STL::less<BfmePod20>(),(int *)0);
}


// ?rva00541579@Rva00541579@@QAE_NH@Z retail 0x00541579 (200 bytes): the
// hinted sorted-key locator over 28-byte records keyed by their first word,
// template twin of the matched 0x00541641 (Pod20) and 0x0054034A (Pod40).
// The cached index (+0x1C) answers directly when the key falls in its slot;
// otherwise it is re-found with rva005414C2 above and stepped back past the
// end or between keys. The key vector (+0x10) is a member with inline
// size()/empty(), which keeps retail's per-use begin loads. The class keeps
// its pinned address name.
struct KeyVector28
{
    unsigned int size() const { return m_end - m_begin; }
    bool empty() const { return m_begin == m_end; }
    BfmePod28 *m_begin, *m_end, *m_capacity;
};
class Rva00541579
{
public:
    bool rva00541579(int key);
private:
    char m_pad00[0x10];
    KeyVector28 m_keys;
    int m_hint1C;
};
bool Rva00541579::rva00541579(int key)
{
    int cachedIndex = m_hint1C;
    if (cachedIndex >= 0 && (unsigned)cachedIndex < m_keys.size()) {
        BfmePod28 *keyBegin = m_keys.m_begin;
        int cachedKey = keyBegin[cachedIndex].key;
        if (key >= cachedKey && ((unsigned)(cachedIndex + 1) >= (unsigned)(m_keys.m_end - keyBegin) || key < keyBegin[cachedIndex + 1].key))
            return cachedKey == key;
    }
    if (m_keys.empty())
    {
        m_hint1C = -1;
        return false;
    }
    int &hint = m_hint1C;
    BfmePod28 *keyBegin = m_keys.m_begin;
    hint = rva005414C2(keyBegin, m_keys.m_end, *reinterpret_cast<const BfmePod28 *>(&key)) - keyBegin;
    if ((unsigned)hint >= (unsigned)(m_keys.m_end - keyBegin) || (hint > 0 && keyBegin[hint].key != key))
        --hint;
    return keyBegin[hint].key == key;
}

// ?rva00541641@Rva005418CB@@QAE_NH@Z retail 0x00541641 (200 bytes): the same
// locator over the 20-byte keys, through rva0054150A above.
struct KeyVector20
{
    unsigned int size() const { return m_end - m_begin; }
    bool empty() const { return m_begin == m_end; }
    BfmePod20 *m_begin, *m_end, *m_capacity;
};
class Rva005418CB
{
public:
    bool rva00541641(int key);
private:
    char m_pad00[0x10];
    KeyVector20 m_keys;
    int m_hint1C;
};
bool Rva005418CB::rva00541641(int key)
{
    int cachedIndex = m_hint1C;
    if (cachedIndex >= 0 && (unsigned)cachedIndex < m_keys.size()) {
        BfmePod20 *keyBegin = m_keys.m_begin;
        int cachedKey = keyBegin[cachedIndex].key;
        if (key >= cachedKey && ((unsigned)(cachedIndex + 1) >= (unsigned)(m_keys.m_end - keyBegin) || key < keyBegin[cachedIndex + 1].key))
            return cachedKey == key;
    }
    if (m_keys.empty())
    {
        m_hint1C = -1;
        return false;
    }
    int &hint = m_hint1C;
    BfmePod20 *keyBegin = m_keys.m_begin;
    hint = rva0054150A(keyBegin, m_keys.m_end, *reinterpret_cast<const BfmePod20 *>(&key)) - keyBegin;
    if ((unsigned)hint >= (unsigned)(m_keys.m_end - keyBegin) || (hint > 0 && keyBegin[hint].key != key))
        --hint;
    return keyBegin[hint].key == key;
}
