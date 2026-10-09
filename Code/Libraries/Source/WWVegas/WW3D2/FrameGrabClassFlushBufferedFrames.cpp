// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD /EHs-c-

// Clean BF1 2f243e26d44a74a48ef0ccfe9b543874e6567883 donor,
// game/Libraries/Source/WWVegas/WW3D2/FrameGrabClassFlushBufferedFrames.cpp.
// Target proves 001767D0..0017685E RET0 = 142 bytes; the queue's 139-byte
// extent stopped inside the final stack restoration. Frame fields4/C/10/14/1C
// and eight stdcall AVIStreamWrite arguments independently match retail.
// The source's explicit positive-count guard redundantly reloads the count;
// relying on the real for-loop guard keeps EDI=0 and retail's comparison.
// Existing in-image ji_006547a2 import owner is the AVIFIL32 AVIStreamWrite
// thunk (IAT BBA04C); no second import name or function pin is introduced.
// Address-derived donor spelling is already used by BFME2's GetBuffer and
// is retained without asserting the original historical member name.
extern void ji_006547a2();
extern "C" __declspec(dllimport) int __cdecl sprintf(char *, const char *, ...);
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(const char *);

// TU-scoped BFME FrameGrabClass ABI.  The shared reference header describes
// the older Generals object and cannot represent BFME's buffered frame ring.
class FrameGrabClass
{
public:
	enum MODE
	{
		RAW,
		AVI
	};

	FrameGrabClass(const char *filename, MODE mode, int width, int height,
		int bitdepth, float framerate);
	FrameGrabClass(const char *filename, int width, int height, int bitdepth,
		float framerate, int buffer_count, bool compressed);
	virtual ~FrameGrabClass();

	long *GetBuffer();
	float GetFrameRate() { return FrameRate; }

protected:
	// Address-derived spelling: no surviving named caller proves the original.
	void Rva00958570_Flush_Buffered_Frames();

	int FrameSize;
	union
	{
		int BufferCount;
		float FrameRate;
	};
	long *Buffer;
	int WrittenFrames;
	int BufferedFrames;
	void *AVIFile;
	void *AVIStream;
};

typedef int (__stdcall *AviStreamWrite)( void *stream, long start,
	long samples, void *buffer, long bytes, long flags,
	long *samples_written, long *bytes_written );

// Address-derived spelling: the body is proven to flush FrameGrabClass's
// buffered frames, but no surviving named caller proves the historical name.
void FrameGrabClass::Rva00958570_Flush_Buffered_Frames()
{
	if( AVIStream != 0 && Buffer != 0 )
	{
		register int frame = 0;
		
		{
			int (__cdecl *format)( char *, const char *, ... ) =
				sprintf;
			void (__stdcall *print)( const char * ) =
				OutputDebugStringA;
			char error[ 0x100 ];
			for( ; frame < BufferedFrames; ++frame )
			{
				int result = ((AviStreamWrite)ji_006547a2)( AVIStream,
					WrittenFrames + frame, 1,
					(char *)Buffer + FrameSize * frame,
					FrameSize, 0x10, 0, 0 );
				if( result != 0 )
				{
					format( error, "avi write error %x/%d\n", result, result );
					print( error );
				}
			}
		}
	}

	int count = BufferedFrames;
	WrittenFrames += count;
	BufferedFrames = 0;
}
