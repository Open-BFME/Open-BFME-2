// cl: /Oy- /DNDEBUG /MD /GX-
// ?rva003F1A25@Rva003F1A25@@QAEXP8Rva003F11C7Listener@@AEXPAXH@Z0H@Z @0x003F1A25 31B
// Evidence: forwards its 3 args to Rva003F11C7List::forEach 0x003F11C7 twice first on this+4 then tail on global 0x00E02E88; callers 0x003F1C80 0x003F1CC6; row for forEach in Rva003F0CB9ListenerWalks.cpp; mirrors Rva003F1A03Broadcast.cpp.
class Rva003F11C7Listener
{
public:
	virtual void notify(void *, int);
};

class Rva003F11C7List
{
public:
	void forEach(void (Rva003F11C7Listener::*notify)(void *, int), void *arg, int value);

private:
	Rva003F11C7Listener **m_begin;
	Rva003F11C7Listener **m_end;
	Rva003F11C7Listener **m_capacity;
	unsigned int m_index;
};

extern Rva003F11C7List g_00E02E88;

struct Rva003F1A25
{
	int m_00;
	Rva003F11C7List m_04;
	void rva003F1A25(void (Rva003F11C7Listener::*notify)(void *, int), void *arg, int value);
};

void Rva003F1A25::rva003F1A25(void (Rva003F11C7Listener::*notify)(void *, int), void *arg, int value)
{
	m_04.forEach(notify, arg, value);
	g_00E02E88.forEach(notify, arg, value);
}
