// ?rva000CAFA6@Rva000CAFA6@@QAEXHH@Z
// partial score=0.93 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /GX /MD /DNDEBUG /O1 /arch:SSE /G7
// ?rva000CAFA6@Rva000CAFA6@@QAEXHH@Z @ 0x000CAFA6 328B
// Evidence: vtable slot 8 at 0x007CBEF8; adjacent RenderObjClass animation slot; target string field and drawable/base offsets are observed structurally, class identity remains unknown.

extern "C" int __cdecl sprintf(char *buffer, const char *format, ...);
extern "C" double __cdecl ceil(double value);

class Coord3D;
class Matrix3D;

class Drawable
{
public:
	int getPristineBonePositions(const char *name, int priority, Coord3D *coord,
		Matrix3D *matrix, int flags, int index) const;
};

struct StringHeader
{
	int refs;
	unsigned short length;
	unsigned short capacity;
	char data[1];
};

template <class T>
class StringBase
{
public:
	StringHeader *m_data;
	StringBase(const StringBase<T> &that);
	StringBase(const char *text);
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();
	const char *c_str() const { return m_data ? m_data->data : ""; }
};

class Rva000CAFA6
{
public:
	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
	virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
	virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
	virtual void pad12(); virtual void pad13(); virtual void pad14(); virtual void pad15();
	virtual void pad16(); virtual void pad17(); virtual void pad18(); virtual void pad19();
	virtual void pad20(); virtual void pad21(); virtual void pad22(); virtual void pad23();
	virtual void pad24(); virtual void pad25(); virtual void pad26(); virtual void pad27();
	virtual void pad28(); virtual void pad29(); virtual void pad30(); virtual void pad31();
	virtual void pad32(); virtual void pad33();
	virtual void setFrame(float start, float end, const StringBase<char> &name, int reverse, int flags);
	char m_pad04[0x2D8];
	int m_boneCount;
	int m_frame;
	void rva000CAFA6(int frame, int rate);
};

void Rva000CAFA6::rva000CAFA6(int rate, int frame)
{
	char *owner = *(char **)((char *)this - 8);
	StringBase<char> prefix(*(StringBase<char> *)(owner + 0x188));
	if (m_boneCount == -1) {
		const char *name = prefix.c_str();
		if (!prefix.m_data)
			name = "";
		m_boneCount = (*(Drawable **)((char *)this - 4))->getPristineBonePositions(
			name, 1, 0, 0, 0x7fffffff, 0);
		m_frame = m_boneCount;
	}
	frame = (int)ceil(((double)frame / (double)rate) * m_boneCount);
	if (frame > m_boneCount)
		frame = m_boneCount;
	int old = m_frame;
	if (frame != old) {
		int *low = &m_frame;
		if (frame < m_frame)
			low = &frame;
		int *high = &m_frame;
		if (m_frame > frame)
			high = &frame;
		bool reverse = !(frame < m_frame);
		for (int i = *low + 1; i <= *high; ++i) {
			char buffer[40];
			const char *name = prefix.c_str();
			if (!prefix.m_data)
				name = "";
			sprintf(buffer, "%s%02d", name, i);
			StringBase<char> animationName(buffer);
			setFrame(0.0f, 0.0f, animationName, reverse, 0);
		}
		m_frame = frame;
	}
}
