🌦️ Weather Information System
🧩 Overview

Weather Information System is a console-based C++ application developed as a 2nd semester project by Team Core5 — Asik, Ishtiaq, and Monjur.

It simulates an offline weather data management system that allows users to:

Query weather information of capital cities by entering a country name.

Enable admins to add or update detailed weather records.

🚀 Features
🔐 1. Admin Panel

Secure Authentication — Access protected with username and password.

Comprehensive Data Management — Add or update weather data including:

🌡️ Temperature (°C)

💧 Humidity (%)

☔ Precipitation (mm)

🌬️ Wind Speed (m/s)

🧭 Wind Direction (°)

🌫️ Visibility (m)

🧮 Air Pressure (hPa)

🌡️ Dew Point (°C)

🏙️ Air Quality Index (AQI)

🌞 UV Index

☁️ Weather Condition

🧾 Forecast Summary

City Directory Overview — View all stored city records for quick reference.

Persistent Data Storage — Changes saved to weather_data.txt for future use.

Flexible Exit Options — Save or discard edits before exiting.

👥 2. User Mode

Country–Capital Mapping — Database of 50+ countries linked to their capitals.

Case-Insensitive Search — Accepts user input in any capitalization.

Detailed Weather Display — Retrieves and formats data neatly for readability.

User-Friendly Output — Simple console display for ease of understanding.

💾 3. Data Persistence

File-Based Storage — All data stored in a human-readable file weather_data.txt.

Automatic Loading — Loads existing data at startup if available.

Automatic Saving — Weather data is saved automatically upon exit.

🛠️ Technologies Used

Language: C++

Data Storage: Text File (.txt)

Standard Library Features:

📂 File I/O (fstream)

🔤 String Manipulation (string, sstream)

🗺️ Containers (map)

⚙️ Algorithms (transform)

🚨 Exception Handling (try-catch)

🕓 Time Handling (ctime)

⚙️ How It Works

Startup:

Loads data from weather_data.txt (if available).

Starts with an empty database otherwise.

Main Menu:

Choose between Admin Login, User Mode, or Exit.

Admin Login:

Enter predefined credentials.

Manage or view weather data records.

Admin Panel Options:

Add / Update city weather data.

View stored cities.

Save and exit (or exit without saving).

User Mode:

Enter a country name → retrieves its capital city.

Displays complete weather report for that capital.

Exit:

Automatically saves all data.

📂 Project Structure
Weather_Information_System/
│
├── main.cpp                 # Core program logic
├── weather_data.txt         # Data storage file
│
├── WeatherData struct       # Holds all weather parameters
├── WeatherFileHandler class # Handles file I/O operations
├── maps & data structures   # Country-capital and weather info
└── console UI menus         # Admin and user interfaces

🧭 How to Run

Clone this repository:

git clone https://github.com/your-username/Weather-Information-System.git


Navigate to the project directory:

cd Weather-Information-System


Compile the program:

g++ main.cpp -o WeatherSystem


Run the executable:

./WeatherSystem

🖼️ Screenshots
🔧 Admin Panel

(Sample admin menu interface)

🌤️ Adding Weather Data

(Example of adding or updating records)

🌍 User Mode Query

(Example user input and displayed result)

🖼️ (Add screenshots here when available for better presentation!)

🎓 Challenges & Learning

First major project built in C++.

Learned file handling for persistent data.

Used maps and structs for organized data storage.

Implemented menu-driven console navigation.

Practiced string processing and exception handling.

Improved teamwork and collaboration through task division and code integration.

🚀 Future Improvements

🗑️ Add delete functionality for city data.

✅ Improve input validation.

☁️ Add real-time weather API integration.

🎨 Enhance console UI with colors and formatting.

🌅 Display sunrise and sunset times.

👨‍💻 Team Core5
Member	ID	
Md Asikur Rahman	C241092	
Md Istiaq Uddin	C241089	
Md Monjur Uddin	C241096
