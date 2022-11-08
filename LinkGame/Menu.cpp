#include "Menu.h"
using namespace std;
Menu::Menu() {}
Menu::Menu(int choose = 1 ) :choose(choose) {}

void Menu::print()
{
	cout << "请选择难易程度:" << endl;
	cout << "1  简单" << endl;
	cout << "2  适中" << endl;
	cout << "3  困难" << endl;
}

int Menu::getChoose() const
{
	return this->choose;
}
