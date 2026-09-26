// ?Rva001663F0@BfmeRva00166110@@QAEXPAUElem36@@PBU2@PAHI_N@Z
// partial score=0.93 date=2026-09-26
// ?Rva001663F0@BfmeRva00166110@@QAEXPAUElem36@@PBU2@PAHI_N@Z
// partial score=0.93 date=2026-09-26
// cl: /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// BfmeRva00166110 overflow at 0x001663F0, 274 bytes.
//
// The +0x1C sequence of HTreeClass (Start/Finish/EndOfStorage) reallocates
// here: old count is (Finish-Start)/36, growth is old+max(old,n), the new
// buffer comes from the byte allocator at 0x000307F0 as len*36 bytes, the
// prefix [Start,pos) and the tail [pos,Finish) copy through the Elem36 copy
// helper at 0x001610F0, a single insert constructs once while a multi insert
// fills n copies of the same value, the tail copies only when atend is
// false, and the old buffer frees through _free at 0x00030830. Callers are
// the push-back at 0x00166570 (n=1 atend=1) and the insert at 0x001665B0
// (n=1 atend=0).

namespace _STL {
template <class _Tp> class allocator;
template <> class allocator<char> {
public:
	static char *allocate(unsigned int n, const void *hint = 0);
};
}

extern "C" void __cdecl free(void *block);

struct Elem36
{
	char m_bytes[36];
};

void __cdecl gen001610F0(Elem36 *slot, const Elem36 *source);

struct BfmeRva00166110
{
	Elem36 *Start;
	Elem36 *Finish;
	Elem36 *EndOfStorage;
	void Rva001663F0(Elem36 *pos, const Elem36 *value, int *tmp, unsigned int n, bool atend);
};

template <class T> inline const T &bfme_max(const T &a, const T &b)
{
	return a < b ? b : a;
}

// ?Rva001663F0@BfmeRva00166110@@QAEXPAUElem36@@PBU2@PAHI_N@Z present-unmatched
void BfmeRva00166110::Rva001663F0(Elem36 *pos, const Elem36 *value, int *tmp, unsigned int n, bool atend)
{
	unsigned int old = (unsigned int)(Finish - Start);
	unsigned int len = old + bfme_max(old, n);
	Elem36 *newStart;
	if (len != 0) {
		newStart = (Elem36 *)_STL::allocator<char>::allocate(len * sizeof(Elem36), 0);
	} else {
		newStart = 0;
	}
	Elem36 *prefix = Start;
	Elem36 *newFinish = newStart;
	for (; prefix != pos; ++newFinish, ++prefix) {
		gen001610F0(newFinish, prefix);
	}
	if (n == 1) {
		gen001610F0(newFinish, value);
		++newFinish;
	} else if (n != 0) {
		for (unsigned int i = 0; i < n; ++newFinish, ++i) {
			gen001610F0(newFinish, value);
		}
	}
	if (!atend) {
		Elem36 *tailPos = pos;
		Elem36 *tailEnd = Finish;
		for (Elem36 *p = tailPos; p != tailEnd; ++newFinish, ++p) {
			gen001610F0(newFinish, p);
		}
	}
	if (Start != 0) {
		free((void *)Start);
	}
	Finish = newFinish;
	Start = newStart;
	EndOfStorage = newStart + len;
}
