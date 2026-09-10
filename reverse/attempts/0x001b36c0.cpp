// ?Set_Flag@LineGroupClass@@QAEXW4FlagsType@1@_N@Z
// partial score=0.75 date=2026-09-09
// cl: /G7 /O1 /DNDEBUG /MD
//
// LineGroupClass::Set_Flag, retail 0x001B36C0, 34 bytes.
// Kept out of linegrp.cpp: that TU tests the bool first and emits
// a different shl/or/and layout. Retail computes 1<<flag in edx,
// then cmp-byte [esp+8],0. Flags lives at +0x2C (same as Get_Flag).

class LineGroupClass
{
	unsigned char _M_layout[0x2C];
	volatile int Flags;

public:
	enum FlagsType
	{
		TRANSFORM = 0
	};

	void Set_Flag(FlagsType flag, bool on);
};

void LineGroupClass::Set_Flag(FlagsType flag, bool on)
{
	int mask = 1 << flag;
	if (on)
		Flags |= mask;
	else
		Flags &= ~mask;
}
