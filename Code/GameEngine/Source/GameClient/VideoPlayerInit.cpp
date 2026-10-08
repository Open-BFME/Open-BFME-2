// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O2 /Ob2
// Clean donor: Open-BFME-1 34f59164f6d1efd413c5fd37f4894ec834c3c0fe
// game/GameEngine/Source/Common/BfmeMoviePathAB.cpp and GameClient/VideoPlayerInit.cpp.
// Native 689580..6895F2 formats Data/%s/Movies/ from a cdecl callback at +C.
// The purpose and accessed offsets follow retail; the original helper name
// is unknown. BFME1 supplies the path-building semantics. BFME2's callback
// is +C rather than +8 and the formatter takes a const char* format directly.
#include "ascii_string.h"
class SubtitleEntry;
typedef SubtitleEntry *(__cdecl *CreateSubtitleEntry)(AsciiString *, int,
 const AsciiString &, unsigned int, int, int, int, int, int);
class VideoPlayer
{
public:
 virtual void init();
 void rva00689580(AsciiString &out);
 char m_unknown04[8];
 AsciiString (__cdecl *m_movieName)();
 int m_second;
 CreateSubtitleEntry m_createSubtitleEntry;
};
void VideoPlayer::rva00689580(AsciiString &out)
{
 if(m_movieName != 0)
  out.format("Data/%s/Movies/", m_movieName().str());
}
