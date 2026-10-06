// cl: /EHsc /MD
//
// ?Rva00447FD5Append@@YAPADPADPAV?$StringBase@D@@0@Z @0x00447FD5 88B.
// Checked string append: dst->set(static at 0x00BBAC1C), then append src chars
// via concat until null with limit checks, return past null (src/limit on
// early-out). Evidence: unlock lane; callees set 0x000055F5 concat 0x000369A0
// rowed; caller at 0x00448461; neighbours share flags.
template <typename T> class StringBase
{
public:
	void set(const char *s);
	void concat(const char *s, int len);
private:
	T *m_data;
};

char *__cdecl Rva00447FD5Append(char *src, StringBase<char> *dst, char *limit)
{
	dst->set("");
	if (limit != 0) {
		if (src >= limit)
			return src;
		if (limit - src < 1)
			return src;
	}
	while (*src != 0) {
		if (limit != 0) {
			if (src >= limit)
				return limit;
		}
		char tmp = *src;
		dst->concat(&tmp, 1);
		++src;
	}
	return src + 1;
}
