// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// AptLoadMovieFrame, the strategic HUD's load-dialog frame.
//
// The class name is WorldBuilder's (AptLoadMovieFrame.cpp, Impl::UnloadContent
// at 0x0057C236, rowed in Rva0057C236UnloadContent.cpp). StrategicHUD's
// OnLoadDialogFrameLoaded 0x0042DC04 news the 8-byte frame (vtable 0x00C6F304,
// one slot: the deleting destructor 0x0057C4E2) from the loaded movie's level
// and path; the frame owns its 0x1C-byte Impl at +4. The frame's rowed
// members (destructor 0x0057C3B6 and its Impl clear 0x0057C39C, the forwarders
// 0x0057C2CC and 0x0057C394) and the Impl's (destructor 0x0057C2D4,
// UnloadContent, LoadContent 0x0057C339) live in other units under address
// names; the layout below is the one they and the constructor 0x0057C3C4 use:
// level, path, the bound-name vector, the content callback, the loaded flag.
#include "ascii_string.h"

const char *__cdecl Rva00412845AfterLevel(const char *path);
int __cdecl Rva004128BBGetLevel(const char *path);

// The +0x08 member: the 12-byte list of bound callback names
// (AptCommandMapAdder, AptCallbackAdders.cpp; constructor 0x001F81BF).
class AptCommandMapAdder
{
	unsigned char m_pad[0xC];
};

// The +0x14 content callback: a reference-counted functor released by the
// rowed holder destructor 0x005F8F96 and fired through the rowed two-argument
// invoke 0x001531F2.
class Rva001531F2Ref
{
public:
	Rva001531F2Ref() : m_op(0) {}
	~Rva001531F2Ref();
	int invoke(int a, int b);
	bool isSet() const { return m_op != 0; }

private:
	void *m_op;
};

class AptLoadMovieFrame
{
public:
	class Impl;

	AptLoadMovieFrame(int level, const AsciiString &name);
	virtual ~AptLoadMovieFrame();

private:
	Impl *m_impl; // +0x04, owned
};

class AptLoadMovieFrame::Impl
{
public:
	Impl(int level, const AsciiString &name);

	void OnContentLoaded(const char *path);

private:
	int m_level; // +0x00: the movie's level, "_level%u"
	AsciiString m_name; // +0x04: the frame's path in the movie
	AptCommandMapAdder m_bindings; // +0x08
	Rva001531F2Ref m_onLoaded; // +0x14: set by LoadContent 0x0057C339
	bool m_loaded; // +0x18: set by LoadContent, cleared by UnloadContent
};

// Retail 0x0057C26C, 96 bytes: bound as "_level%u.<path>_OnContentLoaded";
// hands the loaded content's level and path to the LoadContent callback.
void AptLoadMovieFrame::Impl::OnContentLoaded(const char *path)
{
	if (m_loaded && m_onLoaded.isSet())
	{
		AsciiString name(Rva00412845AfterLevel(path));
		m_onLoaded.invoke(Rva004128BBGetLevel(path), (int)&name);
	}
}

// Retail 0x0057C499, 73 bytes. The Impl constructor 0x0057C3C4 binds
// OnContentLoaded under "_level%u.<path>_OnContentLoaded".
AptLoadMovieFrame::AptLoadMovieFrame(int level, const AsciiString &name)
	: m_impl(new Impl(level, name))
{
}
