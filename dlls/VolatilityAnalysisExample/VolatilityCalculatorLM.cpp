#include <cmath>
#include <vector>
#include <windows.h>


//I'm C configuration to tell the complier that wan to use
//The C-style linkage convention and not the C++ name-mangling conversation
//For MQL4 and MQL5 apart from better performance and predicatable function names for exporting
//MQL4 and MQL5 need our function names UNMANGLIED




extern "C" {
    //Params: prices[] as double e.g EUR/USD [1.34556, 1.34600]
    //int arr_size - number of elements in the array 
     __attribute__((visibility("default"))) double CalculateVolatility(double prices[], int arr_size){
        if(arr_size <= 1) return 0.0; //If no prices 
        
        
        //Average Asset Price
        double price_sum = 0.0;
        
        for(int i = 0; i < arr_size; ++i){
            //I am using the for loop to add of the prices together
            //to length of array e.g 30 prices points = 30 iterations 
            price_sum += prices[i];
        }
        //mean = sum of items / number of items 
        double price_mean = price_sum / arr_size;

        double std_variance = 0.0;
        //Variance Calculation, use here to help with the maths
        //https://www.youtube.com/watch?v=URcpEgxUfqU 
        for(int i = 0; i < arr_size; ++i){
            //To get the variance we need to substract the mean for each price and then square the result
            //Finally I am adding result to the variance variable to get the sum
            std_variance += pow(prices[i] - price_mean, 2);
        }

        std_variance /= arr_size;
        //This time dividing variance by the array size gives use the AVERAGE squared difference
        //THIS IS THE VARIANCE which we need to work our the standard deviation for volatility
        double std_deviation = std::sqrt(std_variance);

        //The Max Volatility in this example is at the 5% level threshold change it as you see fit ;)
        double normalized_volatility = std_deviation / price_mean / 0.05;
        //It is mathematically possible for that volatility to be above one
        //So to ensure we say in a normalize range between 0 and 1 use the if statement below
        if(normalized_volatility > 1.0) normalized_volatility = 1.0;
    }

    //Remeber variance allows use calculate price BEHAVIOUR e.g Reversal, trends, ranges etc
}