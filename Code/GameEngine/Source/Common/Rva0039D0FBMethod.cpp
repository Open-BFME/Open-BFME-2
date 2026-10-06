// cl: /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ?rva0039D0FB@Rva0039D0FB@@QAEXIH@Z 0x0039D0FB 117 dual map add via rowed _M_find 0x00357180 and ImageSubscriptMap operator[] 0x002077D6
// 117B __thiscall with ints at +0x74 +0x1c4 and maps at +0x1d4 +0x2ec; callers 0x00480554 pass Player+0x3bc with Image key and count.
// Same find+subscript shape as Rva00222F0A (find) and Rva00358333 (subscript cast).
#include <map>

class Image;

class ImageSubscriptMap
{
public:
	Image *&operator[](const unsigned int &key);
};

struct Rva0039D0FB
{
	char m_pad00[0x74];
	int m_74;
	char m_pad01[0x1c4 - 0x74 - 4];
	int m_1c4;
	char m_pad02[0x1d4 - 0x1c4 - 4];
	_STL::map<unsigned int, void *> m_map1d4;
	char m_pad03[0x2ec - 0x1d4 - 12];
	_STL::map<unsigned int, void *> m_map2ec;
	void rva0039D0FB(unsigned int key, int delta);
};

void Rva0039D0FB::rva0039D0FB(unsigned int key, int delta)
{
	m_74 += delta;
	m_1c4 += delta;
	void *old1 = 0;
	_STL::map<unsigned int, void *>::iterator it1 = m_map2ec.find(key);
	if (it1 != m_map2ec.end())
		old1 = it1->second;
	((ImageSubscriptMap *)&m_map2ec)->operator[](key) = (Image *)((char *)old1 + delta);
	void *old2 = 0;
	_STL::map<unsigned int, void *>::iterator it2 = m_map1d4.find(key);
	if (it2 != m_map1d4.end())
		old2 = it2->second;
	((ImageSubscriptMap *)&m_map1d4)->operator[](key) = (Image *)((char *)old2 + delta);
}
