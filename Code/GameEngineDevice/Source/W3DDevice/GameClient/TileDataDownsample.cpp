// cl: /O1 /Oy- /G7 /arch:SSE /MD
// Native 1117E3..111850, called six times by rowed TileData::updateMips.
// ZH TileData::doMip is the semantic guide (BFME1 dae380faa5f6fa536eec8d6ebbe877321d4cb51d).
// Native averages four unsigned words, rounds upward with +3, and advances
// two source rows per output row. The existing neutral cdecl owner remains.
extern "C" void __cdecl Rva001117E3Downsample(unsigned short *source,
 int width,unsigned short *destination) {
 for(int row=0;row<width;row+=2) {
  unsigned short *pixel=source;
  for(int col=0;col<width;col+=2) {
   int value=pixel[width]+pixel[width+1]+pixel[1]+pixel[0]+3;
   *destination=static_cast<unsigned short>(value/4);
   pixel+=2;
   ++destination;
  }
  source+=width*2;
 }
}
