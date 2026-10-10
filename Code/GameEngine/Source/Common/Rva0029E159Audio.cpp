// cl: /MD /EHsc /DNDEBUG
// WorldBuilder DA7520 names InGameUI::FormationPreviewDecal's constructor
// at InGameUI.cpp:314. The complete native 29E159..29E1EF body initializes
// its four-byte shadow handle using ShadowTypeInfo and manager slot 8.
// The source descriptor is an AsciiString followed by two decal dimensions.
// AudioManager0029E159 below is the existing borrowed manager ABI view;
// its legacy type spelling is retained to preserve the current global binding.
typedef int Int;

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	StringBase(const StringBase<T> &that);
	void releaseBuffer();
public:
	void set(const StringBase<T> &that);	// rowed 0x000366F0
	StringBase() : m_data(0) {}
	~StringBase() { releaseBuffer(); }
	bool isEmpty() const;
private:
	BfmeStringData<T> *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString() {}
	AsciiString(const AsciiString &that) : StringBase<char>(that) {}
	~AsciiString() {}
	// Inline, as retail expands it: StringBase<char>::set (0x000366F0) is called directly, not the
	// out-of-line copy at 0x00001733 the ledger rows ??4AsciiString on (link census, 2026-10-06).
	AsciiString &operator=(const AsciiString &other) { set(other); return *this; }
};

// The descriptor is Shadow::ShadowTypeInfo (rowed ctor 0x00079514 and dtor
// 0x000793FA); the type set below (0x20) is its +8 shadow type.
class Shadow
{
public:
	struct ShadowTypeInfo
	{
		ShadowTypeInfo();
		~ShadowTypeInfo();
		AsciiString m_first;
		AsciiString m_second;
		Int m_type;
		float m_floatC;
		float m_float10;
		float m_float14;
		float m_float18;
		float m_float1C;
		float m_float20;
		unsigned char m_byte24;
		unsigned char m_byte25;
		unsigned char m_byte26;
	};
};

struct Source0029E159
{
	AsciiString m_name;
	float m_x;
	float m_y;
};

class AudioManager0029E159
{
public:
	virtual ~AudioManager0029E159() {}
	virtual void s04() = 0;
	virtual int addDecal(Shadow::ShadowTypeInfo *ev) = 0;
};

// g_00DEC2D4: matched references place it at VA 0xdec2d4 (retail .data initial value 0).
AudioManager0029E159 * g_00DEC2D4 = 0;
class InGameUI { public: class FormationPreviewDecal; };
class InGameUI::FormationPreviewDecal
{
 int m_handle;
public:
 FormationPreviewDecal(const Source0029E159 &src);
};

InGameUI::FormationPreviewDecal::FormationPreviewDecal(const Source0029E159 &src)
{
	m_handle = 0;
	if (src.m_name.isEmpty())
		return;
	Shadow::ShadowTypeInfo ev;
	ev.m_first = src.m_name;
	ev.m_floatC = src.m_x;
	AudioManager0029E159 *mgr = g_00DEC2D4;
	ev.m_float10 = src.m_y;
	ev.m_byte25 = 0;
	ev.m_byte26 = 1;
	ev.m_type = 0x20;
	ev.m_float14 = 0.0f;
	ev.m_float18 = 0.0f;
	m_handle = mgr->addDecal(&ev);
	return;
}
