#ifndef OPI_MYSQL_H_
#define OPI_MYSQL_H_

#include <stdint.h>
#include <mysql/mysql.h>
#include <string.h>
#include <cstring>
#include <sstream>
#include <iostream>
#include <fstream>
#include <ctime>
#include <stdlib.h>
#include <string.h>
#include <stdio.h> 
#include "OPI_Clock.h"
#include <semaphore.h>

class OPI_MYSQL
{
      public:
	   sem_t mutex, mutex2;
          //constructor
          OPI_MYSQL();
         
	  //destructor
	  ~OPI_MYSQL(); 


          //error reporting
          std::string getError();
          int getStatus();
          int reconnect();
          int ping();
          
          
          //connection factory
          bool connect(std::string server, std::string database, std::string user, std::string password);
          
          //query
          int query(std::string statement);
	  int query(std::string statement, bool once);
          
          //clean
        std::string _clean(const char* dataIn, int len);  
	std::string clean(std::string dirty_str);
          
          //get a row/advance
          int nextRow();    
          char * getData(int i);
          int getNumOfFields();
          bool isResult();
          int count();
          
          
          
          //get data back from results
          std::string getString(int i);        
          int getInt(int i);
          float getFloat(int i);
          
      private:
              
            //clean up
	    void cleanup();
	    //logging
            void log(std::string output);
            int logCount;
          
            //Database connection
            MYSQL * conn = new MYSQL();
            
            //login values
            char * server = new char[100];
            char * database = new char[100];
            char * user = new char[100];
            char * password = new char [100]; 
            
            std::string error;    
	//results
            MYSQL_RES *result;
            MYSQL_ROW row;
            unsigned long int *length;
		int numOfFields;
            int rowCount;
            bool Connected;
      
};

//logging
static std::ofstream logFile;
            
#endif
