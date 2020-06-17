#pragma once

enum Pclass 
{ 
	First = 1, 
	Second = 2, 
	Third = 3 
};
enum Sex 
{ 
	Male = 'M', 
	Female = 'F'
};
enum Embarked 
{	
	C, 
	Q, 
	S 
};

short 
	calive = 0, 
	fclass = 0, 
	sclass = 0, 
	tclass = 0, 
	male = 0, 
	female = 0,
	female_all = 0,
	male_all = 0,
	age_all = 0,
	sht[3]{};
double 
	average_age = 0,
	average_female = 0, 
	average_male = 0;

Embarked sht_max = C;

struct Passenger {
	short id;
	bool survival;
	Pclass pclass;
	std::string name;
	Sex sex;
	double age;
	short sibsp;
	short parch;
	std::string ticket;
	double fare;
	std::string cabin;
	Embarked embarked;
};