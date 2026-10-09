// cl: /O1 /MD /EHsc /DNDEBUG
// Native3EF22B..3EF264: clear the ASCII-keyed hash table then free its bucket array.
// Concrete20B storage is target-derived; this replaces the old object-symbol alias.
// The existing throwing GameFree provider preserves the native unwind transition.
class Rva000427195 {public:void rva003A2A41();};
void Rva00030830GameFree(void*);
struct S3RegionBucketStorage {~S3RegionBucketStorage(){if(begin)Rva00030830GameFree(begin);}void**begin;void**end;void**capacity;};
struct Rva003EF22B {void*unused;S3RegionBucketStorage buckets;unsigned count;~Rva003EF22B();};
Rva003EF22B::~Rva003EF22B(){((Rva000427195*)this)->rva003A2A41();}
