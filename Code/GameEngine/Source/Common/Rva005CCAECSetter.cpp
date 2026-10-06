// cl: /MD
// ?rva005CCAEC@Rva005CCAEC@@QAEX_N@Z @0x005CCAEC 34B evidence: calls rowed ??_9@$BBM@AE; tail-jmp target of 0x005CCB7B
// Bool setter with change notification: if new value differs from cached +0x21, notify listener at +4 via its +0x0C virtual then cache it.
class Rva005CCAECListener
{
public:
	virtual void notify00(bool value);
	virtual void notify04(bool value);
	virtual void notify08(bool value);
	virtual void notify0C(bool value);
	virtual void notify10(bool value);
	virtual void notify14(bool value);
	virtual void notify18(bool value);
	virtual void notify1C(bool value);
};
class Rva005CCAEC
{
public:
	void rva005CCAEC(bool value);
private:
	char m_pad0[4];
	Rva005CCAECListener *m_listener;
	char m_pad1[0x21 - 0x08];
	bool m_cached;
};
void Rva005CCAEC::rva005CCAEC(bool value)
{
	if (value == m_cached)
		return;
	Rva005CCAECListener *listener = m_listener;
	if (listener)
		(listener->*(&Rva005CCAECListener::notify1C))(value);
	m_cached = value;
}
