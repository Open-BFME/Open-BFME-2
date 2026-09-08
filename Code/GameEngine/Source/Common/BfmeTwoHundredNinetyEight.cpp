// cl: /Oy-

extern "C" __declspec(dllimport) int __stdcall wvsprintfA(char *out, const char *how, char *rest);

struct BfmeThingQO
{
	void bfmeFlushQO(int how);

	unsigned char m_bfmeHead[0x9cf4];
	int m_bfmeKind;
	char m_bfmeBuf[4];
};

void bfmeLogQO(BfmeThingQO *what, int kind, const char *how, ...)
{
	if (what->m_bfmeKind == 1)
		what->bfmeFlushQO(1);

	what->m_bfmeKind = kind;

	wvsprintfA(what->m_bfmeBuf, how, (char *)(&how + 1));
}
