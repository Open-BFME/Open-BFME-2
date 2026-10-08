// bfmeGo1025F, retail 0x0061F3E0 (45B).
// Ported from Open-BFME-1 Code/GameEngine/Source/Common/BfmeConv1025.cpp
// (BFME1 0x009EBE90). Only the placed name-key probe is defined here; the
// donor's other five members stay out, so the unmatched-definition gate
// passes. Retail checks the global talker, picks name+8 or the fallback
// literal, and tail-returns the talker's char answer through the single
// pinned call site (reached on both arms).

class BfmeP1025
{
public:
	char bfmeSay1025(char *t);
};

extern class Q1Receiver0134FAAC *TheQ1Receiver;

struct BfmeR1025
{
	char *m_bfmeName;
};

// ?bfmeGo1025F@@YADPAUBfmeR1025@@@Z, retail 0x0061F3E0 (45B).
char bfmeGo1025F(BfmeR1025 *p)
{
	if ((*(BfmeP1025 **)&TheQ1Receiver) != 0) {
		char *t;

		if (p->m_bfmeName != 0)
			t = p->m_bfmeName + 8;
		else
			t = (char *)"";

		return (*(BfmeP1025 **)&TheQ1Receiver)->bfmeSay1025(t);
	}

	return 0;
}
