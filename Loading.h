#pragma once

using namespace std::chrono;
DataSet loadDiscoverDelays() {
    string fileName = "updated_2008.csv";
    DataSet ds;
    fstream inputFile;
    inputFile.open(fileName, ios::in);
    string line;

    short int month, delay;
    bool isMonth = true;
    int count = 0;
    int index = 0;
    int rows = 463128;
    pair<short int, short int>* flights = new pair<short int, short int>[rows];

    while (getline(inputFile, line)) {
        if (count == rows)
            break;
        string temp;
        temp = line.substr(0, line.find(','));
        if (temp != "NA") {
            month = stoi(temp);
        }

        temp = line.substr(line.find(',') + 1, line.size() - line.find(','));
        if (temp != "NA") {
            delay = stoi(temp);
            pair<short int, short int> newPair = make_pair(delay, month);
            flights[index] = newPair;
            index++;
        }
        count++;
    }

    cout << "Finished reading in flight data..." << endl;

    pair<short int, short int>* temp = new pair<short int, short int>[count];
    for (int i = 0; i < count; i++)
        temp[i] = flights[i];

    cout << "Performing merge sort..." << endl;
    auto start = high_resolution_clock::now();
    mergeSort(flights, 0, rows);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    ds.mergeTime = duration.count();

    cout << "Performing quick sort..." << endl;
    start = high_resolution_clock::now();
    quickSort(temp, 0, rows);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    ds.quickTime = duration.count();

    int months[12];
    for (int i = 0; i < 12; i++)
        months[i] = 0;

    for (int i = 0; i < 0.25 * rows; i++) {
        months[flights[i].second - 1]++;
    }


    for (int i = 0; i < 12; i++)
        months[i] = 0;

    for (int i = rows - 1; i > 0.75 * rows; i--) {
        months[flights[i].second - 1]++;
    }

    int worst = 0;
    int worstMonth = 0;
    for (int i = 0; i < 12; i++) {
        if (months[i] > worst) {
            worst = months[i];
            worstMonth = i;
        }
    }
    ds.worstMonth = worstMonth;

    int min = INT_MAX;
    int minMonth = 0;
    for (int i = 0; i < 12; i++) {
        ds.numDelaysByMonth[i] = months[i];
        if (min > months[i]) {
            minMonth = i;
            min = months[i];
        }
    }

    ds.bestMonth = minMonth;

    int numDelays[12] = { 0 };

    for (int i = 0; i < rows; i++) {
        ds.totalDelayByMonth[flights[i].second - 1] += flights[i].first;
        if (flights[i].first > 80) {
            numDelays[flights[i].second - 1]++;
        }
    }

    int max = -1;
    int maxindex = 0;
    min = INT_MAX;
    int minindex = 0;
    for (int i = 0; i < 12; i++) {
        if (max < ds.totalDelayByMonth[i]) {
            max = ds.totalDelayByMonth[i];
            maxindex = i;
        }
        if (min > ds.totalDelayByMonth[i]) {
            min = ds.totalDelayByMonth[i];
            minindex = i;
        }
    }

    ds.longestDelMonth = maxindex;
    ds.shortestDelMonth = minindex;

    for (int i = 0; i < 12; i++) {
        ds.numBadDelaysByMonth[i] = numDelays[i];
    }

    return ds;
}