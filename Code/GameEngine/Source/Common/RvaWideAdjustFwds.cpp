// cl: /O1 /G7 /arch:SSE /MD
// Nine wide-adjust forwarders (11B each): add ecx, IMM32 then tail-jump a
// callee with the adjusted this; stack args (if any) pass through to the
// callee, which cleans them (thiscall). Spelled as explicit
// adjust-and-forward casts so no member layout is asserted.
// 0x0023D075 (+0x184 -> 0x0040D380, opaque pin), 0x0023D080 (+0x184 ->
// 0x0040D396, opaque pin), 0x0023D08B (+0x184 -> 0x0040FAFE, opaque pin),
// 0x0023D0AC (+0x184 -> 0x0040D3E8, opaque pin), 0x0023D0B7 (+0x184 ->
// 0x0040D3FF, opaque pin; row keeps the peer GameLogic int(void) pin),
// 0x0023D0C2 (+0x184 -> 0x0040D280, opaque thiscall-view alias pin; same
// body as the rowed stdcall Rva0040D280Set; row keeps the peer GameLogic
// void(Object*,int) pin), 0x0028BC4D (+0x330 -> rowed rva002C7474, no pin;
// row keeps the peer Object pin), 0x002E2F39 (+0x1A8 -> 0x002E2D10, opaque
// pin), 0x004EC072 (+0x90 -> 0x0059A71C, opaque thiscall-view alias pin;
// same body as the rowed Rva0059A71C::rva).
// Wrapper arities follow the peer pins where present, else the callee body
// evidence (all five 0x40Dxxx callees read one stack arg; 0x40D3FF and the
// pins show the rest). New names are address-derived.
// One ledger row per forwarder.

class Object;
class AsciiString;
class ArmySummarySystem {public:const AsciiString *GetArmyNameByID(int);const AsciiString *GetArmyBannerByID(int);};

class Rva0040D380Sub
{
public:
	int method(int value);
};

class Rva0040D396Sub
{
public:
	int method(int value);
};

class Rva0040FAFESub
{
public:
	int method(int value);
};

class Rva0040D3B6Sub
{
public:
	int method(int value);
};

class Rva0040D3E8Sub
{
public:
	int method(int value);
};

class Rva0040D3FFSub
{
public:
	int method();
};

class Rva0040D280Sub
{
public:
	void method(Object *obj, int value);
};

class Rva002C7474
{
public:
	void rva002C7474();
};

class Rva002E2D10Sub
{
public:
	int method(int value);
};

class Rva0059A71CSub
{
public:
	void method(void *arg);
};

struct Rva0040E6D6Arg;
class Rva0040E6D6Host
{
public:
	void __fastcall forwardFrom(int unused, Rva0040E6D6Arg *arg);
};

class GameLogic
{
public:
	void __fastcall rva0023CFFC(int unused, Rva0040E6D6Arg *arg);
	const AsciiString *rva0023D05F(int value);
 const AsciiString *rva0023D06A(int value);
	int rva0023D075(int value);
	int rva0023D080(int value);
	int rva0023D08B(int value);
	int rva0023D096(int value);
	int rva0023D0AC(int value);
	int rva0023D0B7();
	void rva0023D0C2(Object *obj, int value);
};

class Object
{
public:
	void rva0028BC4D();
};

class Rva002E2F39Owner
{
public:
	int fwd(int value);
};

class Rva004EC072Owner
{
public:
	void fwd(void *arg);
};

void __fastcall GameLogic::rva0023CFFC(int unused, Rva0040E6D6Arg *arg)
{
	((Rva0040E6D6Host *)((char *)this + 0x184))->forwardFrom(unused, arg);
}

int GameLogic::rva0023D075(int value)
{
	return ((Rva0040D380Sub *)((char *)this + 0x184))->method(value);
}

int GameLogic::rva0023D080(int value)
{
	return ((Rva0040D396Sub *)((char *)this + 0x184))->method(value);
}

int GameLogic::rva0023D08B(int value)
{
	return ((Rva0040FAFESub *)((char *)this + 0x184))->method(value);
}

int GameLogic::rva0023D096(int value)
{
	return ((Rva0040D3B6Sub *)((char *)this + 0x184))->method(value);
}

int GameLogic::rva0023D0AC(int value)
{
	return ((Rva0040D3E8Sub *)((char *)this + 0x184))->method(value);
}

// GameLogic::rva0023D0B7 is defined with its retail-matched body in Code/GameEngine/Source/Common/RvaMixedMemberForwarders.cpp (0x0023D0B7).

void GameLogic::rva0023D0C2(Object *obj, int value)
{
	((Rva0040D280Sub *)((char *)this + 0x184))->method(obj, value);
}


void Rva004EC072Owner::fwd(void *arg)
{
	((Rva0059A71CSub *)((char *)this + 0x90))->method(arg);
}

// WB D0B960 calls named ArmySummarySystem::GetArmyNameByID; native
//23D05F..23D06A adjusts the GameLogic receiver by184 and tail-jumps
//40D34C. The outer method spelling remains unknown; return is the native
//stable AsciiString pointer. Existing provider owner is renamed rather
//than retaining a second alias at the same address.
const AsciiString *GameLogic::rva0023D05F(int value) {
 return ((ArmySummarySystem*)((char*)this+0x184))->GetArmyNameByID(value);
}

// WB D0B980 calls named ArmySummarySystem::GetArmyBannerByID. Retail
//23D06A..23D075 uses the same GameLogic+184 member and26B provider40D366.
const AsciiString *GameLogic::rva0023D06A(int value) {
 return ((ArmySummarySystem*)((char*)this+0x184))->GetArmyBannerByID(value);
}
