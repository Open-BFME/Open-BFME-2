// Ported from the BFME1 reconstruction; this body has a unique byte-verified
// placement in BFME2 at RVA 0x006BE160.
typedef int Int;
typedef bool Bool;

class BfmeThingTemplateShadowSelector
{
public:
	Bool usePluralShadowName() const;

private:
	char m_pad[0x2c];
	const char * volatile m_begin;
	const char *m_end;
};

Bool BfmeThingTemplateShadowSelector::usePluralShadowName() const
{
	Int count = (Int)(m_end - m_begin) / 36;
	if (count != 1)
		return false;
	return *(const Int *)m_begin == 2;
}
