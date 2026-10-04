// cl: /O1 /DNDEBUG /MD
// ?Rva003F5584CopyBackward@@YAPADPAD00@Z @0x003F5584 50B counted copy-backward stride 48.
// Evidence: (last-first)/0x30 with idiv then counted loop decrementing last/result before each Element assign 0x003F554C; callers 0x003F58B6; sibling of Rva003F1F38CopyBackward 0x003F1F38.
struct Rva003F610FElement
{
	Rva003F610FElement &operator=(const Rva003F610FElement &that);
};
char *__cdecl Rva003F5584CopyBackward(char *first, char *last, char *result)
{
	int n = (last - first) / 0x30;
	if (n <= 0)
		return result;
	for (; n != 0; --n)
	{
		last -= 0x30;
		result -= 0x30;
		*reinterpret_cast<Rva003F610FElement *>(result) = *reinterpret_cast<Rva003F610FElement *>(last);
	}
	return result;
}
