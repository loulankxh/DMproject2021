import pandas as pd
import pydeck as pdk

DATA_URL = "low.json"
df = pd.read_json(DATA_URL)

layer = pdk.Layer(
    "ScreenGridLayer",
    df,
    # get_path='coordinates',
    # get_timestamps='timestamp',
    # get_color=[253, 128, 93],
    # opacity=0.8,
    # width_min_pixels=5,
    # rounded=True,
    # trail_length=600,
    # current_time=500,
    # pickable=True
    pickable=False,
    opacity=0.8,
    cell_size_pixels=10,
    color_range=[
        [0, 25, 0, 25],
        [0, 85, 0, 85],
        [0, 127, 0, 127],
        [0, 170, 0, 170],
        [0, 190, 0, 190],
        [0, 255, 0, 255],
    ],
    get_position="coordinates"
)

view_state = pdk.ViewState(
    longitude=114.023465,
    latitude=22.632468,
    zoom=11,
    pitch=0,
    bearing=0
)

r = pdk.Deck(layers=[layer], initial_view_state=view_state)
r.to_html('low.html')
