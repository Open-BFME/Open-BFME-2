// cl: /O1 /DNDEBUG /MD
// ?Rva003F58F8Copy@@YAPADPAD00@Z @0x003F58F8 50B counted copy stride 48.
// Evidence: (last-first)/0x30 with idiv then counted loop calling Element assign 0x003F554C per element incrementing first/result; caller 0x003F5B51; sibling of Rva003F1F06Copy 0x003F1F06 and Rva003F5584CopyBackward 0x003F5584.
struct Rva003F610FElement
{
	Rva003F610FElement &operator=(const Rva003F610FElement &that);
};
char *__cdecl Rva003F58F8Copy(char *first, char *last, char *result)
{
	int n = (last - first) / 0x30;
	if (n <= 0)
		return result;
	for (; n != 0; --n, first += 0x30, result += 0x30)
		*reinterpret_cast<Rva003F610FElement *>(result) = *reinterpret_cast<Rva003F610FElement *>(first);
	return result;
}
