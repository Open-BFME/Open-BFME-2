// cl: /O1
// Five pre-increment-then-two-call members (36B each): push esi,
// mov esi, ecx, mov eax, [esi+0x10], inc eax, push eax, call <note>,
// push [esp+0x0C], mov ecx, esi, push [esp+0x0C], call <run>,
// mov eax, [esp+8], pop esi, ret 8. Each passes m_count+1 (loaded, not
// stored) to its note helper, then (a, b) to its run helper, and returns
// a. /O1 keeps the argument reads on the stack slots.
// 0x00057B27 (note 0x00056BFE, run 0x00054BC3),
// 0x00057D38 (note 0x0053F1EC-opaque-alias of the rowed Armor hashtable
//   resize, run 0x000556AB),
// 0x000E0536 (note 0x000E0322, run 0x000E0298),
// 0x003EF34A (note 0x00212858, run 0x003EF264),
// 0x0052B7F8 (note 0x00212858, run 0x0052B737).
// Helper identities unproven (opaque pins); owner names address-derived.
// One ledger row per member.

class Rva00056BFESub
{
public:
	void note(int value);
};

class Rva00054BC3Sub
{
public:
	void run(int a, int b);
};

class Rva0053F1ECSub
{
public:
	void note(int value);
};

class Rva000556ABSub
{
public:
	void run(int a, int b);
};

class Rva000E0322Sub
{
public:
	void note(int value);
};

class Rva000E0298Sub
{
public:
	void run(int a, int b);
};

class Rva00212858Sub
{
public:
	void note(int value);
};

class Rva003EF264Sub
{
public:
	void run(int a, int b);
};

class Rva0052B737Sub
{
public:
	void run(int a, int b);
};

class Rva00057B27Owner
{
public:
	int fwd(int a, int b);

private:
	char m_pad[0x10];
	int m_count;
};

class Rva00057D38Owner
{
public:
	int fwd(int a, int b);

private:
	char m_pad[0x10];
	int m_count;
};

class Rva000E0536Owner
{
public:
	int fwd(int a, int b);

private:
	char m_pad[0x10];
	int m_count;
};

class Rva003EF34AOwner
{
public:
	int fwd(int a, int b);

private:
	char m_pad[0x10];
	int m_count;
};

class Rva0052B7F8Owner
{
public:
	int fwd(int a, int b);

private:
	char m_pad[0x10];
	int m_count;
};

int Rva00057B27Owner::fwd(int a, int b)
{
	int next = m_count + 1;
	((Rva00056BFESub *)this)->note(next);
	((Rva00054BC3Sub *)this)->run(a, b);
	return a;
}

int Rva00057D38Owner::fwd(int a, int b)
{
	int next = m_count + 1;
	((Rva0053F1ECSub *)this)->note(next);
	((Rva000556ABSub *)this)->run(a, b);
	return a;
}

int Rva000E0536Owner::fwd(int a, int b)
{
	int next = m_count + 1;
	((Rva000E0322Sub *)this)->note(next);
	((Rva000E0298Sub *)this)->run(a, b);
	return a;
}

int Rva003EF34AOwner::fwd(int a, int b)
{
	int next = m_count + 1;
	((Rva00212858Sub *)this)->note(next);
	((Rva003EF264Sub *)this)->run(a, b);
	return a;
}

int Rva0052B7F8Owner::fwd(int a, int b)
{
	int next = m_count + 1;
	((Rva00212858Sub *)this)->note(next);
	((Rva0052B737Sub *)this)->run(a, b);
	return a;
}
