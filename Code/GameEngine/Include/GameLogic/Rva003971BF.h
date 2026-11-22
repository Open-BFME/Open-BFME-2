// Rva003971BF: canonical declarations for the members 3 units call through private views of it.
// The layout is the one rva003971BF (0x003971BF) reads: retail compares the dword at +0x34
// with 4 and walks the ObjectID ranges [+0x50,+0x54) and [+0x74,+0x78).
#ifndef CANONICAL_RVA003971BF_H
#define CANONICAL_RVA003971BF_H

struct Arg3971BF;
enum ObjectID;

class Rva003971BF
{
public:
	bool rva003971BF(Arg3971BF *arg);
private:
	char m_pad00[0x34];
	int m_34;
	char m_pad38[0x50 - 0x38];
	ObjectID *m_begin50;
	ObjectID *m_end54;
	char m_pad58[0x74 - 0x58];
	ObjectID *m_begin74;
	ObjectID *m_end78;
};

#endif // CANONICAL_RVA003971BF_H
