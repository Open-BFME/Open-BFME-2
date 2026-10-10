// cl: /DNDEBUG /MD /EHsc
// BFME1 6583b3c1 WW3D_Shutdown_Bfme.cpp and ZH ww3d.cpp semantic donors.
// Native117A10..117A5A and shutdown1180E0 call prove movie cleanup identity.
// Movie pointer atDEC3DC and capture byteDEC3D6 are target facts.
// Class/global spellings come from the donor; explicit global delete emits
// the target virtual destructor call with flags0, then frees its result.
class FrameGrabClass { public: virtual ~FrameGrabClass(); };
class StaticSortListClass { public: virtual ~StaticSortListClass(); };
// ww3d.cpp defines WW3D's statics private (?IsCapturing@WW3D@@0_NA, ...); spell them so.
class WW3D { static bool IsCapturing;
public:
    static FrameGrabClass *Movie;
    static void Stop_Movie_Capture(); };
void __cdecl operator delete(void *);
void WW3D::Stop_Movie_Capture()
{
    if (IsCapturing) {
        IsCapturing=false;
        ::delete Movie;
        Movie=0;
    }
}
