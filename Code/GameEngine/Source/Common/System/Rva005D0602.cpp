// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc
// ?rva005D0602@Rva005D0602@@QAEHPAG@Z, retail 0x005D0602, 28 bytes.
// Ref-plus-char copy: copies BFME2WideStringRef payload via rowed
// copyPayloadTo then appends word at this+4 and returns len+1.
// Evidence: callee rowed 0x0021AC32; caller 0x005D061E passes this with
// second ref at this+8; prev/next neighbours in System.
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

int Rva005D0602::rva005D0602(unsigned short *dst)
{
	int len = m_ref.copyPayloadTo(dst);
	dst[len] = m_extra;
	return len + 1;
}
