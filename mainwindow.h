#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "matrix.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_createMatrixButton_clicked();
    void on_addButton_clicked();
    void on_multiplyButton_clicked();
    void on_transposeButton_clicked();

private:
    Ui::MainWindow *ui;
    Matrix<double>* matrixA;
    Matrix<double>* matrixB;
    Matrix<double>* resultMatrix;
    void updateMatrixDisplay(const Matrix<double>& matrix, QTableWidget* table);
    void updateMatricesFromTables();
    void clearMatrix(Matrix<double>*& matrix);
};

#endif // MAINWINDOW_H
