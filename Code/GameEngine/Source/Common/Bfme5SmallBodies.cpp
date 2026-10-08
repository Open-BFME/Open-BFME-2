// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Open-BFME5 conversions: small self-contained bodies.

struct Bfme5Quad16
{
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
};

class Bfme5QuadOwner
{
public:
	Bfme5Quad16 bfmeGetQuad(void);

	char m_bfmePad[0x84];
	Bfme5Quad16 m_bfmeQuad;
};

Bfme5Quad16 Bfme5QuadOwner::bfmeGetQuad(void)
{
	return m_bfmeQuad;
}

// Address-owned scalar accessors in the complete native 94B8D..94BF2 run.
// Every entry follows the preceding body's RET; each ends in RET0 or RET4.
// MOVSS slots and scalar equality establish the floating operations; byte
// stores independently establish offsets69/6A and one-byte arguments.
// Float-equality semantic donor: BF1 34f59164 Common/Rva006E1990FloatEq.cpp.
// The neighboring mutators are reconciled directly from their own retail
// instructions. Separate owners preserve uncertainty about class identity.
class Rva00094B8DFloats {
public: void zero();
private: char unknown[0x38]; float value38,value3C,value40;
};
void Rva00094B8DFloats::zero()
{ value40=0.0f; value3C=0.0f; value38=0.0f; }
class Rva00094BA0Float {
public: void zero();
private: char unknown[0x38]; float value;
};
void Rva00094BA0Float::zero() { value=0.0f; }
class Rva00094BA9Floats {
public: void zero();
private: char unknown[0x3C]; float value3C,value40;
};
void Rva00094BA9Floats::zero() { value40=0.0f; value3C=0.0f; }
class Rva00094BB7Float {
public: void set(float value);
private: char unknown[0x38]; float value;
};
void Rva00094BB7Float::set(float input) { value=input; }
class Rva00094BC5Byte {
public: void set(unsigned char value);
private: char unknown[0x69]; unsigned char value;
};
void Rva00094BC5Byte::set(unsigned char input) { value=input; }
class Rva00094BCFByte {
public: void set(unsigned char value);
private: char unknown[0x6A]; unsigned char value;
};
void Rva00094BCFByte::set(unsigned char input) { value=input; }
class Rva00094BD9Float {
public: bool valueIsHundred() const;
private: char unknown[0x40]; float value;
};
bool Rva00094BD9Float::valueIsHundred() const { return value==100.0f; }
