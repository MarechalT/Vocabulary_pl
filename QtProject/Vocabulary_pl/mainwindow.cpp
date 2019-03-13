#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbmanager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), m_testSession{0,0}
{
    ui->setupUi(this);
    path = "../../database/vocabulary.db";

    db = new DbManager(path);
    if (db->isOpen()){
        QString categories = ("Category");
    }
    else{
    std::string temp = exec("pwd");
    qDebug() << "Couldn't open db, current directory: " << QString::fromStdString(temp) ;
    }
    this->categoryModel = new QSqlQueryModel();
    categoryModel->setQuery("SELECT Category FROM Category;");
   // m_cat = 3;
   // ui->comboBox->setCurrentIndex(m_cat);
    ui->comboBox->setModel(categoryModel);

    ui->tableView->hide();
}


MainWindow::~MainWindow()
{
    db->close();
    delete ui;
}

void MainWindow::on_generateTest_button_clicked()
{
    processRandomField();
}

void MainWindow::on_validate_pushbutton_clicked()
{
    //Compare the typed texted with the database value
    if(compareAnswer(ui->answer_lineEdit->text()))
    {
        qDebug() << "Bravo !";
        m_testSession.validAnswer++;
        scoreUpdate();
        on_generateTest_button_clicked();
    }
    else
    {
        qDebug() << "Wrong answer !, answer is " << ui->answer_lineEdit->text() << "instead of :" << m_translationUnit.englishWord;
    }
}

    void MainWindow::processRandomField()
{
    m_testSession.test++;
    scoreUpdate();
    QString q("SELECT * FROM Vocabulary Where Category = ");
    q.append(QString::number(m_cat));
    q.append(" ORDER BY RANDOM() LIMIT 1;");

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(q);
    m_translationUnit.id = model->record(0).value("Id").toInt();
    m_translationUnit.polishWord = model->record(0).value("Polish").toString();
    m_translationUnit.englishWord = model->record(0).value("English").toString();
    m_translationUnit.category = model->record(0).value("Category").toInt();

    qDebug() << m_translationUnit.id << " " << m_translationUnit.polishWord  << " " << m_translationUnit.englishWord  << " " << m_translationUnit.category  << " end";

    if(m_polishToEnglish)
        ui->test_label->setText(m_translationUnit.polishWord);
    else
        ui->test_label->setText(m_translationUnit.englishWord);
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
            m_cat = index+1;
            QString q("SELECT Polish,English FROM Vocabulary Where Category = ");
            q.append(QString::number(m_cat));
            qDebug() << q;
            this->vocabularyModel = new QSqlQueryModel();
            vocabularyModel->setQuery(q);
            ui->tableView->setModel(vocabularyModel);
            updateMaxCount(vocabularyModel->rowCount());
}

void MainWindow::updateMaxCount(int count){
    maxCount = count;
    if (maxCount == 0){
        ui->validate_pushbutton->setEnabled(false);
        ui->validate_pushbutton->repaint();
    }
    else{
        ui->validate_pushbutton->setEnabled(true);
        ui->validate_pushbutton->repaint();
    }
}

bool MainWindow::compareAnswer(QString suppliedAnswer){
    if (m_polishToEnglish)
        return !m_translationUnit.englishWord.compare(suppliedAnswer, Qt::CaseInsensitive);
    else
        return !m_translationUnit.polishWord.compare(suppliedAnswer, Qt::CaseInsensitive);
}

void MainWindow::on_invertLanguage_clicked()
{
    m_polishToEnglish = !m_polishToEnglish;
    ui->generateTest_button->click();
}

void MainWindow::scoreUpdate(){

    QString score("Score: ");
    score.append(QString::number(m_testSession.validAnswer));
    score.append("/");
    score.append(QString::number(m_testSession.test));
    ui->score_label->setText(score);
}

