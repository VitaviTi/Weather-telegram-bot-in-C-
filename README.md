# Weather telegram bot on cpp
## The weather bot is written in C++ using the library  [tgbot-cpp](https://github.com/reo7sp/tgbot-cpp), library communicating with the weather service [*.h](https://github.com/kovdan01/weather-bot/blob/master/src/weather_api.h)  [*.cpp](https://github.com/kovdan01/weather-bot/blob/master/src/weather_api.cpp). [Weather service](https://openweathermap.org)
This bot communicates with you only in English, but can accept requests in any language. As a response, the bot provides a text message, which, depending on what data was obtained using the OpenWeatherMap API, contains weather data in a given city. Data from OpenWeatherMap is not always complete, so sometimes some parameters may be missing from the output. The bot takes the name of the city and if this city exists, it gives a choice of weather time: now, 1 day, 2 days, 3 days, 4 days, 5 days. Depending on the choice, the bot sends the weather: 
```
City: Moscow RU
broken clouds
Humidity: 44
Temperature: 26
Wind speed: 3.39 m/s 
southeast wind
sunrise: 3 h. 52 min. 
sunset: 21 h. 3 min.
```
## Code
### The program consists of 3 classes, each class is written in its own *.h file and implemented in a *.cpp file.
#### Class OpenWeatherMapApi
Provides communication with the service [OpenWeatherMap](https://openweathermap.org) according to the scheme:
api.openweathermap.org/data/2.5/forecast?units=metric&q={city name}&appid={API key}.
The public function takes the name of the city and return a json object received from the service.
#### Class Weather_text 
The class that processes the incoming json object into text form for the user. The class allows you to flexibly control the creation of text for the user! Its private part contains handler functions that easily convert json objects into a user-readable form! That's all this class is needed for; it is the flexible change of text that makes this class unique and very important in the program.
#### CLass Bot
This is the heart and brain of the bot library [tgbot-cpp](https://github.com/reo7sp/tgbot-cpp) was used only in this class. All actions of a class are specified in its constructor. The trick of this class is that it contains not one bot, but two, one is a Weather bot, the second is an alert bot (sends you any messages received by the weather bot). The class contains the bot's response to the commands /start, /help and any message. When a non-command message is sent to the bot, it passes that message and receives a search response. If such a city exists in the weather service, the bot will send weather time buttons and, depending on their click, display the weather for that city at that time. If such a city does not exist, the bot says that the city does not exist. All these actions are written in 3 classes and it is the class Bot that brings it all together.
