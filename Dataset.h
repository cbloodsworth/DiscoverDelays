#pragma once

struct DataSet {
    int numBadDelaysByMonth[12];
    int numDelaysByMonth[12];
    int worstMonth;
    int bestMonth;

    long int mergeTime;
    long int quickTime;

    long int totalDelayByMonth[12];

    int longestDelMonth;
    int shortestDelMonth;

    DataSet() {};
};