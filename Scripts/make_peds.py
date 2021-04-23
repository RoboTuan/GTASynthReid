import pandas as pd

statistics = pd.read_csv("/Users/lpdef/Desktop/Polito/Internship/Pedestrian_reID/Peds/statistcs.csv")

non_represented_peds = statistics.loc[statistics["#cams"]<2, ["Ped"]]

non_represented_peds.to_csv("./Peds/non_represented_peds.csv", index=None, header=False)