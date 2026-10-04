// _Rva001118ECResampleRgb555
// partial score=0.117437722419929 date=2026-10-04
// cl: /O1 /MD
// Native1118EC-111A05: average factor-square RGBA blocks with half-count
// rounding and saturate to255, then quantize R/G/B to15-bit RGB555.
// Caller111A05 supplies factors1,2,4,8,16,32,64 and TileData mip buffers.
// ZH TileData::doMip guides averaging; RGB555 and direct source resampling
// are target-specific facts independently read from this complete body.
template<class T> inline const T &tileMin(const T &a,const T &b)
{ return a<b?a:b; }
// ?Rva001118ECResampleRgb555 present-unmatched
extern "C" void __cdecl Rva001118ECResampleRgb555(
    const unsigned char *source,int stride,int factor,unsigned short *destination)
{
    unsigned char channels[4];
    int row=0;
    int count=factor*factor;
    int half=count/2;
    int rowAdvance=stride*factor;
    for(;row<64;row+=factor) {
        const unsigned char *block=source;
        for(int column=0;column<64;column+=factor) {
            unsigned short sums[4]={0,0,0,0};
            const unsigned char *line=block;
            for(int y=0;y<factor;y++) {
                const unsigned char *pixel=line;
                for(int x=0;x<factor;x++) {
                    for(int c=0;c<4;c++)sums[c]+=pixel[c];
                    pixel+=4;
                }
                line+=stride;
            }
            for(int c=0;c<4;c++) {
                int average=(sums[c]+half)/count;
                channels[c]=(unsigned char)tileMin(average,255);
            }
            unsigned short packed=(unsigned short)(((channels[2]+1)*31)/256);
            packed=(unsigned short)((packed<<5)|(((channels[1]+1)*31)/256));
            packed=(unsigned short)((packed<<5)|(((channels[0]+1)*31)/256));
            *destination++=packed;
            block+=factor*4;
        }
        source+=rowAdvance;
    }
}
