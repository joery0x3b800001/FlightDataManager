// databasehandler.cpp

#include "databasehandler.h"

#include <vector>
#include <string>
#include <QStandardPaths>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <sqlite3.h>

void DB::loadIntoDatabase(const std::vector<FlightData> &flights, const std::string &dbFilePath)
{
    // Paths for the two databases
    QString userDbPath = QString::fromStdString(dbFilePath);
    QString resourceDbPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/flights.db";

    // Create the database directory if it doesn't exist
    QDir dir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    // Function to write data to a database
    auto writeToDatabase = [](const QString& dbPath, const std::vector<FlightData>& flights) {
        sqlite3 *db;
        if (sqlite3_open(dbPath.toStdString().c_str(), &db) != SQLITE_OK) {
            qDebug() << "Failed to open database:" << sqlite3_errmsg(db);
            return;
        }

        const char *createTableSQL = "CREATE TABLE IF NOT EXISTS flights ("
                                     "time TEXT NOT NULL,"
                                     "latitude DOUBLE NOT NULL,"
                                     "longitude DOUBLE NOT NULL,"
                                     "course INT NOT NULL,"
                                     "kts INT NOT NULL DEFAULT 0,"
                                     "mph INT NOT NULL DEFAULT 0,"
                                     "altitude_feet INT NOT NULL DEFAULT 0,"
                                     "reporting_facility TEXT NOT NULL)";

        if (sqlite3_exec(db, createTableSQL, 0, 0, 0) != SQLITE_OK) {
            qDebug() << "Failed to create table:" << sqlite3_errmsg(db);
        }

        for (const auto &flight : flights) {
            std::string insertSQL = "INSERT INTO flights (time, latitude, longitude,"
                                    "course, kts, mph, altitude_feet, reporting_facility) "
                                    "VALUES ('" + flight.time + "', '" + flight.latitude
                                    + "', '" + flight.longitude
                                    + "', '" + flight.course + "', '" + flight.kts
                                    + "', '" + flight.mph + "', '" + flight.altitude_feet
                                    + "', '" + flight.reporting_facility + "');";

            if (sqlite3_exec(db, insertSQL.c_str(), 0, 0, 0) != SQLITE_OK) {
                qDebug() << "Failed to insert data:" << sqlite3_errmsg(db);
            }
        }
        sqlite3_close(db);
    };

    // Write to both the user-specified path and the resource location
    writeToDatabase(userDbPath, flights);
    writeToDatabase(resourceDbPath, flights);
}
