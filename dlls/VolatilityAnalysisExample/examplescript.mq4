#import "priceplotwrapper.dll"
   string read_python_file(string file_path);
   void execute_python_code(string python_code);
#import

int OnInit() {
   EventSetTimer(1);  // Update every second
   return(INIT_SUCCEEDED);
}

void OnTimer() {
   double currentPrice = SymbolInfoDouble(_Symbol, SYMBOL_BID);
   string fileName = "price_data.txt";
   int handle = FileOpen(fileName, FILE_WRITE|FILE_TXT);
   if (handle != INVALID_HANDLE) {
      FileWrite(handle, DoubleToString(currentPrice, 5));
      FileClose(handle);
   } else {
      Print("Failed to open file for writing");
   }
}

void OnDeinit(const int reason) {
   EventKillTimer();
}
