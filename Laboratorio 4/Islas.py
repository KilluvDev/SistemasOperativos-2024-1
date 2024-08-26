import threading
import random as rand
from datetime import datetime
import time

def files(filename):
    for name in filename:
        try:
            with open(f"{name}.txt", "w") as f:
                print(f"Archivo {name}.txt creado.")
        except Exception as e:
            print(f"Error al crear el archivo {name}.txt: {e}")

names = ['Isla_del_Trueno', 'Isla_de_las_Sombras', 'Isla_de_los_Susurros',
         'BarOraculo', 'Salida', 'Isla_de_las_Estrellas',
         'Isla_del_Dragón_Rojo', 'Isla_del_Bosque_Encantado', 'Isla_del_Tesoro_Oculto']

name2 = ['Isla_del_Trueno', 'Isla_de_las_Sombras', 'Isla_de_los_Susurros', 'Isla_de_las_Estrellas',
         'Isla_del_Dragón_Rojo', 'Isla_del_Bosque_Encantado', 'Isla_del_Tesoro_Oculto']

islands = {
    "Isla_de_las_Sombras": (20, 9, 10),
    "Isla_del_Dragón_Rojo": (8, 5, 2),
    "Isla_de_las_Estrellas": (15, 7, 5),
    "Isla_del_Bosque_Encantado": (6, 4, 3),
    "Isla_de_los_Susurros": (6, 1, 5),
    "Isla_del_Trueno": (9, 4, 4),
    "Isla_del_Tesoro_Oculto": (7, 5, 2)
}

class Islands:

    def __init__(self, data, name):
        self.name = name
        self.max_bridge = threading.Semaphore(data[0])
        self.max_island = threading.Semaphore(data[2])
        self.condition = threading.Condition()
        self.lock = threading.Lock()
        self.actual_bridge = 0
        self.full_island = 0
        self.Top_island = data[2]
        self.in_island = 0
        self.search = data[1]

    def Start_bridge(self, pirate):
        time.sleep(0.5)
        self.max_bridge.acquire()
        self.lock.acquire()
        timenow = datetime.now().strftime("%H:%M:%S.%f")
        pirate[0] = f"{pirate[2][0]},{timenow},"
        self.actual_bridge += 1
        self.lock.release()
        with self.condition:
            if self.actual_bridge >= self.Top_island and self.full_island == 0:
                self.condition.notify()
        with self.condition:
            self.condition.wait()
        self.island(pirate)

    def island(self, pirate):
        self.max_island.acquire()
        self.lock.acquire()
        self.actual_bridge -= 1
        self.max_bridge.release()
        self.in_island += 1
        if self.in_island == self.Top_island:
            self.full_island = 1
        timenow = datetime.now().strftime("%H:%M:%S.%f")
        with open(f"{self.name}.txt", "a") as file:
            file.write(f"{pirate[0]} {timenow}, {pirate[-1]+1}\n")
        self.lock.release()
        time.sleep(self.search)

        self.lock.acquire()
        pirate[-1] += 1
        self.in_island -= 1
        self.lock.release()
        with self.condition:
            if self.in_island == 0:
                self.full_island = 0
                self.condition.notify_all()
        self.max_island.release()

    def last_call(self):
        with self.condition:
            self.condition.notify_all()

class Oracle():
    ThreadsPirates = []

    def __init__(self):
        self.Shadows = Islands(data=islands['Isla_de_las_Sombras'], name=name2[1])
        self.RedDragon = Islands(data=islands['Isla_del_Dragón_Rojo'], name=name2[4])
        self.Stars = Islands(data=islands['Isla_de_las_Estrellas'], name=name2[3])
        self.Enchanted = Islands(data=islands['Isla_del_Bosque_Encantado'], name=name2[5])
        self.Whisper = Islands(data=islands['Isla_de_los_Susurros'], name=name2[2])
        self.Tunder = Islands(data=islands['Isla_del_Trueno'], name=name2[0])
        self.Hidden = Islands(data=islands['Isla_del_Tesoro_Oculto'], name=name2[6])
        self.pirates = []
        self.condition = threading.Condition()
        self.max_Oracle = 500
        self.act_Oracle = 0
        self.lock = threading.Lock()
        for i in range(1, self.max_Oracle + 1):
            a = rand.randint(1, 7)
            b = rand.randint(1, 7)
            while (a == b):
                b = rand.randint(1, 7)
            timenow = datetime.now().strftime("%H:%M:%S.%f")[:-3]
            sample = ["", f"Pirate{i}, {timenow},", ("Pirate{}".format(i), a, b), 0]
            thread = threading.Thread(target=self.Oracle_bridge, args=(sample,))
            self.ThreadsPirates.append(thread)

    def ready(self):
        for threadpirate in self.ThreadsPirates:
            threadpirate.start()
        for threadpirate in self.ThreadsPirates:
            threadpirate.join()

    def Oracle_bridge(self, pirate):
        self.pirates.append(pirate)
        timenow = datetime.now().strftime("%H:%M:%S.%f")
        self.lock.acquire()
        pirate[1] = f"{pirate[1]} {name2[int(pirate[2][1] - 1)]}, {timenow},"
        self.lock.release()
        island_method = {
            1: self.Shadows,
            2: self.RedDragon,
            3: self.Stars,
            4: self.Enchanted,
            5: self.Whisper,
            6: self.Tunder,
            7: self.Hidden
        }
        island_method[pirate[2][1]].Start_bridge(pirate)
        self.lock.acquire()
        self.act_Oracle -= 1
        self.lock.release()
        self.OracleQueue(pirate)

    def OracleQueue(self, pirate):
        timenow = datetime.now().strftime("%H:%M:%S.%f")
        self.lock.acquire()
        pirate[1] = f"{pirate[1]} {name2[int(pirate[2][2] - 1)]}, {timenow}"
        with open("BarOraculo.txt", "a") as file:
            file.write(f"{pirate[1]}\n")
        self.lock.release()
        island_method = {
            1: self.Shadows,
            2: self.RedDragon,
            3: self.Stars,
            4: self.Enchanted,
            5: self.Whisper,
            6: self.Tunder,
            7: self.Hidden
        }
        island_method[pirate[2][2]].Start_bridge(pirate)
        self.lock.acquire()
        self.act_Oracle -= 1
        self.lock.release()
        timenow = datetime.now().strftime("%H:%M:%S.%f")
        self.lock.acquire()
        with open("Salida.txt", "a") as file:
            file.write(f"{pirate[2][0]}, {timenow}\n")
        self.pirates.pop()
        self.lock.release()
        if len(self.pirates) < 10:
            self.Whisper.last_call()
            self.Stars.last_call()
            self.Shadows.last_call()
            self.RedDragon.last_call()
            self.Hidden.last_call()
            self.Enchanted.last_call()
            self.Tunder.last_call()

files(names)
Oraculo = Oracle()
Oraculo.ready()
