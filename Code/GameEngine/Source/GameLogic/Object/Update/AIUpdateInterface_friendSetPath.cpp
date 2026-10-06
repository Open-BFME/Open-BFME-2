// cl: /DNDEBUG /MD
//
// ?friend_setPath@AIUpdateInterface@@QAEXPAVPath@@@Z, retail 0x00262AF9, 22 bytes.
// ZH donor AIUpdate.cpp friend_setPath verbatim: destroyPath then m_path at
// +0x140 from the Path pointer arg. Layout follows the landed destroyPath
// 0x00262A8A row via GameLogicDestroyObject with m_path at +0x140. Single
// rowed callee destroyPath; six callers including path helpers.

class Path;

class AIUpdateInterface
{
	char m_pad00[0x140];
	Path *m_path;
public:
	void destroyPath();
	void friend_setPath(Path *newPath);
};

void AIUpdateInterface::friend_setPath(Path *newPath)
{
	destroyPath();
	m_path = newPath;
}
