#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <fstream>
#include <vector>
#include <QMessageBox>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    list<vector<string>> read_file_auth();
    list<vector<string>> read_file_tools();
    list<vector<string>> read_file_orders();

private slots:
    void fileCheck();
    void clearAuth();
    void cleanTable();
    void updateWorkers();
    void switchToWorkers();

    void updateCustomers();
    void switchToCustomers();

    void updateTools();
    void switchToTools();

    void updateOrders();
    void switchToOrders();

    void adminInterface();
    void workerInterface();
    void customerInterface();
    void guestInterface();

    void on_pushButton_clicked();

    void on_pushButton_6_clicked();
    void cleanField();
    void addWorkers();
    void addCustomers();
    void addTools();
    void addOrders();

    void editWorkers();
    void editCustomers();
    void editTools();
    void editOrders();

    void delWorkers();
    void delCustomers();
    void delTools();
    void delOrders();

    bool fieldsIsEmpty();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_tableWidget_itemClicked(QTableWidgetItem *item);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
