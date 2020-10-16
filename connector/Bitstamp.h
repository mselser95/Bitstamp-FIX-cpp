//
// Created by matias on 10/16/20.
//

#ifndef TEST_BITSTAMP_H
#define TEST_BITSTAMP_H

#include "Connector.h"
#include "quickfix/Session.h"
#include <iostream>
#include "quickfix/FileStore.h"
#include "quickfix/SocketInitiator.h"
#include <quickfix/SSLSocketInitiator.h>
#include "quickfix/SessionSettings.h"
#include "quickfix/Log.h"
#include <string>
#include <fstream>

#include "Book.h"
#include <vector>
using std::vector;

void bookUpdated(vector<float>,vector<float>,vector<float>,vector<float>,int,BOOK*,std::string);
void tradesUpdated(vector<float>,double,BOOK*,std::string);

class Bitstamp {
public:

    FIX::Initiator * initiator;
    FIX::SessionSettings settings;
    Connector * application = 0;

    char connect(void);
    Bitstamp(BOOK * book){
        this -> initiator = 0;
        this -> settings = FIX::SessionSettings("config/tradeclient.cfg");
        this -> application = new(Connector){bookUpdated,tradesUpdated,book};
    }

    void get_streaming_data(std::string ticker,std::string ID);
    void stop_streaming_data(std::string ticker,std::string ID);
};


#endif //TEST_BITSTAMP_H


//Bitstamp(void (*bookUpdated)(int),void (*tradesUpdated)(int)){
//    this -> initiator = 0;
//    this -> settings = FIX::SessionSettings("config/tradeclient.cfg");
//    this ->application = new(Connector){bookUpdated,tradesUpdated};
//}
