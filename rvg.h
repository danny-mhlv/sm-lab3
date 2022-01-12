#ifndef RANDOMVALUEGENERATOR_H
#define RANDOMVALUEGENERATOR_H

#include <QObject>

#include <vector>
#include <time.h>
#include <iostream>
#include <limits>

#include "category.h"

class RandomValue : public QObject
{
    Q_OBJECT
public:
    explicit RandomValue(QObject *parent = nullptr);
    void linkWindowSignals(void* sender);
    void reset();

    void restorePSD();
    void restorePSF();
    //void genValues(int num);
    void estMathExp();
    void estDisp();
    void estLambda();

    std::vector<double>* getValuePool();
signals:
    void DrawBars(std::vector<Category>* categories);
    void DrawFunc(std::vector<double>* x, std::vector<double>* psf, std::vector<double>* true_psf);

    void WriteM(QString m);
    void WriteD(QString d);
    void WriteL(QString l, QString dr);
public slots:
    void genValues(int num);
private:
    std::vector<double> pool; // Random values pool
    int poolcount; // Number of RVs (Volume of pool) [n]

    // For PSD
    std::vector<Category> categories;
    int catcount; // Number of categories [m]

    double scope; // Scope (x_max - x_min)
    double mexp; // Math. expectation [m_x]
    double disp; // Dispersion [D_x]

    // For PSF
    std::vector<double> psf;
    std::vector<double> true_psf;
};

#endif // RANDOMVALUEGENERATOR_H
