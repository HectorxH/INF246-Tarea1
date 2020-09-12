import pandas as pd
import random

generos = ["Visual Novel", "Open World", "RPG", "Strategy", "Simulation", "Action", "Party Game", "Adventure"]

lorem = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Ut gravida, quam nec accumsan finibus, ipsum lacus faucibus felis, eu viverra nulla odio bibendum arcu. Curabitur volutpat a nulla eget fringilla. Vestibulum sit amet volutpat ex, ut lacinia nisl. Praesent semper ornare lacus et porttitor. Curabitur in velit vehicula, feugiat nisl vel, posuere justo. Pellentesque eget erat tempus, pretium velit vel, finibus mauris. Donec auctor id est ut viverra."

df = pd.read_csv('./Generador/games.csv')

for indes, row in df.iterrows():
    with open(f'./Juegos/{row["Title"]}', 'w') as file:
        file.write(row['Title']+'\n')
        g = ', '.join(random.sample(generos, random.randint(1, 5)))
        file.write(g+'\n')
        file.write(row['Developer']+'\n')
        file.write(lorem+'\n')