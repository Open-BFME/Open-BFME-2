// cl: /EHsc /Oy- /O1 /Ob2
// ?rva005CECF3@Rva005CECF3@@QBE?AURva005CECF3Handle@@XZ, retail 0x005CECF3, 68 bytes.
// Clone returning handle: allocates 0x10-byte refcounted object copying 8-byte payload from this, wraps in handle with AddRef.
// Evidence: packet disassembly push 0x10 call ??2 row pop ecx clean and [eax+4] 0 vtable store two movs jmp/xor null path test mov je inc mov eax ret 4, VTABLE slot 1 of table at 0x008751D0.
struct Rva005CECF3Handle
{
	void *m_p;
	__forceinline Rva005CECF3Handle(void *p) : m_p(p)
	{
		if (p != 0)
			((int *)p)[1]++;
	}
	~Rva005CECF3Handle();
};

struct Rva005CECF3
{
	virtual ~Rva005CECF3();
	int m_ref;
	int m_08;
	int m_0C;
	__forceinline Rva005CECF3(const Rva005CECF3 &src) : m_ref(0), m_08(src.m_08), m_0C(src.m_0C) {}
	Rva005CECF3Handle rva005CECF3() const;
};

Rva005CECF3Handle Rva005CECF3::rva005CECF3() const
{
	return Rva005CECF3Handle(new Rva005CECF3(*this));
}
