import pandas as pd 
import numpy as np 
import sys 

airport_dataset_titles = ['Airport ID', 'Name', 'City', 'Country', 'IATA', 'ICAO', 'Latitude', 'Longitude', 'Altitude', 'Timezone', 'DST', 'Tz database time zone', 'Type', 'Source']
airport_read_file = pd.read_csv (r'dataset/airports.dat.txt', names = airport_dataset_titles)
dataframe = pd.DataFrame(airport_read_file)

country = 'United States'
df_filtered_by_country = dataframe[dataframe['Country'] == country]

df_filtered_by_country.to_csv (r'dataset/us_airports.csv', index=None)

route_dataset_titles = ['Airline', 'Airline ID', 'Source Airport', 'Source Airport ID', 'Destination Airport', 'Destination Airport ID', 'Codeshare', 'Stops', 'Equipment']
route_read_file = pd.read_csv (r'dataset/routes.dat.txt', names = route_dataset_titles)
# dataframe2 = pd.DataFrame(route_read_file)

us_airports_list = dataframe['Airport ID'].tolist()
us_airports_str = [str(i) for i in us_airports_list]

filter1 = route_read_file['Source Airport ID'].isin(us_airports_str)
df_routes_filtered_by_country = route_read_file[filter1]


df_routes_filtered_by_country.to_csv (r'dataset/us_airports_routes.csv', index=None)
