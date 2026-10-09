// _UpdateUMVBorder
// partial score=0.683728 date=2026-10-09
// cl: /O2 /G6 /arch:SSE /MD
// Clean-room: reverse/vp6_cleanroom/specs/001b96a0.md and retail only.
// Native 001B96A0..001B9AB7, cdecl, two stack parameters, no calls.
// The context view contains only independently observed retail fields.
extern "C" void *memcpy(void *, const void *, unsigned int);
extern "C" void *memset(void *, int, unsigned int);
#pragma intrinsic(memcpy, memset)

struct VP6BorderPostProcessor {
    unsigned char unknown00[0x78];
    unsigned int reconY, reconU, reconV;
    unsigned char unknown84[0x90-0x84];
    int horizontalFragments, verticalFragments, yStride, uvStride;
    unsigned char unknownA0[0xb4-0xa0];
    unsigned int border;
};

extern "C" void __cdecl UpdateUMVBorder(VP6BorderPostProcessor *post, unsigned char *frame)
{
    int rows = post->verticalFragments * 8;
    int width = post->horizontalFragments * 8;
    unsigned int border = post->border;
    int stride = post->yStride;
    unsigned char *first = frame + post->reconY;
    unsigned char *last = first + width - 1;
    unsigned char *left = first - border;
    unsigned char *right = last + 1;
    for (int row = rows; row > 0; --row) {
        memset(left, *first, border);
        first += stride;
        memset(right, *last, border);
        last += stride;
        left += stride;
        right += stride;
    }
    first = frame + border * stride;
    last = first + (post->verticalFragments * 8 - 1) * stride;
    left = frame;
    right = last + stride;
    for (int row = border; row > 0; --row) {
        memcpy(left, first, stride);
        memcpy(right, last, stride);
        left += stride;
        right += stride;
    }

    rows = post->verticalFragments * 4;
    stride = post->uvStride;
    first = frame + post->reconU;
    width = post->horizontalFragments * 4;
    last = first + width - 1;
    border >>= 1;
    left = first - border;
    right = last + 1;
    for (int row = rows; row > 0; --row) {
        memset(left, *first, border);
        memset(right, *last, border);
        last += stride;
        first += stride;
        left += stride;
        right += stride;
    }
    first = frame + post->reconU - border;
    last = first + (post->verticalFragments * 4 - 1) * stride;
    left = first - border * stride;
    right = last + stride;
    for (int row = border; row > 0; --row) {
        memcpy(left, first, stride);
        memcpy(right, last, stride);
        left += stride;
        right += stride;
    }

    first = frame + post->reconV;
    last = first + post->horizontalFragments * 4 - 1;
    left = first - border;
    right = last + 1;
    for (int row = rows; row > 0; --row) {
        memset(left, *first, border);
        memset(right, *last, border);
        last += stride;
        first += stride;
        left += stride;
        right += stride;
    }
    first = frame + post->reconV - border;
    last = first + (post->verticalFragments * 4 - 1) * stride;
    left = first - border * stride;
    right = last + stride;
    for (int row = border; row > 0; --row) {
        memcpy(left, first, stride);
        memcpy(right, last, stride);
        left += stride;
        right += stride;
    }
}
