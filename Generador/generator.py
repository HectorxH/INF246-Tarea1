import pandas as pd
import random
import os

generos = ["Visual Novel", "Open World", "RPG", "Strategy",
           "Simulation"]

lorem = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Ut gravida, quam nec accumsan finibus, ipsum lacus faucibus felis, eu viverra nulla odio bibendum arcu. Curabitur volutpat a nulla eget fringilla. Vestibulum sit amet volutpat ex, ut lacinia nisl. Praesent semper ornare lacus et porttitor. Curabitur in velit vehicula, feugiat nisl vel, posuere justo. Pellentesque eget erat tempus, pretium velit vel, finibus mauris. Donec auctor id est ut viverra."

df = pd.read_csv('games.csv')
curpath = os.getcwd()
if not os.path.exists(curpath + "/Juegos"):
    os.makedirs(curpath + "/Juegos")
for indes, row in df.iterrows():
    with open(f'./Juegos/{row["Title"]}' + ".txt", 'w') as file:
        file.write(row['Title'] + '\n')
        g = ', '.join(random.sample(generos, random.randint(1, 5)))
        file.write(g + '\n')
        file.write(row['Developer'] + '\n')
        file.write(lorem + '\n')
