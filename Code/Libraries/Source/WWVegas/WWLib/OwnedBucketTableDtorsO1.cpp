// cl: /O1 /MD /EHsc
// STLport hashtable teardown guide: clear the chains while the bucket vector
// is live, then destroy that vector. Native 0041EBD2..0041EC0B establishes
// clear(0041EA88), bucket storage at +4, and throwing free(00030830).
// Rva0041EA88Clear.cpp establishes the matching +4/+8/+10 table view.
// The source names are address-derived; original container identity is unknown.
void __cdecl free(void *);
struct OwnedBucketStorage
{
    void **begin;
    void **end;
    void **capacity;
    ~OwnedBucketStorage();
};
// ?OwnedBucketStorage::~OwnedBucketStorage present-unmatched
inline OwnedBucketStorage::~OwnedBucketStorage()
{
    if (begin)
        free(begin);
}
class Rva0041EA88
{
public:
    void rva0041EA88();
    ~Rva0041EA88();
private:
    int m_functors;
    OwnedBucketStorage m_buckets;
    unsigned int m_count;
};
Rva0041EA88::~Rva0041EA88()
{
    rva0041EA88();
}
