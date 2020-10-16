#include "Connector.h"
#include "quickfix/Session.h"
#include <iostream>
#include "quickfix/SessionSettings.h"
#include "quickfix/Log.h"
#include <string>
#include <vector>
using std::vector;

vector<float> bid_price;
vector<float> ask_price;
vector<float> bid_size;
vector<float> ask_size;

void Connector::onLogon( const FIX::SessionID& sessionID )
{
    std::cout << std::endl << "Logon - " << sessionID << std::endl;
}

void Connector::onLogout( const FIX::SessionID& sessionID )
{
    std::cout << std::endl << "Logout - " << sessionID << std::endl;
}

void Connector::fromApp( const FIX::Message& message, const FIX::SessionID& sessionID )
EXCEPT( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType )
{
    crack( message, sessionID );
    std::cout << std::endl << "IN: " << message << std::endl;
}
void Connector::fromAdmin( const FIX::Message& message, const FIX::SessionID& sessionID )
EXCEPT( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon ){
}

void Connector::toAdmin( FIX::Message& message, const FIX::SessionID& sessionID)
{
    if (FIX::MsgType_Logon == message.getHeader().getField(FIX::FIELD::MsgType))
    {
        FIX::Password fixpasswd = std::string("eSEMPHiajtPWk3ZvYXFx4MhziuzqIyRc"); //use your std::string password here.
        message.getHeader().setField(FIX::Password(fixpasswd)); //also add username here.
        FIX::Password fixusername = std::string("w8poYpKKww6gHqclxdzxYYcVnHODFnAz"); //use your std::string password here.
        message.getHeader().setField(FIX::Username(fixusername)); //also add username here.
    }
}

void Connector::toApp( FIX::Message& message, const FIX::SessionID& sessionID )
EXCEPT( FIX::DoNotSend )
{
    try
    {
        FIX::PossDupFlag possDupFlag;
        message.getHeader().getField( possDupFlag );
        if ( possDupFlag ) throw FIX::DoNotSend();
    }
    catch ( FIX::FieldNotFound& e)
    {
        //std::cout <<  e.what() << " " << message.toString() << ENDLINE;
    }
    std::cout << std::endl
              << "OUT: " << message << std::endl;
}

void Connector::onMessage
        ( const FIX44::ExecutionReport&, const FIX::SessionID& ) {}
void Connector::onMessage
        ( const FIX44::OrderCancelReject&, const FIX::SessionID& ) {}
void Connector::onMessage
        ( const FIX44::MarketDataSnapshotFullRefresh& mds, const FIX::SessionID& )
{
    // Get symbol name of the snapshot; e.g., EUR/USD. Our example only subscribes to EUR/USD so
    // this is the only possible value
    std::string symbol = mds.getField(FIX::FIELD::Symbol);
    // Declare variables for both the bid and ask prices. We will read the MarketDataSnapshotFullRefresh
    // message for tthese values
    // For each MDEntry in the message, inspect the NoMDEntries group for
    // the presence of either the Bid or Ask (Offer) type

    bid_price.clear();
    bid_size.clear();
    ask_size.clear();
    ask_price.clear();
    int entry_count = FIX::IntConvertor::convert(mds.getField(FIX::FIELD::NoMDEntries));
    for(int i = 1; i < entry_count; i++){
        FIX44::MarketDataSnapshotFullRefresh::NoMDEntries group;
        mds.getGroup(i,group);
        std::string entry_type = group.getField(FIX::FIELD::MDEntryType);
        if(entry_type == "0"){ // Bid
            bid_price.push_back(FIX::DoubleConvertor::convert(group.getField(FIX::FIELD::MDEntryPx)));
            bid_size.push_back(FIX::DoubleConvertor::convert(group.getField(FIX::FIELD::MDEntrySize)));
        }else if(entry_type == "1"){ // Ask (Offer)
            ask_price.push_back(FIX::DoubleConvertor::convert(group.getField(FIX::FIELD::MDEntryPx)));
            ask_size.push_back(FIX::DoubleConvertor::convert(group.getField(FIX::FIELD::MDEntrySize)));
        }
    }
    std::cout << "MarketDataSnapshotFullRefresh -> Symbol - " << symbol
         << " Bid - " << bid_price[0] << " Ask - " << ask_price[0] << std::endl;

    this->bookUpdated(bid_price,ask_price,bid_size,ask_size,entry_count, this->book,symbol);

}
void Connector::onMessage(const FIX44::MarketDataIncrementalRefresh& message, const FIX::SessionID &)
{
}

void Connector::MarketDataRequest(std::string ticker,std::string ID, char subscription)
{
    std::cout << "\nMarketDataRequest\n";
    FIX::MDReqID mdReqID(ID);
    FIX::SubscriptionRequestType subType( subscription );
    FIX::MarketDepth marketDepth( 4 );

    FIX44::MarketDataRequest::NoMDEntryTypes marketDataEntryGroup_bid;
    FIX::MDEntryType mdEntryType_bid( FIX::MDEntryType_BID );
    marketDataEntryGroup_bid.set( mdEntryType_bid );

    FIX44::MarketDataRequest::NoMDEntryTypes marketDataEntryGroup_ask;
    FIX::MDEntryType mdEntryType_offer( FIX::MDEntryType_OFFER );
    marketDataEntryGroup_ask.set( mdEntryType_offer );

//    FIX44::MarketDataRequest::NoMDEntryTypes marketDataEntryGroup_trade;
//    FIX::MDEntryType mdEntryType_trade( FIX::MDEntryType_TRADE );
//    marketDataEntryGroup_trade.set( mdEntryType_trade );


    FIX44::MarketDataRequest::NoRelatedSym symbolGroup;
    FIX::Symbol symbol( ticker );
    symbolGroup.set( symbol );

    FIX44::MarketDataRequest message( mdReqID, subType, marketDepth );
    message.addGroup( marketDataEntryGroup_bid );
    message.addGroup( marketDataEntryGroup_ask );
//    message.addGroup( marketDataEntryGroup_trade );
    message.addGroup( symbolGroup );

    message.getHeader().setField(FIX::SenderCompID(std::string("lpwp6653")));
    message.getHeader().setField(FIX::TargetCompID(std::string("BITSTAMP")));

    std::cout << message.toXML() << std::endl;
    std::cout << message.toString() << std::endl;

    FIX::Session::sendToTarget(message);
}
