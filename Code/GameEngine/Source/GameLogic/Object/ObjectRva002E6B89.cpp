// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva002E6B89@Object@@QAE_NXZ @0x002E6B89 24B.
// Proven Object method: all 9 callers pass Object* as this (e.g. 0x002EC935
// mov ecx esi after Object getter 0x0028B511; 0x002F1497 mov ecx esi after
// findObjectByID; 0x002F1443 mov ecx [esi+8] Object field). Byte-exact model:
// visit-stamp at +0x224 vs global counter at 0x00DFECD0 (inc in callers
// 0x002EC92F 0x002F13A8): if equal return true else store and return false.
// Evidence: callers test al al and jne to skip on true (0x002F144B 0x002F149E)
// proves byte bool return; callees none; flags /O1 from ObjectRvaSmallGetters.
// Taking &m_224 into a local first gives retail lea eax plus mov ecx global
// order per shape-lever load-order rule; direct member compare gives add ecx.

class Object
{
	char m_pad[0x224];
	int m_224;
public:
	bool rva002E6B89();
};

// g_Va00DFECD0: VA 0x00DFECD0 (.data/bss); zero-filled retail dword counter.
int g_Va00DFECD0;

bool Object::rva002E6B89()
{
	int *p = &m_224;
	int cur = g_Va00DFECD0;
	if (*p == cur)
		return true;
	*p = cur;
	return false;
}
