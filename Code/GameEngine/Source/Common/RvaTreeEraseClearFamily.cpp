// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// STLport red-black tree node erase and clear bodies, one pair per tree
// instantiation, with the shapes of the rowed Rva00226883::rva00226883 (45-byte
// recursive erase: erase the right subtree, free the node, walk left) and
// Rva00226883::rva0022999F (41-byte clear: if non-empty, erase from the root and
// reset the header's links and the count). Found by searching .text for those
// shapes with call displacements masked: each erase calls only itself and free
// (0x00030830), each clear only its tree's erase. Which tree each belongs to is
// not recovered, so the owners are named after their erase's address (an erase
// already rowed keeps its owner and parameter type).

extern "C" void __cdecl free(void *block);

struct RvaTreeFamilyNode
{
	char m_pad[8]; // +0x00..0x07
	RvaTreeFamilyNode *m_next; // +0x08
	RvaTreeFamilyNode *m_child; // +0x0C
};

struct RvaTreeFamilyHead
{
	char m_pad00[4]; // +0x00
	RvaTreeFamilyNode *m_first; // +0x04
	RvaTreeFamilyHead *m_next; // +0x08
	RvaTreeFamilyHead *m_child; // +0x0C
};

// owner Rva0006F318: erase 0x0006F318, clear 0x0006FA70
class Rva0006F318
{
public:
	void rva0006F318(void *node);
	void rva0006FA70();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva0006F318::rva0006F318(void *node)
{
	if (!node)
		return;
	RvaTreeFamilyNode *cur = (RvaTreeFamilyNode *)node;
	do {
		rva0006F318(cur->m_child);
		RvaTreeFamilyNode *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva0006F318::rva0006FA70()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva0006F318(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva0007E971: erase 0x0007E971, clear 0x0007FAC1
class Rva0007E971
{
public:
	void rva0007E971(void *node);
	void rva0007FAC1();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva0007E971::rva0007E971(void *node)
{
	if (!node)
		return;
	RvaTreeFamilyNode *cur = (RvaTreeFamilyNode *)node;
	do {
		rva0007E971(cur->m_child);
		RvaTreeFamilyNode *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva0007E971::rva0007FAC1()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva0007E971(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva000D20A9: erase 0x000D20A9, clear 0x000D2294
class Rva000D20A9
{
public:
	void rva000D20A9(void *node);
	void rva000D2294();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva000D20A9::rva000D20A9(void *node)
{
	if (!node)
		return;
	RvaTreeFamilyNode *cur = (RvaTreeFamilyNode *)node;
	do {
		rva000D20A9(cur->m_child);
		RvaTreeFamilyNode *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva000D20A9::rva000D2294()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva000D20A9(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva001DD70F: erase 0x001DD70F, clear 0x001DD846
class Rva001DD70F
{
public:
	void rva001DD70F(void *node);
	void rva001DD846();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva001DD70F::rva001DD70F(void *node)
{
	if (!node)
		return;
	RvaTreeFamilyNode *cur = (RvaTreeFamilyNode *)node;
	do {
		rva001DD70F(cur->m_child);
		RvaTreeFamilyNode *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva001DD70F::rva001DD846()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva001DD70F(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva0021119B: erase 0x0021119B, clear 0x00211DD2
class Rva0021119B
{
public:
	void rva0021119B(void *node);
	void rva00211DD2();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva0021119B::rva0021119B(void *node)
{
	if (!node)
		return;
	RvaTreeFamilyNode *cur = (RvaTreeFamilyNode *)node;
	do {
		rva0021119B(cur->m_child);
		RvaTreeFamilyNode *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva0021119B::rva00211DD2()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva0021119B(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva002294A3: erase 0x002294A3, clear 0x0022C409
class Rva002294A3
{
public:
	void rva002294A3(void *node);
	void rva0022C409();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva002294A3::rva002294A3(void *node)
{
	if (!node)
		return;
	RvaTreeFamilyNode *cur = (RvaTreeFamilyNode *)node;
	do {
		rva002294A3(cur->m_child);
		RvaTreeFamilyNode *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva002294A3::rva0022C409()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva002294A3(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva002294D0: erase 0x002294D0, clear 0x0022C432
class Rva002294D0
{
public:
	void rva002294D0(void *node);
	void rva0022C432();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva002294D0::rva002294D0(void *node)
{
	if (!node)
		return;
	RvaTreeFamilyNode *cur = (RvaTreeFamilyNode *)node;
	do {
		rva002294D0(cur->m_child);
		RvaTreeFamilyNode *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva002294D0::rva0022C432()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva002294D0(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva0027F4CB: erase 0x0027F4CB, clear 0x00280AB6
class Rva0027F4CB
{
public:
	void rva0027F4CB(void *node);
	void rva00280AB6();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva0027F4CB::rva0027F4CB(void *node)
{
	if (!node)
		return;
	RvaTreeFamilyNode *cur = (RvaTreeFamilyNode *)node;
	do {
		rva0027F4CB(cur->m_child);
		RvaTreeFamilyNode *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva0027F4CB::rva00280AB6()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva0027F4CB(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva0028881C: erase 0x0028881C, clear 0x002889BB
class Rva0028881C
{
public:
	void rva0028881C(void *node);
	void rva002889BB();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva0028881C::rva0028881C(void *node)
{
	if (!node)
		return;
	RvaTreeFamilyNode *cur = (RvaTreeFamilyNode *)node;
	do {
		rva0028881C(cur->m_child);
		RvaTreeFamilyNode *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva0028881C::rva002889BB()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva0028881C(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva002A8B8C: erase 0x002A8B8C, clear 0x002A8BEE
class Rva002A8B8C
{
public:
	void rva002A8B8C(void *node);
	void rva002A8BEE();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva002A8B8C::rva002A8B8C(void *node)
{
	if (!node)
		return;
	RvaTreeFamilyNode *cur = (RvaTreeFamilyNode *)node;
	do {
		rva002A8B8C(cur->m_child);
		RvaTreeFamilyNode *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva002A8B8C::rva002A8BEE()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva002A8B8C(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva00372F00: erase 0x00372F00, clear 0x00372F56
class Rva00372F00
{
public:
	void rva00372F00(void *node);
	void rva00372F56();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva00372F00::rva00372F00(void *node)
{
	if (!node)
		return;
	RvaTreeFamilyNode *cur = (RvaTreeFamilyNode *)node;
	do {
		rva00372F00(cur->m_child);
		RvaTreeFamilyNode *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva00372F00::rva00372F56()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva00372F00(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva00388EAE: erase 0x00388EAE, clear 0x00389129
class Rva00388EAE
{
public:
	void rva00388EAE(void *node);
	void rva00389129();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva00388EAE::rva00388EAE(void *node)
{
	if (!node)
		return;
	RvaTreeFamilyNode *cur = (RvaTreeFamilyNode *)node;
	do {
		rva00388EAE(cur->m_child);
		RvaTreeFamilyNode *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva00388EAE::rva00389129()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva00388EAE(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva0041331E: erase 0x0041331E, clear 0x0041334B
class Rva0041331E
{
public:
	void rva0041331E(void *node);
	void rva0041334B();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva0041331E::rva0041331E(void *node)
{
	if (!node)
		return;
	RvaTreeFamilyNode *cur = (RvaTreeFamilyNode *)node;
	do {
		rva0041331E(cur->m_child);
		RvaTreeFamilyNode *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva0041331E::rva0041334B()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva0041331E(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva0043B2E2: erase 0x0043B2E2, clear 0x0043B334
class Rva0043B2E2
{
public:
	void rva0043B2E2(void *node);
	void rva0043B334();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva0043B2E2::rva0043B2E2(void *node)
{
	if (!node)
		return;
	RvaTreeFamilyNode *cur = (RvaTreeFamilyNode *)node;
	do {
		rva0043B2E2(cur->m_child);
		RvaTreeFamilyNode *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva0043B2E2::rva0043B334()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva0043B2E2(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

// ?Rva0043B30FNewNode@@YGPAXPBX@Z @0x0043B30F 37B: tree node allocator for the
// 0x9C-byte nodes of owner Rva0043B2E2 (value Rva0043B23E pair at +0x10).
// Evidence: allocate 0x9C through rowed byte allocator 0x000307F0 then rowed
// Construct 0x0043B2D0 at +0x10 from the arg; callers at 0x0043B3C9/0x0043B3E2
// in 0x0043B3A1; ret 4 so __stdcall free function following Rva002ACFD6NewNode.
namespace _STL {
template <class _Tp> class allocator
{
public:
	static _Tp *allocate(unsigned int, const void *);
};
}
class Rva0043B23E;
void __cdecl Rva0043B2D0Construct(class Rva0043B23E *, const class Rva0043B23E &);

void *__stdcall Rva0043B30FNewNode(const void *src)
{
	char *node = _STL::allocator<char>::allocate(0x9C, 0);
	Rva0043B2D0Construct((Rva0043B23E *)(node + 0x10), *(const Rva0043B23E *)src);
	return node;
}

// owner Rva0043EA9C: erase 0x0043EA9C, clear 0x0043F124
class Rva0043EA9C
{
public:
	void rva0043EA9C(void *node);
	void rva0043F124();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva0043EA9C::rva0043EA9C(void *node)
{
	if (!node)
		return;
	RvaTreeFamilyNode *cur = (RvaTreeFamilyNode *)node;
	do {
		rva0043EA9C(cur->m_child);
		RvaTreeFamilyNode *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva0043EA9C::rva0043F124()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva0043EA9C(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva004D0545: erase 0x004D0545, clear 0x004D0F82
class Rva004D0545
{
public:
	void rva004D0545(void *node);
	void rva004D0F82();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva004D0545::rva004D0545(void *node)
{
	if (!node)
		return;
	RvaTreeFamilyNode *cur = (RvaTreeFamilyNode *)node;
	do {
		rva004D0545(cur->m_child);
		RvaTreeFamilyNode *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva004D0545::rva004D0F82()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva004D0545(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva004D0572: erase 0x004D0572, clear 0x004D0FAB
class Rva004D0572
{
public:
	void rva004D0572(void *node);
	void rva004D0FAB();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva004D0572::rva004D0572(void *node)
{
	if (!node)
		return;
	RvaTreeFamilyNode *cur = (RvaTreeFamilyNode *)node;
	do {
		rva004D0572(cur->m_child);
		RvaTreeFamilyNode *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva004D0572::rva004D0FAB()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva004D0572(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva004E7B13: erase 0x004E7B13, clear 0x004E7BAF
class Rva004E7B13
{
public:
	void rva004E7B13(void *node);
	void rva004E7BAF();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva004E7B13::rva004E7B13(void *node)
{
	if (!node)
		return;
	RvaTreeFamilyNode *cur = (RvaTreeFamilyNode *)node;
	do {
		rva004E7B13(cur->m_child);
		RvaTreeFamilyNode *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva004E7B13::rva004E7BAF()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva004E7B13(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva004E9419: erase 0x004E9419, clear 0x004E94A1
class Rva004E9419
{
public:
	void rva004E9419(void *node);
	void rva004E94A1();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva004E9419::rva004E9419(void *node)
{
	if (!node)
		return;
	RvaTreeFamilyNode *cur = (RvaTreeFamilyNode *)node;
	do {
		rva004E9419(cur->m_child);
		RvaTreeFamilyNode *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva004E9419::rva004E94A1()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva004E9419(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva004EA149: erase 0x004EA149, clear 0x004EA264
class Rva004EA149
{
public:
	void rva004EA149(void *node);
	void rva004EA264();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva004EA149::rva004EA149(void *node)
{
	if (!node)
		return;
	RvaTreeFamilyNode *cur = (RvaTreeFamilyNode *)node;
	do {
		rva004EA149(cur->m_child);
		RvaTreeFamilyNode *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva004EA149::rva004EA264()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva004EA149(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva004FCA9C: erase 0x004FCA9C, clear 0x004FCBCD
class Rva004FCA9C
{
public:
	void rva004FCA9C(void *node);
	void rva004FCBCD();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva004FCA9C::rva004FCA9C(void *node)
{
	if (!node)
		return;
	RvaTreeFamilyNode *cur = (RvaTreeFamilyNode *)node;
	do {
		rva004FCA9C(cur->m_child);
		RvaTreeFamilyNode *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva004FCA9C::rva004FCBCD()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva004FCA9C(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva004FCAC9: erase 0x004FCAC9, clear 0x004FCBF6
class Rva004FCAC9
{
public:
	void rva004FCAC9(void *node);
	void rva004FCBF6();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva004FCAC9::rva004FCAC9(void *node)
{
	if (!node)
		return;
	RvaTreeFamilyNode *cur = (RvaTreeFamilyNode *)node;
	do {
		rva004FCAC9(cur->m_child);
		RvaTreeFamilyNode *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva004FCAC9::rva004FCBF6()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva004FCAC9(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva004FCAF6: erase 0x004FCAF6, clear 0x004FCC1F
class Rva004FCAF6
{
public:
	void rva004FCAF6(void *node);
	void rva004FCC1F();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva004FCAF6::rva004FCAF6(void *node)
{
	if (!node)
		return;
	RvaTreeFamilyNode *cur = (RvaTreeFamilyNode *)node;
	do {
		rva004FCAF6(cur->m_child);
		RvaTreeFamilyNode *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva004FCAF6::rva004FCC1F()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva004FCAF6(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva004FF3DB: erase 0x004FF3DB, clear 0x004FF49F
class Rva004FF3DB
{
public:
	void rva004FF3DB(void *node);
	void rva004FF49F();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva004FF3DB::rva004FF3DB(void *node)
{
	if (!node)
		return;
	RvaTreeFamilyNode *cur = (RvaTreeFamilyNode *)node;
	do {
		rva004FF3DB(cur->m_child);
		RvaTreeFamilyNode *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva004FF3DB::rva004FF49F()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva004FF3DB(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva004FF408: erase 0x004FF408, clear 0x004FF4C8
class Rva004FF408
{
public:
	void rva004FF408(void *node);
	void rva004FF4C8();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva004FF408::rva004FF408(void *node)
{
	if (!node)
		return;
	RvaTreeFamilyNode *cur = (RvaTreeFamilyNode *)node;
	do {
		rva004FF408(cur->m_child);
		RvaTreeFamilyNode *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva004FF408::rva004FF4C8()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva004FF408(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva0053BAE1: erase 0x0053BAE1, clear 0x0053BCC4
class Rva0053BAE1
{
public:
	void rva0053BAE1(void *node);
	void rva0053BCC4();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva0053BAE1::rva0053BAE1(void *node)
{
	if (!node)
		return;
	RvaTreeFamilyNode *cur = (RvaTreeFamilyNode *)node;
	do {
		rva0053BAE1(cur->m_child);
		RvaTreeFamilyNode *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva0053BAE1::rva0053BCC4()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva0053BAE1(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva005980F3: erase 0x005980F3, clear 0x00598120
class Rva005980F3
{
public:
	void rva005980F3(void *node);
	void rva00598120();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva005980F3::rva005980F3(void *node)
{
	if (!node)
		return;
	RvaTreeFamilyNode *cur = (RvaTreeFamilyNode *)node;
	do {
		rva005980F3(cur->m_child);
		RvaTreeFamilyNode *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva005980F3::rva00598120()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva005980F3(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva005C45FE: erase 0x005C45FE, clear 0x005C4667
class Rva005C45FE
{
public:
	void rva005C45FE(void *node);
	void rva005C4667();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva005C45FE::rva005C45FE(void *node)
{
	if (!node)
		return;
	RvaTreeFamilyNode *cur = (RvaTreeFamilyNode *)node;
	do {
		rva005C45FE(cur->m_child);
		RvaTreeFamilyNode *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva005C45FE::rva005C4667()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva005C45FE(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva005C8C73: erase 0x005C8C73, clear 0x005C8CDA
class Rva005C8C73
{
public:
	void rva005C8C73(void *node);
	void rva005C8CDA();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva005C8C73::rva005C8C73(void *node)
{
	if (!node)
		return;
	RvaTreeFamilyNode *cur = (RvaTreeFamilyNode *)node;
	do {
		rva005C8C73(cur->m_child);
		RvaTreeFamilyNode *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva005C8C73::rva005C8CDA()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva005C8C73(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

struct HashNode00056CF8;

// owner Rva00056CF8: erase 0x00056CF8 (rowed as ?rva00056CF8@Rva00056CF8@@QAEXPAUHashNode00056CF8@@@Z), clear 0x00057B74
class Rva00056CF8
{
public:
	void rva00056CF8(HashNode00056CF8 *node);
	void rva00057B74();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva00056CF8::rva00057B74()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva00056CF8((HashNode00056CF8 *)h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

struct Rva000B646BNode;

// owner Rva000B646B: erase 0x000B646B (rowed as ?rva000B646B@Rva000B646B@@QAEXPAURva000B646BNode@@@Z), clear 0x000B92FB
class Rva000B646B
{
public:
	void rva000B646B(Rva000B646BNode *node);
	void rva000B92FB();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva000B646B::rva000B92FB()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva000B646B((Rva000B646BNode *)h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva002D394B: erase 0x002D394B (rowed as ?rva002D394B@Rva002D394B@@QAEXPAX@Z), clear 0x002D43C6
class Rva002D394B
{
public:
	void rva002D394B(void *node);
	void rva002D43C6();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva002D394B::rva002D43C6()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva002D394B(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

struct Rva0038404ANode;

// owner Rva0038404A: erase 0x0038404A (rowed as ?rva0038404A@Rva0038404A@@QAEXPAURva0038404ANode@@@Z), clear 0x00384E8E
class Rva0038404A
{
public:
	void rva0038404A(Rva0038404ANode *node);
	void rva00384E8E();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva0038404A::rva00384E8E()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva0038404A((Rva0038404ANode *)h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva00395CEB: erase 0x00395CEB (rowed as ?rva00395CEB@Rva00395CEB@@QAEXPAX@Z), clear 0x0039611E
class Rva00395CEB
{
public:
	void rva00395CEB(void *node);
	void rva0039611E();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva00395CEB::rva0039611E()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva00395CEB(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva00395D18: erase 0x00395D18 (rowed as ?rva00395D18@Rva00395D18@@QAEXPAX@Z), clear 0x00396147
class Rva00395D18
{
public:
	void rva00395D18(void *node);
	void rva00396147();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva00395D18::rva00396147()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva00395D18(h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

struct Rva0057CC43Node;

// owner AptMapPreview: erase 0x0057CC43 (rowed as ?rva0057CC43@AptMapPreview@@QAEXPAURva0057CC43Node@@@Z), clear 0x0057CD78
class AptMapPreview
{
public:
	void rva0057CC43(Rva0057CC43Node *node);
	void rva0057CD78();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void AptMapPreview::rva0057CD78()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva0057CC43((Rva0057CC43Node *)h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

struct Node00599FAA;

// owner Rva00599FAA: erase 0x00599FAA (rowed as ?rva00599FAA@Rva00599FAA@@QAEXPAUNode00599FAA@@@Z), clear 0x0059A258
class Rva00599FAA
{
public:
	void rva00599FAA(Node00599FAA *node);
	void rva0059A258();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva00599FAA::rva0059A258()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva00599FAA((Node00599FAA *)h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

struct Rva0059BD58Node;

// owner Rva0059BD58: erase 0x0059BD58 (rowed as ?rva0059BD58@Rva0059BD58@@QAEXPAURva0059BD58Node@@@Z), clear 0x0059BDB9
class Rva0059BD58
{
public:
	void rva0059BD58(Rva0059BD58Node *node);
	void rva0059BDB9();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva0059BD58::rva0059BDB9()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva0059BD58((Rva0059BD58Node *)h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

struct Rva005ACF0BNode;

// owner Rva005ACF0B: erase 0x005ACF0B (rowed as ?rva005ACF0B@Rva005ACF0B@@QAEXPAURva005ACF0BNode@@@Z), clear 0x005AD085
class Rva005ACF0B
{
public:
	void rva005ACF0B(Rva005ACF0BNode *node);
	void rva005AD085();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva005ACF0B::rva005AD085()
{
	if (m_04Flag == 0)
		return;
	RvaTreeFamilyHead *h = (RvaTreeFamilyHead *)m_00Head;
	rva005ACF0B((Rva005ACF0BNode *)h->m_first);
	((RvaTreeFamilyHead *)m_00Head)->m_next = (RvaTreeFamilyHead *)m_00Head;
	((RvaTreeFamilyHead *)m_00Head)->m_first = 0;
	((RvaTreeFamilyHead *)m_00Head)->m_child = (RvaTreeFamilyHead *)m_00Head;
	m_04Flag = 0;
}

class Rva000589F6
{
public:
	void rva000589F6();
};

void Rva000589F6::rva000589F6()
{
	((Rva00056CF8 *)this)->rva00057B74();
}

class Rva0006FB4B
{
public:
	void rva0006FB4B();
};

void Rva0006FB4B::rva0006FB4B()
{
	((Rva0006F318 *)this)->rva0006FA70();
}

class Rva000D3940
{
public:
	void rva000D3940();
};

void Rva000D3940::rva000D3940()
{
	((Rva000D20A9 *)this)->rva000D2294();
}

class Rva001DD9B6
{
public:
	void rva001DD9B6();
};

void Rva001DD9B6::rva001DD9B6()
{
	((Rva001DD70F *)this)->rva001DD846();
}

class Rva00211F00
{
public:
	void rva00211F00();
};

void Rva00211F00::rva00211F00()
{
	((Rva0021119B *)this)->rva00211DD2();
}

class Rva002819C9
{
public:
	void rva002819C9();
};

void Rva002819C9::rva002819C9()
{
	((Rva0027F4CB *)this)->rva00280AB6();
}

class Rva002A8CCB
{
public:
	void rva002A8CCB();
};

void Rva002A8CCB::rva002A8CCB()
{
	((Rva002A8B8C *)this)->rva002A8BEE();
}

class Rva002D50A8
{
public:
	void rva002D50A8();
};

void Rva002D50A8::rva002D50A8()
{
	((Rva002D394B *)this)->rva002D43C6();
}

class Rva0038934F
{
public:
	void rva0038934F();
};

void Rva0038934F::rva0038934F()
{
	((Rva00388EAE *)this)->rva00389129();
}

class Rva003968CE
{
public:
	void rva003968CE();
};

void Rva003968CE::rva003968CE()
{
	((Rva00395CEB *)this)->rva0039611E();
}

class Rva004D1ABE
{
public:
	void rva004D1ABE();
};

void Rva004D1ABE::rva004D1ABE()
{
	((Rva004D0545 *)this)->rva004D0F82();
}

class Rva004D1AFB
{
public:
	void rva004D1AFB();
};

void Rva004D1AFB::rva004D1AFB()
{
	((Rva004D0572 *)this)->rva004D0FAB();
}

class Rva004E9592
{
public:
	void rva004E9592();
};

void Rva004E9592::rva004E9592()
{
	((Rva004E9419 *)this)->rva004E94A1();
}

class Rva004FF62B
{
public:
	void rva004FF62B();
};

void Rva004FF62B::rva004FF62B()
{
	((Rva004FF408 *)this)->rva004FF4C8();
}

class Rva005981C5
{
public:
	void rva005981C5();
};

void Rva005981C5::rva005981C5()
{
	((Rva005980F3 *)this)->rva00598120();
}
