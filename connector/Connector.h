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
#include "quickfix/fix44/MarketDataIncrementalRefresh.h"
#include "quickfix/fix44/MarketDataRequest.h"

#include <queue>

#include "Book.h"
#include <vector>
using std::vector;

class Connector :
        public FIX::Application,
        public FIX::MessageCracker
{
public:
    void MarketDataRequest(std::string ticker,std::string ID, char subscription);
    void (*bookUpdated)(BOOK*,std::string);
    void (*tradesUpdated)(LT*,std::string);

    BOOK* book;
    LT* last_trade;

    Connector(void (*bookUpdated)(BOOK*,std::string),
              void (*tradesUpdated)(LT*,std::string),
              BOOK * book, LT* last_trade){
        this ->bookUpdated = bookUpdated;
        this ->tradesUpdated = tradesUpdated;
        this ->book = book;
        this ->last_trade = last_trade;
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

};

#endif
