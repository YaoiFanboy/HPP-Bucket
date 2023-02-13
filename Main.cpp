#include <iostream>
#include <algorithm>
#include <chrono>
#include <cmath>
using namespace std;
using namespace std::chrono;

// Functie om een array van ints en doubles te bucket sorten.
void bucketSort(double arr[], int n) {
// twee-dimensionale array van integers, met rijen genummerd van 0 tot 9 en kolommen geïndexeerd van 0 tot n-1
    double posBucket[1000][n];
    double negBucket[1000][n];
// Arrays om de pos en neg count te storen in elke bucket

    int posCount[1000] = {0};
    int negCount[1000] = {0};

// Distribution pass
    for (int i = 0; i < n; i++) {
// Meest rechtse digit van de abs(absolute value) van de int te bepalen
        int digit = floor(abs(arr[i]) / 10);
// Nummer in goeie bucket zetten
        if (arr[i] >= 0) {
            posBucket[digit][posCount[digit]++] = arr[i];
        } else {
            negBucket[digit][negCount[digit]++] = arr[i];
        }
    }
    int k = 0;
// Gathering pass voor neg nummertjes
    for (int i = 999; i >= 0; i--) {
// Kijken of bucket leeg is
        if (negCount[i] == 0) continue;
// Sorten van de waardes in de bucket in reverse
        sort(negBucket[i], negBucket[i] + negCount[i]);

// Kopieren van de waardes van de bucket in de orginele array
        for (int j = 0; j < negCount[i]; j++) {
            arr[k++] = negBucket[i][j];
        }
    }

// Gathering pass voor pos nummers (zelfde als neg allemaal)
    for (int i = 0; i < 1000; i++) {
        if (posCount[i] == 0) continue;
        sort(posBucket[i], posBucket[i] + posCount[i]);
        for (int j = 0; j < posCount[i]; j++) {
            arr[k++] = posBucket[i][j];
        }
    }

}

int main() {

//const int size = 3000;
    //double arr[size];

    //for (int i = 0; i < size; i++) {
        //arr[i] = i;
    //
    double arr[] = {-64, -2588.3, 4, -69, 2, -1.5, 5, 9.8, 1357, 82, -36, 637, -9979};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << "Before sorting: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

// functie aanroepen en die chrono shit gebruiken voor tijd
    auto start = high_resolution_clock::now();
    bucketSort(arr, n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);


    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;
    cout << "After sorting: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}