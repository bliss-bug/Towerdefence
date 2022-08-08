#pragma once
#include "Defender.h"

class Wallnut :public Defender
{
public:
	Wallnut();
	void advance(int phase) override;
};