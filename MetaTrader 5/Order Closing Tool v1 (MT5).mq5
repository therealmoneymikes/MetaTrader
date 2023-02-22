//+------------------------------------------------------------------+
//|                                  Order Closing Tool v1 (MT5).mq5 |
//|                                  Copyright 2023, Michael Roberts.|
//|                 https://github.com/therealmoneymikes/MetaTrader |
//+------------------------------------------------------------------+
#property copyright "Copyright 2023, Michael Roberts."
#property link      "https://github.com/therealmoneymikes/MetaTrader4"
#property version   "1.00"

//Trade Library to derive attributes of trade//
#include <Trade\Trade.mqh>


//+------------------------------------------------------------------+
//| Script program start function                                    |
//+------------------------------------------------------------------+
void OnStart()
  {
   CloseTrades();
   
  }
//+------------------------------------------------------------------+

void CloseTrades(){
   CTrade Trade;
   for(int i=0; i<PositionsTotal(); i++){
       ulong Ticket = PositionGetTicket(i);
         if(!Trade.PositionClose(Ticket, ULONG_MAX)){
           Print("Position Close Error", Trade.ResultRetcode());
           return;
         }
      else{
      i--;
      MessageBox("All Trades have successfully closed with Order Closing Tool! ", "Closing Status",1);
      }
   }

}
  
 






