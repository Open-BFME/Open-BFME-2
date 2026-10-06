// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Address-derived owners for small bodies formerly in gen_asm d_0087dd30.asm.
// No caller, vtable or string names them; members describe only the bytes.

// 0x0087DD30: byte +1 greater than the argument
class Rva0087DD30Body
{
public:
	bool body(int value) const;

private:
	unsigned char m_byte0;
	unsigned char m_byte1;
};

// ?body@Rva0087DD30Body@@QBE_NH@Z
bool Rva0087DD30Body::body(int value) const
{
	return m_byte1 > value;
}
