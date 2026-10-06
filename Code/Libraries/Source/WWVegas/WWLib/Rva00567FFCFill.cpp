// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?Rva00567FFCFill@@YAPAVRva00567BD7@@PAV1@IPBV1@@Z @0x00567FFC 37B
// Evidence: fills [dst,dst+count) with value via rowed ?Rva00567F91Copy (chain from 0x00567F91);
// dst+=0x10 per step (sizeof Rva00567BD7), returns end; caller 0x005680EF.
struct Rva00567BD7Ref
{
	int m_0;
	int m_ref;
};

class Rva00567BD7
{
public:
	Rva00567BD7(const Rva00567BD7 &that);
	int m_0;
	unsigned char m_4;
	Rva00567BD7Ref *m_8;
	unsigned char m_C;
};

void Rva00567F91Copy(Rva00567BD7 *dst, const Rva00567BD7 *src);

Rva00567BD7 *Rva00567FFCFill(Rva00567BD7 *dst, unsigned int count, const Rva00567BD7 *value)
{
	Rva00567BD7 *cur = dst;
	while (count > 0) {
		Rva00567F91Copy(cur, value);
		++cur;
		--count;
	}
	return cur;
}
