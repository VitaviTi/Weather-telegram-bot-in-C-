#include "weather_text.h"
 
Weather_text::Weather_text(std::string token) : m_weather(std::move(token))
{
    std::ifstream file("rus.json");
    file >> json;
}


std::string Weather_text::convert_to_str(nlohmann::json const &_json)
{
    std::stringstream ss;
    std::string str;
    ss << _json;
    ss >> str;
    return str;    
}

std::string Weather_text::transform_to_str(nlohmann::json const& _json)
{
    return _json.template get<std::string>(); 
}

std::string Weather_text::convert_unixtime(uint64_t subt)
{
    subt += json_["timezone"];
    uint32_t days = (uint32_t)floor(subt / 86400);
    uint32_t hours = (uint32_t)floor(((subt - days * 86400) / 3600) % 24);
    uint32_t minutes = (uint32_t)floor((((subt - days * 86400) - hours * 3600) / 60) % 60);
    std::string strh;
    switch (hours)
    {
    case 1:
        strh = transform_to_str(json["sun"]["hours0"]);
        break;
    case 2:
    case 3:
    case 4:
        strh = transform_to_str(json["sun"]["hours1"]);
    default:
        strh = transform_to_str(json["sun"]["hours"]);
    }
    return std::to_string(hours) + " " + strh + " " + std::to_string(minutes) + " " + transform_to_str(json["sun"]["minutes"]);
}


std::string Weather_text::_print(int const& cityID)
{
    json_ = m_weather.make_request_by_city_id(cityID, "ru");//weather information
    return cityName() + "\n" + hum() + "\n" + temp() + "\n" + wind() + "\n" + sun();
}

std::string Weather_text::temp()
{
    return transform_to_str(json["t"]["temp"]) + convert_to_str(json_["main"]["temp"]) + transform_to_str(json["t"]["degres"]) + ",\n" + //temperarture: ___
           transform_to_str(json["t"]["feel"]) + convert_to_str(json_["main"]["feels_like"]) + transform_to_str(json["t"]["degres"]) + ";\n"; // feels like: ___
}

std::string Weather_text::hum()
{
    return transform_to_str(json["hum"]) + convert_to_str(json_["main"]["humidity"]) + "%" + ";\n";//humidity: __ %;
}

std::string Weather_text::cityName()
{
    return transform_to_str(json["city"]) + transform_to_str(json_["name"]) + "\n" + //city name:  ____
           transform_to_str(json_["weather"][0]["description"]) + ";\n"; //<weather description>
}

std::string Weather_text::press()
{
    return transform_to_str(json["press"]["pressure"]) + "\n" + //Atmospheric pressure:
           convert_to_str(json_["main"]["pressure"]) + transform_to_str(json["press"]["mm"]) + ";\n"; // <pressure> mm Hg
}

std::string Weather_text::wind()
{
    return transform_to_str( json["wind"]["speed_wind"] ) + //Speed wind:
           convert_to_str( json_["wind"]["speed"] ) + transform_to_str( json["wind"]["m/s"] ) + ",\n" + // ___ m/s
           windDegree( json_["wind"]["deg"] ) + " " + transform_to_str(json["wind"]["wind"]) + ";\n";
}

std::string Weather_text::windDegree(nlohmann::json & _json)
{
    std::stringstream ss1;
    float k;
    ss1 << _json;
    ss1 >> k;

    int n = k / 9;

    if (n >  3 && n <  7)return transform_to_str(json["degree"]["ne"]);/*северо-восток*/
    if (n > 13 && n < 17)return transform_to_str(json["degree"]["se"]);/*юго-восток*/
    if (n > 23 && n < 27)return transform_to_str(json["degree"]["sw"]);/*юго-запад*/
    if(n > 33 && n < 37)return transform_to_str(json["degree"]["nw"]);/*северо-запад*/

    n = n / 10;
    switch (n)
    {
    case 0:
    case 4:
        return transform_to_str(json["degree"]["n"]);/*север*/
    case 1:
        return transform_to_str(json["degree"]["e"]);/*восток*/
    case 2:
        return transform_to_str(json["degree"]["s"]);/*юг*/
    case 3:
        return transform_to_str(json["degree"]["w"]);/*запад*/
    default:
        return "eror_0!!!";
    }

    return "eror_1!!!";
}

std::string Weather_text::sun()
{
    return transform_to_str(json["sun"]["rise"]) + " " + convert_unixtime(json_["sys"]["sunrise"]) + ",\n" +
           transform_to_str(json["sun"]["set"]) + " " + convert_unixtime(json_["sys"]["sunset"]) + ";\n";
}
