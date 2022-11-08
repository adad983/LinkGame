#pragma once
class Character
{
public:
	Character(int x, int y, int data);
	~Character();

public:
	int showData()const;
	void setData(int data);
	int showX()const;
	void setX(int x);
	int showY()const;
	void setY(int y);
private:
	int x;
	int y;
	int data;
};

