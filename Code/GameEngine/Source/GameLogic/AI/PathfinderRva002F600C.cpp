// cl: /O1 /arch:SSE /G7 /MD /Oy-
// Native 002F600C..002F6075 RET10. The rowed Pathfinder cell-line walker
// 002F6D22 and its existing pin prove the callback ABI. A previous cell and
// matching six-bit layer permit the query; a zero output records its position.
// Query helper 002F52A7..002F57E6 RET34 has ordinary stack arguments, and
// receives the previous-cell argument slot as its output word. Original
// callback/query names and the semantics of the query settings remain open.
class PathfindCell
{
public:
 char pad[12];
 unsigned int flags;
};
struct Rva002F600CPosition { float x, y, z; };
class Pathfinder
{
public:
 bool rva002F52A7(void *subject, void *settings, bool extentCheck, int x, int y,
  int layer, int otherArg, bool otherFlag, Rva002F600CPosition *position,
  void *optionalPosition, float value, int *output, unsigned extra);
};
class Rva002F600CInfo
{
public:
 int cellCallback(PathfindCell *previousCell, PathfindCell *currentCell, int x, int y);
private:
 Pathfinder *m_pathfinder;
 void *m_subject;
 void *m_settings;
 int m_otherArg;
 bool m_otherFlag;
 char m_pad11[3];
 int m_layer;
 bool m_found;
 char m_pad19[3];
 Rva002F600CPosition m_position;
 Rva002F600CPosition m_result;
};

int Rva002F600CInfo::cellCallback(PathfindCell *previousCell, PathfindCell *currentCell, int x, int y)
{
 if (previousCell)
 {
  int layer = (currentCell->flags >> 4) & 0x3f;
  if (m_layer == layer)
  {
   if (m_pathfinder->rva002F52A7(m_subject, m_settings, true, x, y, layer,
    m_otherArg, m_otherFlag, &m_position, 0, 0.0f, (int *)&previousCell, 0)
    && previousCell == 0)
   {
    m_found = true;
    m_result = m_position;
   }
  }
 }
 return 0;
}
