#include "drinksWindow.h"

DrinksWindow::DrinksWindow()
{
	CtrlLayout(*this, "Drink Order Form");
	Sizeable().Zoomable();
	scroller.EnableScroll();
	Add(scroller.SizePos());
	CtrlLayout(scroller_view);
	scroller.AddPane(scroller_view);
	scroller_view.base = -1;
	scroller_view.temp = -1;
	scroller_view.size = -1;
	
	for(int i = 0; i < NUM_DAIRY; i++)
	{
		scroller_view.dairy.Add(dairyStr[i]);
	}
	
	int optionSize = 100;
	int checkDist = 20;
	int checkCount = 0;
	for(int i = 0; i < NUM_FLAV; i++)
	{
		flavor[i].SetLabel(flavStr[i].c_str());
		scroller_view.flavorOptions.Add(flavor[i].LeftPosZ(optionSize*(i%2), optionSize).TopPosZ(checkDist * checkCount));
		if(i%2 == 1)
		{
			checkCount++;
		}
	}
	
	scroller_view.base << [&, this]
	{
		
		baseType b = bases[(int)scroller_view.base];
		d.setBase(b);
		checkPrice();
		
	};
	scroller_view.temp << [&, this]
	{
		tempType t = temps[(int)scroller_view.temp];
		d.setTemperature(t);
		checkPrice();
	};
	scroller_view.size << [&, this]
	{
		sizeType s = sizes[scroller_view.size.GetData()];
		d.setSize(s);
		checkPrice();
	};
	
	
}

void DrinksWindow::checkPrice()
{
	if((int)scroller_view.base != -1 && (int)scroller_view.temp != -1 &&
	(int)scroller_view.size != -1)
	{
		std::ostringstream priceStr;
		priceStr << std::setprecision(2) << std::fixed << std::showpoint;
		priceStr << "$" << d.getPrice();
		scroller_view.price.SetData(priceStr.str());
	}
}