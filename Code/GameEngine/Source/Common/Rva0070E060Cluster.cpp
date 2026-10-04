// cl: /O2 /MD /EHsc
// Rva0070E060::rva0070E060, retail 0x0070E060 (148 B).
// Byte-flag getter plus interface lookup of the same table class as the rowed
// sibling Rva0070DFF0 0x0070DFF0: writes the low byte of the +0x1C flag to the
// out pointer, and when that low byte is non-zero builds the "__INTERFACES__"
// EAStringC key, queries the embedded +8 table through the pinned
// bfmeLookup1279 0x0070B380 and returns the hit checked-cast to an array value
// (rva006DCFA0 0x006DCFA0).  The flag is a dword whose low byte is masked; the
// call targets and the +8/+0x1C offsets are target evidence.
class BfmeNode1279;
struct BfmeKey1279;

class EAStringC
{
public:
	EAStringC(const char *s);
	~EAStringC();
};

class BfmeAptValue006DCD20
{
public:
	BfmeAptValue006DCD20 *rva006DCFA0();
};

class BfmeLookup1279
{
public:
	BfmeNode1279 *bfmeLookup1279(BfmeKey1279 &key);
};

class Rva0070B380
{
public:
	void *lookup(const EAStringC &key);
};

class Rva0070E060
{
public:
	BfmeAptValue006DCD20 *rva0070E060(int *out);

private:
	char m_pad[8];
	BfmeLookup1279 m_table;	// +8
	char m_pad2[0x1c - 8 - 1];
	unsigned int m_flag;	// +0x1C
};

BfmeAptValue006DCD20 *Rva0070E060::rva0070E060(int *out)
{
	*out = m_flag & 0xff;
	if ((m_flag & 0xff) > 0)
	{
		EAStringC key("__INTERFACES__");
		return ((BfmeAptValue006DCD20 *)((Rva0070B380 *)&m_table)->lookup(key))->rva006DCFA0();
	}
	return 0;
}
