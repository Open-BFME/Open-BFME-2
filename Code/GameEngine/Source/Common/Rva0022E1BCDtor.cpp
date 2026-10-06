// cl: /MD /EHs
// ??1Rva0022E1BC@@QAE@XZ @0x0022E1BC 53B: non-virtual dtor destroying vector<BfmeVectorRecord0002154F3> at +0x0C via rowed 0x0021579C then GameEngineDeletingBase member at +0x00 via rowed 0x001B4E74. Evidence: retail call pair plus deleting-dtor caller 0x0022E1A0 plus neighbour TUs RvaTreeValueEraseFamily/RvaTreeDtorFamily; owner name honest-address.
namespace _STL {
template <class T> class allocator;
template <class T, class A> class vector
{
public:
	~vector();
	void *m_begin;
	void *m_end;
	void *m_storage;
};
}
struct BfmeVectorRecord0002154F3
{
	char m_pad[16];
};
class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
private:
	char m_pad04[8];
};
class Rva0022E1BC
{
public:
	~Rva0022E1BC();
private:
	GameEngineDeletingBase m_base00;
	_STL::vector<BfmeVectorRecord0002154F3, _STL::allocator<BfmeVectorRecord0002154F3> > m_vec0C;
};
Rva0022E1BC::~Rva0022E1BC()
{
}
