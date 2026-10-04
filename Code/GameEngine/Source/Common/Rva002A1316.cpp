// cl: /O1 /DNDEBUG /MD
// ?Rva002A1316Store@@YGPAXPAPAXPAX0@Z retail 0x002A1316 37B
// Doubly-linked insert via rowed freelist store 0x0029FB80. Evidence: ret 0xC
// with 3 args returning first; push third for Store; link pos/next/node/out.
void *__stdcall Rva0029FB80Store(void **p);

void *__stdcall Rva002A1316Store(void **out, void *pos, void **val)
{
	void *node = Rva0029FB80Store(val);
	void *next = *(void **)((char *)pos + 4);
	*(void **)node = pos;
	*(void **)((char *)node + 4) = next;
	*(void **)next = node;
	*(void **)((char *)pos + 4) = node;
	*out = node;
	return out;
}

// Native 2A1B6F/26 appends one four-byte element to the sentinel at [ECX].
// Its 2A1B80 call reaches the rowed 37-byte insertion helper above. That
// helper consumes hidden result, iterator node, and element address on the
// stack, returns the result address, and has no receiver-dependent operation.
// Native 3320FC and BridgeBehavior's 457FC4 call independently establish
// this append ABI. Original template/class spelling remains unknown.
struct Rva002A1316Iterator
{
    // ?Rva002A1316Iterator::Rva002A1316Iterator present-unmatched
    explicit Rva002A1316Iterator(void *p) : node(p) {}
    // ?Rva002A1316Iterator::Rva002A1316Iterator present-unmatched
    Rva002A1316Iterator(const Rva002A1316Iterator &other) : node(other.node) {}
    void *node;
};

class Rva002A1B6FNativeList
{
public:
    void append(void *const &value);
private:
    Rva002A1316Iterator insert(Rva002A1316Iterator pos, void *const &value);
    // ?Rva002A1B6FNativeList::end present-unmatched
    Rva002A1316Iterator end() { return Rva002A1316Iterator(head); }
    void *head;
};
#pragma comment(linker, "/alternatename:?insert@Rva002A1B6FNativeList@@AAE?AURva002A1316Iterator@@U2@ABQAX@Z=?Rva002A1316Store@@YGPAXPAPAXPAX0@Z")

void Rva002A1B6FNativeList::append(void *const &value)
{
    insert(end(), value);
}
