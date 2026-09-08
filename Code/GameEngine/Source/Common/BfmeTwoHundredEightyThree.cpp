// cl: /Od

int bfmeMakeOX(void *one);

void bfmeDoPW(char *first, char *last, char *otherFirst, char *otherLast);

struct BfmeThingPW
{
	void bfmeGoPW(char *at);

	char *m_bfmeAt;
	char *m_bfmeEnd;
};

void BfmeThingPW::bfmeGoPW(char *at)
{
	unsigned char spare[0x10];

	bfmeDoPW(m_bfmeAt, m_bfmeEnd, at, at + bfmeMakeOX(at));
}
