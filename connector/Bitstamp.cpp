//
// Created by matias on 10/16/20.
//

#include "quickfix/FileStore.h"
#include <quickfix/SSLSocketInitiator.h>
#include <string>
#include <iostream>
#include <vector>
using std::vector;

#include "Bitstamp.h"


void bookUpdated(vector<float> bid_price, vector<float> ask_price, vector<float> bid_size, vector<float> ask_size,
                 int entries_size,BOOK* Book,std::string ticker) {

    Book->ask_price.clear();
    Book->bid_price.clear();
    Book->ask_size.clear();
    Book->bid_size.clear();
    for(int i = 0; i < entries_size/2; i++){

        Book->ask_price.push_back(ask_price[i]);
        Book->bid_price.push_back(bid_price[i]);
        Book->ask_size.push_back(ask_size[i]);
        Book->bid_size.push_back(bid_size[i]);
    }
}

void tradesUpdated(vector<float>,double,BOOK*,std::string) {

}


char Bitstamp::connect(void){
    try
    {
        FIX::FileStoreFactory storeFactory(settings);
//        FIX::ScreenLogFactory logFactory( settings );
//        initiator = new FIX::SSLSocketInitiator ( application, storeFactory, settings, logFactory );
        this->initiator = new FIX::SSLSocketInitiator ( *this->application, storeFactory, this->settings);
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