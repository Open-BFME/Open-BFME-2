// cl: /EHsc
// ?rva0050EE23@Rva0050EE23@@QAEHPBDHUCharCompare@@@Z @0x0050EE23
// (53B): StringBase<char> compareNoCase wrapper extracting data/len with
// empty fallback then tail-calling rowed compareRangeNoCase; unblocks 41B.
// Identity via compareRangeNoCase 0x00005841 plus empty string
// the empty-string literal plus caller 0x0050F210; /O1 frameless.

struct CharCompare
{
	char m_unused;
};

int __cdecl compareRangeNoCase(const char *a, int alen, const char *b, int blen, CharCompare tag);
extern "C" unsigned int strlen(const char *s);


class Rva0050EE23
{
public:
	int rva0050EE23(const char *b, int blen, CharCompare tag);
	int rva0050F1F0(const char *b, CharCompare tag);
private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};
	Header *m_data;
};

int Rva0050EE23::rva0050EE23(const char *b, int blen, CharCompare tag)
{
	int alen;
	if (m_data)
		alen = m_data->length;
	else
		alen = 0;
	const char *a;
	if (m_data)
		a = (const char *)&m_data->data[0];
	else
		a = "";
	return compareRangeNoCase(a, alen, b, blen, tag);
}

// Retail 0x0050F1F0 (41B): C-string overload measuring a non-null argument with
// strlen (import thunk 0x00629170) before forwarding to 0x0050EE23.
int Rva0050EE23::rva0050F1F0(const char *b, CharCompare tag)
{
	return rva0050EE23(b, b ? strlen(b) : 0, tag);
}

// Retail 0x0050F841 (28B): free cdecl wrapper supplying a value-initialized
// tag; the tribute page factory 0x00510D98 tests its result against zero.
int __cdecl rva0050F841(Rva0050EE23 *a, const char *b)
{
	return a->rva0050F1F0(b, CharCompare());
}
