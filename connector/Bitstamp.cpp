//
// Created by matias on 10/16/20.
//

#include "quickfix/FileStore.h"
#include "quickfix/FileLog.h"
#include <quickfix/SSLSocketInitiator.h>
#include <string>
#include <iostream>
#include <vector>
using std::vector;

#include "Bitstamp.h"


void bookUpdated(BOOK* Book,std::string ticker) {
    std::cout << "TOP OF BOOK FOR " << ticker << ":" << std::endl
    <<"Ask px: "<< Book->ask_price [0]<< "\t"
    <<"Ask size: "<< Book->ask_size [0]<< "\t"
    <<"Bid px: "<< Book->bid_price [0]<< "\t"
    <<"Bid size: "<< Book->bid_size [0]<< "\t"
    << std::endl;
}

void tradesUpdated(LT* last_trade,std::string ticker) {
    std::cout << "LAST TRADE FOR " << ticker << ": Px: " << last_trade->px << " Qty: " << last_trade->qty << std::endl;
}


char Bitstamp::connect(void){
    try
    {
        FIX::FileStoreFactory storeFactory(settings);
        FIX::FileLogFactory logFactory( settings );
        this->initiator = new FIX::SSLSocketInitiator ( *this->application, storeFactory, this->settings,logFactory);
        this->initiator->start();
        while(!this->initiator->isLoggedOn());
    }
    catch ( std::exception & e )
    {
        std::cout << e.what();
        delete this->initiator;
        return 1;
    }
}

void Bitstamp::get_streaming_data(std::string ticker,std::string ID){
    this -> application->MarketDataRequest(ticker,ID,'1');
}
void Bitstamp::stop_streaming_data(std::string ticker,std::string ID){
    this -> application->MarketDataRequest(ticker,ID,'2');
}

void Bitstamp::send_market_order(std::string ticker,std::string side,double qty){
    this -> application ->SendOrder(ticker,side,"MARKET",0,qty);
}
void Bitstamp::send_limit_order(std::string ticker,std::string side,double px,double qty){
    this -> application ->SendOrder(ticker,side,"LIMIT",px,qty);
}
