#include "category.h"

Category::Category(double left, double right)
{
    lb = left; rb = right;
    midval = (left + right) / 2;
    elem_count = 2;
    freq = 0;
}

void Category::setBorders(double left, double right)
{
    lb = left; rb = right;
    midval = (left + right) / 2;
    elem_count = 2;
    freq = 0;
}

double Category::getLB()
{
    return lb;
}

double Category::getRB()
{
    return rb;
}

std::vector<double> *Category::makeVMidValue(std::vector<Category> *categories)
{
    std::vector<double>* mids = new std::vector<double>;

    for(auto elem : *categories) {
        mids->push_back(elem.getMidValue());
    }

    return mids;
}

std::vector<double>* Category::makeVFreq(std::vector<Category> *categories)
{
    std::vector<double>* freqs = new std::vector<double>;

    for(auto elem : *categories) {
        freqs->push_back(elem.getFreq());
    }

    return freqs;
}

double Category::calculateFreq(int totalElements)
{
    freq = elem_count / totalElements;
    return freq;
}

double Category::getFreq()
{
    return freq;
}

double Category::getElemCount()
{
    return elem_count;
}

double Category::getMidValue()
{
    return midval;
}

void Category::incElemCount()
{
    elem_count++;
}
