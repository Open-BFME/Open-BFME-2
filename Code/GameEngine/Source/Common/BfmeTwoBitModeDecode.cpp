// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva009B4680State;
int __cdecl Rva009B4680Normalize(Rva009B4680State *p);

int Rva009B5090DecodeMode(unsigned char *ctx)
{
	void *state = ctx + 0x150;
	int value = Rva009B4680Normalize((Rva009B4680State *)state) * 2;
	value += Rva009B4680Normalize((Rva009B4680State *)state);

	switch (value) {
	case 0:
		return 0;
	case 1:
		return 2;
	case 2:
		return 3;
	case 3:
		return 4;
	}
	return 0;
}
