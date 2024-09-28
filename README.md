# Flight Data Processing Project

## Overview

This project involves reading flight data from a CSV file, parsing it into objects, sorting the data, and then exporting it to a JSON file and a database. A Qt GUI is provided for user interaction, allowing users to load a CSV file, sort the data, write it to a JSON file, and load it into a database.

## Project Structure

```
/FlightDataManager
│
├── main.cpp            // Entry point for the application
├── FlightData.h        // Class definition for flight data
├── FlightData.cpp      // Class implementation
├── csvreader.h         // CSV parsing functionality
├── csvreader.cpp       // Implementation of CSV parser
├── JsonWriter.h        // JSON writing functionality
├── JsonWriter.cpp      // Implementation of JSON writer
├── databasehandler.h   // Database management functionalities
├── databasehandler.cpp // Implementation of database manager
│
├── resources
│   └── LTX Programming Assignment - SDE Qt_NZ5_flightdatar.csv // CSV file
│
├── outputs
│   └── output.json   // Output JSON file
|   └-- output.db     // SQLite database file
│
└── README.md              // Project documentation
```

## Dependencies

- **Qt 5/6**: For GUI development
- **SQLite/PostgreSQL/MySQL**: For database operations (depending on your choice)
- **nlohmann/json**: For JSON handling (if not included with your compiler)

## Installation

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/joery0x3b800001/FlightDataManager.git
   cd FlightDataManager
   ```

2. **Install Dependencies:**
   - Make sure you have Qt installed on your machine.
   - Install the database drivers you plan to use (SQLite, PostgreSQL, MySQL).

3. **Build the Project:**
   - Open the project in Qt Creator and configure it to use the necessary database drivers.
   - Build the project.

## Usage

1. **Load CSV:**
   - Click on the "Load CSV" button to load your `LTX Programming Assignment - SDE Qt_NZ5_flightdatar.csv` file.

2. **Sort Data:**
   - Click on the "Sort Data" button to sort the entries based on the `Time` column.

3. **Write JSON:**
   - Click on the "Write JSON" button to save the sorted data as a JSON file.

4. **Write to Database:**
   - Click on the "Write to Database" button to store the sorted data in the selected database.

5. **Display Data:**
   - The sorted data will be displayed in a `QTableView` within the GUI.

## Code Explanation

### Class Definition

The `FlightData` class represents the structure of each flight entry, containing members for each column in the CSV.

```cpp
class FlightData {
public:
    std::string time, latitude, longitude, course, kts, mph, altitude_feet, reporting_facility;

    FlightData(const std::string &t, const std::string &lat, const std::string &lon,
               const std::string &cour, const std::string &k, const std::string &m,
               const std::string &af, const std::string &rf)
        : time(t), latitude(lat), longitude(lon), course(cour),
        kts(k), mph(m), altitude_feet(af), reporting_facility(rf) {}
};
```

### CSV Parsing

The `csvreader` class is responsible for reading the CSV file and populating an array of `FlightData` objects.

### JSON Writing

The same class `csvreader` handles converting the array of `FlightData` objects into a JSON format and saving it to a file.

### Database Management

The `databasehandler` class contains methods for connecting to the database and executing SQL commands to insert the sorted flight data.

## Example Output

The resulting `output.json` file will look like:

```json
[
    {
        "AltitudeFeet": "2025",
        "Course": "265",
        "Latitude": "33.9303",
        "Longitude": "-118.4759",
        "Reporting Facility": "FlightAware ADS-B (KSMO)",
        "Time": "10:34:51 AM",
        "kts": "218",
        "mph": "251"
    },
    // More entries...
]
```

## Database Schema

Ensure that your database table has the same columns as defined in the `FlightData` class. For example:

```sql
    CREATE TABLE IF NOT EXISTS flights (
                        time TEXT NOT NULL,
                        latitude DOUBLE NOT NULL,
                        longitude DOUBLE NOT NULL,
                        course INT NOT NULL,
                        kts INT NOT NULL DEFAULT 0,
                        mph INT NOT NULL DEFAULT 0,
                        altitude_feet INT NOT NULL DEFAULT 0,
                        reporting_facility TEXT NOT NULL
    )
```

## Conclusion

This project provides a comprehensive solution for loading, sorting, and storing flight data in various formats.