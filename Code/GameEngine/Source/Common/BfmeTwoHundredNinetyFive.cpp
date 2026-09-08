// cl: /Od

extern "C" void *__cdecl memcpy(void *to, const void *from, unsigned int many);
#pragma intrinsic(memcpy)

class BfmeThingQK
{
public:
	void bfmeMoveQK(char *first, char *last, char *to);
};

void BfmeThingQK::bfmeMoveQK(char *first, char *last, char *to)
{
	unsigned int many = (unsigned int)(last - first);

	(many == 0) ? (void *)to : memcpy(to, first, many);
}
