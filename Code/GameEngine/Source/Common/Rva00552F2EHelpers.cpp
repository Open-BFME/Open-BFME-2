// cl: /MD

struct Rva00552F2E
{
	int a[4];
	int b[4];
	Rva00552F2E();
};

Rva00552F2E::Rva00552F2E()
{
	for (int i = 0; i < 4; ++i)
	{
		b[i] = 0;
		a[i] = 0;
	}
}

struct Rva00552F55
{
	char b;
	char pad;
	short s;
	Rva00552F55 &set(const char *pc, const short *ps);
};

Rva00552F55 &Rva00552F55::set(const char *pc, const short *ps)
{
	b = *pc;
	s = *ps;
	return *this;
}

struct Rva00552F6D
{
	char b;
	char pad[3];
	int i;
	Rva00552F6D &set(const char *pc, const int *pi);
};

Rva00552F6D &Rva00552F6D::set(const char *pc, const int *pi)
{
	b = *pc;
	i = *pi;
	return *this;
}
