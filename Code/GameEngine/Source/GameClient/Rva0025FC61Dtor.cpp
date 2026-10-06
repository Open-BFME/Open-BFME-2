// cl: /MD /EHsc
// ??1Rva0025FC61@@MAE@XZ 0x0025FC61 89B: dtor of SubtitleEntry-derived class with vtable 0x007F63F8.
// Evidence: stores vtable at [this], loops over count at +0x30 releasing array at +0x24 via global at 0x009FEAD8 slot 0x3c, then calls base ??1SubtitleEntry@@MAE@XZ at 0x006885A0. Caller 0x0025FF73 is its ??_G deleting dtor.
template <typename T> class StringBase {
public:  ~StringBase();
private: T *m_data; };
class SubtitleEntry
{
protected:
	virtual ~SubtitleEntry();
private:
	StringBase<unsigned short> m_text;
	unsigned int m_color;
	int m_style;
	int m_alignment;
	int m_line;
	int m_startFrame;
	int m_endFrame;
	bool m_displayed;
};

class DisplayManager
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual void f6();
	virtual void f7();
	virtual void f8();
	virtual void f9();
	virtual void f10();
	virtual void f11();
	virtual void f12();
	virtual void f13();
	virtual void f14();
	virtual void FreeEntry(void *p);
};

extern DisplayManager *g_009FEAD8;

class Rva0025FC61 : public SubtitleEntry
{
protected:
	virtual ~Rva0025FC61();
private:
	void *m_items[3];
	int m_count;
};

Rva0025FC61::~Rva0025FC61()
{
	for (int i = 0; i < m_count; ++i)
	{
		g_009FEAD8->FreeEntry(m_items[i]);
		m_items[i] = 0;
	}
}
