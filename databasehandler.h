#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <vector>
#include "FlightData.h"

class DB {
public:
    static void loadIntoDatabase(const std::vector<FlightData> &flights, const std::string &dbFilePath);
};

#endif // DATABASEHANDLER_H
