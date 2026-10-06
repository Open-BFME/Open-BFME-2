// cl: /MD
// ?Rva00552C5FGet@@YAEXZ 0x00552C5F 27B: free returns 1 if stats connected else init==0; callers 0x0055819C
extern "C" int __cdecl IsStatsConnected();
extern "C" int __cdecl InitStatsConnection(int);

unsigned char __cdecl Rva00552C5FGet()
{
	if (IsStatsConnected())
		return 1;
	return (unsigned char)(InitStatsConnection(0) == 0);
}

// ?rva00552C7ACallback@@YAXHHHHPAX@Z
void rva00552C7ACallback(int a0, int a1, int a2, int a3, void *userData)
{
	if (userData)
	{
		char *p = (char *)userData;
		p[0x51] = 1;
		p[0x50] = (a2 != 0);
	}
}

// ?rva00552C92Callback@@YAXHHHHHHPAX@Z
void rva00552C92Callback(int a0, int a1, int a2, int a3, int a4, int a5, void *userData)
{
	if (userData)
	{
		int *p = (int *)((char *)userData + 0x54);
		--(*p);
	}
}

// ?rva00552C9ECallback@@YAXHHHHPAX@Z
void rva00552C9ECallback(int a0, int a1, int a2, int a3, void *userData)
{
	char *p = (char *)userData;
	p[0] = (a2 != 0);
	p[1] = 1;
	*(int *)(p + 4) = a1;
}
