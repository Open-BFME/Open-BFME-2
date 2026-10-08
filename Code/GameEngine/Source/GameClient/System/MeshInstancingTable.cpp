// cl: /O1 /DNDEBUG /MD /EHsc
// ??1Rva0041FA59@@QAE@XZ, native 0x0041FA59..0x0041FA92 (57B).
// Native AsciiString-keyed table destructor reached by MeshInstancingManager.
// Its old gen-alias copy used another destructor's symbol/EH identity.
// Clear owns string-node destruction; then the bucket storage is freed through
// the verified GameMemory free override. No STL CRT header declaration is
// imported, preserving the allocator's native potentially-throwing contract.
extern "C" void __cdecl free(void *block) throw(...);
class Rva000427195 { public: void rva003A2A41(); };
struct MeshInstancingBucketHandle
{
    ~MeshInstancingBucketHandle()
    {
        if (m_beginBuckets)
            free(m_beginBuckets);
    }
    void **m_beginBuckets;
    void **m_endBuckets;
    void **m_storageEnd;
};
class Rva0041FA59
{
public:
    ~Rva0041FA59();
private:
    void *m_unused00;
    MeshInstancingBucketHandle m_buckets;
    unsigned int m_numElements;
};
Rva0041FA59::~Rva0041FA59()
{
    reinterpret_cast<Rva000427195 *>(this)->rva003A2A41();
}
