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