// cl: /Od

void bfmeDoPA(void *one, void *two, void *three, void *four, unsigned char *five,
	unsigned char *six, unsigned char seven);

void bfmeGoPA(void *one, void *two, void *three, void *four, unsigned char five)
{
	unsigned char second;

	unsigned char first;

	bfmeDoPA(one, two, three, four, &second, &first, five);
}
