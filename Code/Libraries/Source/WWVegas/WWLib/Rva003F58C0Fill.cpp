// cl: /O1 /DNDEBUG /MD
// ?Rva003F58C0Fill@@YAXPAD00@Z @0x003F58C0 29B range fill stride 48.
// Evidence: while first!=last assign Element 0x003F554C from value and advance 0x30; callers 0x003F624D/0x003F628D; sibling of Rva003F1ECEFill 0x003F1ECE.
struct Rva003F610FElement
{
	Rva003F610FElement &operator=(const Rva003F610FElement &that);
};
void __cdecl Rva003F58C0Fill(char *first, char *last, char *value)
{
	for (; first != last; first += 0x30)
		*reinterpret_cast<Rva003F610FElement *>(first) = *reinterpret_cast<Rva003F610FElement *>(value);
}
