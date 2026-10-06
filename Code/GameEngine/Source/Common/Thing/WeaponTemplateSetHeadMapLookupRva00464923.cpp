// cl: /O1 /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
//
// ?rva00464923@Rva00464923@@QAEAAVWeaponTemplateSetHead@@ABI@Z @0x00464923 (97B).
// Lookup-or-create of a 0x4C-byte WeaponTemplateSetHead under an unsigned key.
// Target calls the rowed unsigned lower_bound at 0x004FF3B6, the pair ctor at
// 0x0046262D, and the adjacent hinted-insert wrapper at 0x00464431. The map
// owner name is not established; the address-derived method preserves that.
#include <map>
#include <string.h>

class WeaponTemplateSetHead
{
public:
	__declspec(nothrow) WeaponTemplateSetHead(const WeaponTemplateSetHead &other);
private:
	unsigned int m_bits[19];
};

typedef _STL::map<unsigned int, WeaponTemplateSetHead, _STL::less<unsigned int>,
	_STL::allocator<_STL::pair<const unsigned int, WeaponTemplateSetHead> > >
	WeaponTemplateSetHeadMap;

typedef _STL::map<unsigned int, void *, _STL::less<unsigned int>,
	_STL::allocator<_STL::pair<const unsigned int, void *> > >
	UnsignedPointerMap;

class Rva0046262D
{
public:
	__declspec(nothrow) Rva0046262D(void *key, const WeaponTemplateSetHead &head);
private:
	void *m_key;
	WeaponTemplateSetHead m_head;
};

class Rva00464923
{
public:
	WeaponTemplateSetHead &rva00464923(const unsigned int &key);
};

WeaponTemplateSetHead &Rva00464923::rva00464923(const unsigned int &key)
{
	WeaponTemplateSetHeadMap *map = (WeaponTemplateSetHeadMap *)(void *)this;
	UnsignedPointerMap *lookup = (UnsignedPointerMap *)(void *)this;
	UnsignedPointerMap::iterator position = lookup->lower_bound(key);
	if (position == lookup->end() || key < position->first) {
		unsigned char emptyHead[0x4C];
		memset(emptyHead, 0, sizeof(emptyHead));
		unsigned char pairStorage[sizeof(Rva0046262D)];
		Rva0046262D *value = new (pairStorage) Rva0046262D((void *)&key,
			*(const WeaponTemplateSetHead *)(const void *)emptyHead);
		WeaponTemplateSetHeadMap::iterator hint =
			*(WeaponTemplateSetHeadMap::iterator *)(void *)&position;
		WeaponTemplateSetHeadMap::value_type &pair =
			*(WeaponTemplateSetHeadMap::value_type *)(void *)value;
		hint = map->insert(hint, pair);
		position = *(UnsignedPointerMap::iterator *)(void *)&hint;
	}
	return *(WeaponTemplateSetHead *)&position->second;
}
