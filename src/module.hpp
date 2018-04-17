#include <omp.h>
#include <iostream>
#include <windows.h>

int getThreads(){
    // Get number of threads
    omp_set_num_threads(3);
    int n = 0;
    #pragma omp parallel reduction(+:n)
    n += 1;
    return n;
}

double GetPi(short numOfThreads,long numberOfSteps){
    long i;
    double pi, sum = 0.0;
    double step = 1.0/(double) numberOfSteps;

    omp_set_num_threads(numOfThreads);

    #pragma omp parallel
    {
        std::cout<< "This thread is running on processor: " << GetCurrentProcessorNumber() << "\n";
        double x;
        #pragma omp for reduction(+:sum) 
            for(i = 0; i < numberOfSteps; i++) {
                x = ( i + 0.5 ) * step;
                sum += 4.0 / (1 + x*x);
            }
    }

    std::cout << "Total no. of threads (not processors): " << getThreads() << std::endl;
    pi =  step * (double)sum;
    return pi;
}
