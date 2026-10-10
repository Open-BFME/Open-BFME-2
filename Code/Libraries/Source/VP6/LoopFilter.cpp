// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c0af0.md and
// reverse/vp6_cleanroom/specs/001c1120.md plus retail only.
// No decoder source was consulted.
// _ApplyReconLoopFilter retail 0x001C0AF0..0x001C111F (1583 bytes) and
// _LoopFilter retail 0x001C1120..0x001C174F (1583 bytes) both cdecl
// (post-processor instance / frame Q index / last recon frame /
// post-process buffer / fragment info / fragment element size / coded
// mask); neither is referenced in retail (no call and no stored address)
// so they keep their plain C names. The six arguments are stored at
// 0x0C..0x20; the limit is the 64-dword table at 0x00DB7428 by Q index and
// a zero limit returns. The bounding array comes from the slot at
// 0x00E22F84 and the edges are filtered through the slots 0x00E22FB8
// (horizontal: 2 pixels before a vertical edge) and 0x00E22FD8 (vertical
// edge at a fragment row start) each as (instance / pixel / line length /
// bounding). A fragment is coded when its fragment-info byte has a mask
// bit set; coded fragments filter their left / top edges and the right /
// lower edge when that neighbour is not coded. Y U and V run with their
// strides (0x98 / 0x9C) fragment counts (0x90 / 0x94 halved for chroma)
// first fragments (0 / 0x84 / 0x84 + 0x88) and recon offsets (0x78 / 0x7C /
// 0x80). LoopFilter runs the last fragment row inside the plane loop and
// ApplyReconLoopFilter once after it on the V plane state; the two also
// read the fragment counts in opposite order. Retail forms 8 lines times
// the line length as one term (rowStep) and keeps the running fragment
// index first in its frame.

struct Vp6LoopFilterInstance
{
	int m_mode;
	int m_04;
	int m_08;
	int m_frameQIndex;
	unsigned char *m_lastRecon;
	unsigned char *m_postProcBuffer;
	unsigned char *m_fragInfo;
	int m_fragInfoElementSize;
	int m_fragInfoCodedMask;
	unsigned char m_pad24[0x78 - 0x24];
	int m_reconYOffset;
	int m_reconUOffset;
	int m_reconVOffset;
	unsigned int m_yPlaneFragments;
	unsigned int m_uvPlaneFragments;
	unsigned int m_8c;
	unsigned int m_hFragments;
	unsigned int m_vFragments;
	unsigned int m_yStride;
	unsigned int m_uvStride;

	bool IsCoded(int index) const
	{
		return (m_fragInfo[index * m_fragInfoElementSize] & m_fragInfoCodedMask) != 0;
	}
};

struct Rva009AF530Context;
typedef void (__cdecl *Vp6LoopFilterEdge)(Vp6LoopFilterInstance *, unsigned char *, unsigned int, int *);

extern int *(__cdecl *g_rva01356e68SetupBounding)(Rva009AF530Context *, int);
extern Vp6LoopFilterEdge g_00E22FB8;
extern Vp6LoopFilterEdge g_00E22FD8;
extern const int g_00DB7428[64];

#define CODED(i) ctx->IsCoded(i)
#define FILTER_H(x) g_00E22FB8(ctx, (x), stride, bounding)
#define FILTER_V(x) g_00E22FD8(ctx, (x), stride, bounding)

extern "C" void __cdecl ApplyReconLoopFilter(Vp6LoopFilterInstance *ctx, int frameQIndex,
	unsigned char *lastRecon, unsigned char *postProcBuffer, unsigned char *fragInfo,
	int fragInfoElementSize, int fragInfoCodedMask)
{
	int frag = 0;
	unsigned char *pixel = 0;
	int start = 0;
	int lineFragments = 0;
	unsigned int stride = 0;
	int across = ctx->m_hFragments;
	int down = ctx->m_vFragments;
	unsigned int rowStep;
	int plane;
	int n;
	int m;
	int limit;
	int *bounding;

	ctx->m_frameQIndex = frameQIndex;
	ctx->m_lastRecon = lastRecon;
	ctx->m_postProcBuffer = postProcBuffer;
	ctx->m_fragInfo = fragInfo;
	ctx->m_fragInfoElementSize = fragInfoElementSize;
	ctx->m_fragInfoCodedMask = fragInfoCodedMask;

	limit = g_00DB7428[frameQIndex];
	if (limit == 0)
		return;
	bounding = g_rva01356e68SetupBounding((Rva009AF530Context *)ctx, limit);

	for (plane = 0; plane < 3; plane++) {
		switch (plane) {
		case 0:
			start = 0;
			across = ctx->m_hFragments;
			down = ctx->m_vFragments;
			stride = ctx->m_yStride;
			lineFragments = ctx->m_hFragments;
			pixel = ctx->m_lastRecon + ctx->m_reconYOffset;
			break;
		case 1:
			start = ctx->m_yPlaneFragments;
			across = ctx->m_hFragments >> 1;
			down = ctx->m_vFragments >> 1;
			stride = ctx->m_uvStride;
			lineFragments = ctx->m_hFragments >> 1;
			pixel = ctx->m_lastRecon + ctx->m_reconUOffset;
			break;
		case 2:
			start = ctx->m_yPlaneFragments + ctx->m_uvPlaneFragments;
			across = ctx->m_hFragments >> 1;
			down = ctx->m_vFragments >> 1;
			stride = ctx->m_uvStride;
			lineFragments = ctx->m_hFragments >> 1;
			pixel = ctx->m_lastRecon + ctx->m_reconVOffset;
			break;
		}

		rowStep = 8 * stride;
		frag = start;
		if (CODED(frag)) {
			if (!CODED(frag + 1))
				FILTER_H(pixel + 6);
			if (!CODED(frag + lineFragments))
				FILTER_V(pixel + rowStep);
		}
		frag++;
		for (n = 1; n < across - 1; n++, frag++) {
			if (CODED(frag)) {
				FILTER_H(pixel + 8 * n - 2);
				if (!CODED(frag + 1))
					FILTER_H(pixel + 8 * n + 6);
				if (!CODED(frag + lineFragments))
					FILTER_V(pixel + 8 * n + rowStep);
			}
		}
		if (CODED(frag)) {
			FILTER_H(pixel + 8 * n - 2);
			if (!CODED(frag + lineFragments))
				FILTER_V(pixel + 8 * n + rowStep);
		}
		frag++;
		pixel += rowStep;

		for (m = 1; m < down - 1; m++) {
			if (CODED(frag)) {
				FILTER_V(pixel);
				if (!CODED(frag + 1))
					FILTER_H(pixel + 6);
				if (!CODED(frag + lineFragments))
					FILTER_V(pixel + rowStep);
			}
			frag++;
			for (n = 1; n < across - 1; n++, frag++) {
				if (CODED(frag)) {
					FILTER_H(pixel + 8 * n - 2);
					FILTER_V(pixel + 8 * n);
					if (!CODED(frag + 1))
						FILTER_H(pixel + 8 * n + 6);
					if (!CODED(frag + lineFragments))
						FILTER_V(pixel + 8 * n + rowStep);
				}
			}
			if (CODED(frag)) {
				FILTER_H(pixel + 8 * n - 2);
				FILTER_V(pixel + 8 * n);
				if (!CODED(frag + lineFragments))
					FILTER_V(pixel + 8 * n + rowStep);
			}
			frag++;
			pixel += rowStep;
		}
	}

	if (CODED(frag)) {
		FILTER_V(pixel);
		if (!CODED(frag + 1))
			FILTER_H(pixel + 6);
	}
	frag++;
	for (n = 1; n < across - 1; n++, frag++) {
		if (CODED(frag)) {
			FILTER_H(pixel + 8 * n - 2);
			FILTER_V(pixel + 8 * n);
			if (!CODED(frag + 1))
				FILTER_H(pixel + 8 * n + 6);
		}
	}
	if (CODED(frag)) {
		FILTER_H(pixel + 8 * n - 2);
		FILTER_V(pixel + 8 * n);
	}
}

extern "C" void __cdecl LoopFilter(Vp6LoopFilterInstance *ctx, int frameQIndex,
	unsigned char *lastRecon, unsigned char *postProcBuffer, unsigned char *fragInfo,
	int fragInfoElementSize, int fragInfoCodedMask)
{
	int frag = 0;
	unsigned char *pixel = 0;
	int start = 0;
	int lineFragments = 0;
	unsigned int stride = 0;
	int down = ctx->m_vFragments;
	int across = ctx->m_hFragments;
	unsigned int rowStep;
	int plane;
	int n;
	int m;
	int limit;
	int *bounding;

	ctx->m_frameQIndex = frameQIndex;
	ctx->m_lastRecon = lastRecon;
	ctx->m_postProcBuffer = postProcBuffer;
	ctx->m_fragInfo = fragInfo;
	ctx->m_fragInfoElementSize = fragInfoElementSize;
	ctx->m_fragInfoCodedMask = fragInfoCodedMask;

	limit = g_00DB7428[frameQIndex];
	if (limit == 0)
		return;
	bounding = g_rva01356e68SetupBounding((Rva009AF530Context *)ctx, limit);

	for (plane = 0; plane < 3; plane++) {
		switch (plane) {
		case 0:
			start = 0;
			across = ctx->m_hFragments;
			down = ctx->m_vFragments;
			stride = ctx->m_yStride;
			lineFragments = ctx->m_hFragments;
			pixel = ctx->m_lastRecon + ctx->m_reconYOffset;
			break;
		case 1:
			start = ctx->m_yPlaneFragments;
			across = ctx->m_hFragments >> 1;
			down = ctx->m_vFragments >> 1;
			stride = ctx->m_uvStride;
			lineFragments = ctx->m_hFragments >> 1;
			pixel = ctx->m_lastRecon + ctx->m_reconUOffset;
			break;
		case 2:
			start = ctx->m_yPlaneFragments + ctx->m_uvPlaneFragments;
			across = ctx->m_hFragments >> 1;
			down = ctx->m_vFragments >> 1;
			stride = ctx->m_uvStride;
			lineFragments = ctx->m_hFragments >> 1;
			pixel = ctx->m_lastRecon + ctx->m_reconVOffset;
			break;
		}

		rowStep = 8 * stride;
		frag = start;
		if (CODED(frag)) {
			if (!CODED(frag + 1))
				FILTER_H(pixel + 6);
			if (!CODED(frag + lineFragments))
				FILTER_V(pixel + rowStep);
		}
		frag++;
		for (n = 1; n < across - 1; n++, frag++) {
			if (CODED(frag)) {
				FILTER_H(pixel + 8 * n - 2);
				if (!CODED(frag + 1))
					FILTER_H(pixel + 8 * n + 6);
				if (!CODED(frag + lineFragments))
					FILTER_V(pixel + 8 * n + rowStep);
			}
		}
		if (CODED(frag)) {
			FILTER_H(pixel + 8 * n - 2);
			if (!CODED(frag + lineFragments))
				FILTER_V(pixel + 8 * n + rowStep);
		}
		frag++;
		pixel += rowStep;

		for (m = 1; m < down - 1; m++) {
			if (CODED(frag)) {
				FILTER_V(pixel);
				if (!CODED(frag + 1))
					FILTER_H(pixel + 6);
				if (!CODED(frag + lineFragments))
					FILTER_V(pixel + rowStep);
			}
			frag++;
			for (n = 1; n < across - 1; n++, frag++) {
				if (CODED(frag)) {
					FILTER_H(pixel + 8 * n - 2);
					FILTER_V(pixel + 8 * n);
					if (!CODED(frag + 1))
						FILTER_H(pixel + 8 * n + 6);
					if (!CODED(frag + lineFragments))
						FILTER_V(pixel + 8 * n + rowStep);
				}
			}
			if (CODED(frag)) {
				FILTER_H(pixel + 8 * n - 2);
				FILTER_V(pixel + 8 * n);
				if (!CODED(frag + lineFragments))
					FILTER_V(pixel + 8 * n + rowStep);
			}
			frag++;
			pixel += rowStep;
		}

		if (CODED(frag)) {
			FILTER_V(pixel);
			if (!CODED(frag + 1))
				FILTER_H(pixel + 6);
		}
		frag++;
		for (n = 1; n < across - 1; n++, frag++) {
			if (CODED(frag)) {
				FILTER_H(pixel + 8 * n - 2);
				FILTER_V(pixel + 8 * n);
				if (!CODED(frag + 1))
					FILTER_H(pixel + 8 * n + 6);
			}
		}
		if (CODED(frag)) {
			FILTER_H(pixel + 8 * n - 2);
			FILTER_V(pixel + 8 * n);
		}
	}
}
