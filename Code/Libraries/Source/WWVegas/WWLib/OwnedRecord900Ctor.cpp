// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0BfmeRecordOwner900@@QAE@XZ, retail 0x004CB74C, 162 bytes.
// Default ctor for the 900-byte owner: two 0x80 clears at +0/+0x80 via rowed
// clear80 0x001EAE6F, two E16 vectors at +0x100/+0x10C via rowed Vector_base
// 0x00211E58, two 0x4C members at +0x118/+0x164 via rowed 0x00042526, array
// at +0x1B0 via rowed 0x00254FE4, map at +0x370 via rowed 0x0024613C, then
// zeroes +0x37C/+0x380-382. Layout from copy TU OwnedRecord900Copy plus
// retail offsets; E16 stands in for 16-byte vector element (same 12B base).
// Evidence: callees all rowed; prev/next same class; caller at 0x004CBB72.
#include <vector>
#include <map>

class Rva001EAE6FHelper
{
public:
	Rva001EAE6FHelper() { clear80(); }
	Rva001EAE6FHelper *clear80();
private:
	char m_pad[0x80];
};

struct BfmeE16
{
	float x;
	float y;
	float z;
	float w;
};

class Rva0042526Member
{
public:
	Rva0042526Member();
private:
	unsigned char m_pad[0x4C];
};

struct VoiceSlot900
{
	VoiceSlot900();
	~VoiceSlot900();
	unsigned char m_data[8];
};

class Rva00254FE4Member
{
public:
	Rva00254FE4Member();
private:
	VoiceSlot900 m_slots[56];
};

struct BfmePod8
{
	int a[2];
};

struct BfmeRecordOwner900
{
	Rva001EAE6FHelper fixed_000;
	Rva001EAE6FHelper fixed_080;
	_STL::vector<BfmeE16> strings_100;
	_STL::vector<BfmeE16> strings_10C;
	Rva0042526Member fixed_118;
	Rva0042526Member fixed_164;
	Rva00254FE4Member records_1B0;
	_STL::map<int, BfmePod8, _STL::less<int>, _STL::allocator<_STL::pair<const int, BfmePod8> > > tree_370;
	unsigned int unknown_37C;
	unsigned char unknown_380;
	unsigned char unknown_381;
	unsigned char unknown_382;
	BfmeRecordOwner900();
};

BfmeRecordOwner900::BfmeRecordOwner900()
	: unknown_37C(0)
	, unknown_380(0)
	, unknown_381(0)
	, unknown_382(0)
{
}
