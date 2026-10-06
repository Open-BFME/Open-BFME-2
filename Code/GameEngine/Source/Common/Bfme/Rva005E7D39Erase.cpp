// cl: /MD
// ?rva005E7D39@Rva005E7D39@@QAEPAXPAX@Z @0x005E7D39 57B
// Vector erase one element: if (pos+1 != finish) copy_forward(pos+1 finish pos)
// via rowed 0x005E748D then --finish then destroy finish via rowed 0x005E74AA flag 0
// then return pos. Callers: 0x005E85BE. Callees rowed.
class Rva005E7198
{
public:
	Rva005E7198 &operator=(const Rva005E7198 &other);
private:
	void *m_object;
};
Rva005E7198 *__cdecl Rva005E748DForward(Rva005E7198 *first, Rva005E7198 *last, Rva005E7198 *dest, void *ignored);
struct Rva005E74AA { void *rva005E74AA(unsigned int); };
struct Rva005E7D39 { char m_pad[4]; Rva005E7198 *m_finish; void *rva005E7D39(void *pos); };
void *Rva005E7D39::rva005E7D39(void *pos)
{
	Rva005E7198 *position = (Rva005E7198 *)pos;
	Rva005E7198 *finish = m_finish;
	if (position + 1 != finish) {
		char tag;
		Rva005E748DForward(position + 1, finish, position, &tag);
	}
	--m_finish;
	((Rva005E74AA *)m_finish)->rva005E74AA(0);
	return position;
}
