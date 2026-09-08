// cl: /Od

void *bfmeAllocQG(int kind, unsigned int bytes);

class BfmeThingQG
{
public:
	void bfmeMakeQG(unsigned int bytes, const int *from);
};

void BfmeThingQG::bfmeMakeQG(unsigned int bytes, const int *from)
{
	int *got = (int *)bfmeAllocQG(4, bytes);

	(got != 0) ? (*got = *from, (void *)got) : (void *)0;
}
