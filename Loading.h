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

    int best = 0;
    int bestMonth = 0;
    for (int i = 0; i < 12; i++) {
        if (months[i] > best) {
            best = months[i];
            bestMonth = i;
        }
    }
    ds.bestMonth = bestMonth;

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

    for (int i = 0; i < 12; i++) {
        ds.numDelaysByMonth[i] = months[i];
        
    }

    int numDelays[12] = { 0 };

    for (int i = 0; i < rows; i++) {
        if (flights[i].first > 80) {
            numDelays[flights[i].second - 1]++;
        }
    }

    for (int i = 0; i < 12; i++) {
        ds.numBadDelaysByMonth[i] = numDelays[i];
    }

    return ds;
}