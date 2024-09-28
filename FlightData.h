#ifndef FLIGHTDATA_H
#define FLIGHTDATA_H

#include <string>

class FlightData {
public:
    std::string time, latitude, longitude, course, kts, mph, altitude_feet, reporting_facility;

    FlightData(const std::string &t, const std::string &lat, const std::string &lon,
               const std::string &cour, const std::string &k, const std::string &m,
               const std::string &af, const std::string &rf)
        : time(t), latitude(lat), longitude(lon), course(cour),
        kts(k), mph(m), altitude_feet(af), reporting_facility(rf) {}
};

#endif // FLIGHTDATA_H
