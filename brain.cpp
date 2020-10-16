
#include "connector/Bitstamp.h"
#include "Book.h"
#include <time.h>

int main( int argc, char** argv )
{
    BOOK* book = new (BOOK);
    Bitstamp bitstamp_connector = Bitstamp(book);

    bitstamp_connector.connect();
    bitstamp_connector.get_streaming_data("BTC/USD","1");
    bitstamp_connector.get_streaming_data("ETH/USD","2");
    bitstamp_connector.get_streaming_data("LTC/USD","3");

    sleep(5);
    bitstamp_connector.stop_streaming_data("BTC/USD","1");
    bitstamp_connector.stop_streaming_data("ETH/USD","2");
    bitstamp_connector.stop_streaming_data("LTC/USD","3");





    while (1){
        int a = 1;
    }

}
