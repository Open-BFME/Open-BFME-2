// cl: /DNDEBUG /MD
// ?Rva0006297CClamp@@YGXPBM0PAM1@Z @0x0006297C 160B
// Evidence: vslot 17 of 0x007C57E0 class Rva00628FD; single callee
// Get_Render_Target_Resolution rowed; neighbours VslotSmallBodiesAJ/B.
class WW3D
{
public:
	static void Get_Render_Target_Resolution(int &a, int &b, int &c, bool &d);
};

void __stdcall Rva0006297CClamp(const float *pos, const float *size, float *outPosition, float *outSize)
{
	int width = 0;
	int height = 0;
	int w2 = 0;
	bool flag = false;
	WW3D::Get_Render_Target_Resolution(width, height, w2, flag);
	float x = 0.0f;
	if (!(0.0f >= pos[0]))
		x = pos[0];
	outPosition[0] = x;
	float y;
	if (0.0f >= pos[1])
		y = 0.0f;
	else
		y = pos[1];
	outPosition[1] = y;
	float wf = (float)width;
	float t = size[0] + outPosition[0];
	if (t > wf)
		t = wf - outPosition[0];
	else
		t = size[0];
	outSize[0] = t;
	float u = size[1] + outPosition[1];
	if (u > wf)
		u = wf - outPosition[1];
	else
		u = size[1];
	outSize[1] = u;
}

// Installed-vtable store through the first stack argument. Native stack
// cleanup and AL result are known; original owner and field meanings are not.
struct Rva005216CBTarget {char prefix[0xC]; int word;};
class Rva005216CB {public: bool rva005216CB(Rva005216CBTarget *target, int value);};
bool Rva005216CB::rva005216CB(Rva005216CBTarget *target, int value) {target->word=value; return true;}

// Installed-vtable store through the first stack argument. Native stack
// cleanup and AL result are known; original owner and field meanings are not.
struct Rva005216EDTarget {char prefix[0x1C]; int word;};
class Rva005216ED {public: bool rva005216ED(Rva005216EDTarget *target, int value);};
bool Rva005216ED::rva005216ED(Rva005216EDTarget *target, int value) {target->word=value; return true;}

// Installed-vtable store through the first stack argument. Native stack
// cleanup and AL result are known; original owner and field meanings are not.
struct Rva005216FDTarget {char prefix[0x20]; int word;};
class Rva005216FD {public: bool rva005216FD(Rva005216FDTarget *target, int value);};
bool Rva005216FD::rva005216FD(Rva005216FDTarget *target, int value) {target->word=value; return true;}

// Installed-vtable store through the first stack argument. Native stack
// cleanup and AL result are known; original owner and field meanings are not.
struct Rva0052170DTarget {char prefix[0x10]; int word; int second;};
class Rva0052170D {public: bool rva0052170D(Rva0052170DTarget *target, int value);};
bool Rva0052170D::rva0052170D(Rva0052170DTarget *target, int value) {target->word=value; target->second=value; return true;}

// Installed-vtable byte store: stack byte to this+21, RET4.
class Rva005975D7 {public: void rva005975D7(unsigned char value); private: char prefix[0x21]; unsigned char byte;};
void Rva005975D7::rva005975D7(unsigned char value) {byte=value;}

// Installed-vtable scalar clears: word88 and byteD0, no stack arguments.
class Rva0043A0B2 {public: void rva0043A0B2(); private: char prefix[0x88]; int word; char gap[0xD0-0x8C]; unsigned char byte;};
void Rva0043A0B2::rva0043A0B2() {word=0; byte=0;}

// ?rva004E14A5@Rva004E14A5@@QAEXE@Z @0x004E14A5 (23B)
class Rva004E14A5
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	void rva004E14A5(unsigned char value);
private:
	char m_pad04[0x10 - 0x04];
	int m_10;
	char m_pad14[0x20 - 0x14];
	unsigned char m_20;
	unsigned char m_21;
};
void Rva004E14A5::rva004E14A5(unsigned char value)
{
	m_10 = 0;
	m_21 = value;
	m_20 = 1;
	v5();
}

// ?rva005216DB@Rva005216DB@@QAE_NPAVGameSlot@@H@Z @0x005216DB (18B)
class GameSlot { public: void setPlayerTemplate(int value); };
class Rva005216DB { public: bool rva005216DB(GameSlot *target, int value); };
bool Rva005216DB::rva005216DB(GameSlot *target, int value)
{
	target->setPlayerTemplate(value);
	return true;
}
