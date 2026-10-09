// cl: /O1 /G7 /Ob1 /EHsc /MD /arch:SSE /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
#include <map>
#include "ascii_string.h"
class ScriptActions
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void slot40(bool v);
	virtual void slot44(const class AsciiString &name, bool flag);
};
extern ScriptActions *TheScriptActions;
struct TreeHead
{
	void *m_00;
	void *m_04;
	void *m_first08;
};
struct TreeNode
{
	char m_pad[0x10];
	void *m_10;
	bool m_14;
};
class Rva0020530EHost
{
public:
	void rva0020530E();
private:
	char m_pad00[0x190C4];
	TreeHead *m_head190C4;
	char m_pad190C8[0x1A4C9-0x190C8];
	bool m_1A4C9;
};
// Target74B virtual entry has a not-yet-proven receiver view; preserve
// its neutral owner. TheScriptActions data owner proves the singleton;
// slots16/17 take Bool and (AsciiString ref, Bool). Reloading the receiver
// header after every callback preserves its possible mutation.
void Rva0020530EHost::rva0020530E()
{
    TheScriptActions->slot40(m_1A4C9);
    _STL::_Rb_tree_node_base *node = (_STL::_Rb_tree_node_base *)m_head190C4->m_first08;
    for (; node != (_STL::_Rb_tree_node_base *)m_head190C4;
         node = _STL::_Rb_global<bool>::_M_increment(node))
    {
        TreeNode *tn = (TreeNode *)node;
        TheScriptActions->slot44(*(const AsciiString *)&tn->m_10, tn->m_14);
    }
}
