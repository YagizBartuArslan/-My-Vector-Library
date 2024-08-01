// Author: Yaðýz Bartu Arslan - Junior Computer Science & Engineering Student at Sabanci University

// Written in : 02.12.2023

#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <vector>
#include <string>
//#include <algorithm>
#include <cmath>
#include <type_traits>
#include <iostream>

// Forward declaration of myVector class
template <typename T1, typename T2>
class myVector;

// Definition of myVector class
template <typename T1, typename T2>
class myVector {
public:

    void push_back(const T1& value, const T2& key) {
        data.emplace_back(key, value);
    }

    void printVector() const {
        for (const auto& elem : data) {
            std::cout << "Value: " << elem.second << ", Key: " << elem.first << std::endl;
        }
    }


    // Process data method
    void process_data() {
        processData();
    }

    // Additional methods as per main.cpp
    void setName(const std::string& name) {
        vectorName = name;
    }

    std::string getName() const {
        return vectorName;
    }

    bool isEmpty() const {
        return data.empty();
    }

    // Nested Iterator class
    class Iterator {
    public:
        using iterator_type = typename std::vector<std::pair<T2, T1>>::iterator;


        void printVector() const {
            parentVector->printVector();
        }

        bool find(const T2& key, const myVector<T1, T2>& vec) {
            for (auto tempIter = vec.data.begin(); tempIter != vec.data.end(); ++tempIter) {
                if (tempIter->first == key) {
                    // Since 'vec' is const, we cannot modify it, thus we cannot assign a non-const iter to a const_iterator
                    // Instead, we should use the parentVector's non-const data member to update iter
                    if (parentVector != nullptr) { // Add a null check for parentVector
                        iter = std::find_if(parentVector->data.begin(), parentVector->data.end(),
                            [key](const std::pair<T2, T1>& element) { return element.first == key; });
                        return true;
                    }
                    return false;
                }
            }
            }


        void replaceKey(const T2& newKey) {
            if (iter != parentVector->data.end() && parentVector != nullptr) {
                T1 value = iter->second;
                // Erase invalidates the iterator, but returns a new valid iterator.
                iter = parentVector->data.erase(iter);
                // Insert the new element at the position of the erased element.
                iter = parentVector->data.insert(iter, std::make_pair(newKey, value));
                // Now iter points to the new element.
            }
        }

        // Constructor with an additional parameter for the myVector pointer
        Iterator(iterator_type it, myVector<T1, T2>*parentVector)
        : iter(it), parentVector(parentVector) {}


        // Overloading operators
        Iterator& operator++() {
            ++iter;
            return *this;
         }

        bool operator!=(const Iterator & other) const {
            return iter != other.iter;
        }

        std::pair<T2, T1>& operator*() {
            return *iter;
        }

   private:
        iterator_type iter; // Changed to non-const iterator
        myVector<T1, T2>* parentVector; // Points to the associated myVector instance
            };

            // Constructors
            myVector() = default;
            myVector(const myVector<T1, T2>&other) : data(other.data) {}

            // Assignment operator
            myVector<T1, T2>& operator=(const myVector<T1, T2>&other) {
                if (this != &other) {
                    data = other.data;
                }
                return *this;
            }

            // Subscript operator
            T1* operator[](const T2& key) {
                auto it = std::find_if(data.begin(), data.end(), [&key](const std::pair<T2, T1>& element) {
                    return element.first == key;
                    });

                if (it != data.end()) {
                    return &(it->second);
                }
                else {
                    return nullptr; // Return nullptr if key is not found
                }
            }

            // add and remove elements
            void push(const T2 & key, const T1 & value) {
                data.emplace_back(key, value);
            }

            void remove(const T2& key) {
                auto it = std::find_if(data.begin(), data.end(), [&key](const std::pair<T2, T1>& element) {
                    return element.first == key;
                    });

                if (it != data.end()) {
                    data.erase(it);
                }
                else {
                    throw std::runtime_error("Key not found");
                }
            }



            // Equality operator
            bool operator==(const myVector<T1, T2>&other) const {
                return data == other.data;
            }

            Iterator begin() {
                
                return Iterator(data.begin(), this);
            }

            Iterator end() {
                
                return Iterator(data.end(), this);
            }



            // Process data method (specific functionalities)
            void processData() {
                if constexpr (std::is_same<T1, std::string>::value) {
                    processStringData();
                }
                else if constexpr (std::is_arithmetic<T1>::value) {
                    processArithmeticData();
                }
            }


    private:
        std::vector<std::pair<T2, T1>> data;
        std::string vectorName;

        void processStringData() {
            const int MAX_CHAR = 256; // set it to max, this guy has to be at top :)
            std::vector<int> charFrequency(MAX_CHAR, 0);
            std::vector<std::pair<std::string, int>> wordFrequency;
            std::string mostFrequentWord;
            char mostFrequentChar;
            int maxCharFreq = 0, maxWordFreq = 0;

            for (const auto& elem : data) {
                const std::string& word = elem.second;
                for (char c : word) {
                    charFrequency[static_cast<unsigned char>(c)]++;
                    if (charFrequency[static_cast<unsigned char>(c)] > maxCharFreq) {
                        maxCharFreq = charFrequency[static_cast<unsigned char>(c)];
                        mostFrequentChar = c;
                    }
                }

                auto it = std::find_if(wordFrequency.begin(), wordFrequency.end(), [&word](const std::pair<std::string, int>& wf) {
                    return wf.first == word;
                    });

                if (it != wordFrequency.end()) {
                    it->second++;
                    if (it->second > maxWordFreq) {
                        maxWordFreq = it->second;
                        mostFrequentWord = word;
                    }
                }
                else {
                    wordFrequency.emplace_back(word, 1);
                    if (1 > maxWordFreq) {
                        maxWordFreq = 1;
                        mostFrequentWord = word;
                    }
                }
            }

            std::cout << "Most Frequent Character: '" << mostFrequentChar
                << "' (Frequency: " << maxCharFreq << ")\n";
            std::cout << "Most Frequent Word: \"" << mostFrequentWord
                << "\" (Frequency: " << maxWordFreq << ")\n";
        }


        void processArithmeticData() {
            if (data.empty()) return;

            std::vector<T1> values;
            for (const auto& elem : data) {
                values.push_back(elem.second);
            }

            // Sorting using bubble sort
            for (size_t i = 0; i < values.size() - 1; ++i) {
                for (size_t j = 0; j < values.size() - i - 1; ++j) {
                    if (values[j] > values[j + 1]) {
                        std::swap(values[j], values[j + 1]);
                    }
                }
            }

            // Initializations
            T1 sum = 0, max = values[0];

            // Calculate sum and max
            for (const T1& value : values) {
                sum += value;
                if (value > max) {
                    max = value;
                }
            }

            // Calculating mode 
            T1 mode = values[0];
            int maxFreq = 1, currentFreq = 1;
            for (size_t i = 1; i < values.size(); ++i) {
                if (values[i] == values[i - 1]) {
                    ++currentFreq;
                }
                else {
                    if (currentFreq > maxFreq) {
                        maxFreq = currentFreq;
                        mode = values[i - 1];
                    }
                    currentFreq = 1;
                }
            }
            if (currentFreq > maxFreq) {
                mode = values.back();
            }

            double mean = static_cast<double>(sum) / values.size();
            double median = values.size() % 2 == 0 ? (values[values.size() / 2 - 1] + values[values.size() / 2]) / 2.0
                : values[values.size() / 2];

            double variance = 0;
            for (const T1& value : values) {
                variance += (value - mean) * (value - mean);
            }
            double stdDeviation = std::sqrt(variance / values.size());

            std::cout << "Mean: " << mean << "\n";
            std::cout << "Median: " << median << "\n";
            std::cout << "Standard Deviation: " << stdDeviation << "\n";
            std::cout << "Max: " << max << "\n";
            std::cout << "Mode: " << mode << "\n";
        }


        };


#endif //MYVECTOR_H

        /***********************************/