// ?Set_Flag@LineGroupClass@@QAEXW4FlagsType@1@_N@Z
// partial score=0.85 date=2026-09-10
// cl: /O1 /MD
//
// LineGroupClass::Set_Flag, retail 0x001B36C0, 34 bytes.
// Dedicated TU so linegrp.cpp keeps its other matched bodies.
// Flags dword lives at +0x2C.

class LineGroupClass
{
public:
	enum FlagsType {
		SORT,
		DISABLE_BOUNDING_BOX,
		DISABLE_BOUNDING_SPHERE,
		DISABLE_POINT_RENDERING
	};

	void Set_Flag(FlagsType flag, bool on);

private:
	unsigned char Pad[0x2C];
	unsigned Flags;
};

void LineGroupClass::Set_Flag(FlagsType flag, bool on)
{
	unsigned mask = 1u << flag;
	if (on)
		Flags |= mask;
	else
		Flags &= ~mask;
}
