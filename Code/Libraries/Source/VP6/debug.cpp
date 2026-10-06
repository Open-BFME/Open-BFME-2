// cl: /MD
// Retail raw-image debug writers reconstructed from calls, literals and loops.
// Function spellings come from the matching source-handoff debug.c object,
// not from target symbols or a donor PDB name record. No source body imported.
// Evidence: reverse/vp6_structural_evidence.json, debug_writers.
extern "C" {
__declspec(dllimport) int __cdecl sprintf(char *,const char *,...);
__declspec(dllimport) void *__cdecl fopen(const char *,const char *);
__declspec(dllimport) unsigned __cdecl fwrite(const void *,unsigned,unsigned,void *);
__declspec(dllimport) int __cdecl fclose(void *);
}
extern "C" void vp6_draw(char *prefix,int number,unsigned char *pixels,int size)
{
    char filename[256];
    sprintf(filename,"%s%04d.raw",prefix,number);
    void *stream=fopen(filename,"wb");
    fwrite(pixels,size,1,stream);
    fclose(stream);
}
extern "C" void vp6_drawb(char *prefix,int number,unsigned char *pixels,int stride,int width,int height)
{
    char filename[256];
    sprintf(filename,"%s%04d.raw",prefix,number);
    void *stream=fopen(filename,"wb");
    for(int row=0;row<height;++row) {
        fwrite(pixels,width,1,stream);
        pixels+=stride;
    }
    fclose(stream);
}
extern "C" void vp6_drawc(char *filename,unsigned char *pixels,int stride,int width,int height)
{
    void *stream=fopen(filename,"ab");
    for(int row=0;row<height;++row) {
        fwrite(pixels,width,1,stream);
        pixels+=stride;
    }
    fclose(stream);
}
