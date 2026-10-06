// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
//
// Word-element vector single-argument resize (retail 0x00157E50, 15 bytes),
// tail-calling the two-argument form in stlport_vector_word_o1.cpp with a
// literal zero. Lives apart from that unit because it needs /O2: the mov+push
// argument setup retail shows comes from favor-speed codegen, where the /O1
// the 61-byte body needs folds it to a push from memory.
//
// The ledger previously served 0x157E50 as narrow-string resize via a
// locate.py pin, but the callee (BfmeWordVec two-arg resize at 0x000824F9)
// disproves a char element; that row is retracted alongside this landing.
struct BfmeWordVec
{
	void resize(unsigned n, unsigned short x);
	void resize(unsigned n);
};

void BfmeWordVec::resize(unsigned n)
{
	resize(n, 0);
}
