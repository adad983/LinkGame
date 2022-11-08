#pragma once
#include <iostream>
class Menu
{
public:
	Menu();
	Menu(int choose);
public:
	void print();
	int getChoose() const;
private:
	int choose;
};

