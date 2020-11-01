//
// Created by matias on 10/16/20.
//

#ifndef TEST_BITSTAMP_H
#define TEST_BITSTAMP_H

#include "connector/fix/Connector.h"
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

void bookUpdated(BOOK*,std::string);
void tradesUpdated(LT*,std::string);

class Bitstamp {
public:

    FIX::Initiator * initiator;
    FIX::SessionSettings settings;
    Connector * application = 0;
    char connect(void);
    Bitstamp(BOOK * book,LT * last_trade){
        this -> initiator = 0;
        this -> settings = FIX::SessionSettings("config/tradeclient.cfg");
        this -> application = new(Connector){bookUpdated,tradesUpdated,book,last_trade};
    }

    void get_streaming_data(std::string ticker,std::string ID);
    void stop_streaming_data(std::string ticker,std::string ID);
    void send_market_order(std::string ticker,std::string side,double qty);
    void send_limit_order(std::string ticker,std::string side,double px,double qty);

};


#endif //TEST_BITSTAMP_H
