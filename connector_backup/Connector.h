/* -*- C++ -*- */

/****************************************************************************
** Copyright (c) 2001-2014
**
** This file is part of the QuickFIX FIX Engine
**
** This file may be distributed under the terms of the quickfixengine.org
** license as defined by quickfixengine.org and appearing in the file
** LICENSE included in the packaging of this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** See http://www.quickfixengine.org/LICENSE for licensing information.
**
** Contact ask@quickfixengine.org if any conditions of this licensing are
** not clear to you.
**
****************************************************************************/

#ifndef TRADECLIENT_APPLICATION_H
#define TRADECLIENT_APPLICATION_H

#include "quickfix/Application.h"
#include "quickfix/MessageCracker.h"
#include "quickfix/Values.h"
#include "quickfix/Mutex.h"


#include "quickfix/fix44/NewOrderSingle.h"
#include "quickfix/fix44/ExecutionReport.h"
#include "quickfix/fix44/OrderCancelRequest.h"
#include "quickfix/fix44/OrderCancelReject.h"
#include "quickfix/fix44/OrderCancelReplaceRequest.h"
#include "quickfix/fix44/MarketDataRequestReject.h"
#include "quickfix/fix44/MarketDataSnapshotFullRefresh.h"
#include "quickfix/fix44/MarketDataRequest.h"

#include <queue>

#include "Book.h"

class Connector :
        public FIX::Application,
        public FIX::MessageCracker
{
public:
    void run();
    void (*bookUpdated)(double[MAX_BOOK_DEPTH],double[MAX_BOOK_DEPTH],int[MAX_BOOK_DEPTH],int[MAX_BOOK_DEPTH],int);
    void (*tradesUpdated)(double[MAX_BOOK_DEPTH],int);

    Connector(void (*bookUpdated)(double[MAX_BOOK_DEPTH],double[MAX_BOOK_DEPTH],int[MAX_BOOK_DEPTH],int[MAX_BOOK_DEPTH],int),void (*tradesUpdated)(double[MAX_BOOK_DEPTH],int)){
        this ->bookUpdated = bookUpdated;
        this ->tradesUpdated = tradesUpdated;
    }

private:
    void onCreate( const FIX::SessionID& ) {}
    void onLogon( const FIX::SessionID& sessionID );
    void onLogout( const FIX::SessionID& sessionID );
    void toAdmin( FIX::Message&, const FIX::SessionID& );
    void toApp( FIX::Message&, const FIX::SessionID& )
    EXCEPT( FIX::DoNotSend );
    void fromAdmin( const FIX::Message&, const FIX::SessionID& )
    EXCEPT( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon );
    void fromApp( const FIX::Message& message, const FIX::SessionID& sessionID )
    EXCEPT( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType );

    void onMessage( const FIX44::ExecutionReport&, const FIX::SessionID& );
    void onMessage( const FIX44::OrderCancelReject&, const FIX::SessionID& );
    void onMessage( const FIX44::MarketDataSnapshotFullRefresh&, const FIX::SessionID& );
    void onMessage( const FIX44::MarketDataIncrementalRefresh&, const FIX::SessionID& );

    void queryEnterOrder();
    void queryCancelOrder();
    void queryReplaceOrder();
    void queryMarketDataRequest(std::string ticker);

    FIX44::NewOrderSingle queryNewOrderSingle44();
    FIX44::OrderCancelRequest queryOrderCancelRequest44();
    FIX44::OrderCancelReplaceRequest queryCancelReplaceRequest44();
    FIX44::MarketDataRequest queryMarketDataRequest44(std::string ticker);



};

#endif
