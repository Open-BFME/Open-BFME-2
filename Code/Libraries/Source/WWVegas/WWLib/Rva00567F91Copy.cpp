// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?Rva00567F91Copy@@YAXPAVRva00567BD7@@PBV1@@Z @0x00567F91 18B
// Evidence: conditional copy-construct via rowed ??0Rva00567BD7@@QAE@ABV0@@Z; caller 0x00567FFC.
// Chain from 0x00567BD7.
class Rva00567BD7
{
public:
	Rva00567BD7(const Rva00567BD7 &that);
};

void Rva00567F91Copy(Rva00567BD7 *dst, const Rva00567BD7 *src)
{
	if (dst != 0)
		dst->Rva00567BD7::Rva00567BD7(*src);
}
