// Six read-through members (29B each): mov eax, [esp+4], push esi,
// mov esi, ecx, mov ecx, [eax], add eax, 4, mov [esi], ecx, push eax,
// lea ecx, [esi+4], call <read>, mov eax, esi, pop esi, ret 4. Each stores
// *ptr in its first field, asks the +4 sub-object to read the rest, and
// returns this.
// 0x004C7330 (-> 0x001F206E), 0x004F802C (-> 0x004F69D6),
// 0x00501DD4 (-> 0x005017B4), 0x005020AF (-> 0x00501B33),
// 0x00502909 (-> 0x005026EE), 0x005564EB (-> 0x0038630B).
// Callee identities unproven (opaque pins); owner names address-derived.
// One ledger row per member.

class Rva001F206ESub
{
public:
	void read(int *ptr);
};

class Rva004F69D6Sub
{
public:
	void read(int *ptr);
};

class Rva005017B4Sub
{
public:
	void read(int *ptr);
};

class Rva00501B33Sub
{
public:
	void read(int *ptr);
};

class Rva005026EESub
{
public:
	void read(int *ptr);
};

class Rva0038630BSub
{
public:
	void read(int *ptr);
};

class Rva004C7330Owner
{
public:
	Rva004C7330Owner *read(int *ptr);

private:
	int m_first;
	Rva001F206ESub m_sub;
};

class Rva004F802COwner
{
public:
	Rva004F802COwner *read(int *ptr);

private:
	int m_first;
	Rva004F69D6Sub m_sub;
};

class Rva00501DD4Owner
{
public:
	Rva00501DD4Owner *read(int *ptr);

private:
	int m_first;
	Rva005017B4Sub m_sub;
};

class Rva005020AFOwner
{
public:
	Rva005020AFOwner *read(int *ptr);

private:
	int m_first;
	Rva00501B33Sub m_sub;
};

class Rva00502909Owner
{
public:
	Rva00502909Owner *read(int *ptr);

private:
	int m_first;
	Rva005026EESub m_sub;
};

class Rva005564EBOwner
{
public:
	Rva005564EBOwner *read(int *ptr);

private:
	int m_first;
	Rva0038630BSub m_sub;
};

Rva004C7330Owner *Rva004C7330Owner::read(int *ptr)
{
	m_first = *ptr;
	m_sub.read(ptr + 1);
	return this;
}

Rva004F802COwner *Rva004F802COwner::read(int *ptr)
{
	m_first = *ptr;
	m_sub.read(ptr + 1);
	return this;
}

Rva00501DD4Owner *Rva00501DD4Owner::read(int *ptr)
{
	m_first = *ptr;
	m_sub.read(ptr + 1);
	return this;
}

Rva005020AFOwner *Rva005020AFOwner::read(int *ptr)
{
	m_first = *ptr;
	m_sub.read(ptr + 1);
	return this;
}

Rva00502909Owner *Rva00502909Owner::read(int *ptr)
{
	m_first = *ptr;
	m_sub.read(ptr + 1);
	return this;
}

Rva005564EBOwner *Rva005564EBOwner::read(int *ptr)
{
	m_first = *ptr;
	m_sub.read(ptr + 1);
	return this;
}
