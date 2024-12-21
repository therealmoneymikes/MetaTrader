#include <cmath>
#include <numeric>
#include <stdexcept>
#include <vector>
#include <windows.h>


//I'm C configuration to tell the complier that wan to use
//The C-style linkage convention and not the C++ name-mangling conversation
//For MQL4 and MQL5 apart from better performance and predicatable function names for exporting
//MQL4 and MQL5 need our function names UNMANGLIED




/******* PLEASE NOTE IF YOU ARE ON A MAC OR LINUX MACHINE 
- Use  __attribute__((visibility("default"))) instead of _declspec(dllexport) which is for windows only
//See VolatilityCalculatorML.cpp for Mac and Linux Version


 */
extern "C" {
    //Params: prices[] as double e.g EUR/USD [1.34556, 1.34600]
    //int arr_size - number of elements in the array 
    //Default Volatility upper limit is 5% mean 95% standard deviation spread
    __declspec(dllexport) double CalculateVolatility(const double* prices, int arr_size, double maxPriceVolatility = 0.05){
        
        
        if(arr_size <= 1) return 0.0; //If no prices volatility is 0
        if(prices == nullptr) throw std::invalid_argument("Prices array is empty");
        //if the prices pointer is null pointer our price array is null
        
        //Average Asset Price
        double price_sum = std::accumulate(prices, prices + arr_size, 0.0);
        double price_mean = price_sum / arr_size;   //mean = sum of items / number of items 

        //Variance Calculation, use here to help with the maths
        //https://www.youtube.com/watch?v=URcpEgxUfqU 
        double std_variance = 0.0;
        for(int i = 0; i < arr_size; ++i){
            //To get the variance we need to substract the mean for each price and then square the result
            //Finally I am adding result to the variance variable to get the sum
            std_variance += pow(prices[i] - price_mean, 2);
        }

        //This time dividing variance by the array size gives use the AVERAGE squared difference
        //THIS IS THE VARIANCE which we need to work our the standard deviation for volatility
        std_variance /= arr_size;
        
        //The square root of the variance is the standard deviation which need to calculate our
        //volaility tange
        double std_deviation = std::sqrt(std_variance);

        //The Max Volatility in this example is at the 5% level threshold change it as you see fit ;)
        double normalized_volatility = std_deviation / price_mean / 0.05;
        //It is mathematically possible for that volatility to be above one
        //So to ensure we say in a normalize range between 0 and 1 use the if statement below
        if(normalized_volatility > 1.0) normalized_volatility = 1.0;
    }

    //Remeber variance allows use calculate price BEHAVIOUR e.g Reversal, trends, ranges etc
}