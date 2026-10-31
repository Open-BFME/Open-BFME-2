// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Leaf bodies from unrowed .text gaps (no calls), each bounded by its
// neighbour's ret or padding and its own ret. Retail bytes establish every
// shape; owning classes are not recovered, so each keeps an address-derived
// name and a view of only the members it touches. Each mirrors the
// instruction skeleton of an already matched twin named in its comment.

class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;
extern unsigned char g_00E01EA8;
extern unsigned char g_rva005B5C02Flag;
extern unsigned char isLoadingMap;
extern int g_Va00DFECD0;
struct Rva002E373CHolder;
extern Rva002E373CHolder *g_Va00DBD0F4;
class GameLogic;
extern GameLogic *TheGameLogic;
extern int BfmeLogicFramesPerSecond;
extern bool BfmeAIExitDoorFlag;

// --- 0x0024C80D (12B): complement seven consecutive 32-bit words in place
// (twin: Rva00332E83BitWords::flip, four words).
class Rva0024C80DBitWords
{
public:
	void flip();
	unsigned int m_words[7];
};
void Rva0024C80DBitWords::flip()
{
	for (unsigned int i = 0; i < 7; ++i)
		m_words[i] = ~m_words[i];
}

// --- 0x002BE8ED (12B): the byte at +0x2C0 of TheLivingWorldManager (VA
// 0x00DFE1C8), ignoring the receiver (twin: Rva00DFE1C8Host::rva00210DC9).
struct Rva002BE8EDView
{
	char m_pad000[0x2C0];
	bool m_2C0;
};
class Rva002BE8EDHost
{
public:
	bool rva002BE8ED();
};
bool Rva002BE8EDHost::rva002BE8ED()
{
	return ((Rva002BE8EDView *)TheLivingWorldManager)->m_2C0;
}

// --- 0x0020483D (11B): clears the words at +4 and +0xC and returns this
// (twin: Rva002B599FZeroView::rva002B599F).
class Rva0020483DZeroView
{
public:
	Rva0020483DZeroView *rva0020483D();
private:
	unsigned int m_00;
	unsigned int m_04;
	unsigned int m_08;
	unsigned int m_0C;
};
Rva0020483DZeroView *Rva0020483DZeroView::rva0020483D()
{
	m_04 = 0;
	m_0C = 0;
	return this;
}

// --- 0x00215EEC (11B, RET4): the indexed float of the array at +0x3C
// (twin: Rva00427157::rva004270FA).
class Rva00215EECFloats
{
public:
	float rva00215EEC(int index);
private:
	char m_pad00[0x3C];
	float m_values[1];
};
float Rva00215EECFloats::rva00215EEC(int index)
{
	return m_values[index];
}

// --- 0x001E361A (10B, cdecl): stores the byte argument into the global byte
// at VA 0x00E01EA8 (twin: WW3D::Pause_Movie).
void Rva001E361ASetFlag(unsigned char value)
{
	g_00E01EA8 = value;
}

// --- 0x002041A2 (10B, RET8): returns the word at +8 of the first stack
// argument, ignoring the receiver and the second argument (twin:
// TerrainRoadCollection::nextRoad 0x00314C13).
struct Rva002041A2Item
{
	char m_pad00[8];
	void *m_08;
};
class Rva002041A2Host
{
public:
	void *rva002041A2(const Rva002041A2Item *item, int unused);
};
void *Rva002041A2Host::rva002041A2(const Rva002041A2Item *item, int)
{
	return item->m_08;
}

// --- 0x00210C7D (10B, RET4): the address of the indexed dword of the
// receiver (twin: Vector3::operator[] 0x007173D0).
class Rva00210C7DWords
{
public:
	int &rva00210C7D(int index);
	int m_words[1];
};
int &Rva00210C7DWords::rva00210C7D(int index)
{
	return m_words[index];
}

// --- 0x0023C3FA (10B, RET4): stores the byte argument at +0x6D (twin:
// DockUpdate::setDockCrippled).
class Rva0023C3FAFlag
{
public:
	void set(bool value);
private:
	char m_pad00[0x6D];
	bool m_6D;
};
void Rva0023C3FAFlag::set(bool value)
{
	m_6D = value;
}

// --- 0x0023D37F (10B): bit 0 of the dword at +0x94 (twin:
// SegmentedLineClass::Are_End_Caps_Enabled).
class Rva0023D37FFlags
{
public:
	int rva0023D37F() const;
private:
	char m_pad00[0x94];
	unsigned int m_flags;
};
int Rva0023D37FFlags::rva0023D37F() const
{
	return m_flags & 1;
}

// ---- second batch (no calls) -----------------------------------------

// --- 0x001F3536 (7B): the float at +0xAC.
class Rva001F3536Float
{
public:
	float get() const;
	char m_pad00[0xAC];
	float m_AC;
};
float Rva001F3536Float::get() const
{
	return m_AC;
}

// --- 0x002026CE (6B): the address of +0x10 inside the object at +0.
struct Rva002026CEInner
{
	char m_pad00[0x10];
	int m_10;
};
class Rva002026CE
{
public:
	int *rva002026CE();
private:
	Rva002026CEInner *m_inner;
};
int *Rva002026CE::rva002026CE()
{
	return &m_inner->m_10;
}

// --- 0x00215E99 (11B, RET4): copies the word at +4 into +0x38 of the
// object at +0; the stack argument is unused.
struct Rva00215E99Target
{
	char m_pad00[0x38];
	int m_38;
};
class Rva00215E99
{
public:
	void rva00215E99(int unused);
private:
	Rva00215E99Target *m_target;
	int m_value;
};
void Rva00215E99::rva00215E99(int)
{
	m_target->m_38 = m_value;
}

// --- 0x00219134 (6B): the global flag byte at VA 0x00DFE34C, ignoring the
// receiver.
class Rva00219134Host
{
public:
	unsigned char rva00219134();
};
unsigned char Rva00219134Host::rva00219134()
{
	return g_rva005B5C02Flag;
}

// --- 0x00219140 (13B): the address of +0x64 when the flag byte at +0x60 is
// set, else null.
class Rva00219140
{
public:
	int *rva00219140();
private:
	char m_pad00[0x60];
	bool m_60;
	char m_pad61[3];
	int m_64;
};
int *Rva00219140::rva00219140()
{
	return m_60 ? &m_64 : 0;
}

// --- 0x00234361 (11B): +0x10 plus +4 plus one.
class Rva00234361
{
public:
	int rva00234361() const;
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
};
int Rva00234361::rva00234361() const
{
	return m_10 + m_04 + 1;
}

// --- 0x0023C41C (4B): the address of +0x64.
class Rva0023C41C
{
public:
	int *rva0023C41C();
private:
	char m_pad00[0x64];
	int m_64;
};
int *Rva0023C41C::rva0023C41C()
{
	return &m_64;
}

// --- 0x0023C4DB / 0x0023C4E3 (8B each, cdecl): set and clear the global
// flag byte at VA 0x00DFF004.
void Rva0023C4DBSet()
{
	isLoadingMap = 1;
}
void Rva0023C4E3Clear()
{
	isLoadingMap = 0;
}

// (0x0023DAE8, the vtable-0x00BEDAA0 constructor, lives in
// RvaSmallVtableCtors.cpp beside its Rva0007DF07 base.)

// --- 0x0027C218 (8B): the first word of the holder at VA 0x00DBD0F4.
struct Rva0027C218HolderView
{
	void *m_first;
};
class Rva0027C218Host
{
public:
	void *rva0027C218();
};
void *Rva0027C218Host::rva0027C218()
{
	return ((Rva0027C218HolderView *)g_Va00DBD0F4)->m_first;
}

// --- 0x0028A86B (8B): the word of the +8 array indexed by +0x20.
class Rva0028A86B
{
public:
	int rva0028A86B() const;
private:
	char m_pad00[8];
	int m_values[6];
	int m_index;
};
int Rva0028A86B::rva0028A86B() const
{
	return m_values[m_index];
}

// --- 0x0029B251 (6B): the address of +4 inside the object at +0.
struct Rva0029B251Inner
{
	int m_00;
	int m_04;
};
class Rva0029B251
{
public:
	int *rva0029B251();
private:
	Rva0029B251Inner *m_inner;
};
int *Rva0029B251::rva0029B251()
{
	return &m_inner->m_04;
}

// --- 0x002B226E (7B): pre-increments the counter at +0x2C.
class Rva002B226E
{
public:
	int rva002B226E();
private:
	char m_pad00[0x2C];
	int m_2C;
};
int Rva002B226E::rva002B226E()
{
	return ++m_2C;
}

// --- 0x002DB99F (13B): a constructor whose only work is setting the byte at
// +0x6F of TheGameLogic (VA 0x00DFE78C); the receiver is returned untouched.
struct Rva002DB99FLogicView
{
	char m_pad00[0x6F];
	bool m_6F;
};
class Rva002DB99F
{
public:
	Rva002DB99F();
};
Rva002DB99F::Rva002DB99F()
{
	((Rva002DB99FLogicView *)TheGameLogic)->m_6F = true;
}

// --- 0x002E6B3D (9B): bit 0 of +0x2C of the object at +0.
struct Rva002E6B3DInner
{
	char m_pad00[0x2C];
	unsigned int m_flags;
};
class Rva002E6B3D
{
public:
	unsigned int rva002E6B3D() const;
private:
	Rva002E6B3DInner *m_inner;
};
unsigned int Rva002E6B3D::rva002E6B3D() const
{
	return m_inner->m_flags & 1;
}

// --- 0x002E6B82 (7B, cdecl): increments the global counter at VA 0x00DFECD0.
void Rva002E6B82Bump()
{
	++g_Va00DFECD0;
}

// --- 0x002E6C72 (7B): bit 0 of the byte at +0xE.
class Rva002E6C72
{
public:
	unsigned int rva002E6C72() const;
private:
	char m_pad00[0xE];
	unsigned char m_0E;
};
unsigned int Rva002E6C72::rva002E6C72() const
{
	return m_0E & 1;
}

// --- 0x0033A430 (6B, RET4): the address of +4; the argument is unused.
class Rva0033A430
{
public:
	int *rva0033A430(int unused);
private:
	int m_00;
	int m_04;
};
int *Rva0033A430::rva0033A430(int)
{
	return &m_04;
}

// --- 0x0033A501 (6B): a constructor setting the word at +0 to -1.
class Rva0033A501
{
public:
	Rva0033A501();
private:
	int m_00;
};
Rva0033A501::Rva0033A501()
	: m_00(-1)
{
}

// --- 0x002226DA (11B, cdecl): stores the byte argument through the pointer
// argument and returns the pointer (EAX holds it on return).
unsigned char *Rva002226DAStore(unsigned char *target, unsigned char value)
{
	*target = value;
	return target;
}

// --- 0x0023527F (15B): sets the six floats at +0 to 1.0 (a rep stosd fill).
class Rva0023527FScales
{
public:
	void rva0023527F();
private:
	float m_values[6];
};
void Rva0023527FScales::rva0023527F()
{
	for (int i = 0; i < 6; ++i)
		m_values[i] = 1.0f;
}

// --- 0x0029A24F (6B): getter of BfmeFormationPreviewUseDecals (VA DC84F4).
extern bool BfmeFormationPreviewUseDecals;
bool __cdecl Rva0029A24FGet()
{
	return BfmeFormationPreviewUseDecals;
}

// --- 0x0029A255 (8B): the square of the float at +0x2C (x87).
class Rva0029A255Float
{
public:
	float rva0029A255() const;
private:
	char m_pad00[0x2C];
	float m_2C;
};
float Rva0029A255Float::rva0029A255() const
{
	return m_2C * m_2C;
}

// ---- third batch: constant returns ------------------------------------

// --- 0x0024AAEA, 0x0024AC8C, 0x0024B1D7, 0x0024B778, 0x0024C3F7 (4B each):
// constant returns (push imm8 / pop eax / ret); owners and meaning
// unresolved, so each is a static of an address-named holder.
struct Rva0024AAEAConst { static int get(); };
int Rva0024AAEAConst::get() { return 9; }
struct Rva0024AC8CConst { static int get(); };
int Rva0024AC8CConst::get() { return 7; }
struct Rva0024B1D7Const { static int get(); };
int Rva0024B1D7Const::get() { return 0x11; }
struct Rva0024B778Const { static int get(); };
int Rva0024B778Const::get() { return 0x5F; }
struct Rva0024C3F7Const { static int get(); };
int Rva0024C3F7Const::get() { return 5; }

// --- 0x002E0628 (6B): returns the FieldParse table g_00C04820 (the one
// Rva002E2386Parse.cpp defines), the shape of a static getFieldParse();
// owner unresolved.
struct FieldParse;
extern const FieldParse g_00C04820[];
struct Rva002E0628Table { static const FieldParse *getFieldParse(); };
const FieldParse *Rva002E0628Table::getFieldParse() { return g_00C04820; }

// ---- fourth batch: constant returns and small leaves -------------------

struct Rva00151406Const { static int get(); };
int Rva00151406Const::get() { return 0x28; }

struct Rva0028C53AConst { static int get(); };
int Rva0028C53AConst::get() { return 0x68; }

struct Rva0028C6F7Const { static int get(); };
int Rva0028C6F7Const::get() { return 0x0B; }

struct Rva0028C74FConst { static int get(); };
int Rva0028C74FConst::get() { return 0x65; }

struct Rva002B2431Const { static int get(); };
int Rva002B2431Const::get() { return 6; }

struct Rva0030D5EAConst { static int get(); };
int Rva0030D5EAConst::get() { return 0x20; }

struct Rva003182EFConst { static int get(); };
int Rva003182EFConst::get() { return 0x0F; }

struct Rva00584CAEConst { static int get(); };
int Rva00584CAEConst::get() { return 0x0A; }

// 0x0016CB40 (8B, cdecl): returns p + 0x10.
void *__cdecl Rva0016CB40(char *base) { return base + 0x10; }

// 0x00181490 (5B, RET4): empty 1-arg constructor returning this.
class Rva00181490 { public: Rva00181490(int); };
Rva00181490::Rva00181490(int) {}

// 0x001B4E1B (6B): subtracts 8 from the dword at +0 and returns this.
class Rva001B4E1B { public: Rva001B4E1B *rva001B4E1B(); private: int m_00; };
Rva001B4E1B *Rva001B4E1B::rva001B4E1B() { m_00 -= 8; return this; }

// 0x0039ADEC (7B, RET4): returns the float argument.
class Rva0039ADEC { public: float rva0039ADEC(float x) const; };
float Rva0039ADEC::rva0039ADEC(float x) const { return x; }

// 0x0039D8CC (7B, RET16): returns the first of four dword arguments.
class Rva0039D8CC { public: int rva0039D8CC(int first, int, int, int) const; };
int Rva0039D8CC::rva0039D8CC(int first, int, int, int) const { return first; }

// 0x00468A2F (7B): returns the float at +0x528.
class Rva00468A2F { public: float get() const; private: char m_pad[0x528]; float m_528; };
float Rva00468A2F::get() const { return m_528; }

// 0x004DF980 (3B): returns the byte at +0.
class Rva004DF980 { public: unsigned char get() const; private: unsigned char m_00; };
unsigned char Rva004DF980::get() const { return m_00; }

// 0x00299CCE (7B): returns (char *)this - 0x49C.
class Rva00299CCE { public: void *get() const; };
void *Rva00299CCE::get() const { return (char *)this - 0x49C; }

// 0x00299CDD (7B): returns the float at -0x490.
class Rva00299CDD { public: float get() const; };
float Rva00299CDD::get() const { return *(const float *)((const char *)this - 0x490); }

// 0x00462477 (6B): returns the boolean flag BfmeAIExitDoorFlag.
class Rva00462477 { public: bool rva00462477() const; };
bool Rva00462477::rva00462477() const { return BfmeAIExitDoorFlag; }

// 0x001E4132 (21B): height delta divided by twice logic fps.
class Rva001E4132 { public: float rva001E4132(float a, float startHeight, float b, float endHeight); };
float Rva001E4132::rva001E4132(float, float startHeight, float, float endHeight)
{
	return (endHeight - startHeight) / ((float)BfmeLogicFramesPerSecond + (float)BfmeLogicFramesPerSecond);
}

// 0x001513E5 (5B): sets bit 2 at byte offset +7
class Rva001513E5
{
public:
	void set();
private:
	char m_pad[7];
	unsigned char m_flags7;
};
void Rva001513E5::set()
{
	m_flags7 |= 4;
}

// 0x0018C0F9 (5B): returns dword at +0 minus 2
class Rva0018C0F9
{
public:
	int get() const;
private:
	int m_val;
};
int Rva0018C0F9::get() const
{
	return m_val - 2;
}

// 0x0045B49B (11B): returns ms scaled by BfmeClientFramesPerMillisecond
extern float BfmeClientFramesPerMillisecond;
float Rva0045B49BScale(float ms)
{
	return BfmeClientFramesPerMillisecond * ms;
}
