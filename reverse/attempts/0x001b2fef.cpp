// ?UnknownSlot3@BFME2Encoding0MotionChannel@@UAEXMPAMPAPAE@Z
// partial score=0.9373 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD
// UnknownSlot3/4/5 of BFME2Encoding0MotionChannel, retail 0x001B2FEF (362B),
// 0x001B3159 (442B), 0x001B3313 (376B): vtable 0x007D7648 slots 3..5.
// Scalar/vector/quaternion sample interpolation over ushort timecodes with a
// per-call cursor. The FindIndex search (rowed standalone at 0x001B2EFC in
// BFME2Encoding0MotionChannelFindIndex.cpp) is inlined here as a TU-local
// member, with `low` declared and zeroed ahead of `index` (the lever that
// closed the standalone body). BFME1 motchan.cpp TimeCodedMotionChannel is
// the semantic guide; target uses ushort timecodes, not dword packets.
class Vector3 { public: float X, Y, Z; };
class Quaternion { public: float X, Y, Z, W; };
void BFME2_Nlerp(Quaternion &res, const Quaternion &p, const Quaternion &q, float alpha);
class ChunkLoadClass;
class BFME2MotionChannel
{
public:
	virtual bool Load(ChunkLoadClass &);
	virtual ~BFME2MotionChannel();
	virtual int UnknownSlot2();
	virtual void UnknownSlot3(float frame, float *value, unsigned char **cursor);
	virtual void UnknownSlot4(float frame, Vector3 *value, unsigned char **cursor);
	virtual void UnknownSlot5(float frame, Quaternion *value, unsigned char **cursor);
	virtual int UnknownSlot6();
	int Type, Pivot, Count, Components;
};
class BFME2Encoding0MotionChannel : public BFME2MotionChannel
{
public:
	virtual void UnknownSlot3(float frame, float *value, unsigned char **cursor);
	virtual void UnknownSlot4(float frame, Vector3 *value, unsigned char **cursor);
	virtual void UnknownSlot5(float frame, Quaternion *value, unsigned char **cursor);
	unsigned short *TimeCodes;
	float *Samples;
	__forceinline int LocalFindIndex(unsigned int time, int **context)
	{
		int index;
		int low = 0;
		if (context && (unsigned int)(index = **context) < (unsigned int)Count) {
			while (index && (TimeCodes[index] & ~0x8000) > time) --index;
			while (index < Count - 1 && (TimeCodes[index + 1] & ~0x8000) <= time) ++index;
			**context = index; ++*context;
			return index;
		} else {
			if (time <= (TimeCodes[0] & ~0x8000)) index = 0;
			else if (time >= (TimeCodes[Count - 1] & ~0x8000)) index = Count - 1;
			else {
				low = 0; int high = Count - 2;
				for (;;) {
					index = (low + high) / 2;
					if (time < (TimeCodes[index] & ~0x8000)) high = index;
					else if (time >= (TimeCodes[index + 1] & ~0x8000)) {
						int diff = index ^ low; if (diff) low = index; else ++low;
					} else break;
				}
			}
		}
		if (context) { **context = index; ++*context; }
		return index;
	}
};

static __forceinline float lerpMotion(float a, float b, float t) { return (b - a) * t + a; }

void BFME2Encoding0MotionChannel::UnknownSlot3(float frame, float *value, unsigned char **cursor)
{
	int idx = LocalFindIndex((unsigned int)frame, reinterpret_cast<int **>(cursor));
	int index = idx;
	int last = Count - 1;
	if (idx == last || (TimeCodes[idx + 1] & 0x8000)) {
		*value = Samples[last * Components]; return;
	}
	float t0 = float(TimeCodes[idx] & ~0x8000), t1 = float(TimeCodes[idx + 1] & ~0x8000);
	float ratio = (frame - t0) / (t1 - t0);
	float *samples = Samples + Components * idx;
	*value = lerpMotion(samples[0], samples[Components], ratio);
}

void BFME2Encoding0MotionChannel::UnknownSlot4(float frame, Vector3 *value, unsigned char **cursor)
{
	int idx = LocalFindIndex((unsigned int)frame, reinterpret_cast<int **>(cursor));
	int index = idx;
	if (idx == Count - 1 || (TimeCodes[idx + 1] & 0x8000)) {
		float *samples = Samples + idx * Components;
		value->X = samples[0]; value->Y = samples[1]; value->Z = samples[2]; return;
	}
	float t0 = float(TimeCodes[idx] & ~0x8000), t1 = float(TimeCodes[idx + 1] & ~0x8000);
	float ratio = (frame - t0) / (t1 - t0);
	float *samples = Samples + idx * Components;
	value->X = lerpMotion(samples[0], samples[Components], ratio);
	value->Y = lerpMotion(samples[1], samples[Components + 1], ratio);
	value->Z = lerpMotion(samples[2], samples[Components + 2], ratio);
}

void BFME2Encoding0MotionChannel::UnknownSlot5(float frame, Quaternion *value, unsigned char **cursor)
{
	int idx = LocalFindIndex((unsigned int)frame, reinterpret_cast<int **>(cursor));
	int index = idx;
	if (idx == Count - 1 || (TimeCodes[idx + 1] & 0x8000)) {
		float *samples = Samples + idx * Components;
		value->X = samples[0]; value->Y = samples[1]; value->Z = samples[2]; value->W = samples[3]; return;
	}
	float t0 = float(TimeCodes[idx] & ~0x8000), t1 = float(TimeCodes[idx + 1] & ~0x8000);
	float ratio = (frame - t0) / (t1 - t0);
	float *samples = Samples + idx * Components;
	BFME2_Nlerp(*value, *reinterpret_cast<Quaternion *>(samples), *reinterpret_cast<Quaternion *>(samples + Components), ratio);
}
