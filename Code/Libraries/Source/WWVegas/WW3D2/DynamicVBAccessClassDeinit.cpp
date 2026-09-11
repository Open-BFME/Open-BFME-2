// cl: /O2 /G7 /MD
//
// DynamicVBAccessClass::_Deinit, retail 0x0013A840, 150 bytes.
// Dedicated TU so bfmedynamicvertexbuffer.cpp keeps its matched bodies.

class BfmeDynamicVB
{
public:
	virtual void Destroy();
	int Refs;
};

struct BfmeFVFDescriptor
{
	char Pad[96];
	void Initialize(unsigned format, unsigned vertex_size, bool basis, unsigned count);
};

class DynamicVBAccessClass
{
public:
	static void _Deinit();
	static void bfmeRva0013A7D0();
};

extern bool bfmeDynamicVBInUse[15];
extern BfmeDynamicVB *bfmeDynamicVBs[15];
extern unsigned short bfmeDynamicVBSizes[15];
extern unsigned short bfmeDynamicVBOffsets[15];
extern unsigned bfmeDynamicFVFs[15];
extern BfmeFVFDescriptor bfmeDynamicFVFDescs[15];
extern bool bfmeSortingVBInUse;
extern BfmeDynamicVB *bfmeSortingVB;
extern unsigned short bfmeSortingVBSize;
extern unsigned short bfmeSortingVBOffset;

void DynamicVBAccessClass::_Deinit()
{
	int n = 0;
	for (int i = 0; i < 15; i++) {
		BfmeDynamicVB *p = bfmeDynamicVBs[i];
		if (p != (BfmeDynamicVB *)n) {
			if (!(p->Refs += -1))
				p->Destroy();
			bfmeDynamicVBs[i] = (BfmeDynamicVB *)n;
		}
		unsigned fvf = bfmeDynamicFVFs[i];
		bfmeDynamicVBInUse[i] = (char)n;
		bfmeDynamicVBSizes[i] = 5000;
		bfmeDynamicVBOffsets[i] = (unsigned short)n;
		bfmeDynamicFVFDescs[i].Initialize(fvf, n, (bool)n, n);
	}

	BfmeDynamicVB *p = bfmeSortingVB;
	if (p != (BfmeDynamicVB *)n) {
		if (!(p->Refs += -1))
			p->Destroy();
		bfmeSortingVB = (BfmeDynamicVB *)n;
	}
	bfmeSortingVBInUse = (char)n;
	bfmeSortingVBSize = (unsigned short)n;
	bfmeSortingVBOffset = (unsigned short)n;
}

// 0x0013A7D0, 104 bytes, immediately before _Deinit: the same per-format loop
// without the sorting half -- every native pool is released, marked free,
// resized to 5000 and rewound, and its FVF record rebuilt from the format
// table.  Zero Hour has no counterpart, so the name is address-derived.
void DynamicVBAccessClass::bfmeRva0013A7D0()
{
	int n = 0;
	for (int i = 0; i < 15; i++) {
		BfmeDynamicVB *p = bfmeDynamicVBs[i];
		if (p != (BfmeDynamicVB *)n) {
			if (!(p->Refs += -1))
				p->Destroy();
			bfmeDynamicVBs[i] = (BfmeDynamicVB *)n;
		}
		unsigned fvf = bfmeDynamicFVFs[i];
		bfmeDynamicVBInUse[i] = (char)n;
		bfmeDynamicVBSizes[i] = 5000;
		bfmeDynamicVBOffsets[i] = (unsigned short)n;
		bfmeDynamicFVFDescs[i].Initialize(fvf, n, (bool)n, n);
	}
}
