// cl: /DNDEBUG /MD /EHsc
// ?rva004B7ED9@AudioLoopUpgrade@@QAEPAVBfmeFixedStorage002CF0F0@@PAV2@@Z 0x004B7ED9 40: slot 19 mask init.
// Evidence: vtable 0x00858C70 slot 19; callees rowed BitFlags 0x5E5963 and FixedStorage copy 0x2CF0F0; donor AudioLoopUpgradeCtorModuleFactory.
typedef int Int;
typedef unsigned int UnsignedInt;
template <int NUM_BITS> class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};
	BitFlags(BogusInitType init, Int b0, Int b1);
private:
	UnsignedInt m_words[1];
};
class BfmeFixedStorage002CF0F0
{
	char m_bytes[4];
public:
	__declspec(nothrow) BfmeFixedStorage002CF0F0(const BfmeFixedStorage002CF0F0 &other);
};
class AudioLoopUpgrade
{
public:
	BfmeFixedStorage002CF0F0 *rva004B7ED9(BfmeFixedStorage002CF0F0 *out);
};
BfmeFixedStorage002CF0F0 *AudioLoopUpgrade::rva004B7ED9(BfmeFixedStorage002CF0F0 *out)
{
	BitFlags<11> tmp(BitFlags<11>::kInit, 2, 5);
	*(UnsignedInt *)&tmp = ~*(UnsignedInt *)&tmp;
	out->BfmeFixedStorage002CF0F0::BfmeFixedStorage002CF0F0(*(BfmeFixedStorage002CF0F0 *)&tmp);
	return out;
}
