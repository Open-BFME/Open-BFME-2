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
