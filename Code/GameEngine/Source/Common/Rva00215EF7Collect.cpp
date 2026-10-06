// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva00215EF7Collect@@YAXPAPAIPAI111@Z @0x00215EF7 43B collector.
// Evidence: finish lane stash score 0.95, calls rowed 0x00215E6F, walks 0x1C records, copies slots to out. Fix final load order.
class Rva00215E6F
{
public:
	void rva00215E6F(unsigned int *p);
private:
	unsigned int *m_slots[2];
};
void Rva00215EF7Collect(unsigned int **out, unsigned int *begin, unsigned int *end, unsigned int *slot0, unsigned int *slot1)
{
	Rva00215E6F *holder = (Rva00215E6F *)&slot0;
	for (unsigned int *p = begin; p != end; p = (unsigned int *)((char *)p + 0x1c))
		holder->rva00215E6F(p);
	out[0] = *(unsigned * volatile *)&slot0;
	out[1] = slot1;
}
