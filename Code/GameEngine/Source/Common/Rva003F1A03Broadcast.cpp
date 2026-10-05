// cl: /O1 /Oy- /DNDEBUG /MD /GX-
// ?rva003F1A03@Rva003F1A03@@QAEXP8Rva003F119CListener@@AEXPAXHH@Z0HH@Z @0x003F1A03 34B
// Evidence: forwards its 4 args to Rva003F119CList::forEach 0x003F119C twice, first on this+4 then tail on global 0x00E02E88; callers 0x003F1AFF 0x003F2A8C; row for forEach in Rva003F0CB9ListenerWalks.cpp.
class Rva003F119CListener
{
public:
	virtual void notify(void *, int, int);
};

class Rva003F119CList
{
public:
	void forEach(void (Rva003F119CListener::*notify)(void *, int, int), void *arg, int value, int extra);

private:
	Rva003F119CListener **m_begin;
	Rva003F119CListener **m_end;
	Rva003F119CListener **m_capacity;
	unsigned int m_index;
};

extern Rva003F119CList g_00E02E88;

struct Rva003F1A03
{
	int m_00;
	Rva003F119CList m_04;
	void rva003F1A03(void (Rva003F119CListener::*notify)(void *, int, int), void *arg, int value, int extra);
};

void Rva003F1A03::rva003F1A03(void (Rva003F119CListener::*notify)(void *, int, int), void *arg, int value, int extra)
{
	m_04.forEach(notify, arg, value, extra);
	g_00E02E88.forEach(notify, arg, value, extra);
}
