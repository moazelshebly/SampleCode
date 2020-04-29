//
// Created by Moaz Elshebly on 13.10.19.
//
#include <iostream>
#include <cmath>
#include <fstream>
#include "AtomicData.h"
#include "Material.h"
#include "Spectrum.h"

using namespace std;

void testMaterial();
void testAtomicWeight(cAtomicData &a);
void testCrossSection(cAtomicData &a);
void testGetAttCoeff();
void testH2O();

int main()
{
    try
    {
        cout << "Test cMaterial " << endl;
        testMaterial();
        cout << "Successful run" << endl;
    }
    catch (exception &exc)
    {
        cout << "ERROR: " << exc.what() << endl;
    }
    catch (...)
    {
        cout << "ERROR: Unexpected error. " << endl;
    }
    return 0;
}

void testMaterial()
{
    cAtomicData a;
    a.prepare();
    testAtomicWeight(a);
    testCrossSection(a);
    testGetAttCoeff();
    testH2O();
}

void testAtomicWeight(cAtomicData &a)
{
    double hydrogen = a.getStdAtomicWeight(1), copper = a.getStdAtomicWeight(29), platinum = a.getStdAtomicWeight(78);
    if(abs(hydrogen - 1.008) > 0.01 || abs(copper - 63.546) > 0.01 || abs(platinum - 195.08) > 0.01)
    {
        cout << "The standard atomic weights read don't match the expected values." << endl;
    }
}

void testCrossSection(cAtomicData &a)
{
    double cS = a.getTotalCrossSection(13, 27.9);
    if(abs(cS - 61.223) > 0.01)
    {
        cout << "Evaluating the cross section does not work as expected." << endl;
    }
}

void testGetAttCoeff()
{
    cMaterial m{};
    m.setName("Water");
    m.setDensity(1000);
    m.addElement(1, 2);
    m.addElement(8, 1);
    double u = m.getAttCoeff(50.0/1000);
    if(abs( u - 22.7) > 0.02)
    {
        cout << "Evaluating the attenuation coefficient does not work properly" << endl;
    }
}

void testH2O()
{
    cSpectrum spec;
    double voltage = 75;
    string specName;
    double minEnergy;
    cMaterial H2O;

    cout << "+--------------------------------------+" << endl;
    cout << "| test class cMaterial with pure water |" << endl;
    cout << "+--------------------------------------+" << endl;

    // read spectrum
    spec.readSpectrum("SRO33100ROT350.dat", voltage, minEnergy, specName);
    cout << "spectrum name: " << specName << endl;
    cout << "minimum energy: " << minEnergy << endl;

    // prepare material
    H2O.addElement(1, 2);
    H2O.addElement(8, 1);
    H2O.setDensity(1000.0);
    H2O.setName("pure water");

    // get attenuation spectrum
    cSpectrum attSpec;
    vector<double> tmp;
    H2O.getAttSpec(tmp, minEnergy, voltage, spec.size());
    attSpec = tmp;

    // x-ray spectrum behind 1 cm water
    cSpectrum I = attSpec;
    I *= -0.01;
    I.exp();
    I *= spec;
    cout << "sum behind water: " << I.sum() << endl;

    // write spectrum
    ofstream out("specBehindWater.csv");
    if (!out.is_open()) throw runtime_error("Could not open file 'specBehindWater.csv' for writing.");
    out << "energy,intensity" << endl;
    out << "(keV),(#/keV mAs µsr)" << endl;
    for (unsigned k = 0; k < I.size(); k++) {
        out << minEnergy + k * (voltage - minEnergy) / I.size() << ",";
        out << I[k] << endl;
    }
    out << voltage << ",0" << endl;
    out.close();
    cout << "spectrum written in file 'specBehindWater.csv'." << endl;
}

