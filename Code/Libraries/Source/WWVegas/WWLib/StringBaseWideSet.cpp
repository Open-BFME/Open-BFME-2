// cl: /O2 /DNDEBUG /MD /EHs-c-
//
// ?set@?$StringBase@G@@QAEXPBGHH@Z, retail 0x00037E90, 96 bytes.
// StringBase<wchar_t> substring setter: measures the source with wcslen
// (empty for null), clamps the (pos, n) range against the measured length
// (clearing through releaseBuffer when the range is empty or out of range)
// and forwards the clamped slice to the rowed 2-arg set at 0x371E0.
// The pos+n endpoint is recomputed for the clamp branch exactly as retail.
// /O2 is load-bearing: it emits add-esp cleanup for the wcslen call and
// duplicated epilogues instead of the /O1 pop-cleanup plus shared tail.
// Callees resolve through existing pins: wcslen via the 0x6291CC import
// thunk, 2-arg set 0x371E0, releaseBuffer 0x36E70 (private spelling).
// Shape mirrors the landed StringBaseWideTrim TU in this folder.

extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const unsigned short *s);

typedef unsigned short WideChar;

template <typename T>
class StringBase
{
private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;

	void releaseBuffer();

public:
	void set(const T *str, int pos, int count);
	void set(const T *str, int len);
};

template <>
void StringBase<WideChar>::set(const WideChar *str, int pos, int count)
{
	int len;
	if (str)
		len = (int)wcslen(str);
	else
		len = 0;
	int end = pos + count;
	if (end < 0 || pos >= len) {
		releaseBuffer();
		return;
	}
	if (pos < 0) {
		count = end;
		pos = 0;
	}
	if (pos + count >= len)
		count = len - pos;
	set(str + pos, count);
}
