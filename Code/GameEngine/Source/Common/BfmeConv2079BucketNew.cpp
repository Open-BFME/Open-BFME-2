void *bfmeAllocBlock(unsigned int bytes);

class Bucket
{
public:
	enum BucketMagicEnum { BFME_ZERO_JT = 0 };

	static void *operator new(unsigned int n, BucketMagicEnum m);
};

void *Bucket::operator new(unsigned int size, BucketMagicEnum)
{
	return bfmeAllocBlock(size);
}
