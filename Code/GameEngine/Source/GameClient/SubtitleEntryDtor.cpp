// cl: /O2 /MD /EHsc
// ??1SubtitleEntry@@MAE@XZ 0x006885A0 14B: SubtitleEntry dtor (protected virtual).
// Retail mov [ecx],0x8E451C then add ecx,4 then jmp releaseBuffer 0x36E70.
// BFME1 donor SubtitleEntryConstructorDestructor.cpp proves protected virtual
// and StringBase<ushort> m_text at +4 with scalars and bool after. Caller is
// ??_G at 0x006886F0 and Unwind. Vtable 0x008E451C slot 0 is the ??_G.
template <typename T> class StringBase {
public:  ~StringBase() { releaseBuffer(); }   // inline -> tail-jmp to the pinned releaseBuffer
private: void releaseBuffer();                  // declared only: ?releaseBuffer@?$StringBase@G@@AAEXXZ is pinned
         T *m_data; };
class SubtitleEntry {
protected: virtual ~SubtitleEntry();            // BFME1 donor: protected virtual -> ??1SubtitleEntry@@MAE@XZ
private:   StringBase<unsigned short> m_text;   // +4 (vptr at +0)
           unsigned int m_color; int m_style, m_alignment, m_line, m_startFrame, m_endFrame; bool m_displayed; };
SubtitleEntry::~SubtitleEntry() {}
