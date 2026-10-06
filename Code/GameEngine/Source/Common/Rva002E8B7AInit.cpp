// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva002E8B7AInit@@YAPAVMixFileInfoBuffer@@PAPAV1@HPAUIn002E6BA1@@@Z, retail 0x002E8B7A, 33 bytes.
// Calls rowed bfmeUnlink 0x002E6BE2 then rowed rva002E6BA1 0x002E6BA1 then returns node.
// Evidence: chain from 0x002E6BA1 plus unlink 0x002E6BE2; caller 0x002E8BBB pushes global 0x00A049D0 plus this plus arg then add esp 0xC.
struct In002E6BA1
{
	int m_00;
	int m_04;
};

class Rva002E6BA1
{
public:
	void rva002E6BA1(int a, In002E6BA1 *b);
};

class MixFileInfoBuffer
{
private:
	void bfmeUnlink();
	friend class Rva002E6BA1;
public:
	friend MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer **pp, int a, In002E6BA1 *in);
};

MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer **pp, int a, In002E6BA1 *in)
{
	MixFileInfoBuffer *node = *pp;
	node->bfmeUnlink();
	((Rva002E6BA1 *)node)->rva002E6BA1(a, in);
	return node;
}
