/*
                                data.cpp
    This piece of code contains all the member functions of the Data class.

@Author Aditya Joshi
Date: 22 September 2016

Tel: 650-557-8687
Email: aditya@adityamjoshi.com
Web: www.adityamjoshi.com
*/
#include <fstream>
#include <sstream>
#include "data.h"
using namespace std;

/* writeFile() function writes the output to the specified output file.
   input parameters: -NONE--
   returns: --NONE--
*/
void Data::writeFile()
{
  ofstream outputFile;
  outputFile.open("output.csv");     //output filename specified here
  if(outputFile.is_open())
  {
    map<string, Record*>::iterator it;
    for(it = data.begin(); it != data.end(); it++)
    {
      outputFile << it->first << "," << it->second->maxTimeGap << ","
      << it->second->totalVolume << "," << it->second->avgPrice << ","
      << it->second->maxTradePrice << endl;
    }
  }
}

/* readFile() function reads the data from the specified file and parses it.
   After going through each row of the input file, it calls the process()
   function to process the data and update the record for each symbol.
   input parameters: -NONE--
   returns: --NONE--
*/
void Data::readFile()
{
  unsigned long int timestamp;
  int quantity, price;
  string symbol, inputLine, stimestamp, squantity, sprice;
  ifstream inputFile("input.csv");   //input filename specified here
  if(inputFile.is_open())
  {
    while(!getline(inputFile, inputLine).eof())
    {
      stringstream line(inputLine);
      getline(line, stimestamp,',');
      getline(line, symbol,',');
      getline(line, squantity,',');
      getline(line, sprice,',');
      quantity = stoi(squantity);
      price = stoi(sprice);
      timestamp = stol(stimestamp);
      process(symbol, timestamp, quantity, price);
    }
  }
  else
  {
      cout << "File does not exist" << endl;
  }
}

/* processMaxTime() function finds the new time gime gap between current and
   previous timestamp. It will then check if this gap is larger than the
   previously written maxTimeGap. The function returns the maxiumum of the 2
   compared elements.
   input parameters: previousTimeStamp, currentTimeStamp, currentMax
   returns: currentMax or newMax depending on which one is greater
*/
unsigned long int Data::processMaxTime(unsigned long int previousTimeStamp,
  unsigned long int currentTimeStamp, unsigned long int currentMax)
{
  unsigned long int newMax = currentTimeStamp - previousTimeStamp;
  if(newMax > currentMax)
  {
    return newMax;
  }
  return currentMax;
}

/* process() function processes each line of the input. It updates all the
   records of the corrosponding symbol viz. previousTimeStamp, quantityXPrice,
   avgPrice, totalVolume, maxTradePrice, maxTimeGap
   input parameters: symbol, t_timestamp, t_quantity, t_price
   returns: --NONE--
*/
void Data::process(string t_symbol, unsigned long int t_timestamp,
  int t_quantity, int t_price)
{
  if(data.count(t_symbol) == 0)
  {
    Record *rec = new Record();
    data.insert(pair<string, Record*>(t_symbol,rec));
  }
  map<string, Record*>::iterator it;
  it = data.find(t_symbol);

  if(it->second->flag == false)
  {
    it->second->maxTimeGap = processMaxTime(it->second->previousTimeStamp,
      t_timestamp, it->second->maxTimeGap);
  }
  else
  {
    it->second->flag = false;
  }

  it->second->previousTimeStamp = t_timestamp;

  it->second->quantityXPrice = it->second->quantityXPrice +
    (t_price*t_quantity);
  it->second->avgPrice= it->second->quantityXPrice/(it->second->totalVolume +
    t_quantity);


  it->second->totalVolume = it->second->totalVolume + t_quantity;

  if(t_price > it->second->maxTradePrice)
  {
    it->second->maxTradePrice = t_price;

  }
}
//end of file
