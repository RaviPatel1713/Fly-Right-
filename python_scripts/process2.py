import pandas as pd 
import numpy as np 



airport_dataset_titles = ['Airport ID', 'Name', 'City', 'Country', 'IATA', 'ICAO', 'Latitude', 'Longitude', 'Altitude', 'Timezone', 'DST', 'Tz database time zone', 'Type', 'Source']
airport_read_file = pd.read_csv (r'dataset/us_airports.csv', names = airport_dataset_titles)
dataframe = pd.DataFrame(airport_read_file)

# map each airport ID key with its corresponding index value and store in python dictionary
airport_code_index_map = dataframe['Airport ID'].tolist()
airport_code_index_map = dict(zip(airport_code_index_map, np.arange(len(airport_code_index_map))))
print(airport_code_index_map)

## for airport locating data points --> airport ids, latitude, longitude
subset1 = dataframe[['Airport ID', 'IATA', 'Latitude', 'Longitude']]

# create a python dict that maps from airport 3-Letter IATA code to airport ID
non_null_airport_code_index_list = subset1[subset1['IATA'] != '\\N'].index.tolist()
airport_code_keys = subset1.iloc[non_null_airport_code_index_list, 1].tolist()
airport_id_values = subset1.iloc[non_null_airport_code_index_list, 0].tolist()
airport_code_to_id_map = dict(zip(airport_code_keys, airport_id_values))
# print(airport_code_to_id_map)

subset1 = subset1[['Latitude', 'Longitude']]
subset1.to_csv (r'dataset/us_airports_refined.csv', index=None)

## for airport discriptive data --> Name, City, Country (for user-interface purposes)
subset2 = dataframe[['Name', 'City', 'Country']]
subset2.to_csv (r'dataset/us_airports_descriptive.csv', index=None)

route_dataset_titles = ['Airline', 'Airline ID', 'Source Airport', 'Source Airport ID', 'Destination Airport', 'Destination Airport ID', 'Codeshare', 'Stops', 'Equipment']
route_read_file = pd.read_csv (r'dataset/us_airports_routes.csv', names = route_dataset_titles)
dataframe = pd.DataFrame(route_read_file)

## for directed route connection --> source airport id, destination airport id
subset3 = dataframe[['Source Airport', 'Source Airport ID', 'Destination Airport', 'Destination Airport ID']]

null_src_airport_id_index_list = subset3[subset3['Source Airport ID'] == '\N'].index.tolist()
# print('\n')
# print('null src airport id index list = ', null_src_airport_id_index_list)
for idx in null_src_airport_id_index_list:
    if subset3.iloc[idx, 0] in airport_code_to_id_map:
        subset3.set_value(idx,'Source Airport ID', airport_code_to_id_map.get(subset3.iloc[idx, 0]))

null_dest_airport_id_index_list = subset3[subset3['Destination Airport ID'] == '\N'].index.tolist()
# print('null dest airport id index list = ', null_dest_airport_id_index_list)
for idx in null_dest_airport_id_index_list:
    if subset3.iloc[idx, 2] in airport_code_to_id_map:
        subset3.set_value(idx,'Destination Airport ID', airport_code_to_id_map.get(subset3.iloc[idx, 2]))


# we delete all '\N' rows since there is no aiport  mapping ID founds for those IATA airport codes  
# subset3 = subset3.drop(subset3[subset3['Source Airport ID'] == '\N'].index.tolist())
# subset3 = subset3.drop(subset3[subset3['Destination Airport ID'] == '\N'].index.tolist())

subset3 = subset3[['Source Airport ID', 'Destination Airport ID']]

# print('\n---------------------------------------------------------------')
# print('null after changes = ', subset3[subset3['Source Airport ID'] == '\\N'].index.tolist())
# print('null after changes = ', subset3[subset3['Destination Airport ID'] == '\N'].index.tolist())
# print('---------------------------------------------------------------')

subset3 = subset3.replace('\\N', '-1')
for idx in range(subset3.shape[0]):
    if int(subset3.iloc[idx, 0]) in airport_code_index_map:
        subset3.set_value(idx,'Source Airport ID', str(airport_code_index_map.get(int(subset3.iloc[idx, 0]))))
    else:
        subset3.set_value(idx,'Source Airport ID', '-1')
    if int(subset3.iloc[idx, 1]) in airport_code_index_map:
            subset3.set_value(idx,'Destination Airport ID', str(airport_code_index_map.get(int(subset3.iloc[idx, 1]))))
    else:
        subset3.set_value(idx,'Destination Airport ID', '-1')


nan_value = float("NaN")
subset3 = subset3.replace('-1', np.nan).dropna()
subset3 = subset3.drop_duplicates(subset=None)
subset3.to_csv (r'dataset/us_airports_routes_refined.csv', index=None)

# subset4 = pd.read_csv('dataset/routes_refined.csv')
# subset4 = subset4[subset4['Destination Airport ID'] < 100]
# subset4 = subset4[subset4['Source Airport ID'] < 100]
# subset4.to_csv (r'dataset/sample_routes.csv', index=None)



