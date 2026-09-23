// cl: /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target strings, bit vector and overlapping payload copies establish this layout.
// Anonymous union alternatives reproduce the observed member-copy order.
// Original record and payload names are unknown; BFME1 PeerResponse supplied
// the related GameSpy record pattern, without establishing this record's name.
#include <string>
#include <vector>
#include <stddef.h>

struct BfmeOpaqueOwnedRecord492 {
	BfmeOpaqueOwnedRecord492();
	~BfmeOpaqueOwnedRecord492();
	int unknown_00;
	std::string unknown_04;
	std::wstring unknown_10;
	std::string unknown_1c;
	std::string unknown_28;
	std::string unknown_34;
	std::string unknown_40;
	std::string unknown_4c;
	std::string unknown_58;
	std::string unknown_64;
	std::string unknown_70[8];
	unsigned int unknown_d0[10];
	std::string unknown_f8;
	std::vector<bool> unknown_104;
	union {
		struct { int word; } payload_word0;
		struct { int word; } payload_word1;
		struct { int word; } payload_word2;
		struct { bool value; } payload_flag0;
		struct { bool value; } payload_flag1;
		struct { int word; } payload_word3;
		struct { int words[15]; } payload_60;
		struct { int words[53]; } payload_212a;
		struct { bool value; } payload_flag2;
		struct { int words[26]; } payload_104;
		struct { int words[7]; } payload_28;
		struct { int first; int second; } payload_8c;
	};
};

typedef char Record492Extent[
	sizeof(BfmeOpaqueOwnedRecord492) == 492 ? 1 : -1];
typedef char Record492ArrayOffset[
	offsetof(BfmeOpaqueOwnedRecord492, unknown_70) == 0x70 ? 1 : -1];
typedef char Record492RawOffset[
	offsetof(BfmeOpaqueOwnedRecord492, unknown_d0) == 0xd0 ? 1 : -1];
typedef char Record492VectorOffset[
	offsetof(BfmeOpaqueOwnedRecord492, unknown_104) == 0x104 ? 1 : -1];
typedef char Record492PayloadStart[
	offsetof(BfmeOpaqueOwnedRecord492, payload_word0) == 0x118 ? 1 : -1];

template void _STL::_Construct<BfmeOpaqueOwnedRecord492,
	BfmeOpaqueOwnedRecord492>(BfmeOpaqueOwnedRecord492 *,
	const BfmeOpaqueOwnedRecord492 &);

BfmeOpaqueOwnedRecord492::~BfmeOpaqueOwnedRecord492() {}
