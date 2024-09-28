#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "csvreader.h"
#include "databasehandler.h"

#include <QMessageBox>
#include <QFileDialog>

#include <QStandardItemModel>
#include <vector>

// Slot for Load CSV button
void MainWindow::on_loadButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open CSV File"), "", tr("CSV Files (*.csv)"));
    if (!fileName.isEmpty()) {
        flights = CsvJsonSort::readCSV(fileName.toStdString());
        QMessageBox::information(this, "Success", "CSV file loaded successfully!");
    } else {
        QMessageBox::warning(this, "Error", "Failed to load CSV file.");
    }
}

// Slot for Sort Data button
void MainWindow::on_sortButton_clicked() {
    if (flights.empty()) {
        QMessageBox::warning(this, "Warning", "No data to sort. Please load CSV first.");
        return;
    }

    CsvJsonSort::sortFlights(flights);
    displayData(flights);
    QMessageBox::information(this, "Success", "Data sorted successfully!");
}

// Slot for Write JSON button
void MainWindow::on_writeJSONButton_clicked() {
    if (flights.empty()) {
        QMessageBox::warning(this, "Warning", "No data to write. Please load and sort data first.");
        return;
    }

    QString jsonFileName = QFileDialog::getSaveFileName(this, tr("Save JSON File"), "", tr("JSON Files (*.json)"));
    if (!jsonFileName.isEmpty()) {
        CsvJsonSort::writeJSON(flights, jsonFileName.toStdString());
        QMessageBox::information(this, "Success", "JSON file written successfully!");
    } else {
        QMessageBox::warning(this, "Error", "Failed to save JSON file.");
    }
}

// Slot for Write to Database button
void MainWindow::on_writeDBButton_clicked() {
    if (flights.empty()) {
        QMessageBox::warning(this, "Warning", "No data to write to database. Please load and sort data first.");
        return;
    }

    // Open a file dialog to choose the save location
    QString dbFileName = QFileDialog::getSaveFileName(this, tr("Save Database File"), "", tr("Database Files (*.db)"));
    if (!dbFileName.isEmpty()) {
        // Pass the file path to the DB function
        DB::loadIntoDatabase(flights, dbFileName.toStdString());
        QMessageBox::information(this, "Success", "Data written to database successfully at: " + dbFileName);
    } else {
        QMessageBox::warning(this, "Error", "Failed to save database file.");
    }
}

// Function to display data in QTableView
void MainWindow::displayData(const std::vector<FlightData> &flights) {
    QStandardItemModel *model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"Time", "Latitude", "Longitude", "Course", "KTS", "MPH", "Altitude", "Reporting Facility"});


    for (const auto &flight : flights) {
        QList<QStandardItem*> row;
        row.append(new QStandardItem(QString::fromStdString(flight.time)));
        row.append(new QStandardItem(QString::fromStdString(flight.latitude)));
        row.append(new QStandardItem(QString::fromStdString(flight.longitude)));
        row.append(new QStandardItem(QString::fromStdString(flight.course)));
        row.append(new QStandardItem(QString::fromStdString(flight.kts)));
        row.append(new QStandardItem(QString::fromStdString(flight.mph)));
        row.append(new QStandardItem(QString::fromStdString(flight.altitude_feet)));
        row.append(new QStandardItem(QString::fromStdString(flight.reporting_facility)));

        // Set flags to make items uneditable
        for (QStandardItem* item : row) {
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        }

        model->appendRow(row);
    }

    ui->Display->setModel(model);
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Disable resizing
    this->setFixedSize(this->size());

    connect(ui->LoadCSVButton, &QPushButton::clicked, this, &MainWindow::on_loadButton_clicked);
    connect(ui->SortButton, &QPushButton::clicked, this, &MainWindow::on_sortButton_clicked);
    connect(ui->WriteButton, &QPushButton::clicked, this, &MainWindow::on_writeJSONButton_clicked);
    connect(ui->WriteDBButton, &QPushButton::clicked, this, &MainWindow::on_writeDBButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}
