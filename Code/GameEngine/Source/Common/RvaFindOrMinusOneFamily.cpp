// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Three find-or-minus-one members (32B each): push [esp+8],
// call <find>, test eax, eax, je null, push [esp+4], mov ecx, eax,
// call <run>, jmp end, null: or eax, -1, end: ret 8. Each resolves (b)
// through the shared rowed finder 0x00219B9E (this flows through with no
// ecx setup, so the owners derive from it), then tail-returns
// found->run(a), or -1 on null. /O1 keeps the pushes on the stack slots.
// 0x0021BE42 (-> 0x0021BDAB), 0x0021BE62 (-> 0x0021BDD3),
// 0x0021BE82 (-> 0x0021BDFB). Run identities unproven (opaque pins);
// owner names are address-derived. One ledger row per member.

class Rva00219B9E
{
public:
	void *rva00219B9E(unsigned value);
};

class Rva0021BDABSub
{
public:
	int run(int value);
};

class Rva0021BDD3Sub
{
public:
	int run(int value);
};

class Rva0021BDFBSub
{
public:
	int run(int value);
};

class Rva0021BE42 : public Rva00219B9E
{
public:
	int fwd(int a, int b);
};

class Rva0021BE62 : public Rva00219B9E
{
public:
	int fwd(int a, int b);
};

class Rva0021BE82 : public Rva00219B9E
{
public:
	int fwd(int a, int b);
};

int Rva0021BE42::fwd(int a, int b)
{
	void *found = rva00219B9E((unsigned)b);
	return found ? ((Rva0021BDABSub *)found)->run(a) : -1;
}

int Rva0021BE62::fwd(int a, int b)
{
	void *found = rva00219B9E((unsigned)b);
	return found ? ((Rva0021BDD3Sub *)found)->run(a) : -1;
}

int Rva0021BE82::fwd(int a, int b)
{
	void *found = rva00219B9E((unsigned)b);
	return found ? ((Rva0021BDFBSub *)found)->run(a) : -1;
}
