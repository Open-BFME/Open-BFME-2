// ?rva0056C0A5@CellGrid@@QAEIABUCellPoint@@@Z
// partial score=0.96 date=2026-10-10
// ?rva0056C0A5@CellGrid@@QAEIABUCellPoint@@@Z
// partial score=0.96 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
struct CellPoint { float x, y; };
class CellGrid {
public: unsigned int rva0056C0A5(const CellPoint &point);
private: int width, height; unsigned int count; float size, origin;
};
unsigned int CellGrid::rva0056C0A5(const CellPoint &point) {
 if (size > 0.0f) {
  int row = (int)(((double)point.y-origin)/size);
  int index = row*width;
  index += (int)(((double)point.x-origin)/size);
  if ((unsigned int)index < count) return index;
 }
 return 0x7fffffff;
}
