// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc
// ?rva005D061E@Rva005D061E@@QAEHPAG@Z, retail 0x005D061E, 37 bytes.
// Pair copy: first ref-plus-char via rowed Rva005D0602 then second ref via
// rowed copyPayloadTo, returns sum. Evidence: callees rowed; caller 0x005D08AE;
// this+8 second ref matches Rva005D0602 size 8.
// Honest address name; owner unproven.

struct BFME2WideStringRef
{
	const void *m_ptr;
	int copyPayloadTo(unsigned short *dst) const;
};

class Rva005D0602
{
public:
	int rva005D0602(unsigned short *dst);
private:
	BFME2WideStringRef m_ref;
	unsigned short m_extra;
};

class Rva005D061E
{
public:
	int rva005D061E(unsigned short *dst);
private:
	Rva005D0602 m_first;
	BFME2WideStringRef m_second;
};

int Rva005D061E::rva005D061E(unsigned short *dst)
{
	int first = m_first.rva005D0602(dst);
	int second = m_second.copyPayloadTo(dst + first);
	return first + second;
}
