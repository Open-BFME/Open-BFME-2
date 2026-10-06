// ?rva0046AA85@Rva0046AA85@@QAEXXZ
// partial score=0.82 date=2026-10-06
// cl: /MD
// Target evidence: Ghidra boundary 0x0046AA85, 51 bytes. The matched pair
// helper 0x0046247D supplies a list view at this+0x54; the body walks its
// sentinel-linked nodes and calls 0x00469F3A with each payload. Node links at
// +0 and payload at +8 follow the target reads. The cleanup callee's pin is
// address-derived and does not assert its unresolved owner or purpose.
struct Rva0046AA85ListNode {
	Rva0046AA85ListNode *next;
	Rva0046AA85ListNode *previous;
	void *payload;
};

struct Rva0046AA85ListView {
	Rva0046AA85ListNode *sentinel;
};

struct Rva0046247DPair {
	void *first;
	Rva0046AA85ListView *second;
};

class Rva0046247D {
public:
	void rva0046247D(Rva0046247DPair &result);
};

class Rva00469F3A {
public:
	void rva00469F3A(void *payload);
};

class Rva0046AA85 {
public:
	void rva0046AA85();
};

void Rva0046AA85::rva0046AA85()
{
	Rva0046247DPair pair;
	((Rva0046247D *)this)->rva0046247D(pair);
	register Rva0046AA85ListView *list = pair.second;
	register Rva0046AA85ListNode *node = list->sentinel->next;
	while (node != list->sentinel) {
		((Rva00469F3A *)this)->rva00469F3A(node->payload);
		node = node->next;
	}
}
