// cl: /O1 /arch:SSE /G7 /MD /Oy-
// Native 002F70E5..002F714B RET8: query a cell through Pathfinder, stopping
// when the output word is zero and retaining the cell with the smallest
// nonzero signed output. The eleven-argument callee 002F57E6..002F5925 RET2C
// calls rowed Pathfinder::getCell and copies its candidate position to +28.
// This is a target-derived callback slice; its original type/name and the
// exact meanings of the query flags/output remain open.
struct Rva002F70E5Position { float x, y, z; };
class Pathfinder
{
public:
 bool rva002F57E6(void *subject, int arg, bool extentCheck, int x, int y,
  int layer, int otherArg, bool otherFlag, Rva002F70E5Position *position,
  float value, int *output);
};
class Rva002F70E5Info
{
public:
 bool rva002F70E5(int x, int y);
private:
 Pathfinder *m_pathfinder;
 void *m_subject;
 int m_arg;
 bool m_extentCheck;
 bool m_otherFlag;
 char m_pad0E[2];
 int m_otherArg;
 int m_layer;
 float m_value;
 int m_bestX;
 int m_bestY;
 int m_bestOutput;
 Rva002F70E5Position m_position;
};

bool Rva002F70E5Info::rva002F70E5(int x, int y)
{
 int cellY = y;
 if (m_pathfinder->rva002F57E6(m_subject, m_arg, m_extentCheck, x, cellY,
  m_layer, m_otherArg, m_otherFlag, &m_position, m_value, &y))
 {
  if (y == 0)
   return true;
  if (y < m_bestOutput || m_bestOutput == 0)
  {
   m_bestOutput = y;
   m_bestX = x;
   m_bestY = cellY;
  }
 }
 return false;
}
