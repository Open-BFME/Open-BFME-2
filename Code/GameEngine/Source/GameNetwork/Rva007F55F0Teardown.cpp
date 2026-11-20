// cl: /GX-
// Converted from Code/gen_asm/d_007f2a50.asm (?d_007f55f0@@YAXXZ).
// Same teardown as BfmeThingTWB::bfmeDelTWB without the scalar-delete tail.

extern "C" void *__identifier("??_7Rva007F6D60Child@@6B@")[];
extern "C" void *__identifier("??_7Rva007F6D60ChildBase@@6B@")[];

class BfmeStrTWB
{
public:
	void bfmeDtorTWB();
	char m_bfmePad[0x10];
};

class Rva00800290Buffer
{
public:
	void reset();
};
class BfmeListTWB
{
public:
	char m_bfmePad[0x10];
};

class Rva007F55F0Host
{
public:
	void teardown();

	void *m_vft;
	char m_pad04[4];
	int m_08;
	char m_pad0C[0x10];
	BfmeListTWB m_list;
	BfmeStrTWB m_b;
	BfmeStrTWB m_a;
};

void Rva007F55F0Host::teardown()
{
	m_vft = __identifier("??_7Rva007F6D60Child@@6B@");
	m_08 = 0;
	m_a.bfmeDtorTWB();
	m_b.bfmeDtorTWB();
	((Rva00800290Buffer *)&m_list)->reset();
	m_vft = __identifier("??_7Rva007F6D60ChildBase@@6B@");
}

