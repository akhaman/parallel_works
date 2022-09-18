#include <iostream>
#include <omp.h>
#include <sstream>

void firstTask() {
    omp_set_num_threads(8);
    #pragma omp parallel
    {
        std::stringstream ss;
        ss << "Current thread: " << omp_get_thread_num() << "\n";
        ss << "Threads amount: " << omp_get_num_threads() << "\n";
        ss << "Hello world" << "\n\n";

        std::cout << ss.str();
    }
}

void secondTask() {
    std::cout << "Switching to 3 threads\n\n";
    omp_set_num_threads(3);

    #pragma omp parallel if (omp_get_max_threads() > 1)
    {
        std::stringstream ss;
        ss << "Current thread: " << omp_get_thread_num() << "\n";
        ss << "Threads amount: " << omp_get_num_threads() << "\n\n";

        std::cout << ss.str();
    }

    std::cout << "Switching to 1 thread\n\n";
    omp_set_num_threads(1);

    #pragma omp parallel if (omp_get_max_threads() > 1)
    {
        std::stringstream ss;
        ss << "Current thread: " << omp_get_thread_num() << "\n";
        ss << "Threads amount: " << omp_get_num_threads() << "\n\n";

        std::cout << ss.str();
    }
}

void thirdTask() {
    int a = 0;
    int b = 0;

    std::cout << "Initital values: a = " << a << "; b = " << b << "\n\n";

    #pragma omp parallel num_threads(2) private(a) firstprivate(b)
    {
        int threadNum = omp_get_thread_num();
        a = 0;
        a += threadNum;
        b += threadNum;

        std::stringstream ss;
        ss << "Current thread: " << threadNum << "\n";
        ss << "a = " << a << "; b = " << b << "\n\n";

        std::cout << ss.str();
    }

    std::cout << "First block completed with result: "
                 "a = " << a << "; b = " << b << "\n\n";

    #pragma omp parallel num_threads(4) shared(a) private(b)
    {
        int threadNum = omp_get_thread_num();
        b = 0;
        b -= threadNum;
        #pragma omp atomic
        a -= threadNum;

        std::stringstream ss;
        ss << "Current thread: " << threadNum << "\n";
        ss << "a = " << a << "; b = " << b << "\n\n";

        std::cout << ss.str();
    }

    std::cout << "Second block completed with result: "
                 "a = " << a << "; b = " << b << "\n\n";
}

void fourthTask() {
    const int a[10] = { 2, 4, 5, 4,5,7,8,3,12,34 };
    const int b[10] = { 8,3,4,8,9,4,3,6,3,8};
    int minA = a[0];
    int maxB = b[0];

    #pragma omp parallel num_threads(2)
    {
        if (omp_get_thread_num() == 0) {
            for (int i = 0; i < 10; i++) {
                if (a[i] < minA) {
                    minA = a[i];
                }
            }
        } else {
            for (int i = 0; i < 10; i++) {
                if (b[i] > maxB) {
                    maxB = b[i];
                }
            }
        }
    };

    std::cout << "Execution completed with result: "
                 "minA = " << minA << "; maxB = " << maxB;
}

void fifthTask() {
    const int height = 6;
    const int width = 8;
    int array[height][width];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            array[i][j] = rand();
        }
    }

    int average;
    int averageThread;
    int minValue;
    int maxValue;
    int minMaxThread;
    int multiples3Count;
    int multiples3CountThread;

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            int sum = 0;
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    sum += array[i][j];
                }
            }
            average = sum / (height * width);
            averageThread = omp_get_thread_num();
        }

         #pragma omp section
        {
            int min = array[0][0];
            int max = array[0][0];
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    int value = array[i][j];

                    if (value < min) {
                        min = value;
                    }

                    if (value > max) {
                        max = value;
                    }
                }
            }
            minValue = min;
            maxValue = max;
            minMaxThread = omp_get_thread_num();
        }

        #pragma omp section
        {
            int count = 0;
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if (array[i][j] % 3 == 0) {
                        count += 1;
                    }
                }
            }
            multiples3Count = count;
            multiples3CountThread = omp_get_thread_num();
        }
    }
    std::cout << "Average = " << average << "; thread = " << averageThread << "\n";
    std::cout << "Min = " << minValue << "; max = " << maxValue << "; thread = " << minMaxThread << "\n";
    std::cout << "Multiples of 3 count = " << multiples3Count << "; thread = " << multiples3CountThread << "\n";
}

void sixthTask() {
    const int arraySize = 10;
    const int a[arraySize] = {1,4434,435545,343,356,2,2545, 3, 545, 54};
    const int b[arraySize] = {1,5,4,6463,65,34,654,2,543534,231};
    int aAverage = 0;
    int bAverage = 0;

    #pragma omp parallel for reduction(+: aAverage) reduction(+: bAverage)
    for (int i = 0; i < arraySize; i++) {
            aAverage += a[i] / arraySize;
            bAverage += b[i] / arraySize;
    }

    char symbol = aAverage < bAverage ? '<' : aAverage == bAverage ? '=' : '>';

    std::cout << "a average = " << aAverage << ";\n";
    std::cout << "b average = " << bAverage << ";\n";
    std::cout << "a average " << symbol << " b average";
}

void seventhTask() {
    const int arraySize = 12;
    int a[arraySize], b[arraySize], c[arraySize];

    #pragma omp parallel for schedule(static) num_threads(3)
    for(int i = 0; i < arraySize; i++) {
        a[i] = i + i;
        b[i] = i * i;
        std::stringstream ss;
        ss << "Current thread: " << omp_get_thread_num() << "; threads count: " << omp_get_num_threads() << "\n";
        std::cout << ss.str();
    }

    std::stringstream ssA;
    std::stringstream ssB;
    ssA << "A array values:";
    ssB << "B array values:";

    for (int i = 0; i < arraySize; i++) {
        ssA << " " << a[i];
        ssB << " " << b[i];
    }
    std::cout << ssA.str() << "\n" << ssB.str() << "\n\n";

    #pragma omp parallel for schedule(dynamic, 3) num_threads(2)
    for(int i = 0; i < arraySize; i++) {
        c[i] = a[i] + b[i];
        std::stringstream ss;
        ss << "Current thread: " << omp_get_thread_num() << "; threads count: " << omp_get_num_threads() << "\n";
        std::cout << ss.str();
    }

    std::stringstream ssC;
    ssC << "C array values:";

    for (int i = 0; i < arraySize; i++) {
        ssC << " " << c[i];
    }
    std::cout << ssC.str();
}

void eighthTask() {
    const int matrixSize = 7;
    int matrix[matrixSize][matrixSize];
    int vector[matrixSize];
    int resultVector[matrixSize];

    for (int i = 0; i < matrixSize; i++) {
        vector[i] = rand();
        for (int j = 0; j < matrixSize; j++) {
            matrix[i][j] = rand();
        }
    }

    double timeStamp = omp_get_wtime();

    for (int i = 0; i < matrixSize; i++) {
        resultVector[i] = 0;
        for (int j = 0; j < matrixSize; j++) {
            resultVector[i] += matrix[i][j] * vector[j];
        }
    }

    std::cout << "completed after " << omp_get_wtime() - timeStamp << " seconds with 1 thread\n\n";

    timeStamp = omp_get_wtime();

    #pragma omp parallel for schedule(static) num_threads(7)
    for (int i = 0; i < matrixSize; i++) {
        resultVector[i] = 0;
        for (int j = 0; j < matrixSize; j++) {
            resultVector[i] += matrix[i][j] * vector[j];
        }
    }

    std::cout << "completed after " << omp_get_wtime() - timeStamp << " seconds with " << matrixSize << " threads\n\n";
}

int main() {
    eighthTask();
    return 0;
}

