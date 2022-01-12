#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::linkRVGSignals(void *sender)
{
    RandomValue* rvg =  reinterpret_cast<RandomValue*>(sender);
    connect(rvg, SIGNAL(WriteM(QString)), this, SLOT(writeM(QString)));
    connect(rvg, SIGNAL(WriteD(QString)), this, SLOT(writeD(QString)));
    connect(rvg, SIGNAL(WriteL(QString, QString)), this, SLOT(writeL(QString, QString)));
    connect(rvg, SIGNAL(DrawBars(std::vector<Category>*)), this, SLOT(makePlot(std::vector<Category>*)));
    connect(rvg, SIGNAL(DrawFunc(std::vector<double>*, std::vector<double>*, std::vector<double>*)), this,
            SLOT(makeFuncPlot(std::vector<double>*, std::vector<double>*, std::vector<double>*)));
}

void MainWindow::makePlot(std::vector<Category>* categories) {
    ui->customPlot->clearPlottables();

    std::vector<double>* x = Category::makeVMidValue(categories);
    std::vector<double>* p = Category::makeVFreq(categories);

    QCPBars* bars = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    bars->setData(QVector<double>(x->begin(), x->end()), QVector<double>(p->begin(), p->end()));
    bars->setWidthType(QCPBars::wtPlotCoords);
    bars->setWidth(0.01);

    ui->customPlot->rescaleAxes();
    ui->customPlot->replot();
}

void MainWindow::makeFuncPlot(std::vector<double>* x, std::vector<double>* psf, std::vector<double>* true_psf)
{
    ui->customPlot->clearPlottables();

    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->xAxis->setRange(0, 1);
    ui->customPlot->yAxis->setLabel("F*(x)");
    ui->customPlot->yAxis->setRange(0, 1);

    QCPGraph* statF = ui->customPlot->addGraph();
    statF->setLineStyle(QCPGraph::lsStepLeft);
    statF->setData(QVector<double>(x->begin(), x->end()), QVector<double>(psf->begin(), psf->end()));

    QCPGraph* trueF = ui->customPlot->addGraph();
    trueF->setPen(QPen(QColor(Qt::red)));
    trueF->setData(QVector<double>(x->begin(), x->end()), QVector<double>(true_psf->begin(), true_psf->end()));

    ui->customPlot->rescaleAxes();
    ui->customPlot->replot();
}

void MainWindow::on_bNew50_clicked()
{
    emit act_GenValues(50);
}


void MainWindow::on_bNew100_clicked()
{
    emit act_GenValues(100);
}


void MainWindow::on_bNew1000_clicked()
{
    emit act_GenValues(1000);
}


void MainWindow::on_bNew100k_clicked()
{
    emit act_GenValues(100000);
}

void MainWindow::writeM(QString m)
{
    ui->tbpM->setText(m);
}

void MainWindow::writeD(QString d)
{
    ui->tbpD->setText(d);
}

void MainWindow::writeL(QString l, QString dr)
{
    ui->tbpL->setText(l + " | Δ_p: " + dr);
}

