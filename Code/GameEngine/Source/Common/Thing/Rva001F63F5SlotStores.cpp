// cl: /O1 /MD
// Eight 22B slot stores, the leaf form of Rva001FA836ForwardChain.cpp: each
// stores the rowed Slot get(a) of b at +0 and returns (thiscall ret 8).
// Getters by REL32: 001F63F5 -> 001F5D98; 001F6430 -> 001F5DAC; 001F6446 ->
// 001F5DC0; 001F645C -> 001F5DD4; 001F6472 -> 001F5DE8; 001F64BC ->
// 001F5DFC; 001F650B -> 001F5E10; 001F6521 -> 001F5E24. Original names
// unknown so address-derived Rva names are used.
class Rva001F5D98Slot
{
public:
	void *get(void *a);
};
class Rva001F63F5
{
public:
	void rva001F63F5(void *a, void *b);
private:
	void *m_00;
};
void Rva001F63F5::rva001F63F5(void *a, void *b)
{
	m_00 = ((Rva001F5D98Slot *)b)->get(a);
}
class Rva001F5DACSlot
{
public:
	void *get(void *a);
};
class Rva001F6430
{
public:
	void rva001F6430(void *a, void *b);
private:
	void *m_00;
};
void Rva001F6430::rva001F6430(void *a, void *b)
{
	m_00 = ((Rva001F5DACSlot *)b)->get(a);
}
class Rva001F5DC0Slot
{
public:
	void *get(void *a);
};
class Rva001F6446
{
public:
	void rva001F6446(void *a, void *b);
private:
	void *m_00;
};
void Rva001F6446::rva001F6446(void *a, void *b)
{
	m_00 = ((Rva001F5DC0Slot *)b)->get(a);
}
class Rva001F5DD4Slot
{
public:
	void *get(void *a);
};
class Rva001F645C
{
public:
	void rva001F645C(void *a, void *b);
private:
	void *m_00;
};
void Rva001F645C::rva001F645C(void *a, void *b)
{
	m_00 = ((Rva001F5DD4Slot *)b)->get(a);
}
class Rva001F5DE8Slot
{
public:
	void *get(void *a);
};
class Rva001F6472
{
public:
	void rva001F6472(void *a, void *b);
private:
	void *m_00;
};
void Rva001F6472::rva001F6472(void *a, void *b)
{
	m_00 = ((Rva001F5DE8Slot *)b)->get(a);
}
class Rva001F5DFCSlot
{
public:
	void *get(void *a);
};
class Rva001F64BC
{
public:
	void rva001F64BC(void *a, void *b);
private:
	void *m_00;
};
void Rva001F64BC::rva001F64BC(void *a, void *b)
{
	m_00 = ((Rva001F5DFCSlot *)b)->get(a);
}
class Rva001F5E10Slot
{
public:
	void *get(void *a);
};
class Rva001F650B
{
public:
	void rva001F650B(void *a, void *b);
private:
	void *m_00;
};
void Rva001F650B::rva001F650B(void *a, void *b)
{
	m_00 = ((Rva001F5E10Slot *)b)->get(a);
}
class Rva001F5E24Slot
{
public:
	void *get(void *a);
};
class Rva001F6521
{
public:
	void rva001F6521(void *a, void *b);
private:
	void *m_00;
};
void Rva001F6521::rva001F6521(void *a, void *b)
{
	m_00 = ((Rva001F5E24Slot *)b)->get(a);
}
