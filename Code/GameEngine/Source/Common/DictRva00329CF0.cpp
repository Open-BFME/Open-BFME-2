// cl: /DNDEBUG /MD /EHsc
//
// ?Rva00329CF0@Dict@@QAEXPBV1@@Z @0x00329CF0 30B
// Dict nullable-pointer copy: clear then conditional assign.
// Evidence: same-this calls to rowed ?clear@Dict@@QAEXXZ at 0x00313574 (DictPairClear.cpp)
// and rowed ??4Dict@@QAEAAV0@ABV0@@Z at 0x003133E1 (Dict.cpp). This pointer preserved
// in esi across both calls. Caller at 0x0032DAB0 (unclaimed copy loop).
// Class proven by identical ecx for both Dict calls. Honest address name (no donor).

class Dict
{
public:
	void clear();
	Dict &operator=(const Dict &src);
	void Rva00329CF0(const Dict *src);
private:
	void *m_data;
};

void Dict::Rva00329CF0(const Dict *src)
{
	clear();
	if (src)
		*this = *src;
}
