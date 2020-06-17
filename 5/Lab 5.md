


МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ<br>
Федеральное государственное автономное образовательное учреждение высшего образования<br>
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"<br>
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ<br>
Кафедра компьютерной инженерии и моделирования<br>
<br/><br/>

### Отчёт по лабораторной работе №5<br/> по дисциплине "Программирование"
<br/>

студента 1 курса группы ПИ-б-о-191(2)
Решетника Даниила Сергеевича
направления подготовки 09.03.04 "Программная инженерия"
<br/>

<table>
<tr><td>Научный руководитель<br/> старший преподаватель кафедры<br/> компьютерной инженерии и моделирования</td>
<td>(оценка)</td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br/><br/>

Симферополь, 2019
## Лабораторная работа №5
Работа с текстовыми файлами

**Цель:** 1. Научиться работать с текстовыми файлами;
2.Закрепить навыки работы со структурами.

**Ход работы:**
**1.** Из предоставленного репозитория был скачан файл **train.csv**.
**2.** На основании файла **data_dictionary.txt** была создана структура для чтения записей из файла **train.csv**:
```cpp
enum Pclass 
{ 
	First = 1, 
	Second = 2, 
	Third = 3 
};
enum Sex 
{ 
	Male, 
	Female
};
enum Embarked 
{	
	C, 
	Q, 
	S 
};

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
```
**3.** Ознакомился с форматом файлов *CSV* и были считаны все записи в вектор.<br>
**4.** Рассчитаны и сохранены в новый файл **filez.txt** с предоставленными характеристиками (Таблица 1).

Код:
```cpp
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
```
Для просмотра результата: [fliez.txt](https://github.com/dicpic/You-will-die/blob/master/fliez.txt).

Все рассчитанные характеристики в виде таблицы:

| **Характеристика**  | **Результат**   |
| ------------ | ------------ |
| Общее число выживших  | 342  |
| Число выживших из 1 класса  | 136  |
| Число выживших из 2 класса  | 87  |
| Число выживших из 3 класса  | 119  |
| Количество выживших женщин  | 233  |
| Количество выживших мужчин  | 109  |
| Средний возраст пассажира  | 29.6793  |
| Средний женский возраст  | 27.9042  |
| Средний мужской возраст  | 30.702  |
| Штат, в котором село больше всего пассажиров  | S  |
| Список идентификаторов несовершеннолетних (младше 18) пассажиров |8,10,11,15,17,23,25,40,44, <br>51,59,60,64,69,72,79,85,87,112, <br>115,120,126,139,148,157,164,165,166,172, <br>173,183,184,185,194,206,209,221,234,238, <br>262,267,279,283,298,306,308,330,334,341, <br>349,353,375,382,387,390,408,420,434,436, <br>446,447,449,470,480,481,490,501,505,531, <br>533,536,542,543,550,551,575,619,635,643, <br>645,684,687,690,692,721,722,732,747,751, <br>752,756,765,778,781,782,788,789,792,803, <br>804,814,820,825,828,831,832,842,845,851, <br>853,854,870,876 |

**Вывод:** В данной лабораторной работе, я ознакомился с форматом файлов CSV, научился работать с текстовыми файлами и закрепил навыки работы со структурами.
