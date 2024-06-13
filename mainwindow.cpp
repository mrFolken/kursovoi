#include "mainwindow.h"
#include "ui_mainwindow.h"

list<vector<string>> auth;

//режим доступа
//admin
//worker
//customer
//guest
string rang = "guest";

//режим работы
//workers
//customers
//tools
//orders
string mode = "workers";


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fileCheck();
    guestInterface();

    auth = read_file_auth();
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//очистка буферного списка
void MainWindow::clearAuth()
{
    for(auto line : auth)
        line.clear();
    auth.clear();
}

//проверка наличия файлов и создания их
void MainWindow::fileCheck()
{
    ifstream test ("auth.dst");
    ofstream create;

    if (!test.is_open())
        create.open("auth.dst");
    test.close();
    create.close();

    test.open("orders.dst");
    if (!test.is_open())
        create.open("orders.dst");
    test.close();
    create.close();

    test.open("tools.dst");
    if (!test.is_open())
        create.open("tools.dst");
    test.close();
    create.close();
}

//работа с файлами, выгрузка в список
list<vector<string>> MainWindow::read_file_auth()
{
    ifstream fin ("auth.dst");
    list<vector<string>> list;
    clearAuth();
    //файл открыт
    if (fin.is_open())
    {
        //переменные для внесения
        string female;
        string name;
        string login;
        string password;
        string post;

        while (fin)
        {
            //считывание с файла
            fin >> female >> name >> login >> password >> post;
            if (fin)
                list.push_back(vector<string>({female, name, login, password, post}));
        }
    }
    else
    {
        //ошибка открытия файла
        QMessageBox msgBox;
        msgBox.setText("Error - file with auth cracked!");
        msgBox.exec();
        exit(0);
    }
    fin.close();
    return list;
}

list<vector<string>> MainWindow::read_file_tools()
{
    ifstream fin ("tools.dst");
    list<vector<string>> list;
    clearAuth();
    //файл открыт
    if (fin.is_open())
    {
        //переменные для внесения
        string name;
        string info;
        string price;

        while (fin)
        {
            //считывание с файла
            getline(fin, name);
            getline(fin, info);
            getline(fin, price);
            if (fin)
                list.push_back(vector<string>({name, info, price}));
        }
    }
    else
    {
        //ошибка открытия файла
        QMessageBox msgBox;
        msgBox.setText("Error - file with tools cracked!");
        msgBox.exec();
        exit(0);
    }
    fin.close();
    return list;
}

list<vector<string>> MainWindow::read_file_orders()
{
    ifstream fin ("orders.dst");
    list<vector<string>> list;
    clearAuth();
    //файл открыт
    if (fin.is_open())
    {
        //переменные для внесения
        string female;
        string tool;
        string price;

        while (fin)
        {
            //считывание с файла
            getline(fin, female);
            getline(fin, tool);
            getline(fin, price);
            if (fin)
                list.push_back(vector<string>({female, tool, price}));
        }
    }
    else
    {
        //ошибка открытия файла
        QMessageBox msgBox;
        msgBox.setText("Error - file with order cracked!");
        msgBox.exec();
        exit(0);
    }
    fin.close();
    return list;
}

//очистка полей
void MainWindow::cleanField()
{
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
}

//очистка таблицы
void MainWindow::cleanTable()
{
    for(int i = ui->tableWidget->rowCount(); i >= 0; i--)
        ui->tableWidget->removeRow(i);
}

//обновление разделов и таблиц
void MainWindow::updateWorkers()
{
    cleanField();
    cleanTable();

    auth = read_file_auth();

    unsigned int count = 0;
    for (auto line : auth)
    {
        count++;
        if (line[4] == "worker")
        {
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0,
                                     new QTableWidgetItem(QString::fromStdString(line[0])));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1,
                                     new QTableWidgetItem(QString::fromStdString(line[1])));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2,
                                     new QTableWidgetItem(QString::fromStdString(line[2])));
        }
    }
}

void MainWindow::updateCustomers()
{
    cleanField();
    cleanTable();

    auth = read_file_auth();

    unsigned int count = 0;
    for (auto line : auth)
    {
        count++;
        if (line[4] == "customer")
        {
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0,
                                     new QTableWidgetItem(QString::fromStdString(line[0])));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1,
                                     new QTableWidgetItem(QString::fromStdString(line[1])));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2,
                                     new QTableWidgetItem(QString::fromStdString(line[2])));
        }
    }
}

void MainWindow::updateTools()
{
    cleanField();
    cleanTable();

    auth = read_file_tools();

    unsigned int count = 0;
    for (auto line : auth)
    {
        count++;
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0,
                                 new QTableWidgetItem(QString::fromStdString(line[0])));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1,
                                 new QTableWidgetItem(QString::fromStdString(line[1])));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2,
                                 new QTableWidgetItem(QString::fromStdString(line[2])));
    }
}

void MainWindow::updateOrders()
{
    cleanField();
    cleanTable();

    auth = read_file_orders();

    unsigned int count = 0;
    for (auto line : auth)
    {
        count++;
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0,
                                 new QTableWidgetItem(QString::fromStdString(line[0])));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1,
                                 new QTableWidgetItem(QString::fromStdString(line[1])));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2,
                                 new QTableWidgetItem(QString::fromStdString(line[2])));
    }
}

//переключатели интерфейса по уровню доступа
void MainWindow::adminInterface()
{
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->lineEdit->setVisible(false);
    ui->lineEdit_2->setVisible(false);
    ui->pushButton->setVisible(false);

    ui->label_3->setVisible(true);
    ui->label_4->setVisible(true);
    ui->label_5->setVisible(true);
    ui->label_6->setVisible(true);
    ui->label_7->setVisible(true);
    ui->lineEdit_3->setVisible(true);
    ui->lineEdit_4->setVisible(true);
    ui->lineEdit_5->setVisible(true);
    ui->lineEdit_6->setVisible(true);
    ui->pushButton_2->setVisible(true);
    ui->pushButton_3->setVisible(true);
    ui->pushButton_4->setVisible(true);
    ui->pushButton_5->setVisible(true);
    ui->pushButton_6->setVisible(true);
    ui->pushButton_7->setVisible(true);
    ui->pushButton_8->setVisible(true);
    ui->tableWidget->setVisible(true);
}

void MainWindow::workerInterface()
{
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->lineEdit->setVisible(false);
    ui->lineEdit_2->setVisible(false);
    ui->pushButton->setVisible(false);

    ui->label_3->setVisible(true);
    ui->label_4->setVisible(true);
    ui->label_5->setVisible(true);
    ui->label_6->setVisible(true);
    ui->label_7->setVisible(true);
    ui->lineEdit_3->setVisible(true);
    ui->lineEdit_4->setVisible(true);
    ui->lineEdit_5->setVisible(true);
    ui->lineEdit_6->setVisible(true);
    ui->pushButton_2->setVisible(true);
    ui->pushButton_3->setVisible(true);
    ui->pushButton_4->setVisible(true);
    ui->pushButton_5->setVisible(true);
    ui->pushButton_6->setVisible(true);
    ui->pushButton_7->setVisible(true);
    ui->pushButton_8->setVisible(true);
    ui->tableWidget->setVisible(true);
}

void MainWindow::customerInterface()
{
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->lineEdit->setVisible(false);
    ui->lineEdit_2->setVisible(false);
    ui->pushButton->setVisible(false);

    ui->label_3->setVisible(true);
    ui->label_4->setVisible(true);
    ui->label_5->setVisible(true);
    ui->label_6->setVisible(true);
    ui->label_7->setVisible(true);
    ui->lineEdit_3->setVisible(true);
    ui->lineEdit_4->setVisible(true);
    ui->lineEdit_5->setVisible(true);
    ui->lineEdit_6->setVisible(true);
    ui->pushButton_2->setVisible(false);
    ui->pushButton_3->setVisible(true);
    ui->pushButton_4->setVisible(true);
    ui->pushButton_5->setVisible(true);
    ui->pushButton_6->setVisible(true);
    ui->pushButton_7->setVisible(true);
    ui->pushButton_8->setVisible(true);
    ui->tableWidget->setVisible(true);
}

void MainWindow::guestInterface()
{
    ui->label->setVisible(true);
    ui->label_2->setVisible(true);
    ui->lineEdit->setVisible(true);
    ui->lineEdit_2->setVisible(true);
    ui->pushButton->setVisible(true);

    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
    ui->lineEdit_3->setVisible(false);
    ui->lineEdit_4->setVisible(false);
    ui->lineEdit_5->setVisible(false);
    ui->lineEdit_6->setVisible(false);
    ui->pushButton_2->setVisible(false);
    ui->pushButton_3->setVisible(false);
    ui->pushButton_4->setVisible(false);
    ui->pushButton_5->setVisible(false);
    ui->pushButton_6->setVisible(false);
    ui->pushButton_7->setVisible(false);
    ui->pushButton_8->setVisible(false);
    ui->tableWidget->setVisible(false);
}

//переключатели режима работы(вкладки)
void MainWindow::switchToWorkers()
{
    mode = "workers";
    ui->label_3->setText("Список работников");
    ui->tableWidget->horizontalHeaderItem(0)->setText("Фамилия");
    ui->tableWidget->horizontalHeaderItem(1)->setText("Имя");
    ui->tableWidget->horizontalHeaderItem(2)->setText("Логин");

    ui->label_4->setText("Фамилия");
    ui->label_5->setText("Имя");
    ui->label_6->setText("Логин");

    //включение отключение кнопок и полей редактирования
    if (rang == "admin")
    {
        ui->pushButton_6->setVisible(true);
        ui->pushButton_7->setVisible(true);
        ui->pushButton_8->setVisible(true);
        ui->label_7->setVisible(true);
        ui->lineEdit_6->setVisible(true);
    }
    if (rang == "worker")
    {
        ui->pushButton_6->setVisible(false);
        ui->pushButton_7->setVisible(false);
        ui->pushButton_8->setVisible(false);
        ui->label_7->setVisible(false);
        ui->lineEdit_6->setVisible(false);
    }
    if (rang == "customer")
    {
        //такой ситуации не существует, меню недоступно для данного ранга
    }

    updateWorkers();
}

void MainWindow::switchToCustomers()
{
    mode = "customers";
    ui->label_3->setText("Список заказчиков");
    ui->tableWidget->horizontalHeaderItem(0)->setText("Фамилия");
    ui->tableWidget->horizontalHeaderItem(1)->setText("Имя");
    ui->tableWidget->horizontalHeaderItem(2)->setText("Логин");
    ui->label_4->setText("Фамилия");
    ui->label_5->setText("Имя");
    ui->label_6->setText("Логин");

    if (rang == "admin")
    {
        ui->pushButton_6->setVisible(true);
        ui->pushButton_7->setVisible(true);
        ui->pushButton_8->setVisible(true);
        ui->label_7->setVisible(true);
        ui->lineEdit_6->setVisible(true);
    }
    if (rang == "worker")
    {
        ui->pushButton_6->setVisible(true);
        ui->pushButton_7->setVisible(true);
        ui->pushButton_8->setVisible(true);
        ui->label_7->setVisible(true);
        ui->lineEdit_6->setVisible(true);
    }
    if (rang == "customer")
    {
        ui->pushButton_6->setVisible(false);
        ui->pushButton_7->setVisible(false);
        ui->pushButton_8->setVisible(false);
        ui->label_7->setVisible(false);
        ui->lineEdit_6->setVisible(false);
    }
    updateCustomers();
}

void MainWindow::switchToTools()
{
    mode = "tools";
    ui->label_3->setText("Список станков");
    ui->tableWidget->horizontalHeaderItem(0)->setText("Название");
    ui->tableWidget->horizontalHeaderItem(1)->setText("Описание");
    ui->tableWidget->horizontalHeaderItem(2)->setText("Цена");
    ui->label_4->setText("Название");
    ui->label_5->setText("Описание");
    ui->label_6->setText("Цена");
    ui->label_7->setVisible(false);
    ui->lineEdit_6->setVisible(false);

    if (rang == "admin")
    {
        ui->pushButton_6->setVisible(true);
        ui->pushButton_7->setVisible(true);
        ui->pushButton_8->setVisible(true);
    }
    if (rang == "worker")
    {
        ui->pushButton_6->setVisible(true);
        ui->pushButton_7->setVisible(true);
        ui->pushButton_8->setVisible(true);
    }
    if (rang == "customer")
    {
        ui->pushButton_6->setVisible(false);
        ui->pushButton_7->setVisible(false);
        ui->pushButton_8->setVisible(false);
    }

    updateTools();
}

void MainWindow::switchToOrders()
{
    mode = "orders";
    ui->label_3->setText("Список заказов");
    ui->tableWidget->horizontalHeaderItem(0)->setText("Заказчик");
    ui->tableWidget->horizontalHeaderItem(1)->setText("Станок");
    ui->tableWidget->horizontalHeaderItem(2)->setText("Цена");
    ui->label_4->setText("Фамилия заказчика");
    ui->label_5->setText("Станок");
    ui->label_6->setText("Цена");
    ui->label_7->setVisible(false);
    ui->lineEdit_6->setVisible(false);

    if (rang == "admin")
    {
        ui->pushButton_6->setVisible(true);
        ui->pushButton_7->setVisible(true);
        ui->pushButton_8->setVisible(true);
    }
    if (rang == "worker")
    {
        ui->pushButton_6->setVisible(true);
        ui->pushButton_7->setVisible(true);
        ui->pushButton_8->setVisible(true);
    }
    if (rang == "customer")
    {
        ui->pushButton_6->setVisible(false);
        ui->pushButton_7->setVisible(false);
        ui->pushButton_8->setVisible(false);
    }

    updateOrders();
}

//кновка авторизации
void MainWindow::on_pushButton_clicked()
{
    QString login = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    QMessageBox msgBox;

    for(auto line : auth)
    {
        //проверка логина/пароля
        if(QString::fromStdString(line[2]) == login &&
                QString::fromStdString(line[3]) == password)
        {
            //переключение режима взависимости от статуса
            if (QString::fromStdString(line[4]) == "admin")
                rang = "admin";
            else if (QString::fromStdString(line[4]) == "worker")
                rang = "worker";
            else if (QString::fromStdString(line[4]) == "customer")
                rang = "customer";
            else
                rang = "guest";

            //изменение визуала
            if(rang == "guest")
                //интерфейс авторизации
                guestInterface();
            else
            {
                msgBox.setText("Auth complete!");
                msgBox.exec();

                //начальная настройка в зависимости от ранга
                if(rang == "admin")
                {
                    adminInterface();
                    switchToWorkers();
                    updateWorkers();
                }
                if(rang == "worker")
                {
                    workerInterface();
                    switchToWorkers();
                    updateWorkers();
                }
                if(rang == "customer")
                {
                    customerInterface();
                    switchToCustomers();
                    updateCustomers();
                }
            }
            return;
        }
    }

    msgBox.setText("Auth failed!");
    msgBox.exec();

}

//кнопка редактирования
void MainWindow::on_pushButton_7_clicked()
{
    if (mode == "workers")
    {
        if (ui->tableWidget->selectedItems().isEmpty())
        {
            QMessageBox msgBox;
            msgBox.setText("Выделите рабочего!");
            msgBox.exec();
        }
        else
        {
            if(!fieldsIsEmpty())
            {
                editWorkers();
                updateWorkers();
            }
        }
    }
    else if (mode == "customers")
    {
        if (ui->tableWidget->selectedItems().isEmpty())
        {
            QMessageBox msgBox;
            msgBox.setText("Выделите заказчика!");
            msgBox.exec();
        }
        else
        {
            if(!fieldsIsEmpty())
            {
                editCustomers();
                updateCustomers();
            }
        }
    }
    else if (mode == "tools")
    {
        if (ui->tableWidget->selectedItems().isEmpty())
        {
            QMessageBox msgBox;
            msgBox.setText("Выделите станок!");
            msgBox.exec();
        }
        else
        {
            if(!fieldsIsEmpty())
            {
                editTools();
                updateTools();
            }
        }
    }
    else if (mode == "orders")
    {
        if (ui->tableWidget->selectedItems().isEmpty())
        {
            QMessageBox msgBox;
            msgBox.setText("Выделите заказ!");
            msgBox.exec();
        }
        else
        {
            if(!fieldsIsEmpty())
            {
                editOrders();
                updateOrders();
            }
        }
    }
}

//редактирование рабочих
void MainWindow::editWorkers()
{
    QMessageBox msgBox;

    ofstream fout ("auth.dst");
    //файл открыт
    if (fout.is_open())
        for(auto line : auth)
        {
            //запись в файл
            if (ui->tableWidget->selectedItems()[0]->text().toStdString() == line[0] &&
                    ui->tableWidget->selectedItems()[1]->text().toStdString() == line[1])
            {
                line[0] = ui->lineEdit_3->text().toStdString();
                line[1] = ui->lineEdit_4->text().toStdString();
                line[2] = ui->lineEdit_5->text().toStdString();
                line[3] = ui->lineEdit_6->text().toStdString();

                msgBox.setText("Изменения внесены!");
                msgBox.exec();
            }

            fout << line[0] << " " << line[1] << " " << line[2] << " " << line[3] << " " << line[4] << '\n';
        }
    else
    {
        //ошибка открытия файла
        msgBox.setText("Error - file with auth cracked!");
        msgBox.exec();
        exit(0);
    }
}

//редактирование заказчиков
void MainWindow::editCustomers()
{
    QMessageBox msgBox;

    ofstream fout ("auth.dst");
    //файл открыт
    if (fout.is_open())
        for(auto line : auth)
        {
            if (ui->tableWidget->selectedItems()[0]->text().toStdString() == line[0] &&
                    ui->tableWidget->selectedItems()[1]->text().toStdString() == line[1])
            {
                line[0] = ui->lineEdit_3->text().toStdString();
                line[1] = ui->lineEdit_4->text().toStdString();
                line[2] = ui->lineEdit_5->text().toStdString();
                line[3] = ui->lineEdit_6->text().toStdString();

                msgBox.setText("Изменения внесены!");
                msgBox.exec();
            }

            //запись в файл
            fout << line[0] << " " << line[1] << " " << line[2] << " " << line[3] << " " << line[4] << '\n';
        }
    else
    {
        //ошибка открытия файла
        msgBox.setText("Error - file with auth cracked!");
        msgBox.exec();
        exit(0);
    }

}

//редактирование станков
void MainWindow::editTools()
{
    QMessageBox msgBox;

    ofstream fout ("tools.dst");
    //файл открыт
    if (fout.is_open())
        for(auto line : auth)
        {
            if (ui->tableWidget->selectedItems()[0]->text().toStdString() == line[0] &&
                    ui->tableWidget->selectedItems()[1]->text().toStdString() == line[1])
            {
                line[0] = ui->lineEdit_3->text().toStdString();
                line[1] = ui->lineEdit_4->text().toStdString();
                line[2] = ui->lineEdit_5->text().toStdString();

                msgBox.setText("Изменения внесены!");
                msgBox.exec();
            }

            //запись в файл
            fout << line[0] << '\n' << line[1] << '\n' << line[2] << '\n';
        }
    else
    {
        //ошибка открытия файла
        msgBox.setText("Error - file with tools cracked!");
        msgBox.exec();
        exit(0);
    }

}

//редактирование заказов
void MainWindow::editOrders()
{
    QMessageBox msgBox;

    ofstream fout ("orders.dst");
    //файл открыт
    if (fout.is_open())
        for(auto line : auth)
        {
            if (ui->tableWidget->selectedItems()[0]->text().toStdString() == line[0] &&
                    ui->tableWidget->selectedItems()[1]->text().toStdString() == line[1])
            {
                line[0] = ui->lineEdit_3->text().toStdString();
                line[1] = ui->lineEdit_4->text().toStdString();
                line[2] = ui->lineEdit_5->text().toStdString();

                msgBox.setText("Изменения внесены!");
                msgBox.exec();
            }

            //запись в файл
            fout << line[0] << '\n' << line[1] << '\n' << line[2] << '\n';
        }
    else
    {
        //ошибка открытия файла
        msgBox.setText("Error - file with auth cracked!");
        msgBox.exec();
        exit(0);
    }
}

//кнопка удаления
void MainWindow::on_pushButton_8_clicked()
{
    if (mode == "workers")
    {
        if (ui->tableWidget->selectedItems().isEmpty())
        {
            QMessageBox msgBox;
            msgBox.setText("Выделите рабочего!");
            msgBox.exec();
        }
        else
        {
            delWorkers();
            cleanField();
            updateWorkers();
        }
    }
    else if (mode == "customers")
    {
        if (ui->tableWidget->selectedItems().isEmpty())
        {
            QMessageBox msgBox;
            msgBox.setText("Выделите заказчика!");
            msgBox.exec();
        }
        else
        {
            delCustomers();
            cleanField();
            updateCustomers();
        }
    }
    else if (mode == "tools")
    {
        if (ui->tableWidget->selectedItems().isEmpty())
        {
            QMessageBox msgBox;
            msgBox.setText("Выделите станок!");
            msgBox.exec();
        }
        else
        {
            delTools();
            cleanField();
            updateTools();
        }
    }
    else if (mode == "orders")
    {
        if (ui->tableWidget->selectedItems().isEmpty())
        {
            QMessageBox msgBox;
            msgBox.setText("Выделите заказ!");
            msgBox.exec();
        }
        else
        {
            delOrders();
            cleanField();
            updateOrders();
        }
    }
}

//удаление рабочего
void MainWindow::delWorkers()
{
    list<vector<string>>::iterator it = auth.begin();
    for (auto line : auth)
    {
        if (ui->tableWidget->selectedItems()[0]->text().toStdString() == line[0] &&
                ui->tableWidget->selectedItems()[1]->text().toStdString() == line[1])
        {
            line.clear();
            auth.erase(it);
            break;
        }
        it++;
    }

    ofstream fout ("auth.dst");
    //файл открыт
    if (fout.is_open())
        for(auto line : auth)
            //запись в файл
            fout << line[0] << " " << line[1] << " " << line[2] << " " << line[3] << " " << line[4] << '\n';
    else
    {
        //ошибка открытия файла
        QMessageBox msgBox;
        msgBox.setText("Error - file with auth cracked!");
        msgBox.exec();
        exit(0);
    }
}

//удаление заказчика
void MainWindow::delCustomers()
{
    list<vector<string>>::iterator it = auth.begin();
    for (auto line : auth)
    {
        if (ui->tableWidget->selectedItems()[0]->text().toStdString() == line[0] &&
                ui->tableWidget->selectedItems()[1]->text().toStdString() == line[1])
        {
            line.clear();
            auth.erase(it);
            break;
        }
        it++;
    }

    ofstream fout ("auth.dst");
    //файл открыт
    if (fout.is_open())
        for(auto line : auth)
            //запись в файл
            fout << line[0] << " " << line[1] << " " << line[2] << " " << line[3] << " " << line[4] << '\n';
    else
    {
        //ошибка открытия файла
        QMessageBox msgBox;
        msgBox.setText("Error - file with auth cracked!");
        msgBox.exec();
        exit(0);
    }
}

//удаление станка
void MainWindow::delTools()
{
    list<vector<string>>::iterator it = auth.begin();
    for (auto line : auth)
    {
        if (ui->tableWidget->selectedItems()[0]->text().toStdString() == line[0] &&
                ui->tableWidget->selectedItems()[1]->text().toStdString() == line[1])
        {
            line.clear();
            auth.erase(it);
            break;
        }
        it++;
    }

    ofstream fout ("tools.dst");
    //файл открыт
    if (fout.is_open())
        for(auto line : auth)
            //запись в файл
            fout << line[0] << '\n' << line[1] << '\n' << line[2] << '\n';
    else
    {
        //ошибка открытия файла
        QMessageBox msgBox;
        msgBox.setText("Error - file with tools cracked!");
        msgBox.exec();
        exit(0);
    }
}

//удаление заказа
void MainWindow::delOrders()
{
    list<vector<string>>::iterator it = auth.begin();
    for (auto line : auth)
    {
        if (ui->tableWidget->selectedItems()[0]->text().toStdString() == line[0] &&
                ui->tableWidget->selectedItems()[1]->text().toStdString() == line[1])
        {
            line.clear();
            auth.erase(it);
            break;
        }
        it++;
    }

    ofstream fout ("orders.dst");
    //файл открыт
    if (fout.is_open())
        for(auto line : auth)
            //запись в файл
            fout << line[0] << '\n' << line[1] << '\n' << line[2] << '\n';
    else
    {
        //ошибка открытия файла
        QMessageBox msgBox;
        msgBox.setText("Error - file with orders cracked!");
        msgBox.exec();
        exit(0);
    }
}

//проверка на пустоту полей
bool MainWindow::fieldsIsEmpty()
{
    if (mode == "workers" || mode == "customers")
    {
        if (ui->lineEdit_3->displayText().isEmpty() ||
            ui->lineEdit_4->displayText().isEmpty() ||
            ui->lineEdit_5->displayText().isEmpty() ||
            ui->lineEdit_6->displayText().isEmpty())
        {
            QMessageBox msgBox;
            msgBox.setText("Заполните все поля!");
            msgBox.exec();
            return true;
        }
        return false;
    }
    else
    {
        if (ui->lineEdit_3->displayText().isEmpty() ||
            ui->lineEdit_4->displayText().isEmpty() ||
            ui->lineEdit_5->displayText().isEmpty())
        {
            QMessageBox msgBox;
            msgBox.setText("Заполните все поля!");
            msgBox.exec();
            return true;
        }
        return false;
    }
}

//кнопка добавления
void MainWindow::on_pushButton_6_clicked()
{
    if (mode == "workers")
    {
        if (!fieldsIsEmpty())
        {
            addWorkers();
            cleanField();
            updateWorkers();
        }
    }
    else if (mode == "customers")
    {
        if (!fieldsIsEmpty())
        {
            addCustomers();
            cleanField();
            updateCustomers();
        }
    }
    else if (mode == "tools")
    {
        if (!fieldsIsEmpty())
        {
            addTools();
            cleanField();
            updateTools();
        }
    }
    else if (mode == "orders")
    {
        if (!fieldsIsEmpty())
        {
            addOrders();
            cleanField();
            updateOrders();
        }
    }
}

//реализация добавления работников
void MainWindow::addWorkers()
{
    auth.push_back(vector<string>({ui->lineEdit_3->text().toStdString(),
                                   ui->lineEdit_4->text().toStdString(),
                                   ui->lineEdit_5->text().toStdString(),
                                   ui->lineEdit_6->text().toStdString(),
                                   "worker"}));

    ofstream fout ("auth.dst");
    //файл открыт
    if (fout.is_open())
        for(auto line : auth)
            //запись в файл
            fout << line[0] << " " << line[1] << " " << line[2] << " " << line[3] << " " << line[4] << '\n';
    else
    {
        //ошибка открытия файла
        QMessageBox msgBox;
        msgBox.setText("Error - file with auth cracked!");
        msgBox.exec();
        exit(0);
    }
}

//реализация добавления заказчиков
void MainWindow::addCustomers()
{
    auth.push_back(vector<string>({ui->lineEdit_3->text().toStdString(),
                                ui->lineEdit_4->text().toStdString(),
                                ui->lineEdit_5->text().toStdString(),
                                ui->lineEdit_6->text().toStdString(),
                                "customer"}));

     ofstream fout ("auth.dst");
     //файл открыт
     if (fout.is_open())
         for(auto line : auth)
             //запись в файл
             fout << line[0] << " " << line[1] << " " << line[2] << " " << line[3] << " " << line[4] << '\n';
     else
     {
         //ошибка открытия файла
         QMessageBox msgBox;
         msgBox.setText("Error - file with auth cracked!");
         msgBox.exec();
         exit(0);
     }
}

//реализация добавления станков
void MainWindow::addTools()
{
    auth.push_back(vector<string>({ui->lineEdit_3->text().toStdString(),
                                ui->lineEdit_4->text().toStdString(),
                                ui->lineEdit_5->text().toStdString()}));

     ofstream fout ("tools.dst");
     //файл открыт
     if (fout.is_open())
         for(auto line : auth)
             //запись в файл
             fout << line[0] << '\n' << line[1] << '\n' << line[2] << '\n';
     else
     {
         //ошибка открытия файла
         QMessageBox msgBox;
         msgBox.setText("Error - file with tools cracked!");
         msgBox.exec();
         exit(0);
     }
}

//реализация добавления заказов
void MainWindow::addOrders()
{
    auth.push_back(vector<string>({ui->lineEdit_3->text().toStdString(),
                                ui->lineEdit_4->text().toStdString(),
                                ui->lineEdit_5->text().toStdString()}));

     ofstream fout ("orders.dst");
     //файл открыт
     if (fout.is_open())
         for(auto line : auth)
             //запись в файл
             fout << line[0] << '\n' << line[1] << '\n' << line[2] << '\n';
     else
     {
         //ошибка открытия файла
         QMessageBox msgBox;
         msgBox.setText("Error - file with orders cracked!");
         msgBox.exec();
         exit(0);
     }
}

//переключатели режимов
//кнопка работники
void MainWindow::on_pushButton_2_clicked()
{
    switchToWorkers();
}

//кнопка заказчики
void MainWindow::on_pushButton_3_clicked()
{
    switchToCustomers();
}

//кнопка станки
void MainWindow::on_pushButton_4_clicked()
{
    switchToTools();
}

//кнопка заказы
void MainWindow::on_pushButton_5_clicked()
{
    switchToOrders();
}

//заполнение полей по клику на строку таблицы
void MainWindow::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    ui->lineEdit_3->setText(ui->tableWidget->selectedItems()[0]->text());
    ui->lineEdit_4->setText(ui->tableWidget->selectedItems()[1]->text());
    ui->lineEdit_5->setText(ui->tableWidget->selectedItems()[2]->text());
}
