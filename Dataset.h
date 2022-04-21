#pragma once

struct DataSet {
    int numBadDelaysByMonth[12];
    int numDelaysByMonth[12];
    int worstMonth;
    int bestMonth;

    long int mergeTime;
    long int quickTime;

    DataSet() {};
};