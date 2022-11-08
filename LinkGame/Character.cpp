#include "Character.h"
#pragma once

Character::Character(int x, int y, int data) :
			x(x),
			y(y),
			data(data){}

Character::~Character()
{
}

int Character::showData() const
{
	return this->data;
}

void Character::setData(int data)
{
	this->data = data;
}

int Character::showX() const
{
	return this->x;
}

void Character::setX(int x)
{
	this->x = x;
}

int Character::showY() const
{
	return this->y;
}

void Character::setY(int y) 
{
	this->y = y;
}
