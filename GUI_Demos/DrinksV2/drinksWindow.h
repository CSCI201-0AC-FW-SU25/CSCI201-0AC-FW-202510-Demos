#ifndef _DrinksV2_drinksWindow_h_
#define _DrinksV2_drinksWindow_h_
#include <CtrlLib/CtrlLib.h>

#define LAYOUTFILE <DrinksV2/Drinks.lay>
#include "drinks.h"
#include <AutoScroller/AutoScroller.h>
#include <CtrlCore/lay.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace Upp;

class DrinksWindow : public WithMainAppWindow<TopWindow>
{
public:
	DrinksWindow();
	void checkPrice();

private:
	AutoScroller scroller;
	WithDrinksWindowLayout<ParentCtrl> scroller_view;
	Option flavor[NUM_FLAV];
	drink d;
	std::vector<drink> order;
	Button writeBtn;
	OptionTree optree;
};

#endif
