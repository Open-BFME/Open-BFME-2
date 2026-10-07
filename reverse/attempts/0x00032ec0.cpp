// ?rva00032EC0@GeneralAllocator@Allocator@EA@@QAEXPBXPAUBlockInfo@23@@Z
// partial score=0.6 date=2026-10-07
// cl: /O2 /MD
// Native 0x00032EC0..0x00032F57, RET8. The report iterator at 0x32F60
// calls this allocator member with a chunk and a BlockInfo output. The
// matched 0x32A20 supplies payload size. Field offsets and flag tests below
// are target evidence; the original method name remains unknown.
namespace EA { namespace Allocator {
struct BlockInfo
{
    void *m_core;
    unsigned int m_blockSize;
    void *m_data;
    unsigned int m_dataSize;
    char m_blockType;
    bool m_mapped;
};
class GeneralAllocator
{
public:
    void rva00032EC0(const void *block, BlockInfo *out);
    unsigned int rva00032A20(const void *block);
};

void GeneralAllocator::rva00032EC0(const void *block, BlockInfo *out)
{
    const char *chunk = (const char *)block;
    unsigned int header = *(const unsigned int *)(chunk + 4);
    unsigned int mapped = header & 2;
    unsigned int size = header & 0x7FFFFFF8;
    unsigned char nextFlags = *(const unsigned char *)(chunk + size + 4);
    if ((nextFlags & 1) != 0)
    {
        void *data = (void *)(chunk + 8);
        unsigned int usable = rva00032A20(data);
        out->m_blockType = 2;
        if (mapped != 0)
        {
            out->m_core = (void *)((unsigned int)chunk - *(const unsigned int *)chunk);
            unsigned int prefix = *(const unsigned int *)chunk;
            out->m_data = data;
            out->m_blockSize = prefix + size + 0x10;
            out->m_dataSize = usable;
            out->m_mapped = true;
        }
        else
        {
            out->m_data = data;
            out->m_blockSize = size;
            out->m_core = (void *)chunk;
            out->m_dataSize = usable;
            out->m_mapped = false;
        }
    }
    else
    {
        out->m_core = (void *)chunk;
        out->m_blockSize = size;
        out->m_blockType = 4;
        out->m_data = (void *)(chunk + 0x10);
        out->m_dataSize = (*(const unsigned int *)(chunk + 4) & 0x7FFFFFF8) - 0x10;
        out->m_mapped = false;
    }
}
} }
