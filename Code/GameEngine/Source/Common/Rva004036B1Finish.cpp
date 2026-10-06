// cl: /MD /Oy-
// ?rva004036B1@Rva004036B1@@QAE_NPAXPAMPBV?$StringBase@D@@@Z @0x004036B1 (92B)
// Thiscall range find over 0x14-byte elems comparing key at +0 then an
// optional StringBase filter against the inner pointer list at +8/+0xC via
// rowed compare 0x000069D6 then copying float at +4 to out. Caller 0x00214795.
// Evidence unlock lane plus key float string rows.
template <typename T> class StringBase {
public: int compare(const StringBase &other) const;
private: void *m_data;
};
struct Elem004036B1 {
	void *m_key;
	float m_val;
	StringBase<char> *m_strBegin;
	StringBase<char> *m_strEnd;
	int m_pad10;
};
class Rva004036B1 {
public:
	bool rva004036B1(void *key, float *out, const StringBase<char> *filter);
private:
	Elem004036B1 *m_begin;
	Elem004036B1 *m_end;
};
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
bool Rva004036B1::rva004036B1(void *key, float *out, const StringBase<char> *filter)
{
	for (Elem004036B1 *p = m_begin; p != m_end; p++) {
		if (p->m_key == key) {
			if (filter != 0) {
				unsigned n = (unsigned)(p->m_strEnd - p->m_strBegin);
				if (n <= 0)
					goto copy;
				_ReadWriteBarrier();
				for (StringBase<char> *s = p->m_strBegin; s != p->m_strEnd; s++) {
					if (s->compare(*filter) == 0)
						goto copy;
				}
				return false;
			}
		copy:
			*out = p->m_val;
			return true;
		}
	}
	return false;
}
