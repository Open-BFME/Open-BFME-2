// cl: /MD /EHsc /Ireference/shims/bfme2_ascii
// stlport
// ??1SubtitleEntry@@MAE@XZ 0x006885A0 14B: SubtitleEntry dtor (protected virtual).
// Retail mov [ecx],0x8E451C then add ecx,4 then jmp releaseBuffer 0x36E70.
// BFME1 donor SubtitleEntryConstructorDestructor.cpp proves protected virtual
// and StringBase<ushort> m_text at +4 with scalars and bool after. Caller is
// ??_G at 0x006886F0 and Unwind. Vtable 0x008E451C slot 0 is the ??_G.
// The canonical frozen StringBase replaces the private copy; its switch makes
// the dtor public so the member teardown inlines to the pinned releaseBuffer
// (?releaseBuffer@?$StringBase@G@@AAEXXZ).
#define BFME_STRINGBASE_PUBLIC_DTOR
#include "string_base.h"
class SubtitleEntry {
protected: virtual ~SubtitleEntry();            // BFME1 donor: protected virtual -> ??1SubtitleEntry@@MAE@XZ
private:   StringBase<unsigned short> m_text;   // +4 (vptr at +0)
           unsigned int m_color; int m_style, m_alignment, m_line, m_startFrame, m_endFrame; bool m_displayed; };
SubtitleEntry::~SubtitleEntry() {}
