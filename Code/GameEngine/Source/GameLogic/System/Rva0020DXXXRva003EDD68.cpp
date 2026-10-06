// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva003EDD68@Rva0020DXXXElem@@QAE?AVRva003ED658@@XZ @0x003EDD68 108B ret 4.
// Elem range at +0x1C/+0x20 merged into ObjectCreationList then copy-constructed to out.
// Unblocks 0x0020D86C. Callees rowed or pinned. Offsets match Rva0020DXXXElem in ScriptGlueRva003EDC31.

class Rva003ED9B1
{
public:
	void rva003ED9B1(Rva003ED9B1 const &src);
};

class Rva003ED658
{
public:
	Rva003ED658(Rva003ED658 const &src);
	~Rva003ED658();
	char m_pad[12];
};

class Rva003ED94FDtor
{
public:
	~Rva003ED94FDtor();
	void *m_begin;
	void *m_end;
};

class ObjectCreationList
{
public:
	ObjectCreationList();
	Rva003ED94FDtor m_vec;
	void *m_endAlloc;
};

class Rva0020DXXXElem
{
public:
	Rva003ED658 rva003EDD68();
private:
	char m_pad00[0x1C];
	void **m_begin;
	void **m_end;
};

Rva003ED658 Rva0020DXXXElem::rva003EDD68()
{
	ObjectCreationList list;
	for (void **it = m_begin, *end = m_end; it != end; ++it)
		((Rva003ED9B1 *)&list)->rva003ED9B1(*(Rva003ED9B1 const *)*it);
	return *(Rva003ED658 const *)&list;
}
