// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native PCA release96: 3080CE..30812E; original helper name unknown.
// Class relationship is established by WB LoadPCAFile's same-this call and
// native array ownership at A8, AC..CC. No original record type is claimed.
#include <new>
struct StandingWaterPCARecord { float values[4]; };
class StandingWaterArea
{
 unsigned char prefix[0xa8];
 StandingWaterPCARecord *mean;
 StandingWaterPCARecord *channels[9];
public: void rva003080CE();
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
