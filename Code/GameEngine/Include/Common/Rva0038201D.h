#ifndef CANONICAL_RVA0038201D_H
#define CANONICAL_RVA0038201D_H

struct Rva0038201DNode;

class Rva0038201D
{
    // Clear (0x003828B6) reads the sentinel at +0 and the node count at +4.
    // The stats destructor at 0x00383D71 walks these map elements at stride 12.
    Rva0038201DNode *m_head;
    int m_count;
    unsigned char m_storage08[4];

public:
	~Rva0038201D();
	void rva0038201D(Rva0038201DNode *node);
	void rva003828B6();
};

#endif // CANONICAL_RVA0038201D_H
