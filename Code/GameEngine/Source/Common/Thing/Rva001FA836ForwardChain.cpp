// cl: /MD
// Forwarding chain 001FA836 .. 001FC451 (seven 38B bodies) over the rowed
// root Rva001FA54DForward.cpp: each link stores the rowed Slot get(a) of b at
// +0 then forwards (a, b) to the next link held at +4. Getters and next links
// by REL32: 001FA836 get 001F5E10 next 001FA54D; 001FB8EC get 001F5DFC next
// 001FA836; 001FBA8C get 001F5DE8 next 001FB8EC; 001FBC43 get 001F5DD4 next
// 001FBA8C; 001FBFEA get 001F5DC0 next 001FBC43; 001FC357 get 001F5DAC next
// 001FBFEA; 001FC451 get 001F5D98 next 001FC357. Original names unknown so
// address-derived Rva names are used.
class Rva001FA54D
{
public:
	void rva001FA54D(void *a, void *b);
private:
	void *m_00;
	void *m_04;
};
class Rva001F5E10Slot
{
public:
	void *get(void *a);
};
class Rva001FA836
{
public:
	void rva001FA836(void *a, void *b);
private:
	void *m_00;
	Rva001FA54D m_04;
};
void Rva001FA836::rva001FA836(void *a, void *b)
{
	m_00 = ((Rva001F5E10Slot *)b)->get(a);
	m_04.rva001FA54D(a, b);
}
class Rva001F5DFCSlot
{
public:
	void *get(void *a);
};
class Rva001FB8EC
{
public:
	void rva001FB8EC(void *a, void *b);
private:
	void *m_00;
	Rva001FA836 m_04;
};
void Rva001FB8EC::rva001FB8EC(void *a, void *b)
{
	m_00 = ((Rva001F5DFCSlot *)b)->get(a);
	m_04.rva001FA836(a, b);
}
class Rva001F5DE8Slot
{
public:
	void *get(void *a);
};
class Rva001FBA8C
{
public:
	void rva001FBA8C(void *a, void *b);
private:
	void *m_00;
	Rva001FB8EC m_04;
};
void Rva001FBA8C::rva001FBA8C(void *a, void *b)
{
	m_00 = ((Rva001F5DE8Slot *)b)->get(a);
	m_04.rva001FB8EC(a, b);
}
class Rva001F5DD4Slot
{
public:
	void *get(void *a);
};
class Rva001FBC43
{
public:
	void rva001FBC43(void *a, void *b);
private:
	void *m_00;
	Rva001FBA8C m_04;
};
void Rva001FBC43::rva001FBC43(void *a, void *b)
{
	m_00 = ((Rva001F5DD4Slot *)b)->get(a);
	m_04.rva001FBA8C(a, b);
}
class Rva001F5DC0Slot
{
public:
	void *get(void *a);
};
class Rva001FBFEA
{
public:
	void rva001FBFEA(void *a, void *b);
private:
	void *m_00;
	Rva001FBC43 m_04;
};
void Rva001FBFEA::rva001FBFEA(void *a, void *b)
{
	m_00 = ((Rva001F5DC0Slot *)b)->get(a);
	m_04.rva001FBC43(a, b);
}
class Rva001F5DACSlot
{
public:
	void *get(void *a);
};
class Rva001FC357
{
public:
	void rva001FC357(void *a, void *b);
private:
	void *m_00;
	Rva001FBFEA m_04;
};
void Rva001FC357::rva001FC357(void *a, void *b)
{
	m_00 = ((Rva001F5DACSlot *)b)->get(a);
	m_04.rva001FBFEA(a, b);
}
class Rva001F5D98Slot
{
public:
	void *get(void *a);
};
class Rva001FC451
{
public:
	void rva001FC451(void *a, void *b);
private:
	void *m_00;
	Rva001FC357 m_04;
};
void Rva001FC451::rva001FC451(void *a, void *b)
{
	m_00 = ((Rva001F5D98Slot *)b)->get(a);
	m_04.rva001FC357(a, b);
}
