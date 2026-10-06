// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva0020E7E8@Rva0020E7E8@@QAEXPAVRva0020E7E8Callback@@@Z, retail 0x0020E7E8,
// 43 bytes.
// Pointer scan at +0x20/+0x24 calling virtual slot 0 on arg with each
// element breaking on false. Caller at 0x00576792.

class Rva0020E7E8Callback
{
public:
	virtual bool invoke(void *p) = 0;
};

class Rva0020E7E8
{
public:
	void rva0020E7E8(Rva0020E7E8Callback *cb);

private:
	unsigned char m_pad[0x20];
	void **m_begin;
	void **m_end;
};

void Rva0020E7E8::rva0020E7E8(Rva0020E7E8Callback *cb)
{
	void **begin = m_begin;
	void **end = m_end;
	for (; begin != end; ++begin) {
		void *elem = *begin;
		if (!cb->invoke(elem))
			break;
	}
}
