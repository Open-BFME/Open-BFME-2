// cl: /O1 /DNDEBUG /MD
//
// Two-int pack wrappers: each packs its two int arguments into a stack
// TwoInts and passes its address to an unrowed member helper (pinned in
// reverse/symbols.csv from the body's own REL32), returning void.
// 0x002BFCF5 -> 0x002BFA86. 0x003A37DC -> 0x002ADCE1.
// 0x005258F8 -> 0x00525407.

struct TwoInts002BFCF5
{
	int a;
	int b;
};

class Rva002BFCF5
{
public:
	void rva002BFCF5(int a, int b);
private:
	void helper(const TwoInts002BFCF5 *p);
};
void Rva002BFCF5::rva002BFCF5(int a, int b)
{
	TwoInts002BFCF5 t;
	t.a = a;
	t.b = b;
	helper(&t);
}

struct TwoInts003A37DC
{
	int a;
	int b;
};

class Rva003A37DC
{
public:
	void rva003A37DC(int a, int b);
private:
	void helper(const TwoInts003A37DC *p);
};
void Rva003A37DC::rva003A37DC(int a, int b)
{
	TwoInts003A37DC t;
	t.a = a;
	t.b = b;
	helper(&t);
}

struct TwoInts005258F8
{
	int a;
	int b;
};

class Rva005258F8
{
public:
	void rva005258F8(int a, int b);
private:
	void helper(const TwoInts005258F8 *p);
};
void Rva005258F8::rva005258F8(int a, int b)
{
	TwoInts005258F8 t;
	t.a = a;
	t.b = b;
	helper(&t);
}
