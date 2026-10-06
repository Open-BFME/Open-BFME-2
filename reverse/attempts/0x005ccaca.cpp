// ?rva005CCACA@Rva005CCACA@@QAEXH@Z
// partial score=0.93 date=2026-10-06
// cl: /MD
// ?rva005CCACA@Rva005CCACA@@QAEXH@Z @0x005CCACA 34B evidence: calls rowed ??_9@$BBE@AE; tail-jmp target of 0x005CCB73
// Setter with change notification: if new value differs from cached +0xC, notify listener at +4 via its +0x14 virtual then cache it.
class Rva005CCACAListener
{
public:
	virtual void notify00(int value);
	virtual void notify04(int value);
	virtual void notify08(int value);
	virtual void notify0C(int value);
	virtual void notify10(int value);
	virtual void notify14(int value);
};
class Rva005CCACA
{
public:
	void rva005CCACA(int value);
private:
	char m_pad0[4];
	Rva005CCACAListener *m_listener;
	char m_pad1[4];
	int m_cached;
};
void Rva005CCACA::rva005CCACA(int value)
{
	if (value == m_cached)
		return;
	Rva005CCACAListener *listener = m_listener;
	if (listener)
		(listener->*(&Rva005CCACAListener::notify14))(value);
	m_cached = value;
}
