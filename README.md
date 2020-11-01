# Bitstamp Fix Connector

This repository is an example of a FIX connnector with Bitstamp. It connects vía fix API to the exchange to get real time market data and send orders.

## Install

The main dependency here is quickfix.


MAKE SURE YOU COMPILE QUICKFIX WITH SSL SUPPORT!!!!

https://github.com/quickfix/quickfix/blob/master/README.SSL


### INTRODUCTION

This document describes the rudimentary SSL functionality available in QuickFIX. OpenSSL (https://www.openssl.org/) has been used to provide the SSL functionality. The QuickFIX library can be built with OpenSSL or it can be built without OpenSSL support and the classes (files) related to the SSL functionality used directly in the user project.

### BUILDING QUICKFIX WITH OPENSSL SUPPORT

1. Unix

$ ./configure --with-openssl="path to openssl install"

"path to openssl install" dir should have include/openssl and lib directories with appropriate files. If no path is specified, then the default openssl installation is used.

$ make

## Run
In config/tradeclient.cfg:

    [DEFAULT]
    ...
    DataDictionary="[PATH_TO_QUICKFIX]/spec/FIX44.xml"
    ...
    


    [SESSION]
    ...
    SenderCompID="YOUR USERNAME ID"
    ...
    AppataDictionary="[PATH_TO_QUICKFIX]/spec/FIX44.xml"
    ...
    

SenderCompID is the username BITSTAMP assigns you when you register.

In connector/Connector.cpp:

        FIX::Password fixpasswd = std::string("YOUR API SECRET"); //use your std::string password here.
        message.getHeader().setField(FIX::Password(fixpasswd)); //also add username here.
        FIX::Password fixusername = std::string("YOUR API KEY"); //use your std::string password here.
        message.getHeader().setField(FIX::Username(fixusername)); //also add username here.

and

        message.getHeader().setField(FIX::SenderCompID(std::string("YOUR USERNAME ID")));

You have to replace your API KEY, API SECRET and USERNAME ID


This is a CMake project so you should be able to compile it and run it with CMake.

Any contribution to this project is welcome.