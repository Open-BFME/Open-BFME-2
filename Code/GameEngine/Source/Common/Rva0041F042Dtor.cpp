// cl: /O1 /MD /EHsc /DNDEBUG
// Native 0041E77F..0041E7B8: clear the chains through the shared rowed
// 001DBCDC implementation, then destroy the +4 bucket vector. The 20-byte
// table occupies +0C..+1F in the subsystem destructor at 0041F042.
// STLport teardown is a structural guide; the original table type is unknown.
void __cdecl free(void *);

class Rva001DBCDCTarget
{
public:
	void rva001DBCDC();
};

struct OwnedBucketStorage
{
	void **begin;
	void **end;
	void **capacity;
	// ?OwnedBucketStorage::~OwnedBucketStorage present-unmatched
	~OwnedBucketStorage()
	{
		if (begin) free(begin);
	}
};

class Rva0041E77F
{
public:
	~Rva0041E77F();
private:
	int m_functors;
	OwnedBucketStorage m_buckets;
	unsigned int m_count;
};

Rva0041E77F::~Rva0041E77F()
{
	((Rva001DBCDCTarget *)this)->rva001DBCDC();
}
