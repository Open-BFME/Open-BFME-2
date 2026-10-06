// cl: /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/shims/bfmevector /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ?rva001553C0@Rva001553C0@@QAEXPAURva001553C0_Node@@@Z at 0x001553C0 51B: recursive free of sibling/child tree via free.
// Evidence: self-call 0x001553C0, free 0x00030830 rowed, callers 0x00156640 and 0x00156FA0 reset list sentinel.

extern "C" void __cdecl free(void *block);

struct Rva001553C0_Node
{
	void *unk00;
	void *unk04;
	Rva001553C0_Node *next;
	Rva001553C0_Node *child;
};

class Rva001553C0
{
public:
	void rva001553C0(Rva001553C0_Node *node);
};

void Rva001553C0::rva001553C0(Rva001553C0_Node *node)
{
	if (node == 0)
		return;
	Rva001553C0_Node *cur = node;
	do {
		rva001553C0(cur->child);
		Rva001553C0_Node *next = cur->next;
		free(cur);
		cur = next;
	} while (cur != 0);
}
