// cl: /Od

void bfmeDoOV(void *one, void *two, void *three, void *four, unsigned char *five);

void bfmeGoOV(void *one, void *two, void *three, void *four)
{
	int spare[5];
	unsigned char got;

	bfmeDoOV(one, two, three, four, &got);
}
