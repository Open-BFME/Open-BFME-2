// BucketAlloc: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BUCKETALLOC_H
#define CANONICAL_BUCKETALLOC_H

struct BucketAlloc
{
	static void *allocate(unsigned int bytes, const void *hint);
};

#endif // CANONICAL_BUCKETALLOC_H
