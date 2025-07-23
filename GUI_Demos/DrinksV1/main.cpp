#include <CtrlLib/CtrlLib.h>

using namespace Upp;

struct MyAppWindow: public TopWindow
{
	Switch base;
	MyAppWindow()
	{
		const int LBLSIZE = 120;
		const int MARGIN = 12;
		Add(base.HSizePosZ(LBLSIZE).VSizePosZ(MARGIN));
		base.Add("Coffee");
		base.Add("Tea");
		base.Add("Cream");
		base.SetVertical();
		base = -1;
	}
};

GUI_APP_MAIN
{
	MyAppWindow w;
	w.Run();
}
