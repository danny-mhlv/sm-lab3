#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "rvg.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void linkRVGSignals(void* sender);
signals:
    void act_GenValues(int num);

private slots:
    void makePlot(std::vector<Category>* categories);
    void makeFuncPlot(std::vector<double>* x, std::vector<double>* psf, std::vector<double>* true_psf);

    // Button presses
    void on_bNew50_clicked();
    void on_bNew100_clicked();
    void on_bNew1000_clicked();
    void on_bNew100k_clicked();

    // Write to labels
    void writeM(QString m);
    void writeD(QString d);
    void writeL(QString l, QString dr);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
