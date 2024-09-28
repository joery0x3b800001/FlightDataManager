// csvreader.cpp

#include "csvreader.h"

#include <fstream>
#include <sstream>
#include <vector>

#include <json.hpp>

#include <QRegularExpression>
#include <QRegularExpressionMatch>

namespace FlightUtils {

    // Convert time to seconds
    int timeToSeconds(const std::string& time) {
        QString timeQStr = QString::fromStdString(time);
        static QRegularExpression re(R"((\d{1,2}):(\d{2}):(\d{2})\s*(AM|PM)?)");
        QRegularExpressionMatch match = re.match(timeQStr);

        if (!match.hasMatch()) return 0;

        int h = match.captured(1).toInt();
        int m = match.captured(2).toInt();
        int s = match.captured(3).toInt();
        if (match.captured(4) == "PM" && h != 12) h += 12;
        if (match.captured(4) == "AM" && h == 12) h = 0;
        return h * 3600 + m * 60 + s;
    }

    // Compare function
    bool compareFlightData(const FlightData &a, const FlightData &b)
    {
        return timeToSeconds(a.time) < timeToSeconds(b.time);
    }

} // namespace FlightUtils

std::vector<FlightData> CsvJsonSort::readCSV(const std::string &filename)
{
    std::vector<FlightData> flights;
    std::ifstream file(filename);
    std::string line;

    // Skip the header line
    if (std::getline(file, line)) {
        // Do Nothing
    }

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string time, latitude, longitude, course, kts, mph, altitude_feet, reporting_facility;

        std::getline(ss, time, ',');
        std::getline(ss, latitude, ',');
        std::getline(ss, longitude, ',');
        std::getline(ss, course, ',');
        std::getline(ss, kts, ',');
        std::getline(ss, mph, ',');
        std::getline(ss, altitude_feet, ',');
        std::getline(ss, reporting_facility, ',');

        flights.emplace_back(
            time,
            latitude,
            longitude,
            course,
            kts.empty() ? "" : kts,
            mph.empty() ? "" : mph,
            altitude_feet.empty() ? "" : altitude_feet,
            reporting_facility
        );
    }

    return flights;
}

void CsvJsonSort::sortFlights(std::vector<FlightData> &flights)
{
    std::sort(flights.begin(), flights.end(), FlightUtils::compareFlightData);
}

void CsvJsonSort::writeJSON(const std::vector<FlightData> &flights, const std::string &filename)
{
    nlohmann::json j;
    for (const auto &flight : flights)
    {
        j.push_back({{"Time", flight.time}, {"Latitude", flight.latitude}, {"Longitude", flight.longitude},
                     {"Course", flight.course}, {"kts", flight.kts}, {"mph", flight.mph}, {"AltitudeFeet", flight.altitude_feet},
                     {"Reporting Facility", flight.reporting_facility}});
    }
    std::ofstream jsonFile(filename);
    jsonFile << j.dump(4);
}
