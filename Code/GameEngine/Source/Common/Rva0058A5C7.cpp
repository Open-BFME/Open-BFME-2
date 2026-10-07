// cl: /O1 /MD
// ?rva0058A5C7@Rva0058A5C7@@QAEH... @0x0058A5C7 80B
// Linear search over a 41-entry string table. Evidence: exact retail disasm
// (null-key early -1, StringBase temp per table entry via rowed char-ctor
// 0x37BA0 (public QAE spelling, pre-pinned), compare via rowed 0x69B1
// with neg/sbb/inc zero-to-bool, explicit clear via pinned 0x36410,
// index-or-minus-1 return). Non-EH: the temp has a trivial view-dtor and is
// released explicitly, so no unwind prolog. Table address is DIR32-masked
// like vtables.
// class-gate: allow StringBase trivial-dtor codegen view; retail is non-EH with explicit clear (not scope dtor), and the shared header's non-trivial dtor forces an EH prolog (119B vs 80B)
template<typename T> class StringBase
{
public:
	StringBase(const char *s);
	int compare(const char *s) const;
	void clear();
private:
	const void *m_data;
};

extern const char *g_00DD3068[];

int __cdecl rva0058A5C7(const char *key)
{
	int found = -1;
	if (key != 0)
	{
		for (int i = 0; i < 0x29; i++)
		{
			StringBase<char> tmp(g_00DD3068[i]);
			bool eq = (tmp.compare(key) == 0);
			tmp.clear();
			if (eq)
			{
				found = i;
				break;
			}
		}
	}
	return found;
}
