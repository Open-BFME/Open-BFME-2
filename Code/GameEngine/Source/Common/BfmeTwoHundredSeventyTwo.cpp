// cl: /Od

int bfmeMakeOX(void *one);

class BfmeThingPL
{
public:
	void bfmeGoPL(char *at);

	void bfmeAssignPL(char *first, char *last);
};

void BfmeThingPL::bfmeGoPL(char *at)
{
	unsigned char spare[0x68];

	bfmeAssignPL(at, at + bfmeMakeOX(at));
}
