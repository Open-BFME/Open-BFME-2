// cl: /DNDEBUG /MD
// ?rva00214D4A@Rva00214D4A@@QAEMXZ retail 0x00214D4A 15 bytes.
// Float factor from the writable global (offset 0xD40) scaled by the member at
// +0x18 (fld global; fmul member). Single unclaimed caller at 0x00096B4C;
// neighbours are the just-landed 0x00214ADC dtor and 0x00214D59 pack.
class GlobalData
{
public:
	char m_pad000[0xD40];
	float m_valueD40;
};

extern GlobalData *TheWritableGlobalData;

class Rva00214D4A
{
public:
	float rva00214D4A();

private:
	char m_pad00[0x18];
	float m_factor18;
};

float Rva00214D4A::rva00214D4A()
{
	return TheWritableGlobalData->m_valueD40 * m_factor18;
}
