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
	
	writeBtn.SetLabel("Complete Order");
	
	for(int i = 0; i < NUM_DAIRY; i++)
	{
		scroller_view.dairy.Add(dairyStr[i]);
	}
	scroller_view.dairy.GoBegin();
	
	int optionSize = 100;
	int checkDist = 20;
	int checkCount = 0;
	optree.SetRoot("All Flavors");
	optree.Add(0,"Gourmand");
	optree.Add(0,"Fruit");
	
	for(int i = 0; i < NUM_FLAV; i++)
	{
		/*flavor[i].SetLabel(flavStr[i].c_str());
		scroller_view.flavorOptions.Add(flavor[i].LeftPosZ(optionSize*(i%2), optionSize).TopPosZ(checkDist * checkCount));
		if(i%2 == 1)
		{
			checkCount++;
		}*/
		optree.Add(i%2 + 1, flavor[i],flavStr[i].c_str());
		flavor[i] << [&, this, i]
		{
			handleFlavor(i);
		};
	}
	scroller_view.flavorOptions.Add(optree.SizePos());
	
	optree.WhenOption = [&, this]
	{
		if(optree.Get(0) == 1)
		{
			for(int i = 0; i < NUM_FLAV; i++)
			{
				d.addFlavor(flavs[i]);
			}
		}
		else if(optree.Get(0) == 0)
		{
			d.removeAllFlavor();
		}
		else
		{
			if(optree.Get(1) == 1)
			{
				for(int i = 0; i < NUM_FLAV; i = i + 2)
				{
					d.addFlavor(flavs[i]);
				}
			}
			else if(optree.Get(1) == 0)
			{
				for(int i = 0; i < NUM_FLAV; i = i + 2)
				{
					d.removeFlavor(flavs[i]);
				}
			}
			if(optree.Get(2) == 1)
			{
				for(int i = 1; i < NUM_FLAV; i = i + 2)
				{
					d.addFlavor(flavs[i]);
				}
			}
			else if(optree.Get(2) == 0)
			{
				for(int i = 1; i < NUM_FLAV; i = i + 2)
				{
					d.removeFlavor(flavs[i]);
				}
			}
		}
			
			
	};
	
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
	scroller_view.dairy << [&, this]
	{
		d.setDairy(scroller_view.dairy.GetData().ToStd());
		checkPrice();
	};
	scroller_view.addBtn << [&, this]
	{
		if(scroller_view.size.GetData() == -1)
		{
			ErrorOK("Please choose a size!");
			//scroller_view.size.GotFocus();
			return;
		}
		if(scroller_view.base.GetData() == -1)
		{
			ErrorOK("Please choose a drink base!");
			return;
		}
		if(scroller_view.temp.GetData() == -1)
		{
			ErrorOK("Please choose a temperature!");
			return;
		}
		for(int i = 0; i < (int)scroller_view.numDrinks; i++)
		{
			order.push_back(d);
			std::ostringstream drinkStr;
			drinkStr << d << std::endl;
			scroller_view.drinkList.Append(drinkStr.str());
		}
		
		
		scroller_view.base = -1;
		scroller_view.temp = -1;
		scroller_view.size = -1;
		d.setBase(CREAM);
		d.setTemperature(HOT);
		d.setSize(SMALL);
		scroller_view.dairy.GoBegin();
		d.setDairy("None");
		d.removeAllFlavor();
		for( int i = 0; i < NUM_FLAV; i++)
		{
			flavor[i] = 0;
		}
		scroller_view.price.SetData("");
		scroller_view.writeBtnHolder.Add(writeBtn.HSizePosZ().VSizePosZ());
		
		
	};
	
	writeBtn << [&, this]
	{
		saveOrder();
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

void DrinksWindow::handleFlavor(int index)
{
	if(flavor[index].Get())
	{
		d.addFlavor(flavs[index]);
	}
	else
	{
		d.removeFlavor(flavs[index]);
	}
	checkPrice();
}

void DrinksWindow::saveOrder()
{
	FileSel fs;
	String path = fs.GetActiveDir();
	
	fs.DefaultName("order");
	fs.DefaultExt("txt");
	fs.PreSelect("order.txt");
	fs.ExecuteSaveAs("order.txt");
	std::ofstream outFile(fs.Get().ToStd());
	outFile << std::setprecision(2) << std::fixed << std::showpoint;
	double total = 0;
	for(int i = 0; i < order.size(); i++)
	{
		outFile << order[i] << std::endl;
		total += order[i].getPrice();
	}
	outFile << "Total: $" << total;
	outFile.close();
	Close();
}