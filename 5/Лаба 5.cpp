#include"pch.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<conio.h>
#include"description.h"


std::vector<Passenger> passengers;
std::vector<int> children;

int end = -1;
int lastEndSize = 1;

std::string getwhatiwant(std::string strong, std::string endStrong) {  
	int begin = end + lastEndSize;
	end = strong.find(endStrong, begin);
	lastEndSize = endStrong.size();
	return strong.substr(begin, end - begin);
}


int main()
{
	setlocale(LC_ALL, "Russian");
	std::string name;
	std::cout << "Pls type naemm of filee: ";
	std::cin >> name;
	std::ifstream fin(name);
	while (!fin)
	{
		std::cout << "Uh oh, stinky!";
		std::cout << "Pls type naemm of filee: ";
		std::cin >> name;
		std::ifstream fin(name);
	}

	std::ofstream fout("fliez.txt");
	std::string line;
	
	std::getline(fin, line, '\r');
	
	while (std::getline(fin, line, '\r')) {

		Passenger passenger;
		passenger.id		= std::stoi(getwhatiwant(line, ","));
		passenger.survival	= std::stoi(getwhatiwant(line, ","));
		passenger.pclass	= Pclass(std::stoi(getwhatiwant(line, ",\"")));
		passenger.name		= getwhatiwant(line, "\",");

		if (getwhatiwant(line, ",") == "male")
			passenger.sex	= Sex::Male;
		else
			passenger.sex	= Sex::Female;

		std::string age		= getwhatiwant(line, ",");

		if (age == "") 
			passenger.age = -1;
		else 
			passenger.age	= std::stoi(age);

		passenger.sibsp		= std::stoi(getwhatiwant(line, ","));
		passenger.parch		= std::stoi(getwhatiwant(line, ","));
		passenger.ticket	= getwhatiwant(line, ",");
		passenger.fare		= std::stod(getwhatiwant(line, ","));
		passenger.cabin		= getwhatiwant(line, ",");

		std::string embarked = getwhatiwant(line, ",");
		
		if (embarked == "C") 
			passenger.embarked = Embarked::C;
		else if (embarked == "Q") 
			passenger.embarked = Embarked::Q;
		else 
			passenger.embarked = Embarked::S;

		passengers.push_back(passenger);
	}

	for (int i = 0; i < passengers.size(); i++) {
		if (passengers[i].survival) {
			calive++;
			if (passengers[i].pclass == Pclass::First) fclass++;
			else if (passengers[i].pclass == Pclass::Second) sclass++;
			else tclass++;

			if (passengers[i].sex == Sex::Female) female++;
			else male++;
		};
		if (passengers[i].age != -1) {
			average_age += passengers[i].age;
			age_all++;
			if (passengers[i].sex == Sex::Female) {
				female_all++;
				average_female += passengers[i].age;
			}
			else {
				male_all++;
				average_male += passengers[i].age;
			}
		}

		sht[passengers[i].embarked]++;

		if (passengers[i].age < 18 && passengers[i].age != -1) children.push_back(passengers[i].id);
	}
	average_age /= age_all;
	average_female /= female_all;
	average_male /= male_all;

	if (sht[sht_max] < sht[Q]) sht_max = Q; 
	if (sht[sht_max] < sht[S]) sht_max = S;

	fout << "\nОбщее число выживших: " << calive;
	fout << "\nЧисло выживших из 1 класса: " << fclass;
	fout << "\nЧисло выживших из 2 класса: " << sclass;
	fout << "\nЧисло выживших из 3 класса: " << tclass;
	fout << "\nКоличество выживших женщин: " << female;
	fout << "\nКоличество выживших мужчин: " << male;
	fout << "\nСредний возраст пассажира: " << average_age;
	fout << "\nСредний женский возраст: " << average_female;
	fout << "\nСредний мужской возраст: " << average_male;
	fout << "\nШтат, в котором село больше всего пассажиров: ";
	if (sht_max == 0)  
		fout << "C";
	else 
		if (sht_max == 1) 
			fout << "Q";
		else 
			fout << "S";
	fout << "\nСписок идентификаторов несовершеннолетних (младше 18) пассажиров: \n";

	for (int i = 0; i < children.size(); i++) {
		if (i == children.size() - 1) {
			fout << children[i];
			break;
		}
		if (i % 10 == 9)
			fout << "\n";
		fout << children[i] << ",";
	}

	fout.close();
	fin.close();
}