// cl: /O1 /Ob2 /EHsc /MD
// ?rva004182F8@Rva004182F8@@QAEPAUOutIter004182F8@@PAU2@PBVRva004181F5@@@Z
// @0x004182F8 124B: hashed unique insert. Hashes the key through the rowed
// bucketIndex 0x00223149, walks the bucket chain comparing keys with the
// pinned StringBase compare 0x000069D6, and on a miss links a node from the
// thiscall allocator 0x004182D3 at the bucket head and bumps the count at
// +0x10. Returns {node, table, inserted} through the hidden out pointer.
// Target evidence: ret 8 thiscall with hidden return, bucket array at +4,
// count at +0x10, mov ecx,esi before the allocator call. Structural
// inference: the shape is STLport hashtable insert_unique_noresize; the class
// names stay placeholders because no target evidence names the table.
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
class Rva004181F5 {
public:
    Rva004181F5(const Rva004181F5 &other);
private:
    char m_pad[0x1c];
};
class Rva000427195 {
public:
    int bucketIndex(const AsciiString *key);
};
struct Wrapper004182D3 {
    Wrapper004182D3 *m_next;
    Rva004181F5 m_value;
};
struct OutIter004182F8 {
    void *m_node;
    void *m_table;
    unsigned char m_inserted;
};
class Rva004182F8 {
public:
    void *rva004182D3(const Rva004181F5 *src);
    OutIter004182F8 *rva004182F8(OutIter004182F8 *out, const Rva004181F5 *key);
private:
    Rva000427195 m_base;
    Wrapper004182D3 **m_buckets;
    char m_pad08[8];
    int m_size;
};
OutIter004182F8 *Rva004182F8::rva004182F8(OutIter004182F8 *out, const Rva004181F5 *key)
{
    int idx = m_base.bucketIndex((const AsciiString *)key);
    Wrapper004182D3 *head = m_buckets[idx];
    Wrapper004182D3 *cur = head;
    if (cur != 0) {
        do {
            const StringBase<char> &curKey = (const StringBase<char> &)cur->m_value;
            if (curKey.compare((const StringBase<char> &)*key) == 0) {
                out->m_node = cur;
                out->m_table = this;
                out->m_inserted = 0;
                return out;
            }
            cur = cur->m_next;
        } while (cur != 0);
    }
    Wrapper004182D3 *fresh = (Wrapper004182D3 *)rva004182D3(key);
    fresh->m_next = head;
    m_buckets[idx] = fresh;
    ++m_size;
    out->m_node = fresh;
    out->m_table = this;
    out->m_inserted = 1;
    return out;
}
