//
// Created by Moaz Elshebly on 13.10.19.
//

#include "AtomicData.h"
#include <fstream>
#include <iostream>
#include <cmath>

std::vector<cAtomicData::tPoint2d> cAtomicData::tcs[100]{};
float cAtomicData::a[100]{};
bool cAtomicData::prepared = false;

void cAtomicData::prepare()
{
    if(prepared)
    {
        return;
    }

    try
    {
        std::ifstream csFile{"totalCrossSection.dat", std::ios_base::binary};

        if(!csFile.is_open())
        {
            throw std::runtime_error("File could not be opened.");
        }

        // Read title
        char *title = new char[12];
        csFile.read(title, 11);
        title[11] = 0;

        // Read file name size
        uint32_t nameSize;
        csFile.read((char *) &nameSize , sizeof(nameSize));

        // Read file name
        char *name = new char[nameSize+1];
        csFile.read(name, nameSize);
        name[nameSize] = 0;

        // Loop over 100 entries
        for (int i = 0; i < 100; ++i)
        {
            // Read atomic number
            uint32_t atomicN;
            csFile.read((char *) &atomicN , sizeof(atomicN));

            // Read standard atomic weight number
            csFile.read((char *) &a[i] , sizeof(float));

            // Read number of entries
            uint32_t entries;
            csFile.read((char *) &entries , sizeof(entries));

            for (unsigned j = 0; j < entries; ++j)
            {
                // Read energy and cross-section values
                float energy, cs;
                csFile.read((char *) &energy , sizeof(energy));
                csFile.read((char *) &cs , sizeof(cs));

                // Save values into the vector
                tcs[i].push_back(cAtomicData::tPoint2d{energy,cs});
            }
        }
        csFile.close();
        prepared = true;
    }
    catch(std::exception &e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
}

double cAtomicData::getStdAtomicWeight(unsigned z)
{
    if(z < 1 || z > 100)
    {
        throw std::runtime_error("Index out of bounds");
    }
    else
    {
        return a[z-1];
    }
}

double cAtomicData::getTotalCrossSection(unsigned z, double energy)
{
    if(z < 1 || z > 100)
    {
        throw std::runtime_error("Index out of bounds");
    }
    else
    {
        z--;
        // convert from KeV to MeV
        double newEnergy = energy/1000;

        float eK = tcs[z].at(0).x;
        float eK1, sK = 0, sK1;
        for( int i = 0; i != tcs[z].size(); ++i)
        {
            if (newEnergy > tcs[z][i].x)
            {
                continue;
            }

            eK = tcs[z][i-1].x;
            eK1 = tcs[z][i].x;
            sK = tcs[z][i-1].y;
            sK1 = tcs[z][i].y;
            break;
        }

        return (sK * std::exp(log(sK1/sK) * (log(newEnergy/eK)/log(eK1/eK))));
    }
}
