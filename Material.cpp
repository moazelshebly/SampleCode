//
// Created by Moaz Elshebly on 13.10.19.
//
#include "Material.h"
#include "AtomicData.h"

void cMaterial::clear()
{
    density = 1000;
    name = "new material";
    fraction.clear();
    z.clear();
}

void cMaterial::addElement(unsigned newZ, double newFraction)
{
    z.push_back(newZ);
    fraction.push_back(newFraction);
}

void cMaterial::setName(const std::string &name)
{
    this->name = name;
}

void cMaterial::setDensity(double density)
{
    this->density = density;
}

const std::string &cMaterial::getName()
{
    return name;
}

double cMaterial::getDensity()
{
    return density;
}

unsigned cMaterial::getNoOfElements()
{
    return (unsigned int)fraction.size();
}

unsigned cMaterial::getAtomicNumber(unsigned i)
{
    if(i < 1 || i > z.size())
    {
        throw std::runtime_error("Index out of bounds.");
    }
    return z.at(i-1);
}

double cMaterial::getFraction(unsigned i)
{
    if(i < 1 || i > fraction.size())
    {
        throw std::runtime_error("Index out of bounds.");
    }
    return fraction.at(i-1);
}

double cMaterial::getAttCoeff(double energy)
{
    // Avogadro's constant
    const double nA = 6.022140857e23;
    cAtomicData data{};
    data.prepare();
    double sKfK = 0, aKfK = 0;
    for (auto i = 0; i < z.size(); ++i)
    {
        sKfK += data.getTotalCrossSection(z.at(i), energy) * fraction.at(i);
        aKfK += data.getStdAtomicWeight(z.at(i)) * fraction.at(i);
    }

    // convert total cross section to barns
    sKfK *= 1e-28;
    // convert gm to kg
    aKfK /= 1000;
    return (density * nA * (sKfK/aKfK));
}

void cMaterial::getAttSpec(std::vector<double> &spec, double minEnergy, double tubeVoltage, unsigned energySteps)
{
    double stepSize = (tubeVoltage - minEnergy) / energySteps;
    double energy = minEnergy;
    while(energy < tubeVoltage)
    {
        spec.push_back(getAttCoeff(energy));
        energy += stepSize;
    }
}

double cMaterial::getMeanFreePath(double energy)
{
    return 1 / getAttCoeff(energy);
}
