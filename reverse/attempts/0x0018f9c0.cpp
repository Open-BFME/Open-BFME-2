// ??$decompress@$03@AdaptiveDeltaMotionChannelClass@@AAEXKPAMK0@Z
// partial score=0.85 date=2026-10-07
// Banked near miss for ??$decompress@$03@AdaptiveDeltaMotionChannelClass@@AAEXKPAMK0@Z
// retail 0x0018F9C0 222 bytes, BFME2 hcanim.cpp (Code/Libraries/Source/WWVegas/WW3D2/hcanim.cpp).
// The generic template there is byte-exact for N=1 (0x0018F910) but gives 223 bytes / 75 diff
// lines for N=4 (src_idx and the out pointer swap ecx/ebp). This explicit specialization, placed
// right after the template, gives 222 bytes and 39 diff lines: frame layout, spill slots and
// ebp=start/ecx=out/ebx=frame_idx all match; what remains is one register permutation --
// retail keeps srcdata/diff in edx (shared with fi) and Data/base_vi/pPacket in esi with frame
// in edi, this body puts Data in edx and src/diff/frame in esi with pPacket in edi.
// Searched without success: declaration order, NULL-branch order and form, if/else start,
// ternary clamp, uint vi, base advanced per vi, last_value first, cond operand order, fi/frame
// order, for/while frame loops, float* header base, partial local copies, pointer walks.
template <>
void AdaptiveDeltaMotionChannelClass::decompress<4>(uint32 src_idx, float *srcdata, uint32 frame_idx, float *outdata)
{
	unsigned char *base = (unsigned char *) Data;
	float *src = srcdata;
	uint32 start = src_idx;

	if (src == NULL) {
		start = 0;
		src = (float *) base;
	}

	if (frame_idx >= NumFrames) {
		start = frame_idx;
	}

	base += sizeof(float) * 4;
	base += (PACKET_SIZE * 4) * (start >> 4);

	for (int vi = 0; vi < 4; vi++) {
		unsigned char *pPacket = base + PACKET_SIZE * vi;
		float last_value = src[vi];
		if (start < frame_idx) {
			int fi = start & 0xF;
			uint32 frame = start;
			do {
			float filter = filtertable[*pPacket] * Scale;
			pPacket++;
			do {
				int factor = pPacket[fi >> 1] << 24;
				if ((fi & 1) == 0) {
					factor <<= 4;
				}
				factor >>= 28;
				last_value += factor * filter;
				frame++;
				if (frame >= frame_idx) break;
				fi++;
			} while (fi < 16);
			fi = 0;
			pPacket += (PACKET_SIZE * 4) - 1;
			} while (frame < frame_idx);
		}
		outdata[vi] = last_value;
	}
}
