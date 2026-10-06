// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva00241955Insert@@YG?AURva00241955Iter@@U1@ABUBfmeStringRecord00239B46@@@Z retail 0x00241955 37B
// Free stdcall list insert twin of 0x00239E80 via rowed create 0x00240C89 then hook before pos and return via hidden.
// Evidence: chain lane calls just-landed 0x00240C89; same 37B shape as list BfmeStringRecord insert 0x00239E80; caller 0x00242EE7.
struct BfmeStringRecord00239B46
{
	unsigned char m_data[8];
};
struct Rva00240C89Node
{
	struct Rva00240C89Node *_M_next;
	struct Rva00240C89Node *_M_prev;
	struct BfmeStringRecord00239B46 _M_data;
};
struct Rva00240C89Node *__stdcall Rva00240C89Create(const struct BfmeStringRecord00239B46 &x);
struct Rva00241955Iter
{
	struct Rva00240C89Node *_M_node;
	Rva00241955Iter(struct Rva00240C89Node *x) : _M_node(x) {}
	Rva00241955Iter() {}
};
struct Rva00241955Iter __stdcall Rva00241955Insert(struct Rva00241955Iter pos, const struct BfmeStringRecord00239B46 &x)
{
	struct Rva00240C89Node *tmp = Rva00240C89Create(x);
	struct Rva00240C89Node *n = pos._M_node;
	struct Rva00240C89Node *p = n->_M_prev;
	tmp->_M_next = n;
	tmp->_M_prev = p;
	p->_M_next = tmp;
	n->_M_prev = tmp;
	return (struct Rva00241955Iter)tmp;
}
