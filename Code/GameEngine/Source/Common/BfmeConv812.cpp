// Two guarded accessors through a sub-object.
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/BfmeConv812.cpp); trimmed to the two T1
// bodies the sweep places.

// The matched getter at 0x005C4ACD returns the opaque +0x2C pointer that these
// callers view as BfmeSubEHA; both symbols use a no-argument pointer-return ABI.
#pragma comment(linker, "/alternatename:?bfmeGetEHA@BfmeObjEHA@@QAEPAUBfmeSubEHA@@XZ=?winGetUserData@GameWindow@@QAEPAXXZ")

struct BfmeSubEHA
{
	char m_bfmeFlag;
	unsigned char m_bfmePad[3];
	void *m_bfmeP;
	void *m_bfmeQ;
};

class BfmeObjEHA
{
public:
	BfmeSubEHA *bfmeGetEHA();
};

void *bfmeGoEHAa(BfmeObjEHA *o)
{
	if (o)
	{
		BfmeSubEHA *s = o->bfmeGetEHA();
		if (s && s->m_bfmeFlag)
			return s->m_bfmeP;
	}
	return 0;
}

void *bfmeGoEHAb(BfmeObjEHA *o)
{
	if (o)
	{
		BfmeSubEHA *s = o->bfmeGetEHA();
		if (s && s->m_bfmeFlag)
			return s->m_bfmeQ;
	}
	return 0;
}

// Whole BFME1 donor: 5cc75ddda6455c338a5068307e587a793f96d6b3,
// game/GameEngine/Source/Common/BfmeConv433.cpp. Its guessed helper names
// are replaced by this home's existing pointer-return accessor ABI binding.
// Target A2128/15 reads receiver+0, calls the rowed 5C4ACD getter, reads result+8
// and tail-calls that same getter; its native predecessor ends at A2127 and
// next entry begins A2137. Only those pointer reads and EAX return are modelled.
// Wrapper owner/original prototype and full pointee layouts remain unknown.
class Rva000A2128
{
public:
    void *readNestedUserData();
private:
    BfmeObjEHA *m_context;
};
void *Rva000A2128::readNestedUserData()
{
    return ((BfmeObjEHA*)m_context->bfmeGetEHA()->m_bfmeQ)->bfmeGetEHA();
}
