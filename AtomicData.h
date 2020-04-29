//
// Created by Moaz Elshebly on 13.10.19.
//
#include <vector>

#ifndef MATERIAL_ATOMICDATA_H
#define MATERIAL_ATOMICDATA_H

/**
 * Class representing atomic data. It's main mission is to read data from a file and store them to
 * its static variables. It also provides methods to get atomic weights and cross sections.
 */
class cAtomicData
{
public:
    /**
     * default constructor.
     */
    cAtomicData()= default;

    /**
     * default destructor.
     */
    virtual ~cAtomicData()=default;

    /**
     * reads from the atomic weights, energies and cross sections from a file and saves them to
     * the fields of this class. Sets the variable prepared to true if reading was successful.
     */
    void prepare();

    /**
     * gets the standard atomic weight of a given element.
     * @param z Index of the element.
     * @return Atomic weight of the element.
     * @throws runtime_error If index is out of bounds.
     */
    double getStdAtomicWeight(unsigned z);

    /**
     * gets the total cross section of an element.
     * @param z The atomic number of the element.
     * @param energy The minimum energy.
     * @return the cross section of the specified element if found.
     */
    double getTotalCrossSection(unsigned z, double energy);

private:
    typedef struct
    {
        float x; // energy in MeV
        float y; // cross section in barn
    }tPoint2d;

    static std::vector<tPoint2d> tcs[100]; // array of vectors containing energy and cross section for each element.
    static float a[100]; // array of elements' atomic weights.
    static bool prepared; // variable to determine if the file has been read and the class has been prepared.
};


#endif //MATERIAL_ATOMICDATA_H
