//
// Created by Moaz Elshebly on 13.10.19.
//
#include <string>
#include <vector>

#ifndef MATERIAL_MATERIAL_H
#define MATERIAL_MATERIAL_H

/**
 * Class representing a material. It saves the material name, density and the atomic number and fraction
 * by number for each element in the material.
 */
class cMaterial
{
public:
    /**
     * default constructor which calls the method clear inside.
     */
    cMaterial(){ clear(); };

    /**
     * default copy constructor.
     * @param material Object of class cMaterial to be copied.
     */
    cMaterial(const cMaterial &material) = default;

    /**
     * default destructor.
     */
    virtual ~cMaterial() = default;

    /**
     * clears the vectors' contents and sets the name and density of the material.
     */
    void clear();

    /**
     * adds an element to the material.
     * @param newZ The atomic number of the element.
     * @param newFraction The fraction by number of the element.
     */
    void addElement(unsigned newZ, double newFraction);

    /**
     * sets material name.
     * @param name The name of the material.
     */
    void setName(const std::string &name);

    /**
     * sets the density of the material.
     * @param density The density to be set.
     */
    void setDensity(double density);

    /**
     * gets material name.
     * @return The name of the material.
     */
    const std::string &getName();

    /**
     * gets the material density.
     * @return The density of the material.
     */
    double getDensity();

    /**
     * gets the number of elements in the material.
     * @return number of elements in vector z (could also be vector fraction since the both have the same size).
     */
    unsigned getNoOfElements();

    /**
     * gets the atomic number of an element in the material.
     * @param i The index of the element.
     * @return Value of the atomic number of the element.
     * @throws runtime_error If the index is out of bounds.
     */
    unsigned getAtomicNumber(unsigned i);

    /**
     * gets the fraction by number of an element in the material.
     * @param i The index of the element.
     * @return Value of the fraction by number number of the element.
     * @throws runtime_error If the index is out of bounds.
     */
    double getFraction(unsigned i);

    /**
     * calculates the total attenuation coefficient of the material.
     * @param energy The energy to calculate the total cross section at.
     * @return The attenuation coefficient.
     */
    double getAttCoeff(double energy);

    /**
     * divides the energy interval into equal sized steps and for each energy it calculates
     * the attenuation coefficient and saves it in the vector passed as a parameter.
     * @param spec Vector to save the attenuation coefficient for each energy.
     * @param minEnergy Minimum energy in the interval.
     * @param tubeVoltage Maximum energy allowed.
     * @param energySteps Number of steps between energy min and max energy levels.
     */
    void getAttSpec(std::vector<double> &spec, double minEnergy, double tubeVoltage, unsigned energySteps);

    /**
     * calculates the reciprocal of the attenuation coefficient.
     * @param energy The energy to calculate the total cross section at.
     * @return The reciprocal of the attenuation coefficient.
     */
    double getMeanFreePath(double energy);

private:
    std::vector<unsigned> z; // vector containing the atomic weight for each element in the material.
    std::vector<double> fraction; // vector containing the fraction by number for each element in the material.
    double density; // density of the material in kg/m^3.
    std::string name; // name of the material.
};


#endif //MATERIAL_MATERIAL_H
