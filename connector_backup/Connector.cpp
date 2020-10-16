#include "Connector.h"
#include "quickfix/Session.h"
#include <iostream>
#include "quickfix/SessionSettings.h"
#include "quickfix/Log.h"
#include <string>


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
    double bid_price[100];
    double ask_price[100];
    int bid_size[100];
    int ask_size[100];
    // For each MDEntry in the message, inspect the NoMDEntries group for
    // the presence of either the Bid or Ask (Offer) type
    int entry_count = FIX::IntConvertor::convert(mds.getField(FIX::FIELD::NoMDEntries));
    for(int i = 1; i < entry_count; i++){
        FIX44::MarketDataSnapshotFullRefresh::NoMDEntries group;
        mds.getGroup(i,group);
        std::string entry_type = group.getField(FIX::FIELD::MDEntryType);
        if(entry_type == "0"){ // Bid
            bid_price[i-1] = FIX::DoubleConvertor::convert(group.getField(FIX::FIELD::MDEntryPx));
            bid_size[i-1]  = FIX::IntConvertor::convert(group.getField(FIX::FIELD::MDEntrySize));
        }else if(entry_type == "1"){ // Ask (Offer)
            ask_price[i-1] = FIX::DoubleConvertor::convert(group.getField(FIX::FIELD::MDEntryPx));
            ask_size[i-1]  = FIX::IntConvertor::convert(group.getField(FIX::FIELD::MDEntrySize));
        }
    }
    std::cout << "MarketDataSnapshotFullRefresh -> Symbol - " << symbol
         << " Bid - " << bid_price[0] << " Ask - " << ask_price[0] << std::endl;

    this->bookUpdated(bid_price,ask_price,bid_size,ask_size,entry_count);

}
void Connector::onMessage(const FIX44::MarketDataIncrementalRefresh& message, const FIX::SessionID &)
{
}

//void Connector::run()
//{
//    try
//    {
////                queryEnterOrder();
////                queryCancelOrder();
////                queryReplaceOrder();
//        queryMarketDataRequest();
//        while (1){}
//    }
//    catch ( std::exception & e )
//    {
//        std::cout << "Message Not Sent: " << e.what();
//    }
//}

void Connector::queryEnterOrder()
{
    std::cout << "\nNewOrderSingle\n";
    FIX::Message order;
    order = queryNewOrderSingle44();
    FIX::Session::sendToTarget( order );
}

void Connector::queryCancelOrder()
{
    std::cout << "\nOrderCancelRequest\n";
    FIX::Message cancel;
    cancel = queryOrderCancelRequest44();
    FIX::Session::sendToTarget( cancel );
}

void Connector::queryReplaceOrder()
{
    std::cout << "\nCancelReplaceRequest\n";
    FIX::Message replace;
    replace = queryCancelReplaceRequest44();
    FIX::Session::sendToTarget( replace );
}

void Connector::queryMarketDataRequest(std::string ticker)
{
    std::cout << "\nMarketDataRequest\n";
    FIX::MDReqID mdReqID( "MARKETDATAID" );
    FIX::SubscriptionRequestType subType( FIX::SubscriptionRequestType_SNAPSHOT_PLUS_UPDATES );
    FIX::MarketDepth marketDepth( 4 );

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

//    queryHeader( message.getHeader() );

    std::cout << message.toXML() << std::endl;
    std::cout << message.toString() << std::endl;


//    FIX::Message md;
//
//
//    md = queryMarketDataRequest44(ticker);

    FIX::Session::sendToTarget(message);
}

FIX44::NewOrderSingle Connector::queryNewOrderSingle44()
{
//    FIX::OrdType ordType;
//
//    FIX44::NewOrderSingle newOrderSingle(
//            queryClOrdID(), querySide(),
//            FIX::TransactTime(), ordType = queryOrdType() );
//
//    newOrderSingle.set( FIX::HandlInst('1') );
//    newOrderSingle.set( querySymbol() );
//    newOrderSingle.set( queryOrderQty() );
//    newOrderSingle.set( queryTimeInForce() );
//    if ( ordType == FIX::OrdType_LIMIT || ordType == FIX::OrdType_STOP_LIMIT )
//        newOrderSingle.set( queryPrice() );
//    if ( ordType == FIX::OrdType_STOP || ordType == FIX::OrdType_STOP_LIMIT )
//        newOrderSingle.set( queryStopPx() );
//
//    queryHeader( newOrderSingle.getHeader() );
//    return newOrderSingle;
}

FIX44::OrderCancelRequest Connector::queryOrderCancelRequest44()
{
//    FIX44::OrderCancelRequest orderCancelRequest( queryOrigClOrdID(),
//                                                  queryClOrdID(), querySide(), FIX::TransactTime() );
//
//    orderCancelRequest.set( querySymbol() );
//    orderCancelRequest.set( queryOrderQty() );
//    queryHeader( orderCancelRequest.getHeader() );
//    return orderCancelRequest;
}

FIX44::OrderCancelReplaceRequest Connector::queryCancelReplaceRequest44()
{
//    FIX44::OrderCancelReplaceRequest cancelReplaceRequest(
//            queryOrigClOrdID(), queryClOrdID(),
//            querySide(), FIX::TransactTime(), queryOrdType() );
//
//    cancelReplaceRequest.set( FIX::HandlInst('1') );
//    cancelReplaceRequest.set( querySymbol() );
//    if ( queryConfirm( "New price" ) )
//        cancelReplaceRequest.set( queryPrice() );
//    if ( queryConfirm( "New quantity" ) )
//        cancelReplaceRequest.set( queryOrderQty() );
//
//    queryHeader( cancelReplaceRequest.getHeader() );
//    return cancelReplaceRequest;
}
FIX44::MarketDataRequest Connector::queryMarketDataRequest44(std::string ticker)
{
    FIX::MDReqID mdReqID( "MARKETDATAID" );
    FIX::SubscriptionRequestType subType( FIX::SubscriptionRequestType_SNAPSHOT_PLUS_UPDATES );
    FIX::MarketDepth marketDepth( 4 );

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

//    queryHeader( message.getHeader() );

    std::cout << message.toXML() << std::endl;
    std::cout << message.toString() << std::endl;

    return message;
}

void Connector::run()
{
    queryMarketDataRequest("BTC/USD");
//    while(1){}

}

//void Connector::connect()
//{
//    while ( true )
//    {
//        try
//        {
//            char action = queryAction();
//
//            if ( action == '1' )
//                queryEnterOrder();
//            else if ( action == '2' )
//                queryCancelOrder();
//            else if ( action == '3' )
//                queryReplaceOrder();
//            else if ( action == '4' )
//                queryMarketDataRequest();
//            else if ( action == '5' )
//                break;
//        }
//        catch ( std::exception & e )
//        {
//            std::cout << "Message Not Sent: " << e.what();
//        }
//    }
//}