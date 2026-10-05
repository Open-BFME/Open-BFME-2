// cl: /O1
// Four chained lookups (38B each): push [esp+8], mov esi, ecx,
// mov ecx, [esp+0x10], call <find>, push [esp+0x0C], lea ecx, [esi+4],
// push [esp+0x0C], mov [esi], eax, call <chain>, pop esi, ret 8. Each
// resolves (a) through the b-object's find method, stores the result in
// its head field, then tail-returns the +4 sub-object's chained (a, b)
// call. The chain links backward: 0x001FC451 -> 0x001FC357 -> 0x001FBFEA
// -> 0x001FBC43 -> 0x001FBA8C (opaque pin). Finder identities unproven
// except the rowed Rva001F5DD4Slot::get used by the anchor; the chained
// calls resolve through this unit's own rows. Names address-derived.
// One ledger row per member.

class Rva001F5DD4Slot
{
public:
	void *get(void *key);
};

class Rva001F5DC0Slot
{
public:
	void *get(void *key);
};

class Rva001F5DACSlot
{
public:
	void *get(void *key);
};

class Rva001F5D98Slot
{
public:
	void *get(void *key);
};

class Rva001FBA8C
{
public:
	int fwd(int a, int b);
};

class Rva001FBC43
{
public:
	int fwd(int a, int b);

private:
	void *m_head;
	Rva001FBA8C m_sub;
};

class Rva001FBFEA
{
public:
	int fwd(int a, int b);

private:
	void *m_head;
	Rva001FBC43 m_sub;
};

class Rva001FC357
{
public:
	int fwd(int a, int b);

private:
	void *m_head;
	Rva001FBFEA m_sub;
};

class Rva001FC451
{
public:
	int fwd(int a, int b);

private:
	void *m_head;
	Rva001FC357 m_sub;
};

int Rva001FBC43::fwd(int a, int b)
{
	void *found = ((Rva001F5DD4Slot *)b)->get((void *)a);
	m_head = found;
	return m_sub.fwd(a, b);
}

int Rva001FBFEA::fwd(int a, int b)
{
	void *found = ((Rva001F5DC0Slot *)b)->get((void *)a);
	m_head = found;
	return m_sub.fwd(a, b);
}

int Rva001FC357::fwd(int a, int b)
{
	void *found = ((Rva001F5DACSlot *)b)->get((void *)a);
	m_head = found;
	return m_sub.fwd(a, b);
}

int Rva001FC451::fwd(int a, int b)
{
	void *found = ((Rva001F5D98Slot *)b)->get((void *)a);
	m_head = found;
	return m_sub.fwd(a, b);
}
