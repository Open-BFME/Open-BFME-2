// cl: /DNDEBUG /MD
//
// HordeContain::rva0046A893, retail 0x0046A893 (130 bytes). Identity: its three
// callers (0x0046FA46, 0x00473125, 0x00473799) are HordeContain slots (vtables
// installed by the pinned HordeContain ctor 0x0046F543, inherited by the matched
// HorseHordeContain) and pass their this; the body queries slot 59 of the
// interface HordeContain carries at +0x11C (the ctor installs a vtable there,
// after the 0x11C-byte TransportContain base). Name by address.
// Body: for a rider, call slot 13 (on yes) or slot 12 (on no) of its +0x254
// interface with 5, then move it from condition bit 7*32+31 to 7*32+30 (yes) or
// back. Retail tests the bits through a pointer to the word and updates the
// member directly: tests through a const pointer to the bits held in a local.

class Rva0010CBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};
// The Object +0x254 interface: slots 12 and 13 take an int.
class Rva0046A893Rider254
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void rva0046A893Slot12(int arg) = 0;
	virtual void rva0046A893Slot13(int arg) = 0;
};
class Object
{
public:
	void rva0028AE6D();
	unsigned char m_pad000[0x10C];
	Rva0010CBits m_conditionBits; // +0x10C
	unsigned char m_pad158[0x254 - 0x158];
	Rva0046A893Rider254 *m_254; // +0x254
};
template <int N> class Rva0046A893Slots : public Rva0046A893Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva0046A893Slots<0>
{
};
// HordeContain's +0x11C interface: slots 0..58 placeholders, slot 59 a bool query.
class Rva0046A893Iface11C : public Rva0046A893Slots<59>
{
public:
	virtual bool rva0046A893Slot59() = 0;
};
class TransportContain
{
public:
	virtual ~TransportContain();
private:
	unsigned char m_pad004[0x11C - 4];
};
class HordeContain : public TransportContain, public Rva0046A893Iface11C
{
public:
	void rva0046A893(Object *rider);
};
void HordeContain::rva0046A893(Object *rider)
{
	if (!rider)
		return;
	const Rva0010CBits *bits = &rider->m_conditionBits;
	if (rva0046A893Slot59())
	{
		rider->m_254->rva0046A893Slot13(5);
		if (bits->test(7 * 32 + 31)) { rider->m_conditionBits.clear(7 * 32 + 31); rider->rva0028AE6D(); }
		if (bits->test(7 * 32 + 30) == 0) { rider->m_conditionBits.set(7 * 32 + 30); rider->rva0028AE6D(); }
	}
	else
	{
		rider->m_254->rva0046A893Slot12(5);
		if (bits->test(7 * 32 + 30)) { rider->m_conditionBits.clear(7 * 32 + 30); rider->rva0028AE6D(); }
		if (bits->test(7 * 32 + 31) == 0) { rider->m_conditionBits.set(7 * 32 + 31); rider->rva0028AE6D(); }
	}
}
