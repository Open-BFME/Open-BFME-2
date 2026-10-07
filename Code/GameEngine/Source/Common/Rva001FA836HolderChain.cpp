// cl: /MD
// Chained holder-fetch wrappers, 38B each. Every member stores its slot's
// fetch at +0 and delegates to the previous level at +4:
//
//   0x001FA836  slot 0x001F5E10 (Rva001F5E10Slot::get)  prev 0x001FA54D (rowed)
//   0x001FB8EC  slot 0x001F5DFC (Rva001F5DFCSlot::get)   prev 0x001FA836
//   0x001FBA8C  slot 0x001F5DE8 (Rva001F5DE8Slot::get)   prev 0x001FB8EC
//   0x001FBC43  slot 0x001F5DD4 (Rva001F5DD4Slot::get)   prev 0x001FBA8C
//   0x001FBFEA  slot 0x001F5DC0 (Rva001F5DC0Slot::get)   prev 0x001FBC43
//   0x001FC357  slot 0x001F5DAC (Rva001F5DACSlot::get)   prev 0x001FBFEA
//   0x001FC451  slot 0x001F5D98 (Rva001F5D98Slot::get)   prev 0x001FC357
// Slot getters and the chain root are rowed in their own TUs (same class
// spellings redeclared here, methods defined nowhere here) and resolve
// through the ledger. Rva001FA54D's view below copies Rva001FA54DForward.cpp
// member for member. All setups take (void *, void *) so each level can hand
// its slot pointer down unchanged; the slot cast emits no code.
class Rva001F5E10Slot
{
public:
	void *get(void *a);
};
class Rva001F5DFCSlot
{
public:
	void *get(void *a);
};
class Rva001F5DE8Slot
{
public:
	void *get(void *a);
};
class Rva001F5DD4Slot
{
public:
	void *get(void *a);
};
class Rva001F5DC0Slot
{
public:
	void *get(void *a);
};
class Rva001F5DACSlot
{
public:
	void *get(void *a);
};
class Rva001F5D98Slot
{
public:
	void *get(void *a);
};
class Rva001FA54D
{
public:
	void rva001FA54D(void *a, void *b);
private:
	void *m_00;
	void *m_04;
};
class Rva001FA836
{
public:
	void setup(void *a, void *b);
private:
	void *m_00;
	Rva001FA54D m_04;
};
void Rva001FA836::setup(void *a, void *b)
{
	m_00 = ((Rva001F5E10Slot *)b)->get(a);
	m_04.rva001FA54D(a, b);
}
class Rva001FB8EC
{
public:
	void setup(void *a, void *b);
private:
	void *m_00;
	Rva001FA836 m_04;
};
void Rva001FB8EC::setup(void *a, void *b)
{
	m_00 = ((Rva001F5DFCSlot *)b)->get(a);
	m_04.setup(a, b);
}
class Rva001FBA8C
{
public:
	void setup(void *a, void *b);
private:
	void *m_00;
	Rva001FB8EC m_04;
};
void Rva001FBA8C::setup(void *a, void *b)
{
	m_00 = ((Rva001F5DE8Slot *)b)->get(a);
	m_04.setup(a, b);
}
class Rva001FBC43
{
public:
	void setup(void *a, void *b);
private:
	void *m_00;
	Rva001FBA8C m_04;
};
class Rva001FBFEA
{
public:
	void setup(void *a, void *b);
private:
	void *m_00;
	Rva001FBC43 m_04;
};
class Rva001FC357
{
public:
	void setup(void *a, void *b);
private:
	void *m_00;
	Rva001FBFEA m_04;
};
class Rva001FC451
{
public:
	void setup(void *a, void *b);
private:
	void *m_00;
	Rva001FC357 m_04;
};
