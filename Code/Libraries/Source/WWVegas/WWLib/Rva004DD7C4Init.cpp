// cl: /DNDEBUG /MD /EHsc
//
// ??0Rva004DD7C4@@QAE@XZ @ 0x004DD7C4 31B
// 0x18-byte subobject init: magic -666666 (0xFFF5D3D6) x2 then 0 1 0 0.
// Evidence: caller 0x004DD7E3 constructs three members at +4 +0x1C +0x34
// each via this 31B body; no vptr no calls; unlocks 0x004DD7E3.
class Rva004DD7C4
{
public:
	Rva004DD7C4();
private:
	int m00;
	int m04;
	int m08;
	int m0C;
	int m10;
	int m14;
};
Rva004DD7C4::Rva004DD7C4()
	: m00(-666666)
	, m04(-666666)
	, m08(0)
	, m0C(1)
	, m10(0)
	, m14(0)
{
}
