// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva004EABB9@Rva004EABB9@@QAE_NXZ, retail 0x004EABB9, 14 bytes.
// Returns 1 when dwords at +0x34 and +0x3C are both zero.
// Evidence: xor-cmp-jne-cmp-jne-inc shape, caller at 0x004E9DF0.
class Rva004EABB9
{
public:
	bool rva004EABB9();
private:
	unsigned char pad[0x34];
	int f34;
	unsigned char pad38[0x3C - 0x38];
	int f3C;
};

bool Rva004EABB9::rva004EABB9()
{
	return f34 == 0 && f3C == 0;
}
