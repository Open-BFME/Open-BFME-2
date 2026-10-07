// cl: /MD /O1 /arch:SSE /G7
// ?rva002C7253@Rva002C7253@@QBE_NXZ @0x002C7253 25B
// Checks six consecutive pointers at +0x14 through +0x28; caller 0x0033A951
// iterates these records in 0x368-byte steps. Class identity is unproven.
class Rva002C7253
{
public:
	bool rva002C7253() const;

private:
	unsigned char m_pad00[0x14];
	const void *m_entries[6];
};

bool Rva002C7253::rva002C7253() const
{
	for (int i = 0; i < 6; ++i)
	{
		if (m_entries[i] != 0)
			return true;
	}
	return false;
}
