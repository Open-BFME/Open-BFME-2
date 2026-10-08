// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /Ireference/shims/bfmealloc /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Native string-keyed hash insertion at 0x00418A12. STLport 4.5.3 insert_unique_noresize
// supplies the algorithm; key comparison at 0x69D6 and string copy at 0x365F0 establish
// the target key independently. The 32-byte value uses verified copy at 0x4188B6.
// The 37-byte creator and 45-byte construct replace the retired integer-key placeholder views.
#include <memory>
#include "Common/Rva00418A12StringHash.h"

class Rva000427195
{
public:
    void rva00212858(unsigned value);
    int bucketIndex(const AsciiString *name);
};

Rva0041890FRecord::Rva0041890FRecord(const Rva0041890FRecord &other)
    : key(other.key), value(other.value)
{
}

Rva0041890FRecord::Rva0041890FRecord(const AsciiString &name, const Rva004188B6 &mapped)
    : key(name), value(mapped)
{
}

void Rva00418985Construct(Rva0041890FRecord *output, const Rva0041890FRecord &record)
{
    new (output) Rva0041890FRecord(record);
}

Rva00418A12Node *Rva00418A8EHost::newNode(const Rva0041890FRecord &record)
{
    Rva00418A12Node *node = reinterpret_cast<Rva00418A12Node *>(
        _STL::allocator<char>::allocate(sizeof(Rva00418A12Node), 0));
    node->next = 0;
    Rva00418985Construct(&node->value, record);
    return node;
}

Rva00418A12Result *Rva00418A8EHost::apply(Rva00418A12Result *output,
    const Rva0041890FRecord &record)
{
    int index = reinterpret_cast<Rva000427195 *>(this)->bucketIndex(&record.key);
    Rva00418A12Node *head = m_buckets[index];
    Rva00418A12Node *cur = head;
    if (cur != 0)
    {
        do
        {
            const StringBase<char> &left = reinterpret_cast<const StringBase<char> &>(cur->value.key);
            const StringBase<char> &right = reinterpret_cast<const StringBase<char> &>(record.key);
            if (left.compare(right) == 0)
            {
                output->node = cur;
                output->table = this;
                output->inserted = false;
                return output;
            }
            cur = cur->next;
        } while (cur != 0);
    }
    Rva00418A12Node *node = newNode(record);
    node->next = head;
    m_buckets[index] = node;
    ++m_size;
    output->node = node;
    output->table = this;
    output->inserted = true;
    return output;
}

// Target outer at 0x00418A8E passes two words through to the insertion and returns
// its output address. Preserve that witnessed opaque integer ABI.
int Rva00418A8EHost::outer(int outputAddress, int recordAddress)
{
    reinterpret_cast<Rva000427195 *>(this)->rva00212858(m_size + 1);
    apply(reinterpret_cast<Rva00418A12Result *>(outputAddress),
        *reinterpret_cast<const Rva0041890FRecord *>(recordAddress));
    return outputAddress;
}
