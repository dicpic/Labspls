


МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ
Федеральное государственное автономное образовательное учреждение высшего образования
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ
Кафедра компьютерной инженерии и моделирования
<br/><br/>

### Отчёт по лабораторной работе №6<br/> по дисциплине "Программирование"
<br/>

студента 1 курса группы ПИ-б-о-191(2)
Решетник Даниила Сергеевича
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

## Лабораторная работа №6
Погодный информер

**Цель:**  
1. Закрепить навыки разработки многофайловыx приложений;
2. Изучить способы работы с API web-сервиса;
3. Изучить процесс сериализации/десериализации данных.

**Ход работы:**
## Лабораторная работа №6
Погодный информер

**Цель:** 1. Закрепить навыки разработки многофайловыx приложений;
2.Изучить способы работы с API web-сервиса;
3 Изучить процесс сериализации/десериализации данных.

**Ход работы:**
**1\.** Скачиваем [библиотеку](https://github.com/yhirose/cpp-httplib) для работы с сетью с гитхаба и подключаем необходимые файлы.
**2\.** Получаем API key (мой: d1dd437f7b6af2231e3f23acd19eab98) и с помощью него получаем актуальный прогноз погоды.
**3\.** Пишем код для работы с .html файлом. Итоговый код программы выглядит так:
```c++
#include "pch.h"
#include <iostream>
#include <string>
#include "include/httplib/httplib.h"
#include "include/nlohmann/json.hpp"
#include <fstream>
#include <vector>

using namespace httplib;
using namespace nlohmann;


struct info 
{
	std::string data;
	std::vector<json> icon;
	std::vector<std::string> temp;
};

std::string replace(std::string doc, std::string before, std::string after) 
{
	int index;
	if (after[0] == '\"') 
	{
		after = after.substr(1, size(after) - 2);
	}
	index = doc.find(before);
	doc.replace(index, size(before), after);
	return doc;
}
void gen_response(const httplib::Request& req, httplib::Response& red) 
{
	std::string URL = "api.openweathermap.org";
	std::vector<info> days;
	std::string line;
	std::string data;
	std::string city;
	std::string current_data;
	bool nothave;
	httplib::Client client(URL);

	auto res = client.Get("/data/2.5/forecast?q=Simferopol&APPID=d1dd437f7b6af2231e3f23acd19eab98&units=metric");

	if (res && res->status == 200) 
	{

		json j = json::parse(res->body);

		city = j["city"]["name"].dump();

		std::ifstream file("Weather.html");
		if (file.is_open())
		{
			while (getline(file, line))
			{
				data += line + "\r";
			}
		}
		data = replace(data, "{city.name}", city);
		for (int i = 0; i < 40; i++) 
		{
			nothave = true;
			current_data = j["list"][i]["dt_txt"].dump().substr(1, 10);
			for (int k = 0; k < size(days); k++) {
				if (current_data == days[k].data) {
					days[k].icon.push_back(j["list"][i]["weather"][0]["icon"].dump());
					days[k].temp.push_back(j["list"][i]["main"]["temp"].dump());
					nothave = false;
					break;
				}
			}
			if (nothave) 
			{
				days.push_back(info());
				days[days.size() - 1].data = current_data;
				days[days.size() - 1].icon.push_back(j["list"][i]["weather"][0]["icon"].dump());
				days[days.size() - 1].temp.push_back(j["list"][i]["main"]["temp"].dump());
			}

		}

		for (int b = 0; b < 5; b++) 
		{
			data = replace(data, "{list.dt}", days[b].data);
			data = replace(data, "{list.weather.icon}", days[b].icon[0]);
			data = replace(data, "{list.main.temp}", days[b].temp[0]);
		}
	}
	std::ofstream out;
	out.open("WeatherResult.html");
	if (out.is_open()) {
		out << data;
	}
	red.set_content(data, "text/html");
}

int main()
{
	Server server;                    // Создаём сервер (пока-что не запущен)
	server.Get("/", gen_response);    // Вызвать функцию gen_response если кто-то обратиться к корню "сайта"
	server.listen("localhost", 1337); // Запускаем сервер на localhost и порту 1337	
}
```
**4\.** Проверяем работу написанного кода в браузере.
![Рис.1 Ответ клиенту](https://github.com/dicpic/pics/blob/master/weatherclear.jpg?raw=true)


**Вывод:** В ходе выполнения данной лабораторной работы я  закрепил навыки работы с GitHub и многофайловыми файлами, научился работать с серверами и клиентом.
