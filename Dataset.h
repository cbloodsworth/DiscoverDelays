#pragma once

struct DataSet {
    int numBadDelaysByMonth[12];
    int numDelaysByMonth[12];
    int worstMonth;
    int bestMonth;

    string mergeTime;
    string quickTime;

    DataSet() {};
};