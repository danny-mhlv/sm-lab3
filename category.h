#ifndef CATEGORY_H
#define CATEGORY_H

#include <vector>
#include <iostream>

class Category
{
public:
    Category(double left, double right);

    void setBorders(double left, double right);
    void incElemCount();

    double calculateFreq(int totalElements);

    double getFreq();
    double getElemCount();
    double getMidValue();
    double getLB();
    double getRB();

    static std::vector<double>* makeVMidValue(std::vector<Category>* categories);
    static std::vector<double>* makeVFreq(std::vector<Category>* categories);
private:
    double lb, rb; // Left and right borders
    double midval; // Mid value
    double elem_count; // Number of elements in category
    double freq;
};

#endif // CATEGORY_H
