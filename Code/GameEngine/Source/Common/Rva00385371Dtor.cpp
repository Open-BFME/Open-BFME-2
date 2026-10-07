// cl: /MD /EHs
// ??1Gen_uw_00385371@@QAE@XZ @0x00385371 75B composite dtor: members at
// +0x340 via rowed 0x0038454E +0x1B0 via rowed 0x003844D7 +0x08 via rowed
// 0x00385333. Callers 0x3859C2 0x386409 unclaimed thiscall. No vptr store
// so non-virtual QAE. LINK BONUS name Gen_uw_00385371 for 8B waiter.
class Rva00385333
{
public:
	~Rva00385333();
private:
	char m_pad[0x1A0];
};

class Rva003844D7
{
public:
	~Rva003844D7();
private:
	char m_pad[0x190];
};

class Rva0038454E
{
public:
	~Rva0038454E();
private:
	char m_pad[0x208];
};

class Gen_uw_00385371
{
public:
	~Gen_uw_00385371();
private:
	char m_00[8];
	Rva00385333 m_08;
	char m_1A8[8];
	Rva003844D7 m_1B0;
	Rva0038454E m_340;
};

Gen_uw_00385371::~Gen_uw_00385371()
{
}
