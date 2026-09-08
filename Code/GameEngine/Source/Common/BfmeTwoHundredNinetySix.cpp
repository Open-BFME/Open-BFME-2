// cl: /Od

void *bfmeAllocQL(int kind, void *what);

int **bfmeFillQL(int **first, int **last, int **out)
{
	int **at = out;

	for (; first != last; ++first, ++at)
	{
		int *got = (int *)bfmeAllocQL(4, at);

		(got != 0) ? (*got = *(int *)first, (void *)got) : (void *)0;
	}

	return at;
}
