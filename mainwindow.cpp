#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    //clear the screen
    currentFile.clear();
    //create a new text window
    ui->textEdit->setText(QString());
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the File");
    QFile file(fileName);
    currentFile = fileName;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning","Can NOT open File: "+file.errorString());
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    //open window to save file
     QString fileName = QFileDialog::getSaveFileName(this, "Save the File");
     //create object hold file
     QFile file(fileName);
     // open the file notify user if problem
     if(!file.open(QFile::WriteOnly | QFile::Text)){
         QMessageBox::warning(this, "Warning","Can NOT save File: "+file.errorString());
     }
     //store current file
     currentFile = fileName;
     //set window title to name of file
     setWindowTitle(fileName);
    //when writing to out we are actually writing to file on line 60
     QTextStream out(&file);
     //copy text in textEdit widgetconvert to plain text
     QString text = ui->textEdit->toPlainText();
     // write to file and close
     out << text;
     file.close();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionpaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}
