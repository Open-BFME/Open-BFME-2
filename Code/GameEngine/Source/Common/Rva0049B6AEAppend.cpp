// cl: /MD
// ?Rva0049B6AEAppend@@YGXPBDPAV?$StringBase@D@@@Z, retail 0x0049B6AE, 47 bytes.
// Path-like join: if String non-null and non-empty prepend default at 0x00BBD40C then append char arg.
// Evidence: callees isEmpty 0x1E2F concat 0x5629 rowed; callers 8x 234B; prev Disp8 next UpdateDeletingDtors.
template <class T>
class StringBase
{
public:
	bool isEmpty() const;
	void concat(const T *str);
};

typedef StringBase<char> AsciiStringType;

void __stdcall Rva0049B6AEAppend(const char *a, StringBase<char> *b)
{
	if (b == 0)
		return;
	if (!b->isEmpty())
		b->concat(" ");
	b->concat(a);
}
