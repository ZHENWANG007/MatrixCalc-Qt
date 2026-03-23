#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidgetItem>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , matrixA(nullptr)
    , matrixB(nullptr)
    , resultMatrix(nullptr)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    clearMatrix(matrixA);
    clearMatrix(matrixB);
    clearMatrix(resultMatrix);
    delete ui;
}

void MainWindow::on_createMatrixButton_clicked() {
    try {
        int rows = ui->rowsSpinBox->value();
        int cols = ui->colsSpinBox->value();

        clearMatrix(matrixA);
        clearMatrix(matrixB);
        clearMatrix(resultMatrix);

        matrixA = new Matrix<double>(rows, cols);
        matrixB = new Matrix<double>(rows, cols);

        ui->matrixATable->setRowCount(rows);
        ui->matrixATable->setColumnCount(cols);
        ui->matrixBTable->setRowCount(rows);
        ui->matrixBTable->setColumnCount(cols);

        ui->resultTable->clear();
        ui->resultTable->setRowCount(0);
        ui->resultTable->setColumnCount(0);

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void MainWindow::on_addButton_clicked() {
    if (!matrixA || !matrixB) {
        QMessageBox::warning(this, "Warning", "Please create matrices first");
        return;
    }

    try {
        updateMatricesFromTables();
        clearMatrix(resultMatrix);
        resultMatrix = new Matrix<double>(matrixA->add(*matrixB));
        updateMatrixDisplay(*resultMatrix, ui->resultTable);
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void MainWindow::on_multiplyButton_clicked() {
    if (!matrixA || !matrixB) {
        QMessageBox::warning(this, "Warning", "Please create matrices first");
        return;
    }

    try {
        updateMatricesFromTables();
        clearMatrix(resultMatrix);
        resultMatrix = new Matrix<double>(matrixA->multiply(*matrixB));
        updateMatrixDisplay(*resultMatrix, ui->resultTable);
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void MainWindow::on_transposeButton_clicked() {
    if (!matrixA) {
        QMessageBox::warning(this, "Warning", "Please create matrix A first");
        return;
    }

    try {
        updateMatricesFromTables();
        clearMatrix(resultMatrix);
        resultMatrix = new Matrix<double>(matrixA->transpose());
        updateMatrixDisplay(*resultMatrix, ui->resultTable);
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void MainWindow::updateMatricesFromTables() {
    for(int i=0; i<ui->matrixATable->rowCount(); ++i) {
        for(int j=0; j<ui->matrixATable->columnCount(); ++j) {
            QTableWidgetItem* itemA = ui->matrixATable->item(i,j);
            QTableWidgetItem* itemB = ui->matrixBTable->item(i,j);
            if(itemA && itemB) {
                matrixA->setValue(i,j, itemA->text().toDouble());
                matrixB->setValue(i,j, itemB->text().toDouble());
            }
        }
    }
}

void MainWindow::updateMatrixDisplay(const Matrix<double>& matrix, QTableWidget* table) {
    table->setRowCount(matrix.getRows());
    table->setColumnCount(matrix.getCols());

    for (size_t i = 0; i < matrix.getRows(); ++i) {
        for (size_t j = 0; j < matrix.getCols(); ++j) {
            QTableWidgetItem* item = new QTableWidgetItem(QString::number(matrix.getValue(i, j)));
            table->setItem(i, j, item);
        }
    }
}

void MainWindow::clearMatrix(Matrix<double>*& matrix) {
    if (matrix) {
        delete matrix;
        matrix = nullptr;
    }
}
