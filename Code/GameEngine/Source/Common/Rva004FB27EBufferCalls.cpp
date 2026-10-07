// cl: /O1 /Oy- /MD
// Retail 0x004FB27E..0x004FB2C1. Original class and method identities
// remain unknown. The native body supplies seven stack arguments to the
// helper at 0x0059DD3F through receiver+0x8C and advances +0xC by its
// output count. Offsets and the calling convention are target evidence.

extern unsigned int g_Va00E04508;

class Rva0059DD3F
{
public:
	void rva0059DD3F(void *, void *, void *, void *, int, int *, int);
};

struct Rva004FB27EInput
{
	char opaque00[0x14];
	void *field14;
};

class Rva004FB27E
{
public:
	void rva004FB27E();
private:
	Rva004FB27EInput *input;
	unsigned field04;
	int field08;
	int consumed;
	int end;
	int field14;
	char context[0x68 - 0x18];
	char output[0x8C - 0x68];
	Rva0059DD3F helper;
};

void Rva004FB27E::rva004FB27E()
{
	if (input)
	{
		int written = 0;
		helper.rva0059DD3F(output, input->field14, context, &g_Va00E04508,
			end - consumed, &written, field08);
		consumed += written;
	}
}

class Rva0059D2DA
{
public:
	void rva0059D2DA(void *, void *, void *, void *, int, int, int, int *);
};

class Rva004FB2C1
{
public:
	void rva004FB2C1();
private:
	Rva004FB27EInput *input;
	unsigned field04;
	int field08;
	int begin;
	int end;
	int field14;
	char context[0x74 - 0x18];
	char output[0xEC - 0x74];
	Rva0059D2DA helper;
};

// Sibling 0x004FB2C1..0x004FB303: eight arguments to 0x0059D2DA
// through +0xEC. It passes both +0xC and +0x10 and advances +0x10.
// The helper's native RET 32 independently agrees with the stack arguments.
void Rva004FB2C1::rva004FB2C1()
{
	if (input)
	{
		int written = 0;
		helper.rva0059D2DA(output, input->field14, context, &g_Va00E04508,
			begin, end, field14, &written);
		end += written;
	}
}
