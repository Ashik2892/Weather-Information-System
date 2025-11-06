#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <cctype>  

using namespace std;


struct WeatherData {
    float temp;
    int humidity;
    float precipitation;
    float windSpeed;
    int windDirection;
    float pressure;
    int visibility;
    float dewPoint;
    int aqi;
    float uvIndex;
    int sunrise;
    int sunset;
    string condition;
    string forecast;
};


class WeatherFileHandler {
private:
    string filename;

public:
    WeatherFileHandler(const string& file) : filename(file) {}

    
    bool fileExists() const {
        ifstream file(filename);
        return file.good();
    }

   
    map<string, WeatherData> loadData() {
        map<string, WeatherData> data;
        ifstream file(filename);

        if (!file.is_open()) {
            throw runtime_error("Could not open file: " + filename);
        }

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;

            string city;
            WeatherData wdata;
            stringstream ss(line);
            ss >> city >> wdata.temp >> wdata.humidity >> wdata.precipitation >> wdata.windSpeed
                >> wdata.windDirection >> wdata.pressure >> wdata.visibility >> wdata.dewPoint
                >> wdata.aqi >> wdata.uvIndex >> wdata.sunrise >> wdata.sunset;

            
            if (getline(file, wdata.condition) && getline(file, wdata.forecast)) {
               
                wdata.condition = trim(wdata.condition);
                wdata.forecast = trim(wdata.forecast);
                data[city] = wdata;
            }
        }

        file.close();
        return data;
    }

   
    void saveData(const map<string, WeatherData>& weatherData) {
        ofstream file(filename);

        if (!file.is_open()) {
            throw runtime_error("Could not open file for writing: " + filename);
        }

        for (const auto& [city, data] : weatherData) {
            file << city << " "
                 << data.temp << " "
                 << data.humidity << " "
                 << data.precipitation << " "
                 << data.windSpeed << " "
                 << data.windDirection << " "
                 << data.pressure << " "
                 << data.visibility << " "
                 << data.dewPoint << " "
                 << data.aqi << " "
                 << data.uvIndex << " "
                 << data.sunrise << " "
                 << data.sunset << "\n"
                 << data.condition << "\n"
                 << data.forecast << "\n";
        }

        file.close();
    }

   
    static string trim(const string& str) {
        size_t start = str.find_first_not_of(" \t\n\r");
        size_t end = str.find_last_not_of(" \t\n\r");
        return (start == string::npos) ? "" : str.substr(start, end - start + 1);
    }
};


map<string, WeatherData> weatherData;


string toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
              [](unsigned char c){ return tolower(c); });
    return lowerStr;
}


void printWeatherData(const string& city) {
    string formattedCity = toLowerCase(city);

    for (const auto& [entryCity, data] : weatherData) {
        if (toLowerCase(entryCity) == formattedCity) {
            cout << "\nCity Name: " << entryCity << endl;
            cout << "Temperature: " << data.temp << "°C" << endl;
            cout << "Humidity: " << data.humidity << "%" << endl;
            cout << "Precipitation: " << data.precipitation << " mm" << endl;
            cout << "Wind Speed: " << data.windSpeed << " m/s" << endl;
            cout << "Wind Direction: " << data.windDirection << "°" << endl;
            cout << "Air Pressure: " << data.pressure << " hPa" << endl;
            cout << "Dew Point: " << data.dewPoint << "°C" << endl;
            cout << "Air Quality Index (AQI): " << data.aqi << endl;
            cout << "UV Index: " << data.uvIndex << endl;

            
            time_t sunriseTime = data.sunrise;
            time_t sunsetTime = data.sunset;
           
            

            cout << "Weather Condition: " << data.condition << endl;
            cout << "Forecast: " << data.forecast << endl;
            return;
        }
    }

    cout << "No weather data available for " << city << endl;
}


bool adminLogin() {
    string username, password;
    cout << "Admin Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    return (username == "core5" && password == "2866");
}


void adminPanel(WeatherFileHandler& fileHandler) {
    int choice;
    do {
        cout << "\n--- Admin Panel ---\n";
        cout << "1. Add/Update Weather\n";
        cout << "2. View All Cities\n";
        cout << "3. Save and Exit\n";
        cout << "4. Exit Without Saving\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            string city;
            WeatherData data;
            cout << "Enter City Name: ";
            cin.ignore();
            getline(cin, city);

            cout << "Enter Temperature (°C): ";
            cin >> data.temp;
            cout << "Enter Humidity (%): ";
            cin >> data.humidity;
            cout << "Enter Precipitation (mm): ";
            cin >> data.precipitation;
            cout << "Enter Wind Speed (m/s): ";
            cin >> data.windSpeed;
            cout << "Enter Wind Direction (°): ";
            cin >> data.windDirection;
            cout << "Enter Air Pressure (hPa): ";
            cin >> data.pressure;
            cout << "Enter Visibility (m): ";
            cin >> data.visibility;
            cout << "Enter Dew Point (°C): ";
            cin >> data.dewPoint;
            cout << "Enter Air Quality Index (AQI): ";
            cin >> data.aqi;
            cout << "Enter UV Index: ";
            cin >> data.uvIndex;
           // cout << "Enter Sunrise Time (Unix timestamp): ";
            //cin >> data.sunrise;
            //cout << "Enter Sunset Time (Unix timestamp): ";
            //cin >> data.sunset;
            cout << "Enter Weather Condition: ";
            cin.ignore();
            getline(cin, data.condition);
            cout << "Enter Forecast: ";
            getline(cin, data.forecast);

            weatherData[city] = data;
            cout << "Weather data updated!\n";
        }
        else if (choice == 2) {
            cout << "\nCities in Database:\n";
            for (const auto& [city, _] : weatherData) {
                cout << " - " << city << endl;
            }
        }
        else if (choice == 3) {
            try {
                fileHandler.saveData(weatherData);
                cout << "Data saved successfully!\n";
                return;
            } catch (const exception& e) {
                cerr << "Error saving data: " << e.what() << endl;
            }
        }
    } while (choice != 4);
}

// User Mode - Offline
void userPanelOffline() {
    string country;
    cout << "Enter country name to check the weather of its capital: ";
    cin.ignore();
    getline(cin, country);

   
    map<string, string> capitals = {
        {"bangladesh", "Dhaka"},
        {"usa", "Washington"},
        {"uk", "London"},

        {"india", "New Delhi"},
        {"canada", "Ottawa"},
        {"australia", "Canberra"},
        {"japan", "Tokyo"},
        {"germany", "Berlin"},
        {"france", "Paris"},
        {"italy", "Rome"},
        {"spain", "Madrid"},
        {"brazil", "Brasilia"},
        {"china", "Beijing"},
        {"russia", "Moscow"},
        {"afghanistan", "Kabul"},
{"armenia", "Yerevan"},
{"azerbaijan", "Baku"},
{"bahrain", "Manama"},
{"bhutan", "Thimphu"},
{"brunei", "Bandar Seri Begawan"},
{"cambodia", "Phnom Penh"},
{"cyprus", "Nicosia"},
{"georgia", "Tbilisi"},
{"indonesia", "Jakarta"},
{"iran", "Tehran"},
{"iraq", "Baghdad"},
{"israel", "Jerusalem"},
{"jordan", "Amman"},
{"kazakhstan", "Astana"},
{"kuwait", "Kuwait City"},
{"kyrgyzstan", "Bishkek"},
{"laos", "Vientiane"},
{"lebanon", "Beirut"},
{"malaysia", "Kuala Lumpur"},
{"maldives", "Malé"},
{"mongolia", "Ulaanbaatar"},
{"myanmar", "Naypyidaw"},
{"nepal", "Kathmandu"},
{"north korea", "Pyongyang"},
{"oman", "Muscat"},
{"pakistan", "Islamabad"},
{"palestine", "East Jerusalem"},
{"philippines", "Manila"},
{"qatar", "Doha"},
{"saudi arabia", "Riyadh"},
{"singapore", "Singapore"},
{"south korea", "Seoul"},
{"sri lanka", "Sri Jayawardenepura Kotte"},
{"syria", "Damascus"},
{"tajikistan", "Dushanbe"},
{"thailand", "Bangkok"},
{"timor-leste", "Dili"},
{"turkey", "Ankara"},
{"turkmenistan", "Ashgabat"},
{"united arab emirates", "Abu Dhabi"},
{"uzbekistan", "Tashkent"},
{"vietnam", "Hanoi"},
{"yemen", "Sana'a"}
    };

    string countryLower = toLowerCase(country);
    if (capitals.find(countryLower) != capitals.end()) {
        printWeatherData(capitals[countryLower]);
    } else {
        cout << "No data available for the capital of " << country << endl;
    }
}

int main() {
    WeatherFileHandler fileHandler("weather_data.txt");

    try {
        if (fileHandler.fileExists()) {
            weatherData = fileHandler.loadData();
            cout << "Weather data loaded successfully!\n";
        } else {
            cout << "No existing data file. Starting with empty database.\n";
        }
    } catch (const exception& e) {
        cerr << "Error loading data: " << e.what() << endl;
        cout << "Starting with empty database\n";
    }

    int modeChoice;
    do {
        cout << "\n--- Weather Information System ---\n";
        cout << "1. Admin Login\n";
        cout << "2. User Mode\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> modeChoice;

        if (modeChoice == 1) {
            if (adminLogin()) {
                adminPanel(fileHandler);
            } else {
                cout << "Authentication failed!\n";
            }
        } else if (modeChoice == 2) {
            userPanelOffline();
        }

    } while (modeChoice != 3);

    
    try {
        fileHandler.saveData(weatherData);
        cout << "Data saved on exit\n";
    } catch (const exception& e) {
        cerr << "Error saving on exit: " << e.what() << endl;
    }

    return 0;
}

