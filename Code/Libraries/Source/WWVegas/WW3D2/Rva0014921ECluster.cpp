// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// rva0014921e at 0x0014921E, 38 bytes. Address-derived free function; identity
// is not recovered. It calls the container's erase(begin,end) over the whole
// 4-byte-element buffer at +0/+4 (the ICF-folded STLport vector erase pinned at
// 0x00532803) and then hands (arg1, 0, buffer, arg4) to the unpinned worker at
// 0x00149002. The class name and the worker name are address-derived.

class Rva0014921EVector
{
public:
	int *m_begin; // +0
	int *m_end;   // +4

	void erase(int *first, int *last);
};

void rva00149002(int a, int b, Rva0014921EVector *buffer, int d);

void rva0014921e(int a, int b, Rva0014921EVector *buffer, int d)
{
	buffer->erase(buffer->m_begin, buffer->m_end);
	rva00149002(a, 0, buffer, d);
}
