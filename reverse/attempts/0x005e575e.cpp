// ?rva005E575E@Rva005E575E@@QAE_NPAX@Z
// partial score=0.91 date=2026-10-05
// cl: /O1 /DNDEBUG /MD
// ?rva005E575E@Rva005E575E@@QAE_NPAX@Z @0x005E575E 68B.
// Slot 7 (offset 0x1C) of vtable RVA 0x00877D90 (class of ??0Rva005E5A38@@QAE@H@Z).
// Evidence: thiscall ret 4 single void* arg; id chain [this+8]+0x18 then +0x54;
// singleton g_009FEF10 find int+NULL rowed 0x002B51F8; NULL check; stdcall
// Rva002B4948Find rowed 0x002B4948 with (player arg NULL); NULL check; tail
// virtual slot 6 ([vtable+0x18]) with found object; false path xor al al.
class Rva002E2903Player;
class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int id, unsigned int *index);
};
extern Rva002BA8F1Logic *g_009FEF10;
void *__stdcall Rva002B4948Find(void *a1, void *a2, void *a3);
struct Rva005E575EIdInner
{
	char m_pad[0x54];
	int m_id54;
};
struct Rva005E575EOuter
{
	char m_pad[0x18];
	Rva005E575EIdInner *m_ptr18;
};
class Rva005E575ESlots
{
public:
	virtual void v0() throw();
	virtual void v1() throw();
	virtual void v2() throw();
	virtual void v3() throw();
	virtual void v4() throw();
	virtual void v5() throw();
	virtual bool v6(void *arg) throw();
};
class Rva005E575E
{
public:
	bool rva005E575E(void *arg);
private:
	int m_00;
	int m_04;
	Rva005E575EOuter *m_08;
};
// ?rva005E575E@Rva005E575E@@QAE_NPAX@Z present-unmatched
bool Rva005E575E::rva005E575E(void *arg)
{
	int id = m_08->m_ptr18->m_id54;
	Rva002E2903Player *player = g_009FEF10->find(id, 0);
	if (player != 0)
	{
		void *found = Rva002B4948Find(player, arg, 0);
		if (found != 0)
			return ((Rva005E575ESlots *)this)->v6(found);
	}
	return false;
}
