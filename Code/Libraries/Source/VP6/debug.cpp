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
__declspec(dllimport) int __cdecl fprintf(void *, const char *, ...);
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

// Clean-room mode log writer from approved spec001bb830 and complete retail body.
// The offsets, signed data loads, unsigned loop bounds and counter storage are target-proven.
struct VP6DebugMotionVector { short x, y; };
struct VP6ModeDebugState {
    unsigned char pad00[0x1DC];
    int interlaced;
    unsigned char pad1E0[0x4C];
    unsigned int rows, columns;
    unsigned char pad234[0x4B8];
    signed char *interlacedModes;
    signed char *modes;
    VP6DebugMotionVector *motionVectors;
};
int g_vp6ModeDebugFrameCounter;
extern "C" void VP6_printmodes(VP6ModeDebugState *state)
{
    void *stream = fopen("modes.txt", "a");
    fprintf(stream, "Frame %d\n\n", g_vp6ModeDebugFrameCounter);
    for (unsigned int row = 3; row < state->rows - 3; ++row) {
        if (state->interlaced == 1) {
            for (unsigned int column = 3; column < state->columns - 3; ++column)
                fprintf(stream, "%d", state->interlacedModes[row * state->columns + column]);
            fprintf(stream, "   ");
        }
        for (unsigned int column = 3; column < state->columns - 3; ++column)
            fprintf(stream, "%d", state->modes[row * state->columns + column]);
        fprintf(stream, "   ");
        for (unsigned int column = 3; column < state->columns - 3; ++column)
            fprintf(stream, "%3d:%-3d", state->motionVectors[row * state->columns + column].x,
                state->motionVectors[row * state->columns + column].y);
        fprintf(stream, "\n");
    }
    fprintf(stream, "\n");
    fprintf(stream, "\n");
    fclose(stream);
    ++g_vp6ModeDebugFrameCounter;
}
