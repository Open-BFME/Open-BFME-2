// Native12630B..126314 is a five-argument forwarding tail to rowed
// SortingRendererBFME1 Insert12FE00 (1520B). Original wrapper name unknown;
// target ABI independently establishes center reference and four words.
// cl: /O1 /Oy- /G7 /arch:SSE /MD
struct TargetCenter3{float x,y,z;TargetCenter3(float,float,float);};
class BfmeSortingDispatchAt0012FE00{public:static void Insert(const TargetCenter3&,unsigned,unsigned,unsigned,unsigned);};
void Rva0012630BForward(const TargetCenter3&c,unsigned a,unsigned b,unsigned d,unsigned e){BfmeSortingDispatchAt0012FE00::Insert(c,a,b,d,e);}
