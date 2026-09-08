// cl: /Od

int *bfmeFindQH(int *at, int how);

void bfmeSwapQH(int *at, int *other)
{
	int *found = bfmeFindQH(other, 0);

	if (found != other)
	{
		int keep = *at;

		*at = *other;

		*other = 0;

		*found = keep;
	}
}
