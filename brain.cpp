
#include "connector/Bitstamp.h"
#include "Book.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void exception_handler(int s){
    printf("Caught signal %d\n",s);
    exit(1);

}
int main( int argc, char** argv )
{
    BOOK* book = new (BOOK);
    LT * last_trade = new(LT);
    Bitstamp bitstamp_connector = Bitstamp(book,last_trade);

    bitstamp_connector.connect();

//    bitstamp_connector.get_streaming_data("BTC/USD","1");
//    bitstamp_connector.get_streaming_data("ETH/USD","2");
//    bitstamp_connector.get_streaming_data("LTC/USD","3");
//    sleep(5);
//    bitstamp_connector.stop_streaming_data("BTC/USD","1");
//    bitstamp_connector.stop_streaming_data("ETH/USD","2");
//    bitstamp_connector.stop_streaming_data("LTC/USD","3");

    bitstamp_connector.send_market_order("BTC/USD","SELL",0.0001);
    sleep(5);



    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = exception_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
    pause();
    return 0;
}

