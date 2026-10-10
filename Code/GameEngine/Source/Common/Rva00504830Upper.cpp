// cl: /DNDEBUG /MD /EHsc /Oi-
// ?Rva00504830UpperBound@@YAPAURva00504830Item@@PAU1@0PBMEH@Z @ 0x00504830 (64B):
// Upper-bound binary search over 16-byte records keyed by first float.
// len=(last-first); while len>0 { half=len>>1; mid=first+half;
// if mid->key<=*value { first=mid+1; len=len-half-1 } else len=half }
// return first. Evidence: sar 4/shl 4 stride 16; movss/comiss/jbe;
// caller at 0x0050490B pushes 5 args (first last value byte 0); unblocks 0x005048F9.
struct Rva00504830Item
{
	float key;
	char pad[12];
};

Rva00504830Item *__cdecl Rva00504830UpperBound(Rva00504830Item *first, Rva00504830Item *last, const float *value, unsigned char unused1, int unused2)
{
	int len = last - first;
	while (len > 0)
	{
		int half = len >> 1;
		Rva00504830Item *mid = first + half;
		if (mid->key > *value)
		{
			len = half;
		}
		else
		{
			first = mid + 1;
			len = len - half - 1;
		}
	}
	return first;
}

// ?Rva005048F9Forward@@YAPAURva00504830Item@@PAU1@0PBME@Z @ 0x005048F9 (27B):
// Forwards (first last value byte) plus trailing 0 to UpperBound 0x00504830.
// Evidence: 5 pushes then call 0x504830 then add esp 0x14; chain from 0x00504830.
Rva00504830Item *__cdecl Rva005048F9Forward(Rva00504830Item *first, Rva00504830Item *last, const float *value, unsigned char b)
{
	return Rva00504830UpperBound(first, last, value, b, 0);
}

// ?Rva00504870LowerBound@@YAPAURva00504830Item@@PAU1@0PBMEH@Z @ 0x00504870 (64B):
// Lower-bound binary search over 16-byte records keyed by first float.
// len=(last-first); while len>0 { half=len>>1; mid=first+half;
// if mid->key<*value { first=mid+1; len=len-half-1 } else len=half }
// return first. Evidence: sar 4/shl 4 stride 16; movss value/comiss mid/jbe;
// caller at 0x00504926 pushes 5 args; unlocks 0x00504914.
Rva00504830Item *__cdecl Rva00504870LowerBound(Rva00504830Item *first, Rva00504830Item *last, const float *value, unsigned char unused1, int unused2)
{
	int len = last - first;
	while (len > 0)
	{
		int half = len >> 1;
		Rva00504830Item *mid = first + half;
		if (mid->key < *value)
		{
			first = mid + 1;
			len = len - half - 1;
		}
		else
		{
			len = half;
		}
	}
	return first;
}

// ?Rva00504914Forward@@YAPAURva00504830Item@@PAU1@0PBME@Z @ 0x00504914 (27B):
// Forwards (first last value byte) plus trailing 0 to LowerBound 0x00504870.
// Evidence: 5 pushes then call 0x504870 then add esp 0x14; chain from 0x00504870.
Rva00504830Item *__cdecl Rva00504914Forward(Rva00504830Item *first, Rva00504830Item *last, const float *value, unsigned char b)
{
	return Rva00504870LowerBound(first, last, value, b, 0);
}

// Native5049A4..5049C6 RET4: upper-bound wrapper over the sixteen-byte
// range at0/4. A nullable receiver selects the byte at0D, passed in the
// low byte of a four-byte ABI slot. The original comparator type is unknown.
struct Rva00504AB4Key;
class Rva005049A4KeyRange
{
    Rva00504830Item *begin, *end, *capacity;
    unsigned char flagC, comparator;
public:
    Rva00504AB4Key *rva005049A4(const float &value) const;
};
Rva00504AB4Key *Rva005049A4KeyRange::rva005049A4(const float &value) const
{
    const unsigned char *comp = this ? &comparator : 0;
    return (Rva00504AB4Key *)Rva005048F9Forward(begin, end, &value, *comp);
}
