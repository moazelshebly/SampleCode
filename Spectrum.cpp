//
// Created by Moaz Elshebly on 01.10.19.
//

#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include "Spectrum.h"


void cSpectrum::resize(unsigned size)
{
    spec.resize(size);
}

unsigned cSpectrum::size()
{
    return (unsigned) spec.size();
}

double& cSpectrum::operator[](unsigned index)
{
    if (index >= spec.size())
        throw std::runtime_error("Index out of range in class cSpectrum");
    return spec [ index ];
}

cSpectrum::cSpectrum(const cSpectrum &newSpec)
{
    spec = newSpec.spec;
}

const std::vector<double> &cSpectrum::getSpec() const
{
    return spec;
}

cSpectrum &cSpectrum::operator=(double value)
{
    for(double & i : spec)
    {
        i = value;
    }
    return *this;
}

cSpectrum &cSpectrum::operator=(const std::vector<double> &newSpec) {
    spec = newSpec;
    return *this;
}

cSpectrum &cSpectrum::operator+=(const cSpectrum &summand) {
    // check if same size
    if (spec.size()!=summand.spec.size())
    {
        throw std::runtime_error ("Adding spectra of different size not possible!");
    }

    // add elements
    for(unsigned long i=0; i<spec.size(); i++)
    {
        spec[i] +=summand.spec[i];
    }
    return *this;
}

cSpectrum &cSpectrum::operator*=(const cSpectrum &factor)
{
    // check if same size
    if (spec.size()!=factor.spec.size())
    {
        throw std::runtime_error ("Multiplying spectra of different size not possible!");
    }

    // multiply elements
    for(unsigned long i=0; i<spec.size(); i++)
    {
        spec[i] *=factor.spec[i];
    }
    return *this;
}

cSpectrum &cSpectrum::operator*=(double factor)
{
    if (spec.empty())
    {
        throw std::runtime_error ("The vector to be multiplied is empty!");
    }

    for(double & i : spec)
    {
        i *=factor;
    }
    return *this;
}

cSpectrum &cSpectrum::exp() {
    if (spec.empty())
    {
        throw std::runtime_error ("The vector to be exponent is empty!");
    }

    for(double & i : spec)
    {
        i = std::exp(i);
    }
    return *this;
}

double cSpectrum::sum()
{
    if (spec.empty())
    {
        throw std::runtime_error ("The vector to be summed is empty!");
    }

    double sum = 0;
    for(double i : spec)
    {
        sum += i;
    }
    return sum;
}
void cSpectrum::readSpectrum(const std::string &filename, double tubeVoltage, double &minEnergy, std::string &spectrumName)
{
    std::ifstream spectrumFile(filename, std::ios::binary);

    if(!spectrumFile.is_open())
    {
        throw std::runtime_error("The file must be opened first!");
    }
    char *title = new char [14];
    spectrumFile.read(title, 14);
    title[14] = 0;

    if(strcmp(title, "x-ray spectrum") != 0)
    {
        throw std::runtime_error("The title was not read correctly!");
    }
    uint32_t len;
    spectrumFile.read((char *) &len, sizeof(len));

    char *name = new char [len];
    spectrumFile.read(name, len);
    name [len] = 0;
    spectrumName = name;

    uint32_t noSpectra;
    spectrumFile.read((char*) &noSpectra, sizeof(noSpectra));

    float tubeVolt, minPhotonEnergy;
    uint32_t tableLen;
    bool entryFound = false;
    for (unsigned int i = 0; i < noSpectra; ++i)
    {
        spectrumFile.read((char *) &tubeVolt, sizeof(float));

        spectrumFile.read((char *) &minPhotonEnergy, sizeof(float));
        minEnergy = minPhotonEnergy;

        spectrumFile.read((char *) &tableLen, sizeof(tableLen));
        if(abs(tubeVolt-tubeVoltage) < 0.001)
        {
            entryFound = true;
            float spectrumVal;
            for (unsigned int j = 0; j < tableLen; ++j)
            {
                spectrumFile.read((char *) &spectrumVal, sizeof(spectrumVal));
                spec.push_back(spectrumVal);
            }
            break;
        }
        else
        {
            spectrumFile.seekg(tableLen *sizeof(float), std::ios_base::cur);
        }
    }

    delete [] title;
    delete [] name;

    if (!entryFound)
    {
        throw std::runtime_error("Table entry could not be found!");
    }
}

