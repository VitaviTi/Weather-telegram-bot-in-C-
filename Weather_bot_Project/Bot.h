#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <tgbot/tgbot.h>

#include "json.hpp"
#include "weather_text.h"

class Bot
{
public:
	Bot(std::string tg_w_token, std::string tg_n_token, std::string w_token);

private:


	TgBot::Bot bot;
	TgBot::Bot n_bot;
	Weather_text weathertext;
	nlohmann::json cityId;

	//command
	void start(TgBot::Bot &bot);
	void help(TgBot::Bot &bot);
	void weatherButton(TgBot::InlineKeyboardMarkup::Ptr& keyboard, std::vector<std::string> text_, std::vector<std::string> callbackData_);

	void weather(TgBot::Bot &bot, Weather_text &weathertext, nlohmann::json &cityId, TgBot::InlineKeyboardMarkup::Ptr& keyboard);//if the message is a city, sends the weather of that city
	void notification(TgBot::Bot& bot, TgBot::Bot& n_bot);//notification bot, sends to the developer all messages received by the weather bot

};

