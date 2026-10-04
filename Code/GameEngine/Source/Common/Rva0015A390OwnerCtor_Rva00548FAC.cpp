// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Donor Rva0015A390OwnerCtor.cpp: the Bucket ctor is inline in the donor's
// class declaration (`Rva0015A390Bucket() : dword_0(0) {}`); only that body is
// emitted here, out-of-line, so the donor's 322-byte Owner ctor is omitted.
#include <string.h>

class Rva0015A390Inner
{
public:
	Rva0015A390Inner() { memset(this, 0, sizeof(*this)); }

	int dword_0;
	int dword_4;
	int dword_8;
	int dword_c;
	int dword_10;
	int dword_14;
};

class Rva0015A390Bucket
{
public:
	Rva0015A390Bucket();

	int dword_0;
	Rva0015A390Inner inner_4;
};

Rva0015A390Bucket::Rva0015A390Bucket() : dword_0(0) {}
