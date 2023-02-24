//+------------------------------------------------------------------+
//|                                  Order Closing Tool v1 (MT5).mq5 |
//|                                  Copyright 2023, Michael Roberts.|
//|                 https://github.com/therealmoneymikes/MetaTrader |
//+------------------------------------------------------------------+
#property copyright "Copyright 2023, Michael Roberts."
#property link      "https://github.com/therealmoneymikes/MetaTrader4"
#property version   "1.00"

//Trade Library to derive attributes of trade, available as part of the standard MetaTrader 5 library//
#include <Trade\Trade.mqh>


//+------------------------------------------------------------------+
//| Script program start function                                    |
//+------------------------------------------------------------------+

//Called the CloseTrades() Function within the default OnStart() Function which will be initiated when the file is dragged and dropped unto a chart//
void OnStart()
  {
   CloseTrades();
   
  }
//+------------------------------------------------------------------+

void CloseTrades(){
   CTrade Trade;//To access the properties of the Trade calls I have initiated a new instance of the class//
   //The for loop, loops over the Total number of open positions//
   //i is initiated to 0. For trade positions, trade positions are stored in a SERIES Array meaning the array is REVERSE Index, i.e = 0 is the most recent trade//
   //Created a variable called Ticket which stores the results of the PositionsGetTicket() Function which gets the Ticket by index of i, e.g 3 tickets i= 0,1,2//
   //the dot notation allows us to access the Position Close function, the two arguements Ticket is for the ticket selected by the for loop//
   //ULONG_MAX is 2nd arguement in function because it represent the maximum ULONG Ticket value possible since the Ticket variable has been set as ulong variable//
   //The not operand, !, in essence says if you are not able to close a ticket at maximum Ulong, print an error on the terminal//
   //The ResultRetcode() function also use to get the error code for why closing a trade is not possible//
   for(int i=0; i<PositionsTotal(); i++){
       ulong Ticket = PositionGetTicket(i);
         if(!Trade.PositionClose(Ticket, ULONG_MAX)){
           Print("Position Close Error", Trade.ResultRetcode());
           return;
         }
      else{
      i--;
      //The Message Box here is simply a UI Tool which lets the user know with a simple message box that closed//
      MessageBox("All Trades have successfully closed with Order Closing Tool! ", "Closing Status",1);
      }
   }

}
  
 






