// ?calculate@Gen009F5040@@QAEXPAUGen009F5040Node@@PAH11@Z
// partial score=0.949866 date=2026-10-05
// ?calculate@Gen009F5040@@QAEXPAUGen009F5040Node@@PAH11@Z
// partial score=0.95 date=2026-10-05
// ?calculate@Gen009F5040@@QAEXPAUGen009F5040Node@@PAH11@Z
//
// Retail 0x006271D0 225B: two virtual values, float differences via
// bfmeIndexER/ES, combined xor/or into result24, then clear the top bit in
// result28/result2c. Callees rowed (bfmeIndexER 0x626FB0, bfmeIndexES
// 0x627020) plus virtual slots 0/4.
//
// partial: the direct-accumulator form (one `comb`, ER^r28 then |= ES^r2c)
// reproduces retail's register allocation exactly and byte-matches through
// 0x62725A. The residual is the bit-cascade: retail materialises a=comb in
// eax before zeroing the count, ours coalesces a into comb's esi.
struct Gen009F5040Item;

struct Gen009F5040Node
{
	char m_pad00[4];
	Gen009F5040Item *m_item;
	char m_pad08[8];
	Gen009F5040Node **m_secondaryPreviousLink;
	Gen009F5040Node *m_secondaryNext;
	Gen009F5040Node **m_previousLink;
	Gen009F5040Node *m_next;
	volatile int m_index;
	int m_result24;
	int m_result28;
	int m_result2c;
};

struct Gen009F5040Item
{
	virtual void *getValue0();
	virtual void *getValue1();
	virtual void *getValue2();
	virtual void *getValue3();
	virtual void *getValue4();
	virtual void *getValue5();
	virtual void *getValue6();
	virtual int getIndex();
};

class BfmeRecEQR;

class BfmeHostER
{
public:
	unsigned int bfmeIndexER(float v);
};

class BfmeHostES
{
public:
	unsigned int bfmeIndexES(float v);
};

struct CalcV0
{
	char m_pad00[16];
	float m_base;
};

struct CalcV1
{
	float m_x;
	float m_y;
};

struct Gen009F5040Counter
{
	int m_value;
	Gen009F5040Node *m_head;
};

struct Gen009F5040Bucket
{
	Gen009F5040Counter *m_counter;
	int m_pad04;
	int m_pad08;
};

class Gen009F5040
{
public:
	void calculate(Gen009F5040Node *node, int *result28, int *result2c,
		int *result24);

	Gen009F5040Bucket m_buckets[2];
	Gen009F5040Counter *m_rangeBegin;
	Gen009F5040Counter *m_rangeEnd;
	char m_pad20[0xfc];
	unsigned int m_mask;
	Gen009F5040Node *m_node;
};

// ?calculate@Gen009F5040@@QAEXPAUGen009F5040Node@@PAH11@Z
void Gen009F5040::calculate(Gen009F5040Node *node, int *result28, int *result2c,
	int *result24)
{
	CalcV0 *v0;
	CalcV1 *v1;
	v0 = (CalcV0 *)node->m_item->getValue0();
	v1 = (CalcV1 *)node->m_item->getValue1();
	float base = v0->m_base;
	*result28 = (int)((BfmeHostER *)this)->bfmeIndexER(v1->m_x - base);
	*result2c = (int)((BfmeHostES *)this)->bfmeIndexES(v1->m_y - base);
	unsigned int comb = ((BfmeHostER *)this)->bfmeIndexER(base + v1->m_x) ^ (unsigned int)*result28;
	comb |= ((BfmeHostES *)this)->bfmeIndexES(base + v1->m_y) ^ (unsigned int)*result2c;
	*result24 = (int)comb;
	unsigned int a = comb;
	if (a != 0) {
		int c = 0;
		if ((a & 0xffff0000) != 0) {
			a >>= 16;
			c |= 16;
		}
		if ((a & 0xff00) != 0) {
			a >>= 8;
			c |= 8;
		}
		if ((a & 0xf0) != 0) {
			a >>= 4;
			c |= 4;
		}
		if ((a & 0xc) != 0) {
			a >>= 2;
			c |= 2;
		}
		if ((a & 2) != 0)
			c |= 1;
		int mask = ~(1 << c);
		*result28 &= mask;
		*result2c &= mask;
	}
}
