//+------------------------------------------------------------------+
//|                                     Order Closing Tool (MT4).mq4 |
//|                        Copyright 2023, MetaQuotes Software Corp. |
//|                                             https://www.mql5.com |
//+------------------------------------------------------------------+
#property copyright "Copyright 2023, MetaQuotes Software Corp."
#property link      "https://www.mql5.com"
#property version   "1.00"
#property strict
#include <stdlib.mqh>
#include <stderror.mqh>
//+------------------------------------------------------------------+
//| Script program start function                                    |
//+------------------------------------------------------------------+
void OnStart()
  {
   if(OrdersTotal() < 0){
     MessageBox("Script Closed Because No Trades Are Detected");
   }
   else if(!IsExpertEnabled())
     {
      MessageBox("You need to enable AutoTrading", "Please Enable AutoTrading");
      Comment(WindowExpertName(), "is NOT Running because you have AutoTrading Disabled");
      ExpertRemove();
     }
     else{
      CloseSellOrders();
      CloseBuyOrders();
    }//End of Else Bracket//
   
  }//End of On Start Function
//+------------------------------------------------------------------+


void CloseSellOrders(){

   for(int i=0; i < OrdersTotal(); i++){
        if(OrderSelect(i, SELECT_BY_POS, MODE_TRADES)){
           if(OrderSymbol() == Symbol())
            if(OrderType() == (OP_SELL)){
               int attempts = 1;
               while (attempts <=5){
                  int err = 0;
                  bool result = OrderClose(OrderTicket(), OrderLots(),Ask, 30, Red);
                  if(result){
                  i--;
                  break;  
                 }
                 else{
                  err = GetLastError();
                  Print("Last Error = ", ErrorDescription(err));
                  MessageBox("Unable To Close Orders Due to Error: " + ErrorDescription(err), "Unable To Close Trade");
                  if(err==4108)break; //Error 4108: Invalid Ticket, meaning Trade Order does not exist
                  switch(err){
                     case 135: //Price Changed before script could close the Trade Order//
                     case 136: //Off Quotes//
                     case 137: //Broker Server is Busy//
                     case 138: //Requote on Price Feed     
                     case 146: //Trade Context is Busy
                     Sleep(1000);
                     RefreshRates(); //Will Refresh the Symbols Quote Price Data when While loop Closes a Trade//
                     default: break; //Default to break out of the switch loop//
                  
                     }//End of The Switch Bracket//
                    
                   }//End of Else Statement
                   
                 }//While Loop Closing Bracket
               
               }//OP_SELL Closing Bracket 
       
        }//Order Select Closing Bracket
   
      }//End of For Loop Bracket

}//End of Function


void CloseBuyOrders(){

   for(int i=0; i < OrdersTotal(); i++){
        if(OrderSelect(i, SELECT_BY_POS, MODE_TRADES)){
           if(OrderSymbol() == Symbol())
            if(OrderType() == OP_BUY){
               int attempts = 1;
               while (attempts <=5){
                  int err = 0;
                  bool result = OrderClose(OrderTicket(), OrderLots(),Bid, 30, Red);
                  if(result){
                  i--;
                  break;  
                 }
                 else{
                  err = GetLastError();
                  Print("Last Error = ", ErrorDescription(err));
                  MessageBox("Unable To Close Orders Due to Error: " + ErrorDescription(err), "Unable To Close Trade");
                  if(err==4108)break; //Error 4108: Invalid Ticket, meaning Trade Order does not exist
                  switch(err){
                     case 135: //Price Changed before script could close the Trade Order//
                     case 136: //Off Quotes//
                     case 137: //Broker Server is Busy//
                     case 138: //Requote on Price Feed     
                     case 146: //Trade Context is Busy
                     Sleep(1000);
                     RefreshRates(); //Will Refresh the Symbols Quote Price Data when While loop Closes a Trade//
                     default: break; //Default to break out of the switch loop//
                  
                     }//End of The Switch Bracket//
                    
                   }//End of Else Statement
                   
                 }//While Loop Closing Bracket
               
               }//OP_BUY Closing Bracket 
       
        }//Order Select Closing Bracket
   
      }//End of For Loop Bracket

}//End of Function
