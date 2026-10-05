// cl: /O2 /MD
// ?rva006E0AC0@Rva006E0AC0@@QAEHXZ retail 0x006E0AC0 96B
// Evidence: virtual slot 0xC returns hash with flags at +0x10 like AptCIH neighbours; loop over 8-byte table 0xDDC2E8-0xDDC370 via GetString and AptValue findChild; caller 0x006E2EE0
struct AptNativeHash
{
	unsigned char _pad[16];
	int m_10;
};
class EAStringC;
EAStringC *Rva0070B4F0GetString(int v);
struct Rva006E0AC0Entry
{
	int m_mask;
	int m_str;
};
extern Rva006E0AC0Entry g_00DDC2E8[];
struct BfmeW1229
{
	const char *m_bfme00;
	int m_bfme04;
};
extern BfmeW1229 g_bfmeWords1229[];
class AptValue
{
public:
	AptValue *findChild(const EAStringC *s, AptValue *a);
};
class Rva006E0AC0
{
	virtual void u0();
	virtual void u1();
	virtual void u2();
	virtual AptNativeHash *GetNativeHashVirtual();
public:
	int rva006E0AC0();
};

int Rva006E0AC0::rva006E0AC0()
{
	int done = 0;
	AptNativeHash *hash = GetNativeHashVirtual();
	Rva006E0AC0Entry *p = g_00DDC2E8;
	do
	{
		if ((hash->m_10 & p->m_mask) == 0 && (p->m_mask & 0xbfdff) != 0)
		{
			if (((AptValue *)this)->findChild(Rva0070B4F0GetString(p->m_str), 0) != 0)
			{
				hash->m_10 |= p->m_mask;
				if ((p->m_mask & 0xbfcf8) != 0)
					done = 1;
			}
		}
		++p;
	} while ((int)p < (int)g_bfmeWords1229);
	return done;
}
