// cl: /DNDEBUG /MD
// ?Rva005E1A87Copy@@YAPAUTreeHintRef00217D4C@@PBU1@0PAU1@@Z @0x005E1A87 47B unlock copy of TreeHintRef via rowed operator= with sar-2 count loop.
// Evidence: retail sub+sar count then push esi loop calling rowed ??4TreeHintRef00217D4C@@QAEAAU0@ABU0@@Z 0x002174A4; returns final dest; caller 0x004F6A35.
struct TreeHintRef00217D4C
{
	void *m_ptr;
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
};

TreeHintRef00217D4C *__cdecl Rva005E1A87Copy(const TreeHintRef00217D4C *first, const TreeHintRef00217D4C *last, TreeHintRef00217D4C *result)
{
	int n = (int)(last - first);
	if (n <= 0)
		return result;
	int left = n;
	do {
		*result = *first;
		++first;
		++result;
	} while (--left != 0);
	return result;
}
