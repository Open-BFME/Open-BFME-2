// cl: /Oy-
// Six tag-combine members (38B each): push ebp, mov ebp, esp, push esi,
// lea eax, [ebp+0x0B], push eax, push [ebp+8], mov esi, ecx, push [esi+4],
// push [ebp+0x0C], call <worker>, add esp, 0x10, mov [esi+4], eax,
// mov eax, [ebp+8], pop esi, pop ebp, ret 8. Each sets its +4 head field
// from worker(extra, head, tag, (char*)&tag + 3) and returns tag. /O1
// keeps the pushes on the stack slots and /Oy- keeps the ebp frame.
// 0x0007C2F0 (-> 0x0007BF5A), 0x00173DF8 (-> 0x00173714),
// 0x00335C62 (-> 0x003332FE), 0x0054152D (-> 0x00541214),
// 0x00541553 (-> 0x00541231), 0x005B129F (-> 0x005B09D8).
// Worker identities unproven (opaque pins); owner names address-derived.
// One ledger row per member.

int __cdecl Rva0007BF5AWorker(int extra, int head, int tag, char *tail);
int __cdecl Rva00173714Worker(int extra, int head, int tag, char *tail);
int __cdecl Rva003332FEWorker(int extra, int head, int tag, char *tail);
int __cdecl Rva00541214Worker(int extra, int head, int tag, char *tail);
int __cdecl Rva00541231Worker(int extra, int head, int tag, char *tail);
int __cdecl Rva005B09D8Worker(int extra, int head, int tag, char *tail);

class Rva0007C2F0Owner
{
public:
	int fwd(int tag, int extra);

private:
	int m_pad;
	int m_head;
};

class Rva00173DF8Owner
{
public:
	int fwd(int tag, int extra);

private:
	int m_pad;
	int m_head;
};

class Rva00335C62Owner
{
public:
	int fwd(int tag, int extra);

private:
	int m_pad;
	int m_head;
};

class Rva0054152DOwner
{
public:
	int fwd(int tag, int extra);

private:
	int m_pad;
	int m_head;
};

class Rva00541553Owner
{
public:
	int fwd(int tag, int extra);

private:
	int m_pad;
	int m_head;
};

class Rva005B129FOwner
{
public:
	int fwd(int tag, int extra);

private:
	int m_pad;
	int m_head;
};

int Rva0007C2F0Owner::fwd(int tag, int extra)
{
	m_head = Rva0007BF5AWorker(extra, m_head, tag, (char *)&tag + 3);
	return tag;
}

int Rva00173DF8Owner::fwd(int tag, int extra)
{
	m_head = Rva00173714Worker(extra, m_head, tag, (char *)&tag + 3);
	return tag;
}

int Rva00335C62Owner::fwd(int tag, int extra)
{
	m_head = Rva003332FEWorker(extra, m_head, tag, (char *)&tag + 3);
	return tag;
}

int Rva0054152DOwner::fwd(int tag, int extra)
{
	m_head = Rva00541214Worker(extra, m_head, tag, (char *)&tag + 3);
	return tag;
}

int Rva00541553Owner::fwd(int tag, int extra)
{
	m_head = Rva00541231Worker(extra, m_head, tag, (char *)&tag + 3);
	return tag;
}

int Rva005B129FOwner::fwd(int tag, int extra)
{
	m_head = Rva005B09D8Worker(extra, m_head, tag, (char *)&tag + 3);
	return tag;
}
