// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native PCA release96: 3080CE..30812E; original helper name unknown.
// Class relationship is established by WB LoadPCAFile's same-this call and
// native array ownership at A8, AC..CC. No original record type is claimed.
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include <new>
struct StandingWaterPCARecord { float values[4]; };
struct Rva003080AARef;

class StandingWaterArea
{
public:
	void loadFXShaderSetup();
	void rva003080CE();
	unsigned char *getDepthColoringTexturePixels(int *width, int *height);
	void rva00308A12(float position, int *red, int *green, int *blue);

	char before[0x80];
	AsciiString shaderName;
	Rva003080AARef *shader;
private:
	char m_pad88[0x8C - 0x88];
	AsciiString name;
	int width, height;
	unsigned char *pixels;
	bool reload;
	char m_pad9D[0xA8 - 0x9D];
	StandingWaterPCARecord *mean;
	StandingWaterPCARecord *channels[9];
};
void StandingWaterArea::rva003080CE()
{
 if(mean) { delete[] mean; mean=0; }
 for(int i=0;i<3;++i)
 {
  if(channels[i]) { delete[] channels[i]; channels[i]=0; }
  if(channels[i+3]) { delete[] channels[i+3]; channels[i+3]=0; }
  if(channels[i+6]) { delete[] channels[i+6]; channels[i+6]=0; }
 }
}
