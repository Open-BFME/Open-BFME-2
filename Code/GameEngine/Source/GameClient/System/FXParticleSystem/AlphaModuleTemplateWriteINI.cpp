// cl: /O1 /arch:SSE /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ?writeINI@?$DefaultModuleTemplate@$0A@@FXParticleSystem@@UBEXAAVFile@@I@Z
// @0x0055B735 302B: the alpha (category 0) particle module template's INI
// writer, slot 3 of vtables 0x0081BA70 (DefaultModuleTemplate<0>) and
// 0x0081BF20 (its ConcreteModuleTemplate). After the rowed alpha header
// 0x0055B65D it writes each of the eight alpha keyframes that is not the
// default (a zero random variable, rowed test 0x001F3744, at frame 0) as
// "Alpha<n> = <variable> <frame>", through the rowed pad 0x001F6951 and
// variable writer 0x001F87D5, then the rowed file write 0x001F458B and
// footer 0x003AFC6B. Built /O1 like the wind writer.
#include <sstream>

class File {
public:
	virtual ~File();
	virtual bool open(const char *n, int a = 0);
	virtual void close();
	virtual int read(void *b, int bsz);
	virtual int write(const void *b, int bsz);
};
struct Rva001F458BText {
	const char *m_start;
	const char *m_finish;
};
File &Rva001F458BWrite(File &file, const Rva001F458BText &text);
extern "C" void __cdecl free(void *p);

void Rva0055B65DWriteHeader(const void *self, File *file, unsigned int *flags);
void Rva003AFC6BWrite(File *file, unsigned int *flags);

struct S001F87D5 {
	char _0[4];
	float x;
	float y;
};
struct S001F3744 {
	char m_00[4];
	float m_04;
	float m_08;
};
bool __cdecl Rva001F3744IsZero(const S001F3744 *p);
_STL::basic_ostream<char, _STL::char_traits<char> > &Rva001F6951Pad(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int n);
_STL::basic_ostream<char, _STL::char_traits<char> > &Rva001F87D5Put(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	const S001F87D5 &s);

namespace FXParticleSystem {

struct AlphaKeyframe {
	S001F87D5 m_alpha;
	unsigned int m_frame;
};

template <int Category> class DefaultModuleTemplate;

template <> class DefaultModuleTemplate<0> {
public:
	virtual void writeINI(File &file, unsigned int flags) const;

private:
	void *m_moduleClassView;
	void *m_moduleInfoView;
	AlphaKeyframe m_keyframes[8];	// 0x0C
};

void DefaultModuleTemplate<0>::writeINI(File &file, unsigned int flags) const
{
	Rva0055B65DWriteHeader(this, &file, &flags);
	_STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > oss(16);
	for (unsigned int i = 0; i < 8; ++i)
	{
		if (!Rva001F3744IsZero((const S001F3744 *)&m_keyframes[i].m_alpha) || m_keyframes[i].m_frame != 0)
		{
			Rva001F6951Pad(oss, flags) << "Alpha" << (unsigned long)(i + 1) << " = ";
			Rva001F87D5Put(oss, m_keyframes[i].m_alpha) << ' ' << (unsigned long)m_keyframes[i].m_frame << '\n';
		}
	}
	Rva001F458BWrite(file, (const Rva001F458BText &)oss.str());
	Rva003AFC6BWrite(&file, &flags);
}

} // namespace FXParticleSystem
