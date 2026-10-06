// ?rva002907A1@Object@@QAE_NXZ
// Landed from banked partial (score 0.92). Two changes close it.
// The bit8 test reads the mask as a volatile unsigned and takes the second
// byte through a named local: retail loads all four bytes and shifts
// (mov eax,[esi] / shr eax,0x8 / test al,0x1), and without volatile MSVC
// narrows straight to a DWORD test against 0x100.
// The branch is written the other way round -- the popcount check as the taken
// arm and the bit8-clear return as the else -- because retail's je at +0x2D
// falls THROUGH into the popcount call. Both prior banks read the polarity as
// a separate defect; it is the same edit as the load form.
// cl: /DNDEBUG /MD
// ?rva002907A1@Object@@QAE_NXZ @ 0x002907A1 107B: chain from 0x0028F528 popcount;
// Object disabled-mask gate over +0x1C8 BitFlags<11>::any via rowed 0x0023C58B
// then bit8 and popcount==1 via rowed 0x0028F528 then !isKindOf(0x81) then
// template+0x113&0x20 template+0x108&4 then !testStatus(0x3B). Unblocks 59.
// Prev/next Object Rva TUs same flags. 40+ callers prove Object owner.
typedef bool Bool;

enum KindOfType
{
	KINDOF_DUMMY = 0
};

enum ObjectStatusTypes
{
	STATUS_DUMMY = 0
};

template <int N>
class BitFlags
{
public:
	bool any() const;
};

class Rva0028F528
{
public:
	int rva0028F528();
};

struct ThingTemplate907A1
{
	unsigned char m_pad[0x120];
};

class Object
{
public:
	bool rva002907A1();
	Bool isKindOf(KindOfType kind) const;
	Bool testStatus(ObjectStatusTypes bit) const;
	bool rva0028F518();
private:
	unsigned char m_pad00[4];
	ThingTemplate907A1 *m_template;
	unsigned char m_pad08[0x1C8 - 0x08];
	BitFlags<11> m_disabled;
};

bool Object::rva002907A1()
{
	ThingTemplate907A1 *t = m_template;
	if ((t->m_pad[0x108] & 4) != 0)
		return false;
	BitFlags<11> *mask = &m_disabled;
	if (mask->any())
	{
		unsigned char byte2 = (unsigned char)(*(const volatile unsigned *)mask >> 8);
		if ((byte2 & 1u) != 0)
		{
			if (((Rva0028F528 *)mask)->rva0028F528() != 1)
				return false;
		}
		else
		{
			return false;
		}
	}
	if (isKindOf((KindOfType)0x81))
		return false;
	if ((t->m_pad[0x113] & 0x20) != 0)
	{
		if (testStatus((ObjectStatusTypes)0x3B))
			return false;
	}
	return true;
}
