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


LT last_tradee;

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
//    std::cout << std::endl << "IN: " << message << std::endl;
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
        ( const FIX44::ExecutionReport& message, const FIX::SessionID& ) {
    std::cout << "ExecutionReport -> " << std::endl;
    std::cout << "  ClOrdID -> " << message.getField(FIX::FIELD::ClOrdID) << std::endl;
    std::cout << "  Account -> " << message.getField(FIX::FIELD::Account) << std::endl;
    std::cout << "  OrderID -> " << message.getField(FIX::FIELD::OrderID) << std::endl;
    std::cout << "  LastQty -> " << message.getField(FIX::FIELD::LastQty) << std::endl;
    std::cout << "  CumQty -> " << message.getField(FIX::FIELD::CumQty) << std::endl;
    std::cout << "  ExecType -> " << message.getField(FIX::FIELD::ExecType) << std::endl;
    std::cout << "  OrdStatus -> " << message.getField(FIX::FIELD::OrdStatus) << std::endl;
    // ** Note on order status. **
    // In order to determine the status of an order, and also how much an order is filled, we must
    // use the OrdStatus and CumQty fields. There are 3 possible final values for OrdStatus: Filled (2),
    // Rejected (8), and Cancelled (4). When the OrdStatus field is set to one of these values, you know
    // the execution is completed. At this time the CumQty (14) can be inspected to determine if and how
    // much of an order was filled.
}
void Connector::onMessage
        ( const FIX44::OrderCancelReject&, const FIX::SessionID& ) {}
void Connector::onMessage
        ( const FIX44::MarketDataSnapshotFullRefresh& mds, const FIX::SessionID& )
{

    std::string symbol = mds.getField(FIX::FIELD::Symbol);

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

    this->book->ask_price.clear();
    this->book->bid_price.clear();
    this->book->ask_size.clear();
    this->book->bid_size.clear();
    for(int i = 0; i < entry_count/2; i++){
        this->book->ask_price.push_back(ask_price[i]);
        this->book->bid_price.push_back(bid_price[i]);
        this->book->ask_size.push_back(ask_size[i]);
        this->book->bid_size.push_back(bid_size[i]);
    }
    this->bookUpdated(this->book,symbol);

}
void Connector::onMessage(const FIX44::MarketDataIncrementalRefresh& message, const FIX::SessionID &)
{
    FIX::NoMDEntries noMDEntries;
    message.get(noMDEntries);
    if (noMDEntries.getValue()!=1){
        std::cout << "NoMDEntries in MarketDataIncrementalRefresh is not 1!" <<std::endl;
        return;
    }
    FIX44::MarketDataIncrementalRefresh::NoMDEntries group;
    message.getGroup(1, group);

    FIX::MDEntryID entryID; group.get(entryID);
    FIX::MDUpdateAction action; group.get(action);
    FIX::Symbol symbol;
    if(group.isSet(symbol)){
        group.get(symbol);
    }

    FIX::MDEntryPx price;
    if(group.isSet(price)) {
        group.get(price);
    }
    FIX::MDEntrySize qty;
    if(group.isSet(qty)) {
        group.get(qty);
    }
    last_trade ->px = price.getValue();
    last_trade ->qty = qty.getValue();
    this ->tradesUpdated(last_trade,symbol.getString());
}

void Connector::MarketDataRequest(std::string ticker,std::string ID, char subscription)
{
    std::cout << "\nMarketDataRequest\n";
    FIX::MDReqID mdReqID(ID);
    FIX::SubscriptionRequestType subType( subscription );
    FIX::MarketDepth marketDepth( 0 );

    FIX44::MarketDataRequest::NoMDEntryTypes marketDataEntryGroup_bid;
    FIX::MDEntryType mdEntryType_bid( FIX::MDEntryType_BID );
    marketDataEntryGroup_bid.set( mdEntryType_bid );

    FIX44::MarketDataRequest::NoMDEntryTypes marketDataEntryGroup_ask;
    FIX::MDEntryType mdEntryType_offer( FIX::MDEntryType_OFFER );
    marketDataEntryGroup_ask.set( mdEntryType_offer );

    FIX44::MarketDataRequest::NoMDEntryTypes marketDataEntryGroup_trade;
    FIX::MDEntryType mdEntryType_trade( FIX::MDEntryType_TRADE );
    marketDataEntryGroup_trade.set( mdEntryType_trade );


    FIX44::MarketDataRequest::NoRelatedSym symbolGroup;
    FIX::Symbol symbol( ticker );
    symbolGroup.set( symbol );

    FIX44::MarketDataRequest message( mdReqID, subType, marketDepth );
    message.addGroup( marketDataEntryGroup_bid );
    message.addGroup( marketDataEntryGroup_ask );
    message.addGroup( marketDataEntryGroup_trade );
    message.addGroup( symbolGroup );

    message.getHeader().setField(FIX::SenderCompID(std::string("lpwp6653")));
    message.getHeader().setField(FIX::TargetCompID(std::string("BITSTAMP")));

    FIX::Session::sendToTarget(message);
    FIX::Session::sendToTarget(message, this->sessionID);
}

void Connector::SendOrder(std::string ticker,std::string side,std::string type,double px,double qty){
    char s = 0, t = 0;
    if (!side.compare("BUY")){
        s = FIX::Side_BUY;
    }
    else if (!side.compare("SELL")){
        s = FIX::Side_SELL;
    }
    if (!type.compare("MARKET")){
        t = FIX::OrdType_MARKET;
    }
    else if (!type.compare("LIMIT")){
        t = FIX::OrdType_LIMIT;
    }
    FIX44::NewOrderSingle request;
    request.setField(FIX::ClOrdID(NextRequestID()));
    request.setField(FIX::Symbol(ticker));
    request.setField(FIX::Side(s));
    request.setField(FIX::TransactTime());
    request.setField(FIX::Price(px));
    //    request.setField(FIX::OrderQty(qty));
    request.setField(FIX::OrderQty(0));
    request.setField(FIX::OrdType(t));
    request.setField(FIX::TimeInForce(FIX::TimeInForce_GOOD_TILL_CANCEL));
    FIX::Session::sendToTarget(request,this->sessionID);
}

std::string Connector::NextRequestID(void)
{
    if(requestID == 65535)
        requestID = 1;
    requestID++;
    std::string next_ID = FIX::IntConvertor::convert(requestID);
    return next_ID;
}
