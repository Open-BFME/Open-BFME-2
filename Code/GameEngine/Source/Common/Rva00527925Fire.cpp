// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?Rva00527925Fire@@YAHPAX0PBD1PBM@Z @ 0x00527925 (106B): free float Apt firer via rowed Get 0x002228E8 plus rowed AptCall 0x00222B19 and empty fallback g_Rva0107301CEmptyString. Evidence: callers pass level prefix function plus float; callees rowed; neighbours Rva00527890Move and Rva0052798FConcat.
#include "ascii_string.h"

AsciiString Rva002228E8Get(float val);

class Rva00222A8BTarget
{
public:
	int rva00222B19(void *level, const char *prefix, const char *function, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};

__forceinline const char *GetStr00527925(const AsciiString &s)
{
	char *t = *(char * *)(void *)&s;
	return t ? t + 8 : "";
}

int Rva00527925Fire(void *target, void *level, const char *prefix, const char *function, const float *val)
{
	return ((Rva00222A8BTarget *)target)->rva00222B19(level, prefix, function, 1, GetStr00527925(Rva002228E8Get(*val)), 0, 0, 0, 0);
}
