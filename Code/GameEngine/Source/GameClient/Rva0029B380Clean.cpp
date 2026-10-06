// cl: /MD
// ?rva0029B380@Rva0029B380@@QAEXH@Z @0x0029B380 65B.
// Array at +0x5D0 elem 16B: release wide StringBase at +0 then virtual slot 0x3C on global 0xDFEAD8 with ptr at +4 then zero +4 +8.
// Caller 0x002A1684. Unlocks 0x002A1582.
extern class DisplayStringManager *TheDisplayStringManager;

template <typename T> class StringBase {
public: ~StringBase() { releaseBuffer(); }
private: void releaseBuffer();
	T *m_data; };
class Rva0029B380Holder {
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(void *p);
};
struct Rva0029B380Elem {
	StringBase<unsigned short> m_0;
	void *m_4;
	int m_8;
	int m_C;
};
class Rva0029B380 {
public:
 	void rva0029B380(int idx);
	void rva0029B34B();
private:
 	char m_pad[0x5D0];
 	Rva0029B380Elem m_items[128];
};
void Rva0029B380::rva0029B380(int idx)
{
 	m_items[idx].m_0.~StringBase<unsigned short>();
 	void *p = m_items[idx].m_4;
 	if (p != 0)
 		(*(Rva0029B380Holder **)&TheDisplayStringManager)->s15(p);
 	m_items[idx].m_4 = 0;
 	m_items[idx].m_8 = 0;
}

// ?rva0029B34B@Rva0029B380@@QAEXXZ @0x0029B34B 53B.
// Loop version of rva0029B380 over the first 6 entries at +0x5D0.
// Evidence: same elem release virtual s15 zero pattern as 0x0029B380 in this TU.
void Rva0029B380::rva0029B34B()
{
	for (int i = 0; i < 6; ++i) {
		m_items[i].m_0.~StringBase<unsigned short>();
		void *p = m_items[i].m_4;
		if (p != 0)
			(*(Rva0029B380Holder **)&TheDisplayStringManager)->s15(p);
		m_items[i].m_4 = 0;
		m_items[i].m_8 = 0;
	}
}
