# Weather telegram bot on cpp
## The weather bot is written in C++ using the library  [tgbot-cpp](https://github.com/reo7sp/tgbot-cpp), library communicating with the weather service [*.h](https://github.com/kovdan01/weather-bot/blob/master/src/weather_api.h)  [*.cpp](https://github.com/kovdan01/weather-bot/blob/master/src/weather_api.cpp). [Weather service](https://openweathermap.org)
This bot communicates with you only in English, but can accept requests in any language. As a response, the bot provides a text message, which, depending on what data was obtained using the OpenWeatherMap API, contains weather data in a given city. Data from OpenWeatherMap is not always complete, so sometimes some parameters may be missing from the output. The bot takes the name of the city and if this city exists, it gives a choice of weather time: now, 1 day, 2 days, 3 days, 4 days, 5 days. Depending on the choice, the bot sends the weather: 
If “now”:
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
Else:
```
2024-no-no 21:00:00 //in the example the time is missing intentionally
City: Moscow RU
few clouds
Temperature: 16.56
Wind speed: 3.52 m/s 
south wind
```
## Code
### The program consists of 4 classes, each class is written in its own *.h file and implemented in a *.cpp file.
Class OpenWeatherMapApi
Provides communication with the service [OpenWeatherMap](https://openweathermap.org) according to the scheme: api.openweathermap.org/data/2.5/forecast?units=metric&q={city name}&appid={API key}.
The public function takes the name of the city and returns a json file received from the service.
