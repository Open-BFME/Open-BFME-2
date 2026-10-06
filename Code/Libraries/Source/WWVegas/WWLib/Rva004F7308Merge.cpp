// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// ?Rva004F7308Merge@@YAPAUTreeHintRef00217D4C@@PAU1@0000@Z, retail 0x004F7308, 166 bytes.
// Evidence: free merge of TreeHintRef ranges descending by key at [m_ptr+8]+0xc; calls ReleaseTreeHintRef00217D4C operator= Rva004F6E47Copy; prev Rva004F72EDDestroy next stlport_rva004f6352_sort; 5 args first1 last1 first2 last2 result.
struct KeyObj004F7308
{
	char m_pad[0xc];
	int m_key;
};
struct TargetRef00217D4C
{
	void *m_vtbl;
	int m_refs;
	KeyObj004F7308 *m_p08;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
	TreeHintRef00217D4C(const TreeHintRef00217D4C &o) : m_ptr(o.m_ptr) { if (m_ptr) ++m_ptr->m_refs; }
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &o);
	~TreeHintRef00217D4C() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};
TreeHintRef00217D4C *Rva004F6E47Copy(TreeHintRef00217D4C *first, TreeHintRef00217D4C *last, TreeHintRef00217D4C *result);
TreeHintRef00217D4C *Rva004F7308Merge(TreeHintRef00217D4C *first1, TreeHintRef00217D4C *last1, TreeHintRef00217D4C *first2, TreeHintRef00217D4C *last2, TreeHintRef00217D4C *result)
{
	while (first1 != last1 && first2 != last2) {
		bool g;
		{
			TreeHintRef00217D4C a = *first1;
			TreeHintRef00217D4C b = *first2;
			int kb = b.m_ptr->m_p08->m_key;
			g = kb > a.m_ptr->m_p08->m_key;
		}
		if (g) {
			*result = *first2;
			++first2;
		} else {
			*result = *first1;
			++first1;
		}
		++result;
	}
	return Rva004F6E47Copy(first2, last2, Rva004F6E47Copy(first1, last1, result));
}
