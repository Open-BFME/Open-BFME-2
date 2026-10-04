// cl: /O1
// BFME1 donor1281192f682ce6f29b8f06b7daea4b5e8fdfbb24,
// game/GameEngine/Source/Common/Bfme5TinySix3.cpp, compiled /O1.
// Target Ghidra00042FE4/20B independently proves a pointer at+40,
// pointee flag byte+10 mask4, and full EAX results0/1. Constness and
// the int spelling are donor/source inferences; original names and the
// flag's purpose remain unknown. The full donor unit places only this body.
class Rva00042FE4Flags
{
public:
	unsigned char reserved[0x10];
	unsigned char flags;
};

class Rva00042FE4
{
public:
	int test() const;
private:
	unsigned char reserved[0x40];
	Rva00042FE4Flags *held;
};

int Rva00042FE4::test() const
{
	Rva00042FE4Flags *value = held;
	if (value && (value->flags & 4))
		return 1;
	return 0;
}
