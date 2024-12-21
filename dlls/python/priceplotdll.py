import matplotlib.pyplot as plt
import numpy as np
import matplotlib.animation as animation
import time
from collections import deque
import logging



ea_price_file = "ea_price_data.txt"
ea_price_log_file = "ea_price_data_errorlog.txt"
logging.basicConfig(level=logging.ERROR,  format="%(asctime)s - %(levelname)s - %(message)s")

def read_price_from_ea():
    try:
        with open(ea_price_file, "r") as file:
            price = float(file.read().strip())
        return price
    except Exception as e:
        logging.error(f"Error: Unable to read price file: {e}")
        with open(ea_price_log_file, "w") as file:
            file.write(str(e))
        return None
    
#For memory optimisation you can use deque to limit the amount price you need if you prefer
 
#prices = deque(maxlen=24)
#timestamps = deque(maxlen=24)

prices = [] # Storing data in a set 
timestamps = [] #Sore the time series - Remeber is reverse index, index = 0 is the latest price


# Mathplotlib figure  and axis setup
fig, ax = plt.subplots()

def handle_data_plot(dataframe, timefilter: int = 24):
    current_price = read_price_from_ea() # Get the current price from the area
    if current_price is not None:
        prices.append(current_price)
        timestamps.append(time.strftime("%H:%M:%S"))
        
        #My filter is the last 24 H1 Candles meaning 
        #Think about your EA strategy to understand the number of price to read
        if len(prices) > timefilter:
            prices.pop(0)
            timestamps.pop(0)
            
    #  Math Plot
    ax.clear() #Clear the previous plot if there is one
    ax.plot(timestamps, prices, marker="ea", label="Price")
    ax.set_title("Current Price Feed Data", fontsize=16, fontweight="italic")
    ax.set_xlabel("Time (X-axis)", fontsize=12) #Set the X axis label
    ax.set_ylabel("Price (Y-axis)", fontsize=12) #Set the Y axis label
    ax.grid(True, which="both", linestyle="--", linewidth=0.7)#Max our plot a grid for better trend maps
    
    #Only adjust we have prices in the prices list
    if prices:
    #Because the amount of price may vary we can dynamically ajust the Y-axis size to fit the data
        ax.set_ylim(min(prices) * 0.90, max(prices) * 1.10)
    ax.legend()
    plt.xticks(rotation=60)
    plt.tight_layout()
    
    
    
# set_animation = animation.FuncAnimation(fig, handle_data_plot, interval=1000, linestyle="--", color="lightgray") 
#Updating price every second

#Display the graphs
plt.show()
import pybind11
print(pybind11.get_include())
