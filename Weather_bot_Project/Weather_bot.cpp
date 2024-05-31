#include "Bot.h"

int main()
{
    const std::string OPENWEATHERMAP_TOKEN {"TOKEN"};
    const std::string TGWEATHERBOT_TOKEN {"TOKEN"};
    const std::string TGNOTIFICATIONBOT_TOKEN {"TOKEN"};
    Bot bot(TGWEATHERBOT_TOKEN, TGNOTIFICATIONBOT_TOKEN, OPENWEATHERMAP_TOKEN);
}
