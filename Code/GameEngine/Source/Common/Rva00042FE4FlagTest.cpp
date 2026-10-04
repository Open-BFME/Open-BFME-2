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

// Separate target predicate: complete Ghidra entry 300021/84, RET4 at
// 300072, with no calls or globals. Native reads the receiver's first
// word and argument bytes +24/+25/+26, then tests masks 1/2, 4/8 and
// 10/20. Rva0044F630FlagTest.cpp at BFME1 revision
// 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24 supplies the full clean
// source/control-flow lead; /O1 reproduces this target's three return
// arms, including the redundant byte tests. These are distinct partial
// address views: neither an original owner nor a shared owner with the
// predicate above is established. Byte meanings and unused layout are
// unknown; bool spelling carries only the observed zero/nonzero test.
struct Rva00300021Argument
{
    unsigned char reserved[0x24];
    bool byte24;
    bool byte25;
    bool byte26;
};

class Rva00300021Flags
{
public:
    bool test(const Rva00300021Argument *argument) const;
private:
    unsigned int flags;
};

bool Rva00300021Flags::test(const Rva00300021Argument *argument) const
{
    if (!(((flags & 1) && argument->byte26) ||
          ((flags & 2) && !argument->byte26)))
        return false;

    return !((argument->byte24 && (flags & 4)) ||
             (!argument->byte24 && (flags & 8)) ||
             (argument->byte25 && (flags & 0x10)) ||
             (!argument->byte25 && (flags & 0x20)));
}
