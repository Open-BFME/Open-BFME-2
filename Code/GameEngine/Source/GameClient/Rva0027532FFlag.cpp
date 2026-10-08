// cl: /DNDEBUG /MD /EHsc
// ?rva0027532F@Rva0027532F@@QAE_N_N@Z 0x0027532F 71B. Predicate on the object at
// +0xFC: a disabled-mask test (bit 2 of +0x437 when the flag is set), then the
// BitFlags any() at +0x1C8 pinned to 0x0023C58B, then bits 0x24 / 0x40 of the mask word.
class Rva00275327Bits
{
public:
	bool rva0023C58B() const;
	unsigned int m_word;
};

class Rva00275327Obj
{
public:
	unsigned char m_pad00[0x1C8];
	Rva00275327Bits m_bits; // +0x1C8
	unsigned char m_pad1CC[0x437 - 0x1CC];
	unsigned char m_flags437; // +0x437
};

class Rva0027532F
{
public:
	bool rva0027532F(bool flag);
private:
	unsigned char m_pad00[0xFC];
	Rva00275327Obj *m_obj; // +0xFC
};

bool Rva0027532F::rva0027532F(bool flag)
{
	Rva00275327Obj *obj = m_obj;
	if (obj)
	{
		if (flag && (obj->m_flags437 & 2))
			return false;
		if (obj->m_bits.rva0023C58B())
		{
			unsigned int word = obj->m_bits.m_word;
			if (word & 0x24)
				return false;
			if (!flag)
				return true;
			if (word & 0x40)
				return false;
		}
	}
	return true;
}
