#include "Bot.h"

Bot::Bot(std::string tg_w_token, std::string tg_n_token, std::string w_token)
	: bot(std::move(tg_w_token))
	, n_bot(std::move(tg_n_token))
	, weathertext(std::move(w_token))
{
	std::ifstream file("city_id.json");
	file >> cityId;


	start(bot);

	help(bot);
	

	notification(bot, n_bot);

	//keyboard

	std::vector<std::string> //it is implied that text_=callbackData_!!!
		text_{ "Lugansk", "LuganskaOblast", "Moscow", "Krasnodar", "Kaliningrad", "Voronezh", "Kyiv", "Kharkiv", "Minsk", "Beijing", "London", "Tashkent" },
		callbackData_{ "Luhansk", "Luhans’ka Oblast’", "Moscow", "Krasnodar", "Kaliningrad", "Voronezh", "Kyiv", "Kharkiv", "Minsk", "Beijing", "London", "Tashkent" };

	TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
	weatherButton(keyboard, text_, callbackData_);


	//weatherButton
	weather(bot, weathertext, cityId, keyboard);

	//LongPoll
	try {
        std::cout << "Bot username:  " << bot.getApi().getMe()->username << std::endl;
		bot.getApi().deleteWebhook();
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            std::cout << "Long poll started\n";
            longPoll.start();
        }
    }
    catch (TgBot::TgException& e) {
        std::cout << "error: %s\n" << e.what() << std::endl;
    }
}

void Bot::start(TgBot::Bot &bot)
{
	bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
		bot.getApi().sendMessage(message->chat->id, "Hello! This weather bot!\n/help");

		bot.getApi().sendPhoto(message->chat->id, TgBot::InputFile::fromFile("mushroom.jpg", "image/jpeg"));
		});
}

void Bot::help(TgBot::Bot &bot)
{
	bot.getEvents().onCommand("help", [&bot](TgBot::Message::Ptr message) {
		bot.getApi().sendMessage(message->chat->id,
		"To receive weather information, write the name of your city in English or select from those offered:\n/cities");
		});
}

void Bot::weatherButton(TgBot::InlineKeyboardMarkup::Ptr& keyboard, std::vector<std::string> text_, std::vector<std::string> callbackData_)
{
	for (unsigned i = 0; i < text_.size(); i++) {
		std::vector<TgBot::InlineKeyboardButton::Ptr> row;
		TgBot::InlineKeyboardButton::Ptr checkButton(new TgBot::InlineKeyboardButton);

		checkButton->text = text_[i];
		checkButton->callbackData = callbackData_[i];
		row.push_back(checkButton);
		keyboard->inlineKeyboard.push_back(row);
	}
}

void Bot::weather(TgBot::Bot& bot, Weather_text &weathertext, nlohmann::json &cityId, TgBot::InlineKeyboardMarkup::Ptr& keyboard)
{
	bot.getEvents().onCommand("cities", [&bot, &keyboard](TgBot::Message::Ptr message) {
		bot.getApi().sendMessage(message->chat->id, "Weather:", false, 0, keyboard, "Markdown");
		});

	bot.getEvents().onCallbackQuery([&bot, &weathertext, &cityId](TgBot::CallbackQuery::Ptr query) {
		bot.getApi().sendMessage(query->message->chat->id, weathertext._print(cityId[query->data]));
		});

	bot.getEvents().onAnyMessage([&bot, &weathertext, &cityId](TgBot::Message::Ptr message)
		{
			if (cityId[message->text] != nullptr)
			{
				bot.getApi().sendMessage(message->chat->id, weathertext._print(cityId[message->text]));
			}
		});
}

void Bot::notification(TgBot::Bot &bot, TgBot::Bot &n_bot)
{
	bot.getEvents().onAnyMessage([&bot, &n_bot](TgBot::Message::Ptr message)
		{
			uint32_t subt = message->date;
			uint32_t days = (uint32_t)floor(subt / 86400);
			uint32_t hours = (uint32_t)floor(((subt - days * 86400) / 3600) % 24) + 3;
			uint32_t minutes = (uint32_t)floor((((subt - days * 86400) - hours * 3600) / 60) % 60);
			n_bot.getApi().sendMessage("5996699629", 
				message->from->firstName + message->from->lastName + 			
				"(@" + message->from->username + ") wrote: " + "\n" + message->text + "\n" + 
				"date: " + std::to_string(days) + " d. " + std::to_string(hours) + " hours " + std::to_string(minutes) + " min.");
		});
	bot.getEvents().onCallbackQuery([&bot, &n_bot](TgBot::CallbackQuery::Ptr query) {
		n_bot.getApi().sendMessage("5996699629", "Button: \n"  + query->data + "\n" );
		});
}