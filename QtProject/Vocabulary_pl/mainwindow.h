#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QString>

#include "dbmanager.h"
#include "helper.h"

struct traduction_unit{
    int id;
    QString englishWord;
    QString polishWord;
    int category;
};

struct test_session{
    int test;
    int validAnswer;
};


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_validate_pushbutton_clicked();

    void on_invertLanguage_clicked();

    void on_generateTest_button_clicked();

private:
    Ui::MainWindow *ui;
    QSqlQueryModel *categoryModel;
    QSqlQueryModel *vocabularyModel;

    DbManager *db;
    QString path;
    unsigned int m_cat; //selected category
    unsigned int maxCount;
    void processRandomField();
    void updateMaxCount(int category);
    bool compareAnswer(QString suppliedAnswer);
    void scoreUpdate();

    bool m_polishToEnglish{false};
    traduction_unit m_translationUnit;
    test_session m_testSession;
};

#endif // MAINWINDOW_H
