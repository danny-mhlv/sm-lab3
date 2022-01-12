#include "mainwindow.h"

#include "rvg.h"

RandomValue::RandomValue(QObject *parent) : QObject(parent)
{
    srand(time(NULL));

    mexp = 0;
    disp = 0;

    scope = 0;
    poolcount = 0;
    catcount = 0;
}

void RandomValue::linkWindowSignals(void *sender)
{
    MainWindow* window =  reinterpret_cast<MainWindow*>(sender);
    connect(window, SIGNAL(act_GenValues(int)), this, SLOT(genValues(int)));
}

void RandomValue::reset()
{
    pool.clear();
    categories.clear();
    psf.clear();
    true_psf.clear();

    mexp = 0;
    disp = 0;

    scope = 0;
    poolcount = 0;
    catcount = 0;
}

void RandomValue::restorePSD()
{
    // Determine the number of categories
    if (poolcount <= 500) {
        catcount = poolcount / 15;
    } else if (poolcount > 500) {
        catcount = 25;
    }

    double max = *max_element(std::begin(pool), std::end(pool));
    double min = *min_element(std::begin(pool), std::end(pool));

    scope = max - min;
    double deltax = scope / catcount;
    // Setting categories
    double left = min;
    for(int i = 0; i < catcount; i++) {
        if(i + 1 >= catcount) {
            categories.push_back(Category(left, max));
            break;
        }

        categories.push_back(Category(left, left + deltax));
        left = left + deltax;
    }

    // n_j
    for(double rv : pool) {
        for(std::vector<Category>::iterator iter = categories.begin(); iter != categories.end(); iter++) {
            if(rv >= (*iter).getLB() && rv <= (*iter).getRB()) {
                (*iter).incElemCount();
            }
        }
    }

    // Calculate frequency of each category
    for(std::vector<Category>::iterator iter = categories.begin(); iter != categories.end(); iter++) {
        (*iter).calculateFreq(poolcount);
    }

    // Draw histogram
    //emit DrawBars(&categories);
}

void RandomValue::restorePSF()
{
    double sum = 0;

    // Stat. PSF
    for(double rv : pool) {
        for(double xi : pool) {
            if(rv - xi >= 0) {
                sum++;
            }
        }

        psf.push_back(sum / poolcount);
        sum = 0;
    }

    // Theoretical PSF
    for(double rv : pool) {
        if(rv >= -0.5 && rv <= 0) { // [-0.5 ; 0]
            true_psf.push_back(rv + 0.5);
        }
        else if (rv >= 0 && rv <= 1) { // [0 ; 1]
            true_psf.push_back(-((rv-1)*(rv-1))/2 + 1);
        }
    }

    emit DrawFunc(&pool, &psf, &true_psf);
}

void RandomValue::estMathExp()
{
    // Math. expectation
    for(std::vector<Category>::iterator iter = categories.begin(); iter != categories.end(); iter++) {
        mexp += ((*iter).getFreq() * (*iter).getMidValue());
    }
    emit WriteM(QString::number(mexp));
}

void RandomValue::estDisp()
{
    // Dispersion
    for(std::vector<Category>::iterator iter = categories.begin(); iter != categories.end(); iter++) {
        disp += (*iter).getFreq() * ( ((*iter).getMidValue() - mexp) *  ((*iter).getMidValue() - mexp) );
    }
    emit WriteD(QString::number(disp));
}

void RandomValue::estLambda()
{
    double dr = (double)INT_MIN;

    for (size_t i = 0; i < poolcount; i++) {
        if (abs(true_psf.at(i) - psf.at(i)) > dr) {
            dr = abs(true_psf.at(i) - psf.at(i));
        }
    }

    double lambda = dr * sqrt(poolcount);

    emit WriteL(QString::number(lambda), QString::number(dr));
}

void RandomValue::genValues(int num)
{
    // If was previously initialized
    this->reset();

    // Generate new RVs
    double rand_num = 0;
    for (size_t i = 0; i < num; i++) {
        rand_num = (double)rand() / (double)RAND_MAX;

        std::cout << "rv: " << rand_num << std::endl;

        if (rand_num >= 0 && rand_num <= 0.5) {
            pool.push_back(rand_num - 0.5);
            std::cout << "x = rv - 0.5: " << pool.back() << std::endl;
        }
        else if (rand_num > 0.5 && rand_num <= 1) {
            pool.push_back(1 - sqrt(2-2*rand_num));
            std::cout << "x = Vrv*2 - 1: " << pool.back() << std::endl;
        }

        //std::cout << "x: " << pool.back() << std::endl;
    }

    poolcount = num; // Set volume

    restorePSD();
    restorePSF();

    estMathExp();
    estDisp();
    estLambda();
}

std::vector<double> *RandomValue::getValuePool()
{
    return &pool;
}
