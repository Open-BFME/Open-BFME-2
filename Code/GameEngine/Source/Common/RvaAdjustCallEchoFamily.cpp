// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Four adjust-call-echo members (19B each): push [esp+4], add ecx, -N,
// call <run>, mov eax, [esp+4], ret 4. Each runs its argument through the
// adjusted object at this-N, then returns the argument itself. /O1 keeps
// both argument reads on the stack slot (/O2 caches it in esi).
// 0x0030BEE6 (-0x28 -> 0x0053863E), 0x0030BEF9 (-0x28 -> 0x00538674),
// 0x00330C0F (-0x3C -> 0x0007E03A), 0x00330C22 (-0x3C -> 0x002E3876).
// Callee identities unproven (opaque pins); owner names address-derived.
// One ledger row per member.

class Rva0053863ESub
{
public:
	void run(int value);
};

class Rva00538674Sub
{
public:
	void run(int value);
};

class Rva0007E03ASub
{
public:
	void run(int value);
};

class Rva002E3876Sub
{
public:
	void run(int value);
};

class Rva0030BEE6Owner
{
public:
	int fwd(int value);
};

class Rva0030BEF9Owner
{
public:
	int fwd(int value);
};

class Rva00330C0FOwner
{
public:
	int fwd(int value);
};

class Rva00330C22Owner
{
public:
	int fwd(int value);
};

int Rva0030BEE6Owner::fwd(int value)
{
	((Rva0053863ESub *)((char *)this - 0x28))->run(value);
	return value;
}

int Rva0030BEF9Owner::fwd(int value)
{
	((Rva00538674Sub *)((char *)this - 0x28))->run(value);
	return value;
}

int Rva00330C0FOwner::fwd(int value)
{
	((Rva0007E03ASub *)((char *)this - 0x3C))->run(value);
	return value;
}

int Rva00330C22Owner::fwd(int value)
{
	((Rva002E3876Sub *)((char *)this - 0x3C))->run(value);
	return value;
}
