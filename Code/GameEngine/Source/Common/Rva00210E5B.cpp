// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva00210E5B@@YGXPAXH@Z @0x00210E5B 33B
// Target evidence: lookup through g_00DFEF18 using rowed 0x002BFDAE, then
// forward the second stack argument to 0x003FA781 on the returned entry. The
// entry is also used as the address-derived Rva003FA835 view by another target
// consumer. The operation and argument meaning remain unresolved.

class Rva002D3627Host;
extern Rva002D3627Host *g_00DFEF18;

class Rva002BFDAE
{
public:
	void *rva002BFDAE(void *key);
};

class Rva003FA835
{
public:
	void rva003FA781(int value);
};

void __stdcall rva00210E5B(void *key, int value)
{
	void *entry = ((Rva002BFDAE *)g_00DFEF18)->rva002BFDAE(key);
	if (entry)
		((Rva003FA835 *)entry)->rva003FA781(value);
}
