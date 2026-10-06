// cl: /O1
// RTS/Energy.cpp: the two power-bonus dispatchers retail links from this TU
// (tu_map approved), folded from two split units with these exact flags. They
// share the rowed power-add callee views.
// ?rva004DF207@Rva004DF207@@QAEXPAX@Z @ 0x004DF207 (42B)
// Dispatches signed value at [arg+4]+0x548 to rowed power adds (mirror of twin 0x004DF231).
// Retail negs before 0x004DF1AF (v<0 -> -v) and passes v straight to 0x004DF18D (v>0).
// Evidence: caller 0x0028D9D5 in 0x0028D99A (same as twin); callee rows 0x004DF1AF 0x004DF18D;
// twin Code/GameEngine/Source/Common/Rva004DF231Power.cpp // cl: /O1 reused.
class Rva004DF1AF
{
public:
	void rva004DF1AF(int delta);
};

class Rva004DF18D
{
public:
	void rva004DF18D(int delta);
};

struct Rva004DF207Inner
{
	char m_pad[0x548];
	int m_val;
};

struct Rva004DF207Outer
{
	char m_pad[4];
	Rva004DF207Inner *m_ptr;
};

class Rva004DF207
{
public:
	void rva004DF207(void *arg);
};

void Rva004DF207::rva004DF207(void *arg)
{
	if (!arg)
		return;
	Rva004DF207Outer *o = (Rva004DF207Outer *)arg;
	int v = o->m_ptr->m_val;
	if (v < 0)
		((Rva004DF1AF *)this)->rva004DF1AF(-v);
	else if (v > 0)
		((Rva004DF18D *)this)->rva004DF18D(v);
}

// ?rva004DF231@Rva004DF231@@QAEXPAX@Z RVA 0x004DF231 size 42
// Dispatches signed value at [arg+4]+0x548 to rowed power adds.
// Evidence: caller 0x0028D99A passes Object in stack and Player+0x1bc in ecx;
// callee rows 0x004DF1AF 0x004DF18D; twin 0x004DF207.
struct Rva004DF231Inner
{
	char m_pad[0x548];
	int m_val;
};

struct Rva004DF231Outer
{
	char m_pad[4];
	Rva004DF231Inner *m_ptr;
};

class Rva004DF231
{
public:
	void rva004DF231(void *arg);
};

void Rva004DF231::rva004DF231(void *arg)
{
	if (!arg)
		return;
	Rva004DF231Outer *o = (Rva004DF231Outer *)arg;
	int v = o->m_ptr->m_val;
	if (v < 0)
		((Rva004DF1AF *)this)->rva004DF1AF(v);
	else if (v > 0)
		((Rva004DF18D *)this)->rva004DF18D(-v);
}
