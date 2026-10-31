// cl: /O1 /DNDEBUG /MD
//
// Embedded-member forwarders: each body offsets this to an object embedded at a
// fixed field (add ecx, <field>) and tail-jumps a rowed member of it. The
// targets are only declared here so the calls are not inlined, as they would be
// beside their definitions. Owners are unknown; names are address-derived and
// no referencing site was found for these in this pass.
struct Coord3D;
class ArmySummarySystem;
class Rva003B24C7 { public: void rva003B24C7(bool val); };
class AIBaseBuilder { public: void rva00506B96(const Coord3D *point); bool rva00506C39(void *arg); };
class QuadStrip2D { public: void rva0053892C(unsigned int count); };
class Rva005382A6 { public: void *rva005382A6(int i, int off); };
class Rva005D40A6 { public: void Update(); };
class Rva004E7B0CHolder { public: void rva004E7B0C(); void rva004E7D1D(); };
class UnitRevivalTracker { public: void retrieveHeroesForArmySummary(ArmySummarySystem *summary); };

// 0x00203595: this + 0x10 -> Rva003B24C7::rva003B24C7
class Rva00203595Owner
{
public:
	void rva00203595(bool val);
};
void Rva00203595Owner::rva00203595(bool val)
{
	((Rva003B24C7 *)((char *)this + 0x10))->rva003B24C7(val);
}

// 0x002C6AC3: this + 0x4 -> AIBaseBuilder::rva00506B96
class Rva002C6AC3Owner
{
public:
	void rva002C6AC3(const Coord3D *point);
};

// 0x004EC0B9: this + 0x4 -> AIBaseBuilder::rva00506C39
class Rva004EC0B9Owner
{
public:
	bool rva004EC0B9(void *arg);
};
bool Rva004EC0B9Owner::rva004EC0B9(void *arg)
{
	return ((AIBaseBuilder *)((char *)this + 0x4))->rva00506C39(arg);
}

// 0x0030BBF9: this + 0x68 -> QuadStrip2D::rva0053892C
class Rva0030BBF9Owner
{
public:
	void rva0030BBF9(unsigned int count);
};
void Rva0030BBF9Owner::rva0030BBF9(unsigned int count)
{
	((QuadStrip2D *)((char *)this + 0x68))->rva0053892C(count);
}

// 0x0030BC09: this + 0x68 -> Rva005382A6::rva005382A6
class Rva0030BC09Owner
{
public:
	void * rva0030BC09(int i, int off);
};
void * Rva0030BC09Owner::rva0030BC09(int i, int off)
{
	return ((Rva005382A6 *)((char *)this + 0x68))->rva005382A6(i, off);
}

// 0x0057A313: this + 0x8 -> Rva005D40A6::Update
class Rva0057A313Owner
{
public:
	void update();
};
void Rva0057A313Owner::update()
{
	((Rva005D40A6 *)((char *)this + 0x8))->Update();
}

// 0x004CC594: this + 0x58C -> Rva004E7B0CHolder::rva004E7B0C
class Rva004CC594Owner
{
public:
	void rva004CC594();
};
void Rva004CC594Owner::rva004CC594()
{
	((Rva004E7B0CHolder *)((char *)this + 0x58C))->rva004E7B0C();
}

// 0x004CC59F: this + 0x58C -> Rva004E7B0CHolder::rva004E7D1D
class Rva004CC59FOwner
{
public:
	void rva004CC59F();
};
void Rva004CC59FOwner::rva004CC59F()
{
	((Rva004E7B0CHolder *)((char *)this + 0x58C))->rva004E7D1D();
}

// 0x0040C922: this + 0x738 -> UnitRevivalTracker::retrieveHeroesForArmySummary
class Rva0040C922Owner
{
public:
	void rva0040C922(ArmySummarySystem *summary);
};
void Rva0040C922Owner::rva0040C922(ArmySummarySystem *summary)
{
	((UnitRevivalTracker *)((char *)this + 0x738))->retrieveHeroesForArmySummary(summary);
}
