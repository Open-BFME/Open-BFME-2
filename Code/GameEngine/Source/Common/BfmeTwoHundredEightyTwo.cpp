// cl: /Od

void *bfmeAllocPV(int kind, unsigned int bytes);

void bfmeMakePV(unsigned int bytes)
{
	void *out;

	char *got = (char *)bfmeAllocPV(1, bytes);

	if (got != 0)
	{
		*got = 0;

		out = got;
	}
	else
	{
		out = 0;
	}
}
