// cl: /O1 /arch:SSE /G7 /Oy-
// ??0Rva0027D02F@@QAE@PBIHHHGHEE@Z
// Native 0027D02F..0027D08D (94 bytes, RET 32) returns the receiver in EAX.
// This constructor ABI view keeps the original identity and field meanings
// unknown. Retail copies three input dwords, stores five further arguments,
// and initializes byte +18 and floats +1C/+20/+24 to zero. The word
// input view expresses the bit-preserving copies without asserting the
// original source's scalar types. Explicit stores preserve native order.
class Rva0027D02F
{
public:
	Rva0027D02F(const unsigned int *words, int a, int b, int c,
		unsigned short tag, int d, unsigned char e, unsigned char f);
	void ensureByte18();
private:
	unsigned int word00, word04, word08;
	int word0C, word10, word14;
	unsigned char byte18;
	float value1C, value20, value24;
	int word28;
	unsigned char byte2C, byte2D;
	unsigned short word2E;
};

Rva0027D02F::Rva0027D02F(const unsigned int *words, int a, int b, int c,
	unsigned short tag, int d, unsigned char e, unsigned char f)
{
    word00 = words[0];
    word04 = words[1];
    word08 = words[2];
    word0C = a;
    word10 = b;
    word14 = c;
    word28 = d;
    byte2C = e;
    byte2D = f;
    byte18 = 0;
    word2E = tag;
    value1C = 0.0f;
    value20 = 0.0f;
    value24 = 0.0f;
}

// Open-BFME-1 f98983a7d3bb405f1a4ba94bb6a2a168062a819d guide:
// Common/Rva001A3020Flag.cpp (omitted-Common O2/SSE2/G6 placement).
// Native 27D08D starts immediately after this constructor's complete RET32.
// Its 11 bytes test the same unsigned byte18 then write1 only when zero.
// Original owner and flag meaning remain unknown; the 0x30-byte constructor
// record and byte18 are independently measured in native 27D02F/283642.
void Rva0027D02F::ensureByte18()
{
    if (byte18 == 0)
        byte18 = 1;
}
