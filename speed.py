import pandas as pd
import json
import pydeck as pdk

data = pd.read_csv('sample_taxi.csv', nrows=3000000)

data['coordinates'] = data.apply(lambda r: [r['lon'], r['lat']], axis=1)
data['timestamp'] = data['time'].str.slice(0, 2).astype('int') * 3600 + data['time'].str.slice(3, 5).astype(
    'int') * 60 + data['time'].str.slice(6, 8).astype('int')
data = data.sort_values(by=['taxi_id', 'timestamp'])
data['coordinates'] = data['coordinates']
data['timestamp'] = data['timestamp'].apply(lambda r: [r])

data.drop(columns=['lon', 'lat'], inplace=True)
low = data[(data['speed'] <= 15) & (data['speed'] >= 0)]        # divide the data to two part

# df = low.groupby(['taxi_id', 'is_passenger'])[['coordinates', 'timestamp']].sum()
#
# df = df.reset_index()
# high = data[data['speed'] >= 80]      # divide the data to two part

# low.to_csv('low.csv', index=False)
# high.to_csv('high.csv', index=False)

result = low.to_json(orient="records")
parsed = json.loads(result)
strx = json.dumps(parsed, indent=4)
fo = open("low.json", "w")      # generate .json file
fo.write(strx)

