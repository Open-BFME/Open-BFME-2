// cl: /O1 /G7 /MD /EHsc /arch:SSE
// Native38076D..3807AA and GameClient::update caller23C060 prove the
// no-argument cdecl update dispatcher. The first two receivers use the
// independently rowed message-box flush54CBF7. Existing ledger globals and the private
// AptStrategicMessageBox::s_instance establish the four data bindings; the latter
// two interfaces are target-only six-slot ABI views with unknown class names.
// No new data pin or alternate-name mapping is introduced.
class Rva0054CBF7Target { public: void method(); };
class AptStrategicMessageBox { private: static AptStrategicMessageBox *s_instance; friend void Rva0038076DUpdate(); };
class Rva0038076DInterface {
public: virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void update();
};
extern int g_Va00E032FC,g_Va00E04478,g_Va00E046B8;
void Rva0038076DUpdate() {
 Rva0054CBF7Target *first=(Rva0054CBF7Target *)g_Va00E032FC;
 if(first) first->method();
 Rva0054CBF7Target *second=(Rva0054CBF7Target *)AptStrategicMessageBox::s_instance;
 if(second) second->method();
 Rva0038076DInterface *third=(Rva0038076DInterface *)g_Va00E04478;
 if(third) third->update();
 Rva0038076DInterface *fourth=(Rva0038076DInterface *)g_Va00E046B8;
 if(fourth) fourth->update();
}
