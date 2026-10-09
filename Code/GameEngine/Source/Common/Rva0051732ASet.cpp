// cl: /MD
// Native51732A..517345 RET4; constructor from an owned four-byte handle.
// OnYesToInvite at5177EB constructs a temporary here and immediately uses
// the constructor's returned receiver; WB145D6E0 provides the named caller.
// The previous raw-pointer setter view had identical bytes but hid the
// constructor lifetime. The by-value input releases in the callee.
struct TargetRef00217D4C {void *m_vtbl;int references;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct Rva004F6986Member
{
 TargetRef00217D4C *m_ptr;
 ~Rva004F6986Member(){if(m_ptr)ReleaseTreeHintRef00217D4C(m_ptr);}
};
struct Rva0051732A
{
 TargetRef00217D4C *m_ptr;
 Rva0051732A(Rva004F6986Member value);
};
Rva0051732A::Rva0051732A(Rva004F6986Member value)
{
 TargetRef00217D4C *p=value.m_ptr;
 m_ptr=p;
 if(p)++p->references;
}
