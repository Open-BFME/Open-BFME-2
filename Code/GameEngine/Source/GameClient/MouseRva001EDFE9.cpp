// cl: /MD
// ?rva001EDFE9@Mouse@@QBEPAXXZ @0x001EDFE9 14B
// Returns &m_cursorInfo[m_currentCursor]; m_cursorInfo at +0x4c stride 0x54 (BFME1 +8 stride 0x54 moved to +0x4c in BFME2 per Mouse.cpp); m_currentCursor at +0x4fa4 (after cursor bytes +0x4F9D..+0x4FA1 in MouseSetEngineVisibility.cpp); sole caller at 0x0042F4E7.
struct MouseCursorInfo54 { char data[0x54]; };
class Mouse {
	char _pad0[0x4c];
	MouseCursorInfo54 m_info[50];
	char _pad1[0x4fa4 - (0x4c + 50 * 0x54)];
	int m_current;
public:
	void *rva001EDFE9() const;
};
void *Mouse::rva001EDFE9() const
{
	return (void *)&m_info[m_current];
}
