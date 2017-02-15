/*
                                data.h
    This is the header file containg the Data class. All member functions
    are declared here.

@Author Aditya Joshi
Date: 22 September 2016

Tel: 650-557-8687
Email: aditya@adityamjoshi.com
Web: www.adityamjoshi.com
*/
#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <map>
using namespace std;

class Data
{
  public:
    class Record
    {
    public:
      unsigned long int maxTimeGap, previousTimeStamp;
      int totalVolume, maxTradePrice, avgPrice, quantityXPrice;
      bool flag;

      Record()
      {
        maxTimeGap = 0;
        previousTimeStamp = 0;
        quantityXPrice = 0;
        totalVolume = 0;
        maxTradePrice = 0;
        avgPrice = 0;
        flag = true;
      }
    };

    unsigned long int processMaxTime(unsigned long int, unsigned long int,
      unsigned long int);
    void readFile();
    void writeFile();
    void process(string, unsigned long int, int ,int);

  private:
    map<string, Record*> data;
};
#endif
//end of file
