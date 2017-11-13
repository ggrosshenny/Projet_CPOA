#ifndef __ARRAY_H_
#define __ARRAY_H_

#include <iostream>
#include <sstream>
#include <type_traits>

/**
 * Class Array <T, N>
 * Array of n objects of type T
 **/
template <typename T, int N>
class Array
{
private:
    int nb_elements = 0;
// Attributes
protected:
    T data[N];

// Constructors and destructors
public:

    /**
     * @brief Array constructor without arguments. Initialize all data members to T{0}
     */
    Array();


    /**
     * @brief Array constructor with brace-enclosed initilization. Initialize data members with given values or T{0} if unknown
     * @param il
     */
    Array(std::initializer_list<T> il);

// Methods
public:
    /**
     * @brief get_ptr get the encapsulated list of the Array object
     * @return
     */
    T* get_ptr();


    /**
     * @brief swapData swap the array data of two arrays
     * @param other
     */
    void swapData(Array<T,N>& other);


    /**
     * @brief toString return the string version of the Array
     */
    std::string toString();


// Operators overload
public:
    /**
     * @brief operator [] overload of the accessor (get) operator
     * @param i
     * @return
     */
    T operator[](int i) const;


    /**
     * @brief operator [] overload of the accessor (set) operator
     * @param i
     * @return
     */
    T& operator[](int i);


    /**
     * @brief operator = overload of the affectation operator
     * @param other
     * @return
     */
    Array<T,N>& operator=(const Array<T,N>& other);


    /**
     * @brief operator == overload of the equal comparison operator
     * @param leftHandElement left hand element of the comparison
     * @param rightHandElement right hand element of the comparison
     * @return
     */
    bool operator==(const Array<T,N>& rightHandElement);


    /**
     * @brief operator != overload of the non-equal comparison operator
     * @param leftHandElement left hand element of the comparison
     * @param rightHandElement right hand element of the comparison
     * @return
     */
    bool operator!=(const Array<T,N>& rightHandElement);


};



template<typename T>
class DynamicArray
{
protected:
    T* data;
    unsigned int nb_elements;


// Constructor and destructor
public:

    /**
     * @brief DynamicArray
     */
    DynamicArray();


    /**
     * @brief DynamicArray
     * @param size
     */
    DynamicArray(const unsigned int size);


    /**
     * @brief DynamicArray
     * @param elements
     */
    DynamicArray(std::initializer_list<T> elements);


    ~DynamicArray();


// Methods
public:

    /**
     * @brief toString return a string version of the Array
     * @return
     */
    std::string toString();


    /**
     * @brief size return the size of data
     * @return
     */
    unsigned int size();


    T* getPtr();

// Operator overload
public:

    /**
     * @brief operator [] overload of the accessor (get) operator
     * @param i
     * @return
     */
    T operator[](int i) const;


    /**
     * @brief operator [] overload of the accessor (set) operator
     * @param i
     * @return
     */
    T& operator[](int i);


    /**
     * @brief operator = overload of the affectation operator
     * @param other
     * @return
     */
    DynamicArray<T>& operator=(DynamicArray<T>& other);
};

#include "Array.hpp"

#endif
