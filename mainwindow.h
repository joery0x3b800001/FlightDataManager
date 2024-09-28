#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "FlightData.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadButton_clicked();
    void on_sortButton_clicked();
    void on_writeJSONButton_clicked();
    void on_writeDBButton_clicked();

private:
    void displayData(const std::vector<FlightData> &flights);
    std::vector<FlightData> flights;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
