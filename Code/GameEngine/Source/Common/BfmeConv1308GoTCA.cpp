// Single-function extraction from BFME1 BfmeConv1308.cpp.
//
// Retail 0x0066F710 is BFME1's ?bfmeGoTCA@BfmeHostTCA@@QAEXPAVBfmeGetterTCA@@@Z
// verbatim: the host gathers a TID pointer from its getter and forwards it to
// its sink. The donor TU also defines ?bfmeGoTCB, which the sweep never
// placed, so the hook's find_declared_unmatched gate refuses the whole file;
// only this body moves here under its own TU name.
//
// Identity tiebreak over the sweep's 4 ICF needle twins (?bfmeGoDFC/DFI/DFJ):
// those donors each make a single MakeDF* call and return this, while retail
// makes two calls (getter with the "TID" literal, then the sink), matching
// only GoTCA. Both callees are settled: the getter call lands on rowed
// ?bfmeGoRF (0x00655990, which already carries the ?bfmeGetTCA pin for this
// folded getter cluster) and the sink call lands on rowed ?bfmeUseTCA
// (0x006756D0); the "TID" string literal agrees between the images.

// Open-BFME5 conversions.

class BfmeGetterTCA
{
public:
	void *bfmeGetTCA(void *a, void *b);
};

class BfmeSinkTCA
{
public:
	void bfmeUseTCA(void *v);
};

class BfmeHostTCA
{
public:
	void bfmeGoTCA(BfmeGetterTCA *r);
	char m_bfmePad[0x18];
	BfmeSinkTCA *m_bfmeSink;
};

void BfmeHostTCA::bfmeGoTCA(BfmeGetterTCA *r)
{
	m_bfmeSink->bfmeUseTCA(r->bfmeGetTCA((void *)"TID", 0));
}
