#ifndef CSVREADER_H
#define CSVREADER_H

#include "FlightData.h"

namespace CsvJsonSort {
    std::vector<FlightData> readCSV(const std::string &filename);
    void sortFlights(std::vector<FlightData> &flights);
    void writeJSON(const std::vector<FlightData> &flights, const std::string &filename);
}

#endif // CSVREADER_H
