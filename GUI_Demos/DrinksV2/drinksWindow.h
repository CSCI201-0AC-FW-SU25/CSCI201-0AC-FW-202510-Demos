#ifndef _DrinksV2_drinksWindow_h_
#define _DrinksV2_drinksWindow_h_
#include <CtrlLib/CtrlLib.h>

#define LAYOUTFILE <DrinksV2/Drinks.lay>
#include "drinks.h"
#include <AutoScroller/AutoScroller.h>
#include <CtrlCore/lay.h>

using namespace Upp;

class DrinksWindow : public WithMainAppWindow<TopWindow> 
{
public:
	DrinksWindow();

private:
	AutoScroller scroller;
	WithDrinksWindowLayout<ParentCtrl> scroller_view;
};

#endif
