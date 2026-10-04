// cl: /O1 /DNDEBUG /MD
// ?Rva002D0BB8Copy@@YAPADPAD00@Z @0x002D0BB8 50B counted copy stride 92.
// Evidence: (last-first)/0x5C with idiv then counted loop calling bfmeAssign 0x00064605; caller 0x002D0D71; sibling of Rva003F58F8Copy 0x003F58F8.
struct BfmeCopyElementA
{
	BfmeCopyElementA *bfmeAssign(BfmeCopyElementA *source);
};
char *__cdecl Rva002D0BB8Copy(char *first, char *last, char *result)
{
	int n = (last - first) / 0x5C;
	if (n <= 0)
		return result;
	for (; n != 0; --n, first += 0x5C, result += 0x5C)
		((BfmeCopyElementA *)result)->bfmeAssign((BfmeCopyElementA *)first);
	return result;
}
