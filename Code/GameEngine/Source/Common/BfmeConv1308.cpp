// Open-BFME5 conversion.
//
// The donor TU's sibling BfmeThingTCB::bfmeGoTCB has no masked retail match
// in this image, so it is not carried over.

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
