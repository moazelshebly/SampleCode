//
// Created by Moaz Elshebly on 01.10.19.
//

#include <vector>

#ifndef SPECTRUM_SPECTRUM_H
#define SPECTRUM_SPECTRUM_H

/// Class representing a spectrum. It saves all the values of a given spectrum and provides some operations that could
/// be done on that spectrum.
class cSpectrum
{
public:
    /// gets the spectrum vector size
    /// \return the size of the spectrum vector
    unsigned size();

    /// sets the size of the spectrum vector
    /// \param size: the new desired size
    void resize(unsigned size);

    /// overloaded indexing operator
    /// \param index
    /// \return value at given index or index out of bounds
    double& operator[](unsigned index);

    /// default constructor
    cSpectrum() = default;

    /// getter for the spec vector for testing purposes
    [[nodiscard]] const std::vector<double> &getSpec() const;

    /// copy constructor
    /// \param newSpec Spectrum object to copy data from
    cSpectrum(const cSpectrum& newSpec);

    /// overloaded equal operator to assign the whole spectrum to a given value
    /// \param value: the entire spectrum is assigned to this value
    /// \return pointer to self
    cSpectrum &operator=(double value);

    /// overloaded equal operator to assign the spectrum to a given vector
    /// \param newSpec vector to assign to the current object vector
    /// \return pointer to self
    cSpectrum &operator=(const std::vector<double>& newSpec);

    /// overloaded equal operator to assign the spectrum to another spectrum
    /// \param newSpec spectrum object to assign the current spectrum to
    /// \return pointer to self
    cSpectrum &operator=(const cSpectrum& newSpec) = default;

    /// overloaded sum operator to add a spectrum to the current spectrum (element-wise)
    /// \param summand spectrum object to be added (element-wise) to the current spectrum
    /// \return pointer to self
    cSpectrum &operator+=(const cSpectrum& summand);

    /// overloaded multiplication operator to multiply the spectrum with another spectrum (element-wise)
    /// \param factor spectrum object to be multiplied (element-wise) to the current spectrum
    /// \return pointer to self
    cSpectrum &operator*=(const cSpectrum& factor);

    /// overloaded multiplication operator to multiply the whole spectrum with a factor
    /// \param factor The entire spectrum will be multiplied by this factor
    /// \return pointer to self
    cSpectrum &operator*=(double factor);

    /// applies the exponential function to all elements in the spectrum
    /// \return pointer to self
    cSpectrum &exp();

    /// sums all the elements inside a spectrum
    /// \return sum of all elements
    double sum();

    /// reads a specific spectrum from a binary file and stores the results in a text file
    /// \param filename: path of file
    /// \param tubeVoltage: maximum tube voltage allowed
    /// \param minEnergy: minimum energy in the spectrum
    /// \param spectrumName: empty string that will later store the spectrum name read from the file
    void readSpectrum(const std::string &filename, double tubeVoltage, double &minEnergy, std::string &spectrumName);

private:
    std::vector<double> spec;
};

#endif //SPECTRUM_SPECTRUM_H
